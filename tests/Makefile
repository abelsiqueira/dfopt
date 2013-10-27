ROOTDIR = ..
include ../make.inc

TESTS = nm_test1.tst nm_test2.tst ds_test1.tst

all: $(TESTS)

%.tst: %.o 
	$(CXX) -o $@ $< ../libdfopt.a $(CXXFLAGS)

