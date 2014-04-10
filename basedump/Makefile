include ../make_config.mk
VPATH += ../lib
GENE_CV_OBJ = generic_basedata_cv.o NameIndex.o genericTask.o \
	 geneCodeData.o   generic_product_cv.o generic_dump.o
basedump:   basedump.o $(GENE_CV_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  $(INCLUDES)
all= demo
demo: main.o generic_basedata_cv.o generic_product_cv.o geneCodeData.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBPROJ)  
clean:
	rm -fr *.o $(all)
