set title "Position Plot"
set key below box
set xrange [0:700]
set yrange [0:100]
set xlabel 'x (m)'
set ylabel 'y (m)'
plot 'data.csv' using 2:3 with lines, 'data_drag.csv' using 2:3 title "Drag" with lines