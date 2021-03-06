require 'rubygems'
require 'feynman'
require 'ball'

# Simply define our namespace
module ProjectileMotion
  
  CONST_g = 9.8

  class Engine < Feynman::Cartesian::VerletEngine
    def initialize
      @step_size = 0.01
    end
    
    def ax( po )
      po.ax = 0.0 - po.k * po.v * po.vx
    end
    
    def ay( po )
      po.ay = -CONST_g - po.k * po.v * po.vy
    end
    
    def az( po )
      po.az = 0.0 - po.k * po.v * po.vz
    end
  end
  
  class Experiment < Feynman::PhysicalExperiment
    def initialize
      super( 0.01 ) do |ps, rw|
        ps.each do |po|
          po.max_height = po.y if ( po.vy * po.vy_old < 0 )
          
          po.vy_old = po.vy
          
          po.flight_time = ps.time if po.y < 0.0 && po.flight_time.nil?
          
          # Energy calculations
          ps.energy[:kinetic] += 0.5 * po.mass * po.v2
          ps.energy[:potential] += po.mass * CONST_g * po.y
          
          rw.add( po.x, po.y )
        end
      end
    end
    
    def run( ps, iterations )
      ps.any? { |po| po.y >= 0.0 }
    end
    
    # I use the pound symbol (#) because it indicates a comment line for gnuplot.
    def report( ps )
      printf( "# --Final Report--\n# %17s %17s %17s %17s %17s\n", 'Ball ID', 'Max Height', 'Distance Traveled', 'Impact Velocity', 'Flight Time' )
      
      ps.each { |po| printf( "# %17d %17.4f %17.4f %17.4f %17.4f\n", po.object_id, po.max_height, po.x, po.vy, po.flight_time ) }
    end
  end
  
  class System < Feynman::Cartesian::PhysicalSystem
    def initialize
      super
      
      b = Ball::with_gravity( 10.0 )
      b.x = 14.3

      self << b
      self << Ball::with_gravity( 10.0, 10.0 )
    end
  end

  def self.execute
    Feynman.controller( System.new, Engine.new, Experiment.new )
  end
end

# Monkey Patch ball for our purposes to have the appropriate initial acceleration
# by creating an alternate constructor.
class Ball
  def self.with_gravity( y = 0.0, velocity = 0.0, theta = 0.0, mass = 10.0, k = 0.0 )
    ball = new( y, velocity, theta, mass, k )
    
    ball.ay = -ProjectileMotion::CONST_g
    
    ball
  end
end
