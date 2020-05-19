IDIR =../include
CC =gcc
CFLAGS = -g -I$(IDIR)

ODIR =src
LDIR =../lib

LIBS =-lm

_DEPS = char_val.h bparse.h hget.h bprint.h  dparse.h hparse.h ansi_c.h  parser.h conv.h valueprint.h fileprint.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = fileprint.o bparse.o dparse.o hparse.o hget.o bprint.o parser.o hexdump.o valueprint.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hexdump: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)  


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
