GCC = g++ -ggdb3 -Wall

all: lock lock2

% : %.cpp
	$(GCC) -o $@ $<

clean:
	rm -f *.o lock lock2
