PROGRAMS   = funcCompPowLog funcCompSinArcsin
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall -lm

all: $(PROGRAMS)

funcCompPowLog: funcCompPowLog.cpp
	$(CXX) funcCompPowLog.cpp -o funcCompPowLog

funcCompSinArcsin: funcCompSinArcsin.cpp
	$(CXX) funcCompSinArcsin.cpp -o funcCompSinArcsin

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 
