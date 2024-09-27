PROGRAMS   = bucketSort
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

bucketSort: bucketSort.cpp
	$(CXX) $(CXXFLAGS) bucketSort.cpp -o bucketSort $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
