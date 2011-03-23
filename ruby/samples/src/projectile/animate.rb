require 'rubygems'
require 'json'
require 'getoptlong'

columns = Array.new
data = Array.new
maxvals = { :x => -100, :y => -100 }
dimensions = { :width => 800, :height => 600, :padding => 10 }
scales = Hash.new

opts = GetoptLong.new(
  [ '-c', GetoptLong::OPTIONAL_ARGUMENT ],
  [ '-d', GetoptLong::OPTIONAL_ARGUMENT ]
)

opts.each do |opt, arg|
  case opt
    when '-c'
      columns = arg.split( ',' ).map { |v| v.to_i }
    when '-w'
      dimensions[:width] = arg
    when '-h'
      dimensions[:height] = arg
    when '-p'
      dimensions[:padding] = arg
  end
end

$stdin.each do |line|
  next if line[0,1].eql?( '#' )

  values = line.split( ',' ).map { |v| v.to_f }

  tuples = Array.new

  columns.each do |c|
    maxvals[:x] = ( values[c] > maxvals[:x] ) ? values[c] : maxvals[:x]
    maxvals[:y] = ( values[c + 1] > maxvals[:y] ) ? values[c + 1] : maxvals[:y]
    tuples << { :x => values[c], :y => values[c+1] }
  end

  data << tuples
end

scales[:x] = ( dimensions[:width] - 2 * dimensions[:padding] ) / maxvals[:x]
scales[:y] = ( dimensions[:height] - 2 * dimensions[:padding] ) / maxvals[:y]

data.each do |tuples|
  tuples.each do |point|
    point[:x] = dimensions[:padding] + scales[:x] * point[:x]
    point[:y] = dimensions[:height] - dimensions[:padding] - ( point[:y] * scales[:y] )
  end
end

puts <<EOF
var data = #{data.to_json};
var screen_width = #{dimensions[:width]};
var screen_height = #{dimensions[:height]};
EOF


