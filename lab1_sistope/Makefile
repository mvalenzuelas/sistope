CC= gcc
CFLAGS= -Wall -lm -lniceprint -L .
out = lab1
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



