PROGRAMS   = countLines duplicateStrings splitClass
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

countLines: countLines.cpp
	$(CXX) $(CXXFLAGS) countLines.cpp -o countLines $(LDFLAGS)

duplicateStrings: duplicateStrings.cpp
	$(CXX) $(CXXFLAGS) duplicateStrings.cpp -o duplicateStrings $(LDFLAGS)

splitClass: splitClass.cpp
	$(CXX) $(CXXFLAGS) splitClass.cpp -o splitClass $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
