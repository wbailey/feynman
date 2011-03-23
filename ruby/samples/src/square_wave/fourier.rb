class Fourier
  attr_accessor :x, :partial_sum, :harmonics, :overshoot
  
  def initialize( harmonics = nil, x = 0.0 )
    @x = x
    @partial_sum = 0.0
    @harmonics = ( harmonics || 5 ) * 2 - 1
    @overshoot = {
      :pos => 0.0,
      :value => 0.0,
    }
  end

  def value
    i, @partial_sum = 1, 0.0
      
    while i <= @harmonics do
      @partial_sum += Math.sin( i * @x )/i
      i += 2  
    end     
      
    if @partial_sum >= @overshoot[:value]
      @overshoot[:pos] = @x
      @overshoot[:value] = @partial_sum
    end

    @partial_sum
  end
end
