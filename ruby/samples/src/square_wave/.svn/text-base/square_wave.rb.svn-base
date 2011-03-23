require 'rubygems'
require 'feynman'
require 'fourier'

module SquareWave
  
  class Engine < Feynman::AlgorithmEngine
    def integrate( sw )
      sw.x += @step_size
      sw.value
    end
  end
  
  class Experiment < Feynman::PhysicalExperiment
    def initialize( interval )
      super( interval ) do |sw, rw|
        rw.add( sw.x ).add( sw.value ).puts.erase
      end
    end
    
    def run( sw, iterations )
      sw.x <= Math::PI
    end
    
    def report( sw )
      printf( "# Overshoot value: %10.6f at %10.6f\n", sw.overshoot[:value], sw.overshoot[:pos] )
    end
  end
  
  def self.execute
    Feynman.controller( Fourier.new( 50 ), Engine.new( Math::PI/10000.0 ), Experiment.new( Math::PI/10000.0 ) )
  end
end
