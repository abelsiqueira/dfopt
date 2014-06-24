OBJS = nelder_mead.o direct_search.o
CXXFLAGS += -Wall -Wextra -ggdb

all: $(OBJS)
	ar rv libdfopt.a $(OBJS)
	(cd tests; make)

cutest:
	(cd cutest; make neldermead directsearch)

clean:
	rm -f *.o
	(cd tests; make clean)
