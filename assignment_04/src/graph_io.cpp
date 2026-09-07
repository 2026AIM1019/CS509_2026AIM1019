#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <cmath>
using namespace std;

bool readUndirectedGraph(const string& name, Graph& g){
 ifstream f(name); if(!f){ cerr<<"Error: Cannot open input file: "<<name<<"\n"; return false; }
 if(!(f>>g.V>>g.E) || g.V<=0 || g.E<0){ cerr<<"Error: Invalid graph header.\n"; return false; }
 g.adj.assign(g.V,{}); long long listed=0;
 for(int i=0;i<g.V;i++){
  int u,d; if(!(f>>u>>d) || u<0 || u>=g.V || d<0){cerr<<"Error: Invalid vertex/degree at row "<<i<<".\n"; return false;}
  if(u!=i){cerr<<"Error: Vertex rows must be ordered 0..V-1.\n"; return false;}
  for(int j=0;j<d;j++){int v; if(!(f>>v)||v<0||v>=g.V){cerr<<"Error: Out-of-range neighbour.\n";return false;} if(v==u){cerr<<"Error: Self-loop rejected.\n";return false;} g.adj[u].push_back(v); listed++;}
 }
 if(listed != 2LL*g.E){cerr<<"Error: Mismatched degree/neighbour count: listed "<<listed<<", expected "<<2LL*g.E<<".\n";return false;}
 vector<unordered_set<int>> s(g.V); for(int u=0;u<g.V;u++) for(int v:g.adj[u]) s[u].insert(v);
 for(int u=0;u<g.V;u++){ if((int)s[u].size()!= (int)g.adj[u].size()){cerr<<"Error: Parallel/duplicate edge detected.\n";return false;} for(int v:g.adj[u]) if(!s[v].count(u)){cerr<<"Error: Undirected edge missing reverse endpoint.\n";return false;} }
 return true;
}

bool readDirectedPageRankGraph(const string& name, Graph& g, double& d, double& tol, int& maxIter){
 ifstream f(name); if(!f){cerr<<"Error: Cannot open input file: "<<name<<"\n";return false;}
 if(!(f>>g.V>>g.E)||g.V<=0||g.E<0){cerr<<"Error: Invalid PageRank graph header.\n";return false;}
 g.adj.assign(g.V,{}); long long listed=0;
 for(int i=0;i<g.V;i++){int u,out; if(!(f>>u>>out)||u!=i||u<0||u>=g.V||out<0){cerr<<"Error: Invalid PageRank vertex row.\n";return false;} for(int j=0;j<out;j++){int v;if(!(f>>v)||v<0||v>=g.V){cerr<<"Error: Out-of-range PageRank edge.\n";return false;} if(v==u){cerr<<"Error: Self-loop rejected.\n";return false;} g.adj[u].push_back(v);listed++;}}
 string key; if(!(f>>key>>d)||key!="DAMPING"||!(d>0&&d<1)){cerr<<"Error: Invalid damping factor.\n";return false;}
 if(!(f>>key>>tol)||key!="TOLERANCE"||!(tol>0)){cerr<<"Error: Invalid tolerance.\n";return false;}
 if(!(f>>key>>maxIter)||key!="MAX_ITERATIONS"||maxIter<=0){cerr<<"Error: Invalid MAX_ITERATIONS.\n";return false;}
 if(listed!=g.E){cerr<<"Error: E does not match listed directed edges.\n";return false;}
 return true;
}
CSRGraph convertToCSR(const Graph& g){ CSRGraph c; c.V=g.V;c.offset.assign(g.V+1,0);for(int i=0;i<g.V;i++)c.offset[i+1]=c.offset[i]+(int)g.adj[i].size();c.to.resize(c.offset[g.V]);for(int i=0;i<g.V;i++){int p=c.offset[i];for(int v:g.adj[i])c.to[p++]=v;}return c; }
