#include"Graph.h"
#include<string.h>
#include"dijkstra.h"
#include"Heap.h"
#include<queue>
#include"LinkQueue.h"
#include<iostream>
#include<map>
#define INF 10000000
#define N 10000
int flag2[N];
#define INF 10000000
int flag[N];
float diste[N];
int pegg[N];
class cmp
{
private:
	Graph *G;
public:
	cmp(Graph* Gra):G(Gra){}
	bool operator() (int a, int b){
		if (diste[G->incL[a].head] < diste[G->incL[b].head])
			return true;
		return false;

	}
};
namespace Kth_Path
{

	int back[10050];
	struct edge1
	{

		int to, next;
		double cost;
		edge1(){}
		edge1(int _t, int _n, double _c) :to(_t), next(_n), cost(_c){}
	}edger[100050], edge[100050];
	int n, m, K;
	double dist[10050];
	int headr[10050], head[10050], Lr, L;
	void dijkstra(int s)
	{
		int x, y;
		double w;
		priority_queue<pair<double, int> >q;
		vector<int>pre;
		for (int i = 0; i<n; i++)dist[i] = 1e10;
		q.push(make_pair(dist[s] = 0.0, s));
		while (!q.empty())
		{
			w = -q.top().first;
			x = q.top().second;
			q.pop();
			if (w != dist[x])continue;
			for (int i = headr[x]; ~i; i = edger[i].next)
				if (dist[y = edger[i].to]>w + edger[i].cost)
				{
					dist[y] = w + edger[i].cost;
					q.push(make_pair(-dist[y], y));
				}
		}
	}
	int num[10050];
	void add_edge(int x, int y, double w)
	{
		edge[L] = edge1(y, head[x], w); head[x] = L++;
		edger[Lr] = edge1(x, headr[y], w); headr[y] = Lr++;
	}

	int a_star(vector<vector<int> >&ans, int s, int t)
	{
		if (dist[s] == 1e10)return -1;
		int x, y, z;
		double w;
		priority_queue<pair<double, int> >q;
		vector<pair<int, int>>pre;
		q.push(make_pair(-dist[s], 0));
		pre.push_back(make_pair(-1, -1));
		while (!q.empty())
		{
			z = q.top().second;
			if (pre[z].second == -1)x = s;
			else x = edge[pre[z].second].to;
			w = -q.top().first - dist[x];
			q.pop();
			num[x]++;
			if (t == x)
			{
				int h = z;
				vector<int>cp;
				while (h)
				{
					cp.push_back(pre[h].second);
					h = pre[h].first;
				}
				for (int i = 0; i<cp.size() / 2; i++)
					swap(cp[i], cp[cp.size() - 1 - i]);
                 map<int,int>remap;
                 int flag=0;
                 int first=0;
                 for(int i=0;i<cp.size();i++)
                        {
                	       if(first==0)
                	    	   {remap.insert(make_pair(back[cp[i]],1));
                	       	   first=1;}

                            if(remap.find(edge[cp[i]].to)!=remap.end())
                                flag=1;
                          remap.insert(make_pair(edge[cp[i]].to,1));

                        }
		        remap.clear();
                if(flag==0)
                    ans.push_back(cp);
                else
                    {
                       if(K<10000000)
                         K++;
                    }
			}
			if (num[t] == K)
				{//cout<<"find k";
				return 1;}
			if (x == t)continue;
			for (int i = head[x]; ~i; i = edge[i].next)
			{
				y = edge[i].to;
				q.push(make_pair(-w - edge[i].cost - dist[y], pre.size()));
				pre.push_back(make_pair(z, i));
			}
		}
		return -1;
	}
	vector<vector<int> > solv(int nn, int mm, int xx[], int yy[], int px, int py, int k)
	{
		n = nn; m = mm;
		K = k; Lr = L = 0;
		memset(head, -1, sizeof(head));
		memset(headr, -1, sizeof(headr));
		memset(num, 0, sizeof(num));
		for (int i = 0; i<m; i++)
		{
			int u = xx[i], v = yy[i];
			back[i]=xx[i];
			double w = 1.0;
			add_edge(u, v, w);
		}
		int s = px, t = py, f;
		dijkstra(t);
		vector<vector<int> >ans;
		ans.clear();
		f = a_star(ans, s, t);
		return ans;
	}
};


void dijkstra(Graph *G, int s, int t,float d[],int peg[],float lambda[]){
	int n_num = G->n;
	for (int i = 0; i < n_num; i++)
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	for (int i = 0; i < n_num; i++)
	{
		flag[i] = 0;
		peg[i] = -1;
	}
	int cur = s;
	Heap heap;
	for (int i = 0; i < n_num; i++)
		heap.push(i, d[i]);
	do{
		int cur = heap.pop();
		flag[cur] = 1;
		if (cur == t)
			break;
		int size = G->near[cur].size();
		for (int i = 0; i<size; i++){
			int id = G->near[cur][i];
				Edge* e = &G->incL[id];
				int delt = 0;
				if (flag[e->head] == 0 && d[e->head]>(d[e->tail] +e->weight+lambda[id])){
					d[e->head] = d[e->tail] + e->weight+lambda[id];
					heap.update(e->head, d[e->head]);
					peg[e->head] = id;

			}
		}
	} while (!heap.empty());

}
void dijkstra2(Graph *G, int s, int t, float d[], int peg[]){
	int n_num = G->n;
	for (int i = 0; i < n_num; i++)
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	for (int i = 0; i < n_num; i++)
	{
		flag[i] = 0;
		peg[i] = -1;
	}
	int cur = s;
	Heap heap;
	for (int i = 0; i < n_num; i++)
		heap.push(i, d[i]);
	do{
		int cur = heap.pop();
		flag[cur] = 1;
		int size = G->near[cur].size();
		for (int i = 0; i<size; i++){
			int id = G->near[cur][i];
			Edge* e = &G->incL[id];
			int delt = 0;
			if (flag[e->head] == 0 && d[e->head]>(d[e->tail] + e->weight)){
				d[e->head] = d[e->tail] + e->weight;
				heap.update(e->head, d[e->head]);
				peg[e->head] = id;

			}
		}
	} while (!heap.empty());

}
void dijcapacity(Graph *G, int s, int t, float d[], int peg[], float lambda[], float capacity[], float demand)
{
	int n_num = G->n;
	for (int i = 0; i < n_num; i++)
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	for (int i = 0; i < n_num; i++)
	{
		flag[i] = 0;
		//peg[i] = -1;
	}
	int cur = s;
	Heap heap;
	for (int i = 0; i < n_num; i++)
		heap.push(i, d[i]);
	do{
		int cur = heap.pop();
		flag[cur] = 1;
		if (cur == t)
			break;
		int size = G->near[cur].size();
		for (int i = 0; i<size; i++){
			int id = G->near[cur][i];
			if (demand<=capacity[id])
			{
				Edge* e = &G->incL[id];
				int delt = 0;
				if (flag[e->head] == 0 && d[e->head]>(d[e->tail] + e->weight + lambda[id])){
					d[e->head] = d[e->tail] + e->weight + lambda[id];
					heap.update(e->head, d[e->head]);
					//peg[e->head] = id;
			}
			}
		}
	} while (!heap.empty());
}
/*vector<vector<int>>kpathf(Graph*G, int s, int t){

}*/
vector<vector<int>>kpw(Graph*G, int*ss, int*yy, int s, int t){
	//cout<<"Graph check:"<<G->n<<" "<<G->m<<endl;
	return Kth_Path::solv(G->n, G->m, ss, yy, s, t,30);
}
void BFS(Graph *G, int s, int t, float d[], int peg[], float demand, float capacity[]){
	int n_num = G->n;
	for (int i = 0; i < n_num; i++)
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	for (int i = 0; i < n_num; i++)
	{
		flag2[i] = 0;
		peg[i] = -1;
	}
	int cur = s;
	LinkQueue que;
	que.push(s);
	do{
		int cur = que.pop();
		//printf("cur is %d\n", cur);
		flag2[cur] = 1;
		if (cur == t)
			break;
		int size = G->near[cur].size();
		for (int i = size - 1; i >= 0; i--)
		{
			int id = G->near[cur][i];
			if (capacity[id] >= demand)
			{
				int head = G->incL[id].head;
				int tail = G->incL[id].tail;
				if (flag2[head] == 0 && d[head] > d[tail] + 1)
				{
					d[head] = d[tail] + 1;
					peg[head] = id;
					que.push(head);
				}
			}
		}
	} while (!que.isEmpty());
}
