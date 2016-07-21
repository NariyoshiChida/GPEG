main: gpeg_parser node
	g++ -std=c++11 main.cc gpeg_parser.o node.o -o main
	g++ -std=c++11 tree.cc gpeg_parser.o node.o -o tree

gpeg_parser: gpeg_parser.cc
	g++ -std=c++11 -c gpeg_parser.cc

node: node.cc
	g++ -std=c++11 -c node.cc

