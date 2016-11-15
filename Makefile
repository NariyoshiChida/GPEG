main: gpeg_parser node packrat_parser generalized_packrat_parser
	g++ -std=c++11 main.cc gpeg_parser.o node.o -o main
	g++ -std=c++11 tree.cc gpeg_parser.o node.o -o tree
	g++ -std=c++11 packrat_main.cc gpeg_parser.o node.o packrat_parser.o -o packrat_main
	g++ -std=c++11 generalized_packrat_main.cc gpeg_parser.o node.o generalized_packrat_parser.o -o generalized_packrat_main

gpeg_parser: gpeg_parser.cc
	g++ -std=c++11 -c gpeg_parser.cc

node: node.cc
	g++ -std=c++11 -c node.cc

packrat_parser: packrat_parser.cc
	g++ -std=c++11 -c packrat_parser.cc

generalized_packrat_parser: generalized_packrat_parser.cc
	g++ -std=c++11 -c generalized_packrat_parser.cc
