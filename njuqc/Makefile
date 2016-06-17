include ../make_config.mk
VPATH += ../lib

#baseqc:baseqc.o $(GENE_CV_OBJ)
#	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  $(INCLUDES)

base2rr:base2rr.o $(GENE_CV_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  $(INCLUDES)

ALL = base2rr baseqc
all: $(ALL)
clean:
	rm -fr *.o $(ALL)
