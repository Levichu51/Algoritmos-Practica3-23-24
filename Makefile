main.out: main.c monticulo.h monticulo.o
	gcc -o main.out main.c monticulo.c -lm

monticulo.o: monticulo.h monticulo.c
	gcc -c monticulo.c -lm

limpiar:
	rm main.out monticulo.o
