output: main.o noise_utils.o gradient_noise.o
	cc main.o noise_utils.o gradient_noise.o -o output -lxxhash -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall
	rm *.o
	./output

main.o: main.c
	cc -c main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra

gradient_noise.o: gradient_noise.c gradient_noise.h
	cc -c gradient_noise.c -lm -Wall -Wextra

noise_utils.o: noise_utils.c noise_utils.h
	cc -c noise_utils.c -lm -Wall -Wextra