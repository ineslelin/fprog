PROGRAMS   = bucketSort bubbleSort selectionSort quickSort
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1 -Wall -Werror
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

bucketSort: bucketSort.cpp
	$(CXX) $(CXXFLAGS) bucketSort.cpp -o bucketSort $(LDFLAGS)

bubbleSort: bubbleSort.cpp
	$(CXX) $(CXXFLAGS) bubbleSort.cpp -o bubbleSort $(LDFLAGS)

selectionSort: selectionSort.cpp
	$(CXX) $(CXXFLAGS) selectionSort.cpp -o selectionSort $(LDFLAGS)

quickSort: quickSort.cpp
	$(CXX) $(CXXFLAGS) quickSort.cpp -o quickSort $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
