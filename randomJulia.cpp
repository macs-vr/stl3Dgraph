#include <cmath>
#include <complex>
using namespace std;

#include "graph.hpp"

class randomJulia : public graph {
public:
  int max;
  int step;
  
  double escapeNorm;
  complex<double> a1, b1, c1, a2, b2, c2;
  
  virtual double f(double x, double y);

  complex<double> Q1(complex<double> z) { return (a1*z + b1)*z + c1; }
  complex<double> Q2(complex<double> z) { return (a2*z + b2)*z + c2; }
  
  double escapeProb(complex<double> z, int n);
  double escapeProb(complex<double> z) {
    return escapeProb(z, max);
  }
};

double randomJulia::escapeProb(complex<double> z, int n)
{
  double p=0;
  if (norm(z) > escapeNorm) {
    return 0;
  } else if (n <= 0) {
    return 1;
  } else {
    complex<double> z1=z, z2=z;
    for (int i=0; i<step; i++) {
      z1 = Q1(z1);
      z2 = Q2(z2);
    }
    return (escapeProb(z1, n-1)+escapeProb(z2,n-1))/2;
  }
}

double randomJulia::f(double x, double y) {
  return escapeProb(complex<double>(x,y));
}

int main()
{
  randomJulia g;

  g.step=2;

  g.a1 = 1.0;
  g.b1 = 0.0;
  g.c1 = -1.0;

  g.a2 = 0.25;
  g.b2 = 0.0;
  g.c2 = 0.0;

  //g.setWH(200,200);
  g.setWH(1000,1000);
  //g.setWH(2000,2000);
  
  g.setRegion(-4.1, 4.1, -4.1, 4.1);
    
  g.max=10;
  //g.max=10000;
  g.escapeNorm=1000;

  g.setZ();
  g.outputSTL();
  
}
