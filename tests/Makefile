ROOTDIR = ..
include ../make.inc

NMTESTS = nm_test1.tst nm_test2.tst 
DSTESTS = ds_test1.tst ds_test2.tst
TESTS = $(NMTESTS) $(DSTESTS)

all: $(TESTS)

%.tst: %.o 
	$(CXX) -o $@ $< ../libdfopt.a $(CXXFLAGS)

clean:
	rm -f *.o *.tst
