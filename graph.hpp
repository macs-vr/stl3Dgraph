#include <iostream>
#include <vector>
#include <cmath>

class graph
{
public:
  int width, height;
  double xmin, xmax, ymin, ymax;

  double zmin;

  double bottomMargin;
  
  graph() : bottomMargin(0.1) {};

  void setWH(int w, int h) {width = w; height=h; }
  void setRegion(double x1, double x2, double y1, double y2)
  { xmin = x1; xmax = x2; ymin = y1; ymax=y2; }

  std::vector<std::vector<double> > z;

  virtual double f(double x, double y);

  void setZ();
  void do_subdivision(double x0, double x1, double y0, double y1, int max);
  
  void outputGraph();
  void outputTriangels(double x0, double x1, double y0, double y1);

  void outputSides();
  void outputBottom();
  
  void outputSTL(bool withSides=true, bool withBottom=true);
  
};

void outputTriangle(double x1, double y1, double z1,
		    double x2, double y2, double z2,
		    double x3, double y3, double z3);
