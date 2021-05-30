#include<bits/stdc++.h>
#define size_m 25
using namespace std;

int maze[size_m][size_m];
vector<pair<int,int>>v;
vector<int>parent(size_m*size_m);
vector<int>length(size_m*size_m);

void initialize()
{
	for(int i=0;i<size_m;i++)
	{
		for(int j=0;j<size_m;j++)
		{
			maze[i][j]=0;
			if(i%2!=0 && j%2!=0 && i<size_m-3 && j<size_m-3)
			{
				v.push_back({25*i+j,25*i+j+2});
				v.push_back({25*i+j,25*(i+2)+j});
			}
			else if(i%2!=0 && j%2!=0 && i==size_m-2 && j<size_m-3)
			{
				v.push_back({25*i+j,25*i+j+2});
			}
			else if(i%2!=0 && j%2!=0 && j==size_m-2 && i<size_m-3)
			{
				v.push_back({25*i+j,25*(i+2)+j});
			}
		}
	}
}

int findParent(int child)
{
	if(parent[child]==child)
		return child;
	int x=findParent(parent[child]);
	parent[child]=x;
	return x;
}

void join(int child1, int child2)
{
	int a=findParent(child1);
	int b=findParent(child2);
	if(a==b)
		return ;
	int avg=(child1+child2)/2;
	maze[avg/25][avg%25]=1;
	int s1=length[a];
	int s2=length[b];
	if(s1>s2)
	{
		parent[b]=a;
		length[a]+=length[b];
	}
	else
	{
		parent[a]=b;
		length[b]+=length[a];
	}

}

void generate()
{
	random_shuffle(v.begin(),v.end());
	for(int i=1;i<size_m;i+=2)
	{
		for(int j=1;j<size_m;j+=2)
		{
			parent[25*i+j]=25*i+j;
			length[25*i+j]=1;
			maze[i][j]=1;
		}
	}
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i].first<<" "<<v[i].second<<"\n";
		join(v[i].first,v[i].second);
	}


}

