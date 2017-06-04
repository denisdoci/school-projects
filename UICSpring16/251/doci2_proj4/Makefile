doci2_proj4_1.o: doci2_proj4_1.c doci2_proj4.h
	gcc -c doci2_proj4_1.c
 
doci2_proj4_2.o: doci2_proj4_2.c  doci2_proj4.h
	gcc -c doci2_proj4_2.c 

doci2_proj4_3.o: doci2_proj4_3.c doci2_proj4.h
	gcc -c doci2_proj4_3.c

doci2_proj4.exe: doci2_proj4_1.o doci2_proj4_2.o doci2_proj4_3.o 
	gcc doci2_proj4_1.o doci2_proj4_2.o doci2_proj4_3.o -o doci2_proj4.exe 

clean: doci2_proj4_1.o doci2_proj4_2.o doci2_proj4_3.o doci2_proj4.exe
	rm doci2_proj4_1.o doci2_proj4_2.o doci2_proj4_3.o doci2_proj4.exe
