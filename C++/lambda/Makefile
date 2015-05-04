all: lambda
	./lambda

# -O2 and -O3 appear to optimize-away some unneeded loops
GCC = g++ -ggdb3 -Wall -std=c++0x -O3

lambda: lambda.cpp
	$(GCC) -o $@ $<

clean:
	rm -f *.o lambda
