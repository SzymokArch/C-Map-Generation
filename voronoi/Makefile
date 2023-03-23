output: main.o voronoi.o
	gcc main.o voronoi.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -o output
	rm *.o
	./output

main.o: main.c
	gcc -c main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall

voronoi.o: voronoi.c voronoi.h
	gcc -c voronoi.c -lm -Wall

clean:
	rm output
