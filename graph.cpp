#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "graph.hpp"

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

void outputTriangle(double x1, double y1, double z1,
		    double x2, double y2, double z2,
		    double x3, double y3, double z3) {

  double u1=x2-x1, v1=y2-y1, w1=z2-z1,
    u2=x3-x1, v2=y3-y1, w2=z3-z1;
  
  // vertices are ordered counterclockwise
  double n1 = v1*w2-v2*w1, n2= w1*u2-w2*u1, n3 = u1*v2-v1*u2;
  double norm=sqrt(n1*n1+n2*n2+n3*n3);
  n1=n1/norm; n2=n2/norm; n3=n3/norm;

  cout << "facet normal "
       << n1 << " " << n3 << " " << -n2 << endl
       << "    outer loop" << endl
       << "        vertex " << x1 << " " << z1 << " " << -y1 << endl
       << "        vertex " << x2 << " " << z2 << " " << -y2 << endl
       << "        vertex " << x3 << " " << z3 << " " << -y3 << endl
       << "    endloop" << endl
       << "endfacet" << endl;

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
