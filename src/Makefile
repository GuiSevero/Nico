CC      = gcc
LDFLAGS = -g

all: etapa1 

## Etapa 1
etapa1: nico


doc: Doxyfile $(HEAD1)
	doxygen Doxyfile

nico: lex.yy.c
	$(CC) $(LDFLAGS) -o nico lex.yy.c -lfl

lex.yy.c: scanner.l tokens.h
	flex scanner.l

clean:
	rm -f *.o lex.yy.?
