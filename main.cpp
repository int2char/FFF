#include "Graph.h"
#include<string.h>
#include"service.h"
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include"dijkstra.h"
#include<fstream>
#include"taskPath.h"
#include "const.h"
#include<unordered_map>
#include<map>
using namespace std;
#define N 10000
float dm[N];
int pem[N];
char* namepart;
bool UPer(service a, service b){
	if (a.d>b.d)
		return 1;
	return 0;
}
void inline GenerateService(Graph& G,vector<service>&ser, int n,int task){
    map<pair<int,int>,int> flag;
	for (int i = 0; i <task; i++)
	{
		int s = 0, t = 4;
		float d = 100;
		d = 50 + rand() % 50;

		if (i <0.1*task)
			d = 10 + rand() % 10;
		if (i >= 0.1*task && i <0.3*task)
			d = 20 + rand() % 30;
		if (i >= 0.3*task && i <0.6*task)
			d = 40 + rand() % 40;
		if (i >= 0.6*task && i<0.8*task)
			d = 60 + rand() % 40;
		if (i >= 0.8*task)
			d = 90 + rand() % 10;
		do
		{
			s = rand() % n;
			t = rand() % n;
			dijkstra2(&G,s,t,dm,pem);
		} while (s == t||dm[t]>100||flag.find(make_pair(s,t))!=flag.end());
		ser.push_back(service(s, t, d));
		flag.insert(make_pair(make_pair(s,t),1));
	}
	sort(ser.begin(), ser.end(), UPer);

}
void inline Generatep2p(vector<service>&ser,int NODE){
	int s, t;
	for (int i = 0; i <NODE; i++)
	{
		s = i;
		for (int j = 0; j < NODE; j++)
		{
			if (i == j)
				continue;
			t = j;
			float d = 20 + rand() % 80;
			ser.push_back(service(s, t, d));

		}
	}
}
Graph inline GenerateGraph(int n, int m,int GN){
	float tw = 0;
	Graph G(n, m, GN);
	return G;
}
void inline	WriteService(vector<service>&ser,int task)
{
	ofstream outfile("service.txt");
	for (int i = 0; i < task; i++)
	 outfile << ser[i].s << " " << ser[i].t << " " << ser[i].d<< endl;
	outfile.close();
}
void inline	WriteGraph(Graph &G,char*file)
{
	ofstream outfile(file);
	for (int i = 0; i < G.m; i=i+2)
	{
		outfile << G.incL[i].tail << " " << G.incL[i].head << " " << G.incL[i].capacity << endl;
	}
	outfile.close();
}
void inline WriteFile(Graph &G,vector<service>&ser,int task){
	WriteService(ser,task);
	WriteGraph(G, "Graph.txt");
	ofstream outfile("data.txt");
	int cnt = 0;
	int*ss = new int[G.m];
	int *yy = new int[G.m];
	for (int i = 0; i < G.m; i++)
	{
		ss[i] = G.incL[i].tail;
		yy[i] = G.incL[i].head;
	}
	for (int i =0; i < task; i++)
	{
		vector<vector<int> >vec =kpw(&G,ss, yy,ser[i].s,ser[i].t);
		for (int j = 0; j < vec.size(); j++)
		{   
			for (int k = 0; k < vec[j].size(); k++)
			{
				outfile <<","<<vec[j][k];
				cnt++;
			}
			outfile<<"|";
		}
		outfile << endl;
		vec.clear();
	}
	delete[] ss;
	delete[] yy;
	cout <<"total size:"<<cnt << endl;
}
void inline ReadService(vector<service>&ser, char*file)
{
	FILE* rser = fopen(file, "r");
	int s, t;
	float d;
	while (fscanf(rser, "%d %d %f", &s, &t, &d) == 3)
	{
		ser.push_back(service(s, t, d));
	}
	fclose(rser);
}
void inline ChangDmand(vector<service>&ser,int task){
	for (int i = 0; i < task; i++)
		ser[i].d = 50;
	for (int i = 0; i <0.2*task; i++)
		ser[i].d =rand()%20;
	for (int i = 0.2*task; i <0.5*task; i++)
		ser[i].d = 20+rand() % 20;
	for (int i = 0.5*task; i <0.8*task; i++)
		ser[i].d = 30 + rand() %20;
	for (int i = 0.8*task; i <task; i++)
		ser[i].d = 40+ rand() % 60;
	//sort(ser.begin(), ser.end(), UPer);

	WriteService(ser,task);

}
Graph inline ReadFile(int n,int m,vector<service>&ser){
	ReadService(ser,"service.txt");
	Graph G(n, m, "Graph.txt");
	return G;
}
int split(char dst[][100000], char* str, const char* spl)
{
	int n = 0;
	char *result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n-1;
}
char* readline(FILE* f)
{
	char* line = (char*)calloc(1000, sizeof(char));;
	char c;
	int len = 0;

	while ((c = fgetc(f)) != EOF && c != '\n')
	{
		//line = (char*)realloc(line, sizeof(char) * (len + 2));
		line[len++] = c;
		line[len] = '/0';
	}

	return line;
}
void inline GetPath(Graph*G,vector<service>serv,taskPath*Path,int task){
	FILE* data = fopen("data.txt", "r");
	int tnum = 0;
	int shit = task;
	char line[100000];
	int iter = 0;
	while (shit--){
		fgets(line, 99999, data);
		if (line[0] == '\0')
			break;
		char dst[20][100000];
		int n = split(dst, line, "|");
		int aci = 0;
		if (iter >= 0)
		{
			for (int i = 0; i < n; i++)
			{
				char*dem = dst[i];
				int elem = 0;
				int k = 0;
				std:map<int, int> remap;
				int flag = 0;
				while (sscanf(dem, ",%d", &elem) == 1)
				{
					
					//cout << G.incL[elem].head << "=>";
					if (remap.find(G->incL[elem].head) != remap.end())
					{
						cout << tnum << " " << i << " erro" << endl;
						//flag = 1;
					}
					remap.insert(make_pair(G->incL[elem].head, 1));
					Path[tnum].Pathset[i].push_back(elem);
					//cout << tnum <<" "<< i<<" " << k++<<" "<< endl;
					dem = dem + 2;
					if (elem > 9)
						dem++;
					if (elem > 99)
						dem++;
					if (elem > 999)
						dem++;
					if (elem > 9999)
						dem++;
					if (elem > 99999)
						dem++;
					if (elem > 999999)
						dem++;
				}
				//cout << endl;
				Path[tnum].Pathset[i].push_back(-1);
				remap.clear();
			}
			Path[tnum].num = n;
			//if (n <=0)
			//cout << "erro fucker" << endl;
			tnum++;
		}
		iter++;
	}
	for(int i=0;i<task;i++)
		{if (Path[i].num<10)
			cout<<"less than 10";
		for(int j=0;j<Path[i].num;j++)
		{
			if(serv[i].s!=G->incL[Path[i].Pathset[j][0]].tail)
				cout<<"wrong tail";
			int k=0;
			while(true)
			{
				if(Path[i].Pathset[j][k]<0)
					break;
				if(Path[i].Pathset[j][k+1]>=0)
					if(G->incL[Path[i].Pathset[j][k]].head!=G->incL[Path[i].Pathset[j][k+1]].tail)
						cout<<"unconected"<<endl;
				else
					if(serv[i].t!=G->incL[Path[i].Pathset[j][0]].head)
									cout<<"wrong ";
				
				k++;
			}
		}
		}
			
	fclose(data);
}
int main(int arg,char**argv)
{
if(arg!=4)
	return -1;
int NODE = 0;
sscanf(argv[1],"%d",&NODE);
int EDGE = 100;
int task =0;
sscanf(argv[2],"%d",&task);
int Gnum =0;
sscanf(argv[3],"%d",&Gnum);
namepart=argv[4];
cout<<NODE<<" "<<task<<" "<<Gnum<<endl;
   int n = NODE;
   int m = EDGE;
   std::vector<service> ser;
  Graph G =ReadFile(n,m,ser); //GenerateGraph(n, m,Gnum);
  //GenerateService(G,ser,n,task);
  
  //taskPath*Path = new taskPath[task];
  time_t ts = clock();
  WriteFile(G, ser,task);
  //GetPath(&G,ser,Path,task);
  /*int*ss = new int[G.m];
  int *yy = new int[G.m];
  for (int i = 0; i < G.m; i++)
  	{
	    if(i==2494)
	    	{
	    	int a=0;
	    	//ss[i]=0;
	    	}
	    	//yy[i]=5;}
	    
	    else{
  		ss[i] = G.incL[i].tail;
  		yy[i] = G.incL[i].head;
	    }
  	}
  vector<vector<int> >vec =kpw(&G,ss, yy,419,98);
  		for (int j = 0; j < vec.size(); j++)
  		{   
  			for (int k = 0; k < vec[j].size(); k++)
  			{
  				cout<<","<<vec[j][k];
  			}
  			cout<<"|";
  		}
  		cout << endl;
  /*G.incL[569].tail=0;
  G.incL[569].head=1;
  float *lambda=(float*)malloc(G.m*sizeof(float));
  float *d=(float*)malloc(G.n*sizeof(int));
  int *peg=(int*)malloc(G.n*sizeof(int));
  for(int i=0;i<G.m;i++)
	  lambda[i]=0;
  dijkstra(&G,419,98,d,peg,lambda);
  cout<<d[2]<<endl;
  if(d[2]<1000)
	  cout<<"find it ,there is route!!!"<<endl;
  cout<<"peg is:"<<peg[98]<<endl;
  */
  cout <<"size"<<ser.size()<<" "<<G.m<< endl;
  time_t tt =clock();
  cout << "comesue time:" << tt - ts << endl;
   return 0;
}
