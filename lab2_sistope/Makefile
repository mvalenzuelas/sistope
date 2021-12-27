CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
preout = simular
out = lab2 
presource=simular.c 
source = funciones.c
main = lab2.c
preobject= $(presource:.c=.o)
objects = $(source:.c=.o)
mainObjects = $(main:.c=.o)

$(build): 
	$(out) 

$(out): $(objects) $(mainObjects) $(preout)
	$(CC) -o $@ $^ $(CFLAGS) 

$(preout): $(preobject) $(objects)
	$(CC) -o $@ $^ $(CFLAGS)

$(mainObjects):
	$(CC) -C $*.c

$(objects): 
	$(CC) -c $*.c

$(preobject):
	$(CC) -c $*.c

clean:
	$(RM) $(out) $(preout) $(preobject) $(mainObject) $(objects)
.PHONY: 
