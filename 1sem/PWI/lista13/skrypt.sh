set title "Logika dla informatykow prognoza ocen"
set style histogram clustered
set style histogram clustered gap 5
set datafile separator "\t;"
set boxwidth 1
set key inside
set style fill solid border -1
set style data histograms
set yrange [0:12]
set xrange[-1:7]
plot for[COL=2:7] "logika_prognoza.csv" using COL:xtic (1) ti col
#"" u 6 ti col,\
#"" u 5 ti col,\
#"" u 4 ti col,\
#"" u 3 ti col,\
#"" u 2 ti col
