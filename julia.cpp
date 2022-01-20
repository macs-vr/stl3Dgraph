#include <cmath>
#include <complex>
using namespace std;

#include "graph.hpp"

class julia : public graph {
public:
  int max;
  double escapeNorm;
  complex<double> c;
  
  virtual double f(double x, double y);

  complex<double> Q(complex<double> z) { return z*z+c; }
};

double julia::f(double x, double y) {
  complex<double> z(x,y);
  int i;
  for (i=0; i<max; i++) {
    z = Q(z);
    if (norm(z) > escapeNorm) break;
  }
  
  if (i >= max) return 0;
  
  return -log(norm(z))/pow(2,i+1);
}

class julia_metric : public julia {
  double f(double x, double y);

  complex<double> dQ(complex<double> z) { return 2.0*z; }
};

double julia_metric::f(double x, double y) {
  complex<double> z(x,y);
  int i;
  complex<double> dz = 1.0;
  double degpow=1;
  
  for (i=0; i<max; i++) {
    // dz = (d(f^n(c))/dc) / deg^n
    dz *= dQ(z)/2.0;
    degpow *= 2;
    z = Q(z);
    if ( norm(z) >= escapeNorm) break;
  }

  if (i >= max) return 0;

  double g, dg, metricinv;
  g = -log(norm(z))/(2*degpow);
  dg = abs(dz)/abs(z);
  metricinv = -sinh(g)/dg; // 1/metric
  if (isnan(metricinv)) {
    cerr << "z: " << z << "\tdegpow: " << degpow
	 << "\tg: " << g << "\tdg: " << dg << endl;
  }

  return (-metricinv > -0.5) ? -metricinv : -0.5 ;
  //return -sqrt(metricinv);
}

int main()
{
  //julia g;
  julia_metric g;
  //g.c = complex<double>(-1,0); // basilica
  //g.c = complex<double>(0,1); // dendrite
  //g.c = complex<double>(0.25,0); // cauliflower
  g.c = complex<double>(-0.123,0.745); // rabbit
  
  //g.setWH(200,200);
  g.setWH(1000,1000);
  
  g.setRegion(-2, 2, -2, 2);
    
  g.max=1000;
  //g.max=10000;
  g.escapeNorm=1000;

  g.setZ();
  g.outputSTL();
  
}
