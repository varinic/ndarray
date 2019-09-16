
cc=g++


test:main.o
	${cc} $^ -o $@ -std=c++11
main.o:main.cc
	${cc} $^ -c

.PHONY: clean

clean:
	rm *.o test
