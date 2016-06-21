include ../make_config.mk
DEPOBJ = rdats.o iqfunc.o tspack.o
VPATH += ../lib ./
all= iqdump
iqdump: iqdump.o $(DEPOBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) 
clean: 
	rm -f *.o $(all)
