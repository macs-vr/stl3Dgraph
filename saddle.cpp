#include "graph.hpp"

int main()
{
  graph g;
  g.width=200; g.height=200;
  g.xmin=-1; g.xmax=1; g.ymin=-1; g.ymax=1;
  
  g.setZ();
  g.outputSTL();
}
