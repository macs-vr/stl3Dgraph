#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "graph.hpp"
#include "outputtriangle.hpp"

double graph::f(double x, double y)
{
  return x*x-y*y;
}

void graph::setZ()
{
  zmin = std::numeric_limits<double>::max();
  z = vector<vector<double> >(width+1, vector<double>(height+1));
  for (int i=0; i<=width; i++) {
    double x = xmin + (xmax-xmin)/width*i;
    for (int j=0; j<=height; j++) {
      double y = ymin + (ymax-ymin)/height*j;
      z[i][j] = f(x,y);
      zmin = (z[i][j] < zmin) ? z[i][j] : zmin;
    }
  }
}

void graph::outputGraph() {
  // scale [xmin,xmax] to [-1,1]
  double scale = 2.0/width, vmin = -((double) height)/width;
  double scale2 = 2.0/(xmax-xmin);
  
  for (int i=0; i<width; i++) {
    double u = -1 + scale*i;
    double u1 = -1 + scale*(i+1);
    for (int j=0; j<height; j++) {
      double v = vmin + scale*j;
      double v1 = vmin + scale*(j+1);
      outputTriangle(u,v,z[i][j]*scale2,
		     u1,v,z[i+1][j]*scale2,
		     u1,v1,z[i+1][j+1]*scale2);
      outputTriangle(u,v,z[i][j]*scale2,
		     u1,v1,z[i+1][j+1]*scale2,
		     u,v1,z[i][j+1]*scale2);
    }
  }
}

void graph::outputSides() {
  double scale = 2.0/width, vmin = -((double) height)/width, vmax=-vmin;
  double scale2 = 2.0/(xmax-xmin);

  double b = zmin*scale2 - bottomMargin;

  for (int i=0; i<width; i++) {
    double u = -1 + scale*i;
    double u1 = -1 + scale*(i+1);

    outputTriangle(u,  vmin, b,
		  u1, vmin, b,
		  u1, vmin, z[i+1][0]*scale2);
    outputTriangle(u,  vmin, b,
		  u1, vmin, z[i+1][0]*scale2,
		  u, vmin, z[i][0]*scale2);

    outputTriangle(u,  vmax, b,
		  u1, vmax, z[i+1][height]*scale2,
		  u1, vmax, b);
    outputTriangle(u,  vmax, b,
		  u, vmax, z[i][height]*scale2,
		  u1, vmax, z[i+1][height]*scale2);
  }
  
  for (int j=0; j<height; j++) {
    double v = vmin + scale*j;
    double v1 = vmin + scale*(j+1);

    outputTriangle(-1, v, b,
		   -1, v, z[0][j]*scale2,
		   -1, v1, z[0][j+1]*scale2);
    outputTriangle(-1, v, b,
		   -1, v1, z[0][j+1]*scale2,
		   -1, v1, b);

    outputTriangle(1, v, b,
		   1, v1, z[width][j+1]*scale2,
		   1, v, z[width][j]*scale2);
    outputTriangle(1, v, b,
		   1, v1, b,
		   1, v1, z[width][j+1]*scale2);
  }
}

void graph::outputBottom() {
  double v = ((double) height)/width;
  double scale2 = 2.0/(xmax-xmin);
  double b = zmin*scale2 - bottomMargin;
  
  outputTriangle(-1, -v, b,
		 1, v, b,
		 1, -v, b);
  outputTriangle(-1, -v, b,
		 -1, v, b,
		 1, v, b);
}

void graph::outputSTL(bool withSides, bool withBottom) {
  cout << "solid " << endl;

  outputGraph();

  if (withSides)
    outputSides();

  if (withBottom)
    outputBottom();
 
  cout << "endsolid " << endl;
}

/*
int main()
{
  graph g;
  g.width=200; g.height=200;
  g.xmin=-1; g.xmax=1; g.ymin=-1; g.ymax=1;
  
  g.setZ();
  g.outputSTL();
}

*/
