CXX	= g++ -O3

all: saddle mandelbrot

graph.o: graph.cpp graph.hpp
	$(CXX) -c graph.cpp

saddle.o: saddle.cpp graph.hpp
	$(CXX) -c saddle.cpp

saddle: saddle.o graph.o
	$(CXX) -o saddle saddle.o graph.o

mandelbrot.o: mandelbrot.cpp graph.hpp
	$(CXX) -c mandelbrot.cpp

mandelbrot: mandelbrot.o graph.o
	$(CXX) -o mandelbrot mandelbrot.o graph.o
