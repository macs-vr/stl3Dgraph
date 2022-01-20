#include <cmath>
#include <complex>
using namespace std;

#include "graph.hpp"

class mandelbrot : public graph {
public:
  int max;
  double escapeNorm;
  
  virtual double f(double x, double y);

  complex<double> Q(complex<double> z, complex<double> c) { return z*z+c; }
};

double mandelbrot::f(double x, double y) {
  complex<double> c(x,y), z=c;
  int i;
  for (i=0; i<max; i++) {
    z = Q(z,c);
    if (norm(z) > escapeNorm) break;
  }
  
  if (i >= max) return 0;
  
  return -log(norm(z))/pow(2,i+1);
}

class mandelbrot_metric : public mandelbrot {
  double f(double x, double y);

  complex<double> dQ(complex<double> z, complex<double> c=0) { return 2.0*z; }
};

double mandelbrot_metric::f(double x, double y) {
  complex<double> c(x,y), z=c;
  int i;
  complex<double> dz = 1.0;
  double degpow=1;
  
  for (i=0; i<max; i++) {
    // dz = (d(f^n(c))/dc) / deg^n
    dz = (1.0/degpow + dQ(z)*dz)/2.0;
    degpow *= 2;
    z = Q(z,c);
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
  //mandelbrot m;
  mandelbrot_metric m;
  //m.setWH(200,200);
  m.setWH(1000,1000);
  
  //m.setRegion(-2.25, 0.75, -1.5, 1.5);
  //m.setRegion(-10, 10, -10, 10);
  //m.setRegion(-0.1735,-0.1447, 1.0183, 1.0471); // Kokopelli
  m.setRegion(-1.7414, -1.74139, -0.000005, 0.000005); // M in cauliflower
  
  m.max=1000;
  m.escapeNorm=1000;

  m.setZ();
  m.outputSTL();
  
}
