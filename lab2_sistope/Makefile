CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
out = lab2
source = lab1.c funciones.c
objects = $(source:.c=.o)

$(build): $(out)
$(out): $(objects)
	$(CC) -o $@ $^ $(CFLAGS) 

$(objects): 
	$(CC) -c $*.c
clean:
	$(RM) $(out) $(objects) 
.PHONY: clean
run: clean
	gcc -o simular funciones.c simular.c -lm
	gcc -o lab2 lab2.c
	./lab2 -N 10 -p 5 -i entrada.in -o salida.out -c 7




