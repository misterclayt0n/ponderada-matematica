set terminal png size 800,600
set output 'clusters.png'
set title "Clusters de Clientes"
set xlabel "Gasto Total"
set ylabel "Quantidade de Visitas"
set grid

plot 'clusters.dat' using 1:2:(($3 == 0) ? 1 : ($3 == 1) ? 2 : 3) with points pt 7 ps 1.5 lc variable notitle

