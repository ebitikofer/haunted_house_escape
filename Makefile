CC=g++

include ./Makefile.defs

OPTIONS+=-Wall

OBJECTS = $(patsubst %.cc,%,$(wildcard *.cc))

all: $(OBJECTS)

# patterns to allow compilation of many c++ or c programs
.c:
	$(CC) $@.c $(InitShader) $(OPTIONS) $(LDLIBS) -o $@

.cc:
	$(CC) $@.cc $(InitShader) $(OPTIONS) $(LDLIBS) -o $@

clean:
	rm -f $(OBJECTS) *~

shader:
	$(MAKE) -C angel06/Common InitShader.o
