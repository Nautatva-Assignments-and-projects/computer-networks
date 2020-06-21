set term postscript eps color 
set output 'queue_occupancy.eps'
set ylabel 'queue'
set xlabel 'time'
plot 'final_queue_occupancy.txt' using 1:2
