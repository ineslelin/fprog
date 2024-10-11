PROGRAMS   = monadCorrect monadTest
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

monadCorrect: monadCorrect.cpp
	$(CXX) $(CXXFLAGS) monadCorrect.cpp -o monadCorrect $(LDFLAGS)

monadTest: monadTest.cpp
	$(CXX) $(CXXFLAGS) 	monadTest.cpp -o monadTest $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
