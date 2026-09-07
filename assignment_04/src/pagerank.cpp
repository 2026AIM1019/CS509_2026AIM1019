#include "pagerank.h"
#include <cmath>
PageRankResult pageRank(const CSRGraph& g,double d,double tol,int maxIter){
 PageRankResult r;r.rank.assign(g.V,1.0/g.V);vector<double> next(g.V);
 for(int it=1;it<=maxIter;it++){
  fill(next.begin(),next.end(),(1.0-d)/g.V); double dangling=0;
  for(int u=0;u<g.V;u++){int out=g.offset[u+1]-g.offset[u];if(out==0)dangling+=r.rank[u];else for(int p=g.offset[u];p<g.offset[u+1];p++)next[g.to[p]]+=d*r.rank[u]/out;}
  if(dangling!=0)for(double &x:next)x+=d*dangling/g.V;
  double change=0;for(int i=0;i<g.V;i++)change+=fabs(next[i]-r.rank[i]);r.rank.swap(next);r.iterations=it;
  if(change<=tol){r.converged=true;break;}
 }
 return r;
}
