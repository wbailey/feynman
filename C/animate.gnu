set xrange [-1:10]
set yrange [0:11]
num_lines="`wc -l result.gnu`"

set terminal gif

set output 'animate.gif'

plot 'result.gnu' every 1::0::0 using 2:3 w cir title '', 'result.gnu' every 1::0::0 using 4:5 w cir title ""

do for [i=1:num_lines] {
  plot 'result.gnu' every 1::i-1::i using 2:3 w cir lc 000000 title ''\
     , 'result.gnu' every 1::i-1::i using 4:5 w cir lc 000000 title ''
  pause 0.05000
}

set output
