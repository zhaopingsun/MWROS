include ../make_config.mk
VPATH += ../lib
basedump:   basedump.o $(GENE_CV_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  $(INCLUDES)
all= basedump
demo: main.o generic_basedata_cv.o generic_product_cv.o geneCodeData.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  
clean:
	rm -fr *.o $(all)
