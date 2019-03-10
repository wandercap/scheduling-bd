CC = gcc
CFLAGS = -g -Wall -ggdb3

ODIR = bin
SDIR = src
LDIR = lib

_DEPS = graph.h stack.h transaction.h conflict.h vision.h scheduling.h util.h
DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))

_OBJ = main.o graph.o stack.o transaction.o conflict.o vision.o scheduling.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
escalona: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o escalona 
