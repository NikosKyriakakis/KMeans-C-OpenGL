IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -lGL -lGLU -lglut -lm -lconfig

ODIR=obj

_DEPS = window.h parser.h color.h utils.h point.h kmeans.h list.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o parser.o point.o utils.o color.o kmeans.o list.o window.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kmeans: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
