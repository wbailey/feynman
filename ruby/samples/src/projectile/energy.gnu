set title "Energy Plot"
set key below box
set xrange [0:7]
set yrange [0:550]
set xlabel 'Time (Sec)'
set ylabel 'Energy (Joule)'
plot 'data.csv' using 1:11 with lines title "Kinetic", 'data_drag.csv' using 1:11 title "Kinetic - Drag" with lines, \
'data.csv' using 1:12 with lines title "Potential", 'data_drag.csv' using 1:12 title "Potential - Drag" with lines, \
'data.csv' using 1:13 with lines title "Total", 'data_drag.csv' using 1:13 title "Total - Drag" with lines
