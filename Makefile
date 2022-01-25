CXX	= g++ -O3

all: saddle mandelbrot julia randomJulia

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

julia.o: julia.cpp graph.hpp
	$(CXX) -c julia.cpp

julia: julia.o graph.o
	$(CXX) -o julia julia.o graph.o

randomJulia.o: randomJulia.cpp graph.hpp
	$(CXX) -c randomJulia.cpp

randomJulia: randomJulia.o graph.o
	$(CXX) -o randomJulia randomJulia.o graph.o
