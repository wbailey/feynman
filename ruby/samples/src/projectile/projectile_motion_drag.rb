require 'projectile_motion'

# Simply define our namespace
module ProjectileMotion
  class System < Feynman::Cartesian::PhysicalSystem
    def initialize
      super
      b = Ball.new( 10.0, 0.0, 0.0, 10.0, 0.2 )
      b.x=14.3
      self << b
      self << Ball.new( 10.0, 10.0, 0.0, 10.0, 0.2 )
    end
  end
end
