require 'rubygems'
require 'feynman'

class Ball < Feynman::Cartesian::PhysicalObject
  attr_accessor( :k, :max_height, :vy_old, :flight_time )
  
  def initialize( y = 0.0, velocity = 0.0, theta = 0.0, mass = 10.0, k = 0.0 )
    super( mass, 0.0, y )

    # Drag coefficient
    @k = k
    
    # Convert launch angle to radians.
    theta = ( 2.0 * Math::PI * theta ) / 360.0
    
    @vx = velocity * Math.cos( theta )
    @vy = velocity * Math.sin( theta )
    
    # Measurable Properties
    @max_height = y
    @vy_old = 0
    @flight_time = nil
  end
end
