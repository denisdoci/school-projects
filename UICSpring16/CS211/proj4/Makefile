proj4-1.o: proj4-1.c proj4.h
	gcc -c proj4-1.c
 
proj4-2.o: proj4-2.c  proj4.h
	gcc -c proj4-2.c 

proj4-3.o: proj4-3.c  proj4.h
	gcc -c proj4-3.c

proj4.exe: proj4-1.o proj4-2.o proj4-3.o 
	gcc proj4-1.o proj4-2.o proj4-3.o -o proj4.exe 

clean: proj4-1.o proj4-2.o proj4-3.o proj4.exe
	rm proj4-1.o proj4-2.o proj4-3.o proj4.exe
