PROGRAM   = connect4
CXX       = clang++
CXXFLAGS += -std=c++17 -I/usr/include/c++/v1
LDFLAGS   += -lstdc++

$(PROGRAM): connect4Result.cpp
	$(CXX) $(CXXFLAGS) connect4Result.cpp -o $(PROGRAM) $(LDFLAGS)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 
