PROGRAM   = functionalLoops
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall -lm

$(PROGRAM): functionalLoops.cpp
	$(CXX) functionalLoops.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 
