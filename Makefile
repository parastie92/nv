CXX = g++

LDFLAGS = -g -fdiagnostics-color -Wl,--wrap=malloc -Wl,--wrap=free 
CXXFLAGS = -g -c -fdiagnostics-color -DLINKTIME

all : main nvdimm.o main.o

main : main.o nvdimm.o
	$(CXX) $(LDFLAGS) -o main main.o nvdimm.o

nvdimm.o : nvdimm.cpp nvdimm.h
	$(CXX) $(CXXFLAGS) -o nvdimm.o nvdimm.cpp

main.o : main.cpp classNV.h 
	$(CXX) $(CXXFLAGS) -o main.o main.cpp

clean :
	rm *.o main

