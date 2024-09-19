PROGRAM   = connect4
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall -lm

$(PROGRAM): connect4Result.cpp
	$(CXX) connect4Result.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 
