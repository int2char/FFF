#include"Graph.h"
#include <unordered_map>
using namespace std;
void dijkstra(Graph *G, int s, int t, float d[], int peg[], float lambda[]);
void dijcapacity(Graph *G, int s, int t, float d[], int peg[], float lambda[],float capacity[],float demand);
vector<vector<int>>kpath(Graph*G,int ss,int tt);
vector<vector<int>>kpathf(Graph*G, int s, int t);
void BFS(Graph *G, int s, int t, float d[], int peg[], float demand, float capacity[]);
vector<vector<int>>kpw(Graph*G, int*ss, int*yy, int s, int t);
void dijkstra2(Graph *G, int s, int t, float d[], int peg[]);
