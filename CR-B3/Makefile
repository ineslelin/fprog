PROGRAMS   = bucketSort bubbleSort
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

bucketSort: bucketSort.cpp
	$(CXX) $(CXXFLAGS) bucketSort.cpp -o bucketSort $(LDFLAGS)

bubbleSort: bubbleSort.cpp
	$(CXX) $(CXXFLAGS) bubbleSort.cpp -o bubbleSort $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
