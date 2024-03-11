.PHONY: clean unit_tests_recursive

HEADERS := $(wildcard ./src/*.h ./src/*.hpp .admin_files/*.hpp)
SOURCES := $(wildcard ./src/*.cpp)
OBJECTS := $(SOURCES:./src/%.cpp=./build/%.o)
FUNC_SOURCES := ${filter-out ./src/main.cpp, ${SOURCES}}

CPP = g++
CFLAGS = -Wall -Werror -Wextra -Wpedantic -pedantic-errors -g -std=c++14 

program.out: ${OBJECTS}
	${CPP} ${CFLAGS} ${OBJECTS} -o build/program.out
	-@rm -f build/*.o

./build/%.o: ./src/%.cpp ${HEADERS}
	${CPP} ${CFLAGS} -c $< -o $@

unit_tests: $(patsubst ./tests/unit_tests/%.cpp, %.out, $(wildcard ./tests/unit_tests/*.cpp))

mem_tests: $(patsubst ./tests/mem_tests/%.cpp, %.out, $(wildcard ./tests/mem_tests/*.cpp))

%.out: tests/unit_tests/%.cpp
	${CPP} ${CFLAGS} -I ./tests/unit_tests/ -I ./.admin_files/ -I ./src $< ${FUNC_SOURCES} ./.admin_files/*.hpp -o ./build/$@ -std=c++14

%.out: tests/mem_tests/%.cpp
	${CPP} ${CFLAGS} -I ./tests/mem_tests/ -I ./.admin_files/ -I ./src $< ${FUNC_SOURCES} ./.admin_files/*.hpp -o ./build/$@ -std=c++14


# This is redundant, but is here to illustrate an alternative mechanism.
unit_tests_recursive:
	cd ./tests/unit_tests && $(MAKE)

clean:
	-@rm -f ./build/*.out
	-@rm -f ./unit_tests/*.out
	-@rm -f ./${OBJECTS}
