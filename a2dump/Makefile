include ../make_config.mk
VPATH += ../lib
all= a2dump
a2dump: a2dump.o geneCodeData.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)
