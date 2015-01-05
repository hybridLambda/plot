COMPILER = g++
VERSION = ""
FLAGS = -O3 -g -std=c++0x -DVERSION=\"${VERSION}\" -I./graph
SOURCE = figure.cpp graph/node.cpp graph/nodeContainer.cpp graph/graph.cpp main.cpp

.PHONY: all
all: clean_all plot plot_dbg

plot:
	${COMPILER} ${FLAGS} -DNDEBUG -o plot ${SOURCE}

plot_dbg:
	${COMPILER} ${FLAGS} -o plot_dbg ${SOURCE}

.PHONY: clean
clean:
	rm -f *.o 

.PHONY: clean_all
clean_all:
	rm -f *.o plot
