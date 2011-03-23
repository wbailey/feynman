require 'rubygems'
require 'feynman'
require 'fourier'

module Overshoot
  
  class Engine < Feynman::AlgorithmEngine
    def integrate( sw )
      sw.x += @step_size
      sw.value
    end
  end
  
  class Experiment < Feynman::PhysicalExperiment
    def run( sw, iterations )
      sw.x <= Math::PI
    end
    
    def report( sw )
      printf( "%10i %10.8f %10.8f\n", sw.harmonics, sw.overshoot[:value], sw.overshoot[:pos] )
    end
  end
  
  def self.execute
    i, start_pos, step_size = 10, 2.5, 10e-5
    
    while i <= 1000
      os = Fourier.new( i, start_pos )
      
      Feynman.controller( os, Engine.new( step_size ), Experiment.new )
      
      start_pos = os.overshoot[:pos] - 10 * step_size
      
      i += 2
    end
  end
end
