#!/usr/local/bin/ruby -w
require 'rubygems'
require 'bigdecimal'

class CartesianObject < BigDecimal
  attr_accessor :x, :y, :z, :vx, :vy, :vz, :ax, :ay, :az
end

class Ball < CartesianObject
  attr_accessor :mass, :vy_old, :max_height
end

class SimpleGravity
    def self.calculate( ball )
        ball.vy_old = ball.vy
        
        ball.ay = -9.8
        ball.y = ball.y + ball.vy * 0.01
        ball.vy = ball.vy + ball.ay * 0.01
        
        ball.max_height = ball.y if ( ball.vy_old * ball.vy < 0 )
    end
end

ball = Ball.new
ball.y = 0.0
ball.vy = 10.0
ball.mass = 10.0

while ( ball.y >= 0.0 )
    SimpleGravity.calculate( ball )
    printf( "%5.2f\n", ball.y )
end
