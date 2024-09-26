PROGRAMS   = transformPrime accumulate
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

transformPrime: transformPrime.cpp
	$(CXX) $(CXXFLAGS) transformPrime.cpp -o transformPrime $(LDFLAGS)

accumulate: accumulate.cpp
	$(CXX) $(CXXFLAGS) accumulate.cpp -o accumulate $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
