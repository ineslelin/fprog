PROGRAMS   = ex1 ex2 ex3 ex4 ex5
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

all: $(PROGRAMS)

ex1: ex1.cpp
	$(CXX) $(CXXFLAGS) ex1.cpp -o ex1 $(LDFLAGS)

ex2: ex2.cpp
	$(CXX) $(CXXFLAGS) ex2.cpp -o ex2 $(LDFLAGS)

ex3: ex3.cpp
	$(CXX) $(CXXFLAGS) ex3.cpp -o ex3 $(LDFLAGS)

ex4: ex4.cpp
	$(CXX) $(CXXFLAGS) ex4.cpp -o ex4 $(LDFLAGS)

ex5: ex5.cpp
	$(CXX) $(CXXFLAGS) ex5.cpp -o ex5 $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAMS) 
