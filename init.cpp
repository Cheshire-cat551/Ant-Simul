#include<bits/stdc++.h>
#include"maze.h"

using namespace std;

map<pair<int,int>,int>m;

void clean()
{
	map<pair<int,int>,int>p;
	for(auto it:m)
	{
		if(it.second!=0)
			p[it.first]=it.second;
	}
	m=p;
}

void dfs(int p, int prev)
{
	int mex=-1;
	mex=max({m[{p-1,p}],m[{p-25,p}],m[{p,p+1}],m[{p,p+25}]});
	vector<int>neg,w;
	if(m[{p-1,p}]==-1)
		neg.push_back(p-1);
	if(m[{p-25,p}]==-1)
		neg.push_back(p-25);
	if(m[{p,p+1}]==-1)
		neg.push_back(p+1);
	if(m[{p,p+25}]==-1)
		neg.push_back(p+25);
	if(m[{p-1,p}]==mex && mex>0)
		neg.push_back(p-1);
	if(m[{p-25,p}]==mex && mex>0)
		neg.push_back(p-25);
	if(m[{p,p+1}]==mex && mex>0)
		neg.push_back(p+1);
	if(m[{p,p+25}]==mex && mex>0)
		neg.push_back(p+25);
	if(neg.size()==0)
		return;
	random_shuffle(neg.begin(), neg.end());
	if(neg.back()==prev) neg.pop_back();
	if(neg.size()==0) return ;
	for(int i=0;i<neg.size();++i)
	{
		clean();
		int x=neg[i];
		m[{min(x,p),max(x,p)}]+=2;
		dfs(x,p);
		clean();
	}
}

int main()
{
	initialize();
	generate();
	for(int i=0;i<size_m;i++)
	{
		for(int j=0;j<size_m;j++)
		{
			cout<<maze[i][j]<<" ";
		}
		cout<<"\n";
	}
	for(int i=0;i<size_m;i++)
	{
		for(int j=0;j<size_m;j++)
		{
			if(maze[i][j]==1)
			{
				if(j+1<size_m && maze[i][j+1]==1)
				{
					m[{25*i+j,25*i+j+1}]=-1;
				}
				if(i+1<size_m && maze[i+1][j]==1)
				{
					m[{25*i+j,25*(i+1)+j}]=-1;
				}
			}
		}
	}
	dfs(size_m+1,-1);
	
	for(auto it:m)
	{
		cout<<it.first.first<<" "<<it.first.second<<" ";
		cout<<it.second<<"\n";
	}
	
	return 0;
}
