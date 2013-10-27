OBJS = nelder_mead.o direct_search.o
CXXFLAGS += -Wall -Wextra -ggdb

all: $(OBJS)
	ar rv libdfopt.a $(OBJS)
	sudo cp -f libdfopt.a /usr/lib/
	(cd tests; make)
	(cd cuter; make neldermead directsearch)

clean:
	rm -f *.o
	(cd tests; make clean)
