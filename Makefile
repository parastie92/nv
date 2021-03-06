CXX = g++

LDFLAGS = -g
CXXFLAGS = -g -c

all : main nvdimm.o main.o

main : main.o nvdimm.o
	$(CXX) $(LDFLAGS) -o main main.o nvdimm.o

nvdimm.o : nvdimm.cpp nvdimm.h
	$(CXX) $(CXXFLAGS) -o nvdimm.o nvdimm.cpp

main.o : main.cpp classNV.h nvdimm.h
	$(CXX) $(CXXFLAGS) -o main.o main.cpp

clean :
	rm *.o main

