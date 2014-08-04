set xrange [0:12]
set yrange [0:12]
unset tics
num_lines="`wc -l data.csv`"

#set terminal png

#set output 'png/animate000.png'

plot 'data.csv' every 1::0::0 using 5:6 w cir title '' \
   , 'data.csv' every 1::0::0 using 7:8 w cir title ''

do for [i=1:num_lines] {
#  set output sprintf('png/animate%03.0f.png',i)
  plot 'data.csv' every 1::i-1::i using 7:8 w cir lc 000000 title '' \
     , 'data.csv' every 1::i-1::i using 11:12 w cir lc 000000 title ''
  pause 0.00500
}

#set terminal x11
#set output
