all: tbl.o tcalc tsort rowcmp

tbl.o: tbl.c 
	gcc -c tbl.c
tcalc: tbl.c tcalc.c
	gcc tcalc.c tbl.c -o tcalc
tsort: tbl.c tsort.c
	gcc tsort.c tbl.c -o tsort
rowcmp: tbl.c rowcmp.c
	gcc rowcmp.c tbl.c -o rowcmp
clean: tbl.o tcalc tsort rowcmp
	rm tbl.o tcalc tsort rowcmp
