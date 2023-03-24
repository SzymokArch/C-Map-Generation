output: main.o value_noise.o
	gcc main.o value_noise.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -o output
	rm *.o
	./output

main.o: main.c
	gcc -c main.c -lraylib -lGl -lm -lpthread -ldl -lrt -lX11 -Wall

value_noise.o: value_noise.c value_noise.h
	gcc -c value_noise.c -lm -Wall

clean:
	rm output
