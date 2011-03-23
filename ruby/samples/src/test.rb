require 'bigdecimal'

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

module Feynman
  class CartesianObject
    attr_bigdecimal :x, :y, :z, :vx, :vy, :vz, :ax, :ay, :az
  end
end

o = Feynman::CartesianObject.new
o.x = 2.0

o.ay = 100.12
o.ay

o.vz = 1
o.vz

o.y = 'asdf'
