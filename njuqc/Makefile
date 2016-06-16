include ../make_config.mk
VPATH += ../lib
basedump:   baseqc.o $(GENE_CV_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  $(INCLUDES)
all= baseqc
clean:
	rm -fr *.o $(all)
