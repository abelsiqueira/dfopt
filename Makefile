OBJS = nelder_mead.o
TESTS = test1.tst test2.tst
CXXFLAGS += -Wall -Wextra -ggdb

all: $(TESTS)

%.tst: %.o $(OBJS)
	$(CXX) -o $@ $< $(OBJS) $(CXXFLAGS)
