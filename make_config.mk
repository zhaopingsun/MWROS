
CXXFLAGS= -Wall -Wno-sign-compare -ggdb -g3 -fdata-sections -ffunction-sections -fopenmp
INCLUDES += -I ../lib
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<  $(INCLUDES)
