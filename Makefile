CXX	= g++ -O3

all: saddle mandelbrot julia randomJulia

outputrriangle.o: outputtriangle.cpp outputtriangle.hpp
	$(CXX) -c outputtriangle.cpp

graph.o: graph.cpp graph.hpp outputtriangle.hpp
	$(CXX) -c graph.cpp

saddle.o: saddle.cpp graph.hpp
	$(CXX) -c saddle.cpp

saddle: saddle.o graph.o outputtriangle.o
	$(CXX) -o saddle saddle.o graph.o outputtriangle.o

mandelbrot.o: mandelbrot.cpp graph.hpp
	$(CXX) -c mandelbrot.cpp

mandelbrot: mandelbrot.o graph.o outputtriangle.o
	$(CXX) -o mandelbrot mandelbrot.o graph.o outputtriangle.o

julia.o: julia.cpp graph.hpp
	$(CXX) -c julia.cpp

julia: julia.o graph.o outputtriangle.o
	$(CXX) -o julia julia.o graph.o outputtriangle.o

randomJulia.o: randomJulia.cpp graph.hpp
	$(CXX) -c randomJulia.cpp

randomJulia: randomJulia.o graph.o outputtriangle.o
	$(CXX) -o randomJulia randomJulia.o graph.o outputtriangle.o
