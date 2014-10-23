COMPILER = g++
VERSION = ""
FLAGS = -O3 -g -std=c++0x -DVERSION=\"${VERSION}\" -I./graph
SOURCE = figure.cpp graph/node.cpp graph/nodeContainer.cpp graph/graph.cpp 

.PHONY: all
all: clean_all plot plot_dbg

plot:
	${COMPILER} ${FLAGS} -DNDEBUG -o plot ${SOURCE} main.cpp

plot_dbg:
	${COMPILER} ${FLAGS} -o plot_dbg ${SOURCE} main.cpp

unit_tests_CXXFLAGS = -DUNITTEST -DNDEBUG -std=c++0x -DVERSION=\"${VERSION}\" -I./graph
unit_tests_LDADD = -lcppunit -ldl

unittest:
	${COMPILER} ${unit_tests_CXXFLAGS} -o unittest ${SOURCE} test_figure.cpp test_runner.cpp ${unit_tests_LDADD}


.PHONY: clean
clean:
	rm plot plot_dbg unittest

.PHONY: clean_all
clean_all:
	rm -f *.o plot plot_dbg unittest
