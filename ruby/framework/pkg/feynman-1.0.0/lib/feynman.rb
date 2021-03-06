require 'bigdecimal'

# Monkey patching
class BigDecimal
  # http://en.wikipedia.org/wiki/Sign_function.
  #
  # This function is essential when you want to use the change in sign as an
  # event trigger in your simulation.
  def sign
    return 1 if self > 0
    return -1 if self < 0
    return 0
  end
end

class Array
  # Simply sum up all the items in our array assuming the values are of type
  # Float or Fixnum.
  def sum
    inject( nil ) { |sum, x| sum ? sum + x : x }
  end
  
  def avg
    return 0 if size.eql?( 0 )
    sum.to_f / size
  end
end

module AttrBigDecimal
  def attr_bigdecimal( *args )
    args.each do |name|
      raise ArgumentError unless name.is_a?( Symbol )

      class_eval <<-EOF
        def #{name}=( val )
          @#{name} = BigDecimal.new( val.to_s )
        end

        attr_reader :#{name}
      EOF
    end 
  end 

  class << self
    def included( other )
      other.extend( self )
    end 
  end 
end

class Object
  include AttrBigDecimal
end

# This module provides the base classes for the ruby version of the Feynman
# Simulation Framework.
module Feynman
  def self.controller( ps, ae, exp )
    iterations = 0
    
    # Determine when to take measurements if at all.
    if exp.measurement_interval.nil?
      # We do not want to take any measurements while the experiment is running.
      # One might want to do this when using the framework to calculate functions
      # See square_wave/overshoot.rb in the samples
      iterations_per_measurement = nil
    elsif !ae.step_size.nil? && ( exp.measurement_interval > 0 && ae.step_size > 0 )
      iterations_per_measurement = ( exp.measurement_interval / ae.step_size ).to_int
    else
      # Looks like they messed up their definitions so lets help them out.
      iterations_per_measurement = 1
    end
    
    exp.measure( ps ) unless iterations_per_measurement.nil?
    
    # Pretty simple way of running a simulation.
    while ( exp.run( ps, iterations ) )
      ae.integrate( ps )
      
      iterations += 1
      
      exp.measure( ps ) if !iterations_per_measurement.nil? && ( iterations % iterations_per_measurement ).eql?( 0 )
    end
    
    # Do a final measurement if our simulation did not run long enough to capture
    # the last defined measurement.
    exp.measure( ps ) unless !iterations_per_measurement.nil? && ( iterations % iterations_per_measurement ).eql?( 0 )
    
    # Only do this if the report method is defined in our experiment class.
    exp.report( ps ) if exp.respond_to?( 'report' )
  end
  
  # This class is the base class that all physical *objects* will be descendants
  # of.
  class PhysicalObject
    attr_accessor :mass
    
    def initialize( mass = 0.0 )
      @mass = mass
    end
  end
  
  # Every algorithm typically has this attribute so we just make it available by
  # default for those that choose to subclass off of it.
  class AlgorithmEngine
    attr_accessor :step_size

    def initialize( step_size )
      @step_size = step_size
    end
  end

  class RecordWriter
    attr_accessor :values, :format_masks

    def initialize( format_masks = nil )
      @format_masks = format_masks || { :Float => '%18.8f', :Fixnum => '%10d', :String => '%30s' }
      @values = Array.new
    end

    def add( *values )
        @values += values.map{ |v| sprintf( "#{@format_masks[v.class.to_s.to_sym]}", v ) }
      self
    end

    def puts
      $stdout.puts @values.join( ", " ) unless @values.empty?
      self
    end

    def erase
      @values = Array.new
      self
    end
  end
  
  class PhysicalExperiment
    attr_accessor :measurement_interval, :total_iterations

    def initialize( measurement_interval = nil, total_iterations = nil, specification = nil, &block )
      @measurement_interval = measurement_interval
      @total_iterations = total_iterations
      @record_writer = RecordWriter.new( specification )
      @block = block
    end

    def measure( ps )
      ps.energy[:kinetic] = ps.energy[:potential] = ps.energy[:total] = 0.0 if ps.respond_to?( 'energy' )

      @record_writer.add( ps.time ) if ps.respond_to?( 'time' )

      @block.call( ps, @record_writer ) if @block
      
      if ps.respond_to?( 'energy' )
        ps.energy[:total] = ps.energy[:kinetic] + ps.energy[:potential]
        @record_writer.add( ps.energy[:kinetic], ps.energy[:potential], ps.energy[:total] )
      end

      @record_writer.puts.erase unless @record_writer.nil?
    end

    def run( ps, iterations )
      iterations < @total_iterations
    end

    def report( ps )
      raise( RuntimeException, 'Override report method in your class definition' )
    end
  end
  
  class PhysicalSystem < Array
    attr_accessor :time, :energy

    def initialize
      @time = 0.0
      @energy = {
        :kinetic => 0.0,
        :potential => 0.0,
        :total => 0.0,
      }
    end
    
    def delete( po )
      yield unless super( po.object_id )
    end
  end
  
  require 'coordinate_system/cartesian'
end
