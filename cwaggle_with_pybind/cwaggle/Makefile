CC=clang++
CFLAGS=-O3 -std=c++17
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system $(shell python3-config --ldflags)
INCLUDES=-I./include/ -I./src/utils/ $(shell python3-config --includes) $(shell python3 -m pybind11 --includes)
SRC_EXAMPLE=$(wildcard src/example/*.cpp)
OBJ_EXAMPLE=$(SRC_EXAMPLE:.cpp=.o)
SRC_LASSO=$(wildcard src/lasso/*.cpp) 
OBJ_LASSO=$(SRC_LASSO:.cpp=.o)

detected_OS=$(shell sh -c 'uname 2>/dev/null || echo Unknown')
$(info "Detected OS: $(detected_OS)")

ifeq ($(detected_OS),Darwin)
CFLAGS+=-undefined dynamic_lookup
endif

#all: cwaggle_lasso
all: cwaggle_bridge.so

cwaggle_example:$(OBJ_EXAMPLE) Makefile
	$(CC) $(OBJ_EXAMPLE) -o ./bin/$@ $(LDFLAGS)

cwaggle_lasso:$(OBJ_LASSO) Makefile
	$(CC) $(OBJ_LASSO) -o ./bin/$@ $(LDFLAGS)

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

# This creates a library to allow elements of CWaggle to be called from Python.
# The purpose is NOT to make a general purpose Python version of CWaggle, but rather
# to implement the Lasso method using the controller code developed in CWaggle 
# on-board the Kodama robots.
cwaggle_bridge.so: src/cwaggle_bridge/bridge.cpp
	clang++ $(CFLAGS) -shared -fPIC $(INCLUDES) src/cwaggle_bridge/bridge.cpp $(LDFLAGS) -o ./bin/$@ 

clean:
	rm $(OBJ_EXAMPLE) $(OBJ_LASSO) bin/cwaggle_example bin/cwaggle_lasso bin/cwaggle_bridge.so
