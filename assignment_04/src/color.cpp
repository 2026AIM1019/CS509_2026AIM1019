#include "color.h"
#include <algorithm>
#include <unordered_set>
vector<int> greedyWelshPowell(const CSRGraph& g){
 vector<int> deg(g.V), order(g.V), color(g.V,-1); for(int i=0;i<g.V;i++){deg[i]=g.offset[i+1]-g.offset[i];order[i]=i;}
 sort(order.begin(),order.end(),[&](int a,int b){if(deg[a]!=deg[b])return deg[a]>deg[b];return a<b;});
 for(int u:order){unordered_set<int> used;for(int p=g.offset[u];p<g.offset[u+1];p++){int v=g.to[p];if(color[v]>=0)used.insert(color[v]);}int c=0;while(used.count(c))++c;color[u]=c;} return color;
}
bool validColoring(const CSRGraph& g,const vector<int>& c){if((int)c.size()!=g.V)return false;for(int u=0;u<g.V;u++){if(c[u]<0)return false;for(int p=g.offset[u];p<g.offset[u+1];p++)if(c[u]==c[g.to[p]])return false;}return true;}
