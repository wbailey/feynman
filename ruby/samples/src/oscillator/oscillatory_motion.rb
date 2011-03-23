require 'rubygems'
require 'feynman'
require 'spring'

# Simply define our namespace
module OscillatoryMotion
  
  class Engine < Feynman::Cartesian::VerletEngine
    def initialize
      @step_size = 0.01
    end
    
    def ax( po )
      po.ax = -po.w2 * po.x
    end
  end
  
  class Experiment < Feynman::PhysicalExperiment
    def initialize
      super( 0.1, 2000, :Float => '%10.4f' ) do |ps, rw|
        ps.each do |po|
          if ( po.vx * po.vx_old < 0 )
            po.period = 2.0 * ps.time if po.period.nil? && po.vx * po.vx_old < 0
            
            po.amplitude = po.x.abs if po.x.abs > po.amplitude
          end
          
          po.vx_old = po.vx
          
          # Energy calculations
          ps.energy[:kinetic] += 0.5 * po.mass * po.v2
          ps.energy[:potential] += 0.5 * po.k * po.x2
          
          rw.add( po.x, po.vx )
        end
      end
    end

    # The pound symbol indicates a comment in gnuplot.
    def report( ps )
      printf( "# --Final Report--\n# %15s %15s %15s\n", 'Object ID', 'Amplitude', 'Period' )
      
      ps.each do |po|
        format_str = %w{ %15d %15.4f }

        if po.period.nil?
          format_str << '%15s'
          po.period = '--'
        else
          format_str << '%15.4f'
        end

        printf( "# #{format_str.join( ' ' )}\n", po.object_id, po.amplitude, po.period )
      end
    end
  end
  
  class System < Feynman::Cartesian::PhysicalSystem
    def initialize
      super
      self << Spring.new( 10.0, 2.0, 10.0, 3.0e10 )
    end
  end

  def self.execute
    Feynman.controller( System.new, Engine.new, Experiment.new )
  end
end
