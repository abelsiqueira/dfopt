OBJS = nelder_mead.o direct_search.o
CXXFLAGS += -Wall -Wextra -ggdb

PACKS = neldermead directsearch
all: library test

library: $(OBJS)
	ar rv libdfopt.a $(OBJS)

cutest: library
	(cd cutest; make $(PACKS))

test: library
	(cd tests; make)

clean:
	rm -f *.o
	(cd tests; make clean)
