CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
out = lab2 
source = funciones.c lab2.c
objects = $(source:.c=.o)

$(build):
	$(out) 

$(out): $(objects) $(preobject)
	gcc -o bomb funciones.c bomb.c $(CFLAGS)
	$(CC) -o $@ $(objects) $(CFLAGS) 

$(objects): 
	$(CC) -c $*.c

clean: 
	$(RM) $(out) $(objects) bomb
.PHONY: 



