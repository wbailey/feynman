set title "Energy Plot"
set key below box
set xrange [0:2.1]
set yrange [0:55]
set xlabel 'Time (Sec)'
set ylabel 'Energy (Joule)'
plot 'data.csv' using 1:3 title "Kinetic" with lines,\
     'data.csv' using 1:4 title "Potential" with lines;

