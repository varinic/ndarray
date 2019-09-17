
cc=g++


test:main.o
	${cc} $^ -o $@ -std=c++11
main.o:main.cc
	${cc} $^ -c -std=c++11

.PHONY: clean

clean:
	rm *.o test
