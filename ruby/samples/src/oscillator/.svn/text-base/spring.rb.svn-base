require 'rubygems'
require 'feynman'

class Spring < Feynman::Cartesian::PhysicalObject
  attr_accessor( :k, :w2, :amplitude, :vx_old, :period )
  
  def initialize( mass, k, x, vx )
    super( mass, x, 0.0, 0.0, vx )
    
    @k = k
    @w2 = ( @mass.eql?( 0.0 ) ) ? 0.0 : @k/@mass

    # Measurable quantities
    @amplitude = @x
    @vx_old = 0.0
    @period = nil
  end
end
