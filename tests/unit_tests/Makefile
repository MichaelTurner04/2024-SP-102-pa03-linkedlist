SOURCES := $(wildcard ../../src/*.cpp)
FUNC_SOURCES := ${filter-out ../../src/main.cpp, ${SOURCES}}

CPP = g++
CFLAGS = -Wall -Werror -Wextra -Wpedantic -pedantic-errors -g -std=c++14 

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp
	${CPP} ${CFLAGS} -I ../../src/ -I ../../.admin_files/ -I . $< ${FUNC_SOURCES} ../../.admin_files/*.hpp -o ../../build/$@ -std=c++14

.PHONY: clean
clean:
	-@rm -f ../../build/*.out
	-@rm -f *.out
