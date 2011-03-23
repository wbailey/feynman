module Feynman
  module Cartesian
    class PhysicalObject < Feynman::PhysicalObject
      attr_accessor :x, :y, :z, :vx, :vy, :vz, :vz, :ax, :ay, :az
      
      def initialize( mass = 0.0, x = 0.0, y = 0.0, z = 0.0, vx = 0.0, vy = 0.0, vz = 0.0, ax = 0.0, ay = 0.0, az = 0.0 )
        super( mass )
        @x, @y, @z, @vx, @vy, @vz, @ax, @ay, @az = x, y, z, vx, vy, vz, ax, ay, az
      end
      
      def x2
        return @x * @x
      end
      
      def y2
        return @y * @y
      end
      
      def z2
        return @z * @z
      end
      
      def r2
        return @x * @x + @y * @y + @z * @z
      end
      
      def r
        return Math.sqrt( @x * @x + @y * @y + @z * @z )
      end
      
      def vx2
        return @vx * @vx
      end
      
      def vy2
        return @vy * @vy
      end
      
      def vz2
        return @vz * @vx
      end
      
      def v2
        return @vx * @vx + @vy * @vy + @vz * @vz
      end
      
      def v
        return Math.sqrt( @vx * @vx + @vy * @vy + @vz * @vz )
      end
      
      def ax2
        return @ax * @ax
      end
      
      def ay2
        return @ay * @ay
      end
      
      def az2
        return @az * @ax
      end
      
      def a2
        return @ax * @ax + @ay * @ay + @az * @ax
      end
      
      def a
        return Math.sqrt( @ax * @ax + @ay * @ay + @az * @az )
      end

      def zero_vector( vec )
        case vec.to_sym
          when 'pos'.to_sym
            @x, @y, @z = 0.0, 0.0, 0.0
          when 'vel'.to_sym
            @vx, @vy, @vz = 0.0, 0.0, 0.0
          when 'accel'.to_sym
            @ax, @ay, @az = 0.0, 0.0, 0.0
      end
    end
    
    class PhysicalSystem < Feynman::PhysicalSystem
      attr_accessor( :x_length, :y_length, :z_length )
      
      def initialize
        super
        
        @x_length, @y_length, @z_length = nil, nil, nil
      end
    end
    
    class AlgorithmEngine < Feynman::AlgorithmEngine
      def periodic_boundary_conditions( axis, po, length = nil )
        return if length.nil?

        case axis
          when :x
            po.x += length if po.x < 0.0
            po.x -= length if po.x > length
          when :y
            po.y += length if po.y < 0.0
            po.y -= length if po.y > length
          when :z
            po.z += length if po.z < 0.0
            po.z -= length if po.z > length
        end
      end
    end

    class EulerEngine < AlgorithmEngine
      def x( po, lx = nil )
        po.x += po.vx * @step_size
        
        periodic_boundary_conditions( :x, po, lx )
      end
      
      def y( po, ly = nil )
        po.y += po.vy * @step_size
        
        periodic_boundary_conditions( :y, po, ly )
      end
      
      def z( po, lz = nil )
        po.z += po.vz * @step_size
        
        periodic_boundary_conditions( :z, po, lz )
      end
      
      def vx( po )
        po.vx += po.ax * @step_size
      end
      
      def vy( po )
        po.vy += po.ay * @step_size
      end
      
      def vz( po )
        po.vz += po.az * @step_size
      end
      
      def ax( po )
        return 0.0
      end
      
      def ay( po )
        return 0.0
      end
      
      def az( po )
        return 0.0
      end
      
      # Euler algorithm implementation
      def integrate( ps )
        ps.time += @step_size
        
        ps.each do |po|
          self.x( po, ps.x_length )
          self.ax( po )
          self.vx( po )
          
          self.y( po, ps.y_length )
          self.ay( po )
          self.vy( po )
          
          self.z( po, ps.z_length )
          self.az( po )
          self.vz( po )
        end
      end
    end
    
    class EulerCromerEngine < EulerEngine
      def integrate( ps )
        ps.time += @step_size
        
        # Calculate the positions based on the end of the interval.
        ps.each_value do |po|
          self.ax( po )
          self.vx( po )
          self.x( po, ps.x_length )
          
          self.ay( po )
          self.vy( po )
          self.y( po, ps.y_length )
          
          self.az( po )
          self.vz( po )
          self.z( po, ps.z_length )
        end
      end
    end
    
    class VerletEngine < AlgorithmEngine
      def x( po, lx = nil )
        po.x += po.vx * @step_size + 0.5 * po.ax * @step_size * @step_size
        
        periodic_boundary_conditions( :x, po, lx )
      end
      
      def y( po, ly = nil )
        po.y += po.vy * @step_size + 0.5 * po.ay * @step_size * @step_size
        
        periodic_boundary_conditions( :y, po, ly )
      end
      
      def z( po, lz = nil )
        po.z += po.vz * @step_size + 0.5 * po.az * @step_size * @step_size
        
        periodic_boundary_conditions( :z, po, lz )
      end
      
      def vx( po )
        po.vx += 0.5 * po.ax * @step_size
      end
      
      def vy( po )
        po.vy += 0.5 * po.ay * @step_size
      end
      
      def vz( po )
        po.vz += 0.5 * po.az * @step_size
      end
      
      def ax( po, ps = nil )
        return 0.0
      end
      
      def ay( po, ps = nil )
        return 0.0
      end
      
      def az( po, ps = nil )
        return 0.0
      end
      
      # Velocity form of the Verlet algorithm where we average the velocity
      # over the interval.
      def integrate( ps )
        ps.time += @step_size
        
        ps.each do |po|
          self.x( po, ps.x_length )
          self.y( po, ps.y_length )
          self.z( po, ps.z_length )
          
          self.vx( po )
          self.vy( po )
          self.vz( po )
        end
          
        # Account for interaction between the particles where the forces are
        # calculated in a pairwise fashion or otherwise.
        if self.methods.index :accel
          self.accel( ps )
        else
          ps.each do |po|
            self.ax( po )
            self.ay( po )
            self.az( po )
          end
        end
        
        ps.each do |po|
          self.vx( po )
          self.vy( po )
          self.vz( po )
        end
      end
    end
  end
end
