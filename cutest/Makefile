ROOTDIR = ..
include ../make.inc

checkcutest:
	@[ -d $(CUTEST) ] || exit 1

%: checkcutest %main.o
	mkdir -p $(CUTEST)/src/$@
	$(CP) $@.pro $(CUTEST)/packages/$(MYARCH)/double/$@
	chmod a+x $(CUTEST)/packages/$(MYARCH)/double/$@
	$(CP) $@main.cpp $(CUTEST)/src/$@/$@_main.cpp
	$(CP) $@main.o $(CUTEST)/objects/$(MYARCH)/double/$@_main.o
	$(CP) ../libdfopt.a $(CUTEST)/objects/$(MYARCH)/double/
	$(CP) makemaster $(CUTEST)/src/$@
	$(CP) rundfopt $(CUTEST)/bin/

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(I)
