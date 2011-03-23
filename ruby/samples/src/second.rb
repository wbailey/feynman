#!/usr/local/bin/ruby -w

require 'bigdecimal'

class CartesianObject < BigDecimal
    attr_reader :x, :y, :z, :vx, :vy, :vz, :ax, :ay, :az

    def self.define_setter( var )
      define_method var.to_sym do |val|
        instance_variable_set( ( '@' + var.to_s.sub( '=', '' ) ).to_sym, BigDecimal.new( val.to_s ) )
      end
    end

    %w{ x y z vx vy vz ax ay az }.each { |var| define_setter( var ) }
end

class Ball < CartesianObject
    attr_reader :mass, :vy_old, :max_height, :ke, :pe

    def method_missing
    end
end

class SimpleGravity
    def self.calculate( ball )
        ball.vy_old = ball.vy
        
        ball.ay = -9.8
        ball.y = ball.y + ball.vy * 0.01
        ball.vy = ball.vy + ball.ay * 0.01

        ball.ke = 0.5 * ball.mass * ball.vy * ball.vy
        ball.pe = ball.mass * 9.8 * ball.y
        
        ball.max_height = ball.y if ( ball.vy_old * ball.vy < 0 )
    end
end

ball = Ball.new
ball.y = 0.0
ball.vy = 10.0
ball.mass = 10.0

while ( ball.y >= 0.0 )
    SimpleGravity.calculate( ball )
    printf( "%5.4f %5.4f %5.4f %5.4f %5.4f\n", ball.y, ball.vy, ball.ke, ball.pe, ball.ke + ball.pe )
end


