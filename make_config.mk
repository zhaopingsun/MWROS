GENE_CV_OBJ = generic_basedata_cv.o NameIndex.o genericTask.o \
	 geneCodeData.o   generic_product_cv.o generic_dump.o
CXXFLAGS= -Wall -Wno-sign-compare -ggdb -g3 -fdata-sections -ffunction-sections -fopenmp
INCLUDES += -I ../lib
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<  $(INCLUDES)
