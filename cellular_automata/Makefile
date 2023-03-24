output: main.o cellular_automata.o
	gcc main.o cellular_automata.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -o output
	rm *.o
	./output

main.o: main.c
	gcc -c main.c -lraylib -lGl -lm -lpthread -ldl -lrt -lX11 -Wall

cellular_automata.o: cellular_automata.c cellular_automata.h
	gcc -c cellular_automata.c -lm -Wall

clean:
	rm output
