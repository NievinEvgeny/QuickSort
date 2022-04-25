set terminal png
set output "graph.png"

set xrange [2:8]

set yrange [0:12]

set grid

set ytics 1

set xtics 2

set ylabel "Speedup"

set xlabel "Number of threads"

plot "./TestTable.txt" u 1:2 with linespoints lw 3 pt 7 ps 1 title "N = 10^7, threshold = 10^3", "./TestTable.txt" u 1:3 with linespoints lw 3 pt 7 ps 1 title "N = 10^6, threshold = 10^3", "./TestTable.txt" u 1:4 with linespoints lw 3 pt 7 ps 1 title "N = 10^7, threshold = 10^2", "./TestTable.txt" u 1:5 with linespoints lw 3 pt 7 ps 1 title "N = 10^6, threshold = 10^2", "./TestTable.txt" u 1:6 with linespoints lw 3 pt 7 ps 1 title "N = 10^7, threshold = 2.5*10^5", "./TestTable.txt" u 1:7 with linespoints lw 3 pt 7 ps 1 title "Linear speedup"