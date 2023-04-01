CC=clang++
#CC2=g++
CFLAGS=-O3 -std=c++17
#CFLAGS2=-O3 -std=c++14
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system $(shell python3-config --ldflags)
#LDFLAGS2=-O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES=-I./include/ -I./src/utils/ $(shell python3-config --includes) $(shell python3 -m pybind11 --includes)
SRC_EXAMPLE=$(wildcard src/example/*.cpp)
OBJ_EXAMPLE=$(SRC_EXAMPLE:.cpp=.o)
SRC_ORBITAL=$(wildcard src/orbital/*.cpp) 
OBJ_ORBITAL=$(SRC_ORBITAL:.cpp=.o)
SRC_LASSO=$(wildcard src/lasso/*.cpp) 
OBJ_LASSO=$(SRC_LASSO:.cpp=.o)
SRC_CONTROL=$(wildcard src/pybind_control/*.cpp)
OBJ_CONTROL=$(SRC_CONTROL:.cpp=.o)

detected_OS=$(shell sh -c 'uname 2>/dev/null || echo Unknown')
$(info "Detected OS: $(detected_OS)")

ifeq ($(detected_OS),Darwin)
CFLAGS+=-undefined dynamic_lookup
endif

#all: cwaggle_lasso
#all: cwaggle_bridge.so
#all: cwaggle_example
#all: cwaggle_orbital
#all: cwaggle_pybind_control
all: control_bridge.so
#all: cwaggle_example cwaggle_orbital
#all: cwaggle_bridge.so cwaggle_orbital
#all: cwaggle_bridge.so cwaggle_example
#all: cwaggle_bridge.so cwaggle_pybind_control
#all: cwaggle_bridge.so cwaggle_example cwaggle_orbital
#all: cwaggle_bridge.so cwaggle_example cwaggle_orbital cwaggle_pybind_control

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

#T: Testing for the sake of making sure I actually understand how makefiles work
# and how to compile with them. Understanding is still shaky at best
cwaggle_orbital: $(OBJ_ORBITAL) Makefile
	$(CC) $(OBJ_ORBITAL) -o ./bin/$@ $(LDFLAGS)

cwaggle_pybind_control: $(OBJ_CONTROL) Makefile
	$(CC) $(OBJ_CONTROL) -o ./bin/$@ $(LDFLAGS)

control_bridge.so: src/pybind_control/control_bridge.cpp
	clang++ -B $(CFLAGS) -shared -fPIC $(INCLUDES) src/pybind_control/control_bridge.cpp $(LDFLAGS) -o ./bin/$@ 

clean:
	rm bin/control_bridge.so
#	rm $(OBJ_LASSO) $(OBJ_CONTROL) bin/cwaggle_lasso bin/cwaggle_pybind_control bin/cwaggle_bridge.so
#	rm $(OBJ_EXAMPLE) $(OBJ_LASSO) bin/cwaggle_example bin/cwaggle_lasso bin/cwaggle_bridge.so
#	rm $(OBJ_EXAMPLE) $(OBJ_LASSO) $(OBJ_ORBITAL) bin/cwaggle_example bin/cwaggle_lasso bin/cwaggle_orbital

