CC=clang++
CFLAGS= -O3 -Wall -std=c++17
INCLUDES=$(shell python3-config --includes) $(shell python3 -m pybind11 --includes)

all: cbridge.so

cbridge.so: cbridge.cpp
	$(CC) $(CFLAGS) -shared -fPIC $(INCLUDES) cbridge.cpp -o $@

clean:
	rm cbridge.so