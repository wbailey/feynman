set xrange [-1:10]
set yrange [-1:11]
num_lines="`wc -l data2.csv`"

#set terminal png

#set output 'png/animate000.png'

plot 'data2.csv' every 1::0::0 using 2:3 w cir title '' \
   , 'data2.csv' every 1::0::0 using 4:5 w cir title ''

do for [i=1:num_lines] {
#  set output sprintf('png/animate%03.0f.png',i)
  plot 'data2.csv' every 1::i-1::i using 2:3 w cir lc 000000 title '' \
     , 'data2.csv' every 1::i-1::i using 4:5 w cir lc 000000 title ''
  pause 0.05000
}

#set terminal x11
#set output
