require 'feynman'
require 'particle'

# Simply define our namespace
module MolecularDynamics
  class Engine < Feynman::Cartesian::VerletEngine
    def initialize
      @dt = 0.01
    end
    
    def accel( ps )
      # Reset the calculated potential energy of the system.
      ps.pe = 0.0
      
      # Reset the acceleration of each particle.
      ps.each { |po| po.zero_vector( :accel ) }
      
      # Since we are using push and pop we probably don't want to really kill our physical system
      use = ps.clone
      
      while ( po1 = use.pop ) do
        use.each do |po2|
          dx = po1.x - po2.x
          dxp = ps.x_length - dx.abs
          dx = ( dxp < dx ) ? dxp : dx
          
          dy = po1.y - po2.y
          dyp = ps.y_length - dy.abs
          dy = ( dyp < dy ) ? dyp : dy
          
          dz = po1.z - po2.z
          dzp = ps.z_length - dz.abs
          dz = ( dzp < dz ) ? dzp : dz
          
          r = Math.sqrt( dx * dx + dy * dy + dz * dz )
          ri = 1.0/r
          ri6 = ri ** 6
          
          # This is the force in the r-> direction.
          force = 24.0 * ri * ri6 * ( 2.0 * ri6 - 1.0 )
          
          ps.pe += 4.0 * ri6 * ( ri6 - 1.0 )
          
          printf( "EE %5.6f, %5.6f, %5.6f\n", r, force, ps.pe )
          
# This appears to be incorrect and leading to energy conservation problems because
# the force vector is not correct.
          self.ax( po1, force, dx, r )
          self.ax( po2, -force, dx, r )
          
          self.ay( po1, force, dy, r )
          self.ay( po2, -force, dy, r )
          
          self.az( po1, force, dz, r )
          self.az( po2, -force, dz, r )
        end
      end
    end

    def ax( po, force, dx, r )
      po.ax += force * ( dx / r )
    end
    
    def ay( po, force, dy, r )
      po.ay += force * ( dy / r )
    end
    
    def az( po, force, dz, r )
      po.az += force * ( dz / r )
    end
  end
  
  class Experiment < Feynman::PhysicalExperiment
    def initialize
      @measurement_interval = 0.01
    end
    
    def measure( ps, iterations )
      # Allow time for the system to equilibrate.
      # return if iterations < 200
      
      ke = te = 0.0
      
      printf( "%5.6f, ", ps.time )
      
      ps.each do |po|
        # Kinetic Energy calculations
        ke += 0.5 * po.mass * po.v2
        
        printf( "%5.6f, %5.6f, %5.6f, ", po.x, po.vx, po.ax )
      end
      
      te = ke + ps.pe
      
      printf( "%5.6f, %5.6f, %5.6f, %5.6f\n", ke, ps.pe, te, te/4.0 )
    end
    
    def run( ps, iterations )
      return iterations < 1000
    end

    def report( ps )
      puts '--Final Report--'
      printf( "%15s %15s %15s\n", 'Object ID', 'Amplitude', 'Period' )
      
      ps.each do |po|
        printf( "%15d %10.4f %10.4f\n", po.object_id, po.amplitude, po.period )
      end
    end
  end
  
  class System < Feynman::Cartesian::PhysicalSystem
    attr_accessor( :x_length, :y_length, :z_length, :pe )
    
    def initialize
      super
      
      # System Dimensions
      @x_length = 4.0
      @y_length = 4.0
      @z_length = 0.0
      
      # Potential Energy
      @pe = 0.0
    end
    
    def composed_of
      return [
          { 'type' => 'Particle', 'count' => 2, },
      ]
    end
    
    def init
      # This establishes the intial temperature of the system
      vmax = 1.0
      
      self[0].x = 1.5
      self[0].y = 1.0
      self[0].z = 0.0
      
      self[0].vx = 0.5
      self[0].vy = 0.0
      self[0].vz = 0.0
      
      self[1].x = 3.0
      self[1].y = 1.0
      self[1].z = 0.0
      
      self[1].vx = 0.5
      self[1].vy = 0.0
      self[1].vz = 0.0
      
      x_spacing = self.x_length / 8.0
      y_spacing = self.y_length / 3.0
      z_spacing = 0.0
      
      i = 0
      
      vxsum = 0.0
      vysum = 0.0
      vzsum = 0.0
      
      for row in 1 .. 1
        for col in 1 .. 2
          self[i].x = x_spacing * ( col - 0.5 )
          self[i].y = y_spacing * ( row - 0.5 )
          self[i].z = 0.0
          
          vxsum += self[i].vx = vmax * ( 2.0 * rand - 1.0 )
          vysum += self[i].vy = vmax * ( 2.0 * rand - 1.0 )
          vysum += self[i].vz = 0.0
          
          self[i].mass = 1.0
          
          i += 1
        end
      end
      
      # Elimate any random net momentum that the system may have.
      self.each do |po|
        po.vx -= vxsum/2.0
        po.vy -= vysum/2.0
        po.vz -= vzsum/2.0
      end
    end
  end
end
