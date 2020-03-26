IDIR =../include
CC =gcc
CFLAGS = -g -I$(IDIR)

ODIR =src
LDIR =../lib

LIBS =-lm

_DEPS = dparse.h hparse.h ansi_c.h  parser.h conv.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = dparse.o hparse.o parser.o hexdump.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hexdump: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)  


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
