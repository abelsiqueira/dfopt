ROOTDIR = ..
include ../make.inc

neldermead: neldermeadmain.o
	$(CP) neldermead.sh.pro $(CUTER)/build/prototypes/neldermead.sh.pro
	sed -f $(MYCUTER)/double/config/script.sed neldermead.sh.pro > $(MYCUTER)/bin/neldermead
	chmod a+x $(MYCUTER)/bin/neldermead
	$(CP) neldermeadmain.cpp $(MYCUTER)/double/bin/neldermeadma.cpp
	$(MV) neldermeadmain.o   $(MYCUTER)/double/bin/neldermeadma.o  

directsearch: directsearchmain.o
	$(CP) directsearch.sh.pro $(CUTER)/build/prototypes/directsearch.sh.pro
	sed -f $(MYCUTER)/double/config/script.sed directsearch.sh.pro > $(MYCUTER)/bin/directsearch
	chmod a+x $(MYCUTER)/bin/directsearch
	$(CP) directsearchmain.cpp $(MYCUTER)/double/bin/directsearchma.cpp
	$(MV) directsearchmain.o   $(MYCUTER)/double/bin/directsearchma.o  

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
