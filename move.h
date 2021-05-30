#include<bits/stdc++.h>
using namespace std;

int ang[8]={0,45,90,135,180,225,270,315};

map<pair<int,int>,int>m;
map<pair<int,int>,int>n;

struct ant{
	int x=100;
	int y=100;
	vector<pair<int,int>>path;
	bool food=0;
	int index=-1;
	stack<pair<int,int>>s;
	map<pair<int,int>,int>visit;
	ant()
	{
		random_shuffle(ang,ang+7);
		path.push_back({x,y});
		s.push({100,100});
	}
};
pair<int,int>newcor(int x, int y, int angle)
{
	if(angle==0)
	{
		x++;
	}
	else if(angle==45)
	{
		x++;
		y--;
	}
	else if(angle==90)
	{
		y--;
	}
	else if(angle==135)
	{
		x--;
		y--;
	}
	else if(angle==180)
	{
		x--;
	}
	else if(angle==225)
	{
		x--;
		y++;
	}
	else if(angle==270)
	{
		y++;
	}
	else if(angle==315)
	{
		x++;
		y++;
	}
	return {x,y};
}
void angle_sel(ant &p)
{
	random_shuffle(ang,ang+8);
	pair<int,int>cur=p.s.top();
	if(p.visit[cur]==1)
	{
		p.x=cur.first;
		p.y=cur.second;
		p.s.pop();
	}
	else
	{
		p.visit[cur]=1;
		for(int i=0;i<8;++i)
		{
			pair<int,int>cur1=newcor(cur.first,cur.second,ang[i]);
			if(p.visit[cur1]==0 && cur1.first>=0 && cur1.second>=0 && cur1.first<1200 && cur1.second<1000) p.s.push(cur1);
		}
		cur=p.s.top();
		p.x=cur.first;
		p.y=cur.second;
	}
	if(p.food==1)
	{
		--p.index;
		p.x=p.path[p.index].first;
		p.y=p.path[p.index].second;
	}
	if(m[{p.x,p.y}]==1)
	{
		p.food=1;
		p.index=p.path.size();
		m[{p.x,p.y}]=0;
	}
	else if(n[{p.x,p.y}]==1)
	{
		p.food=0;
		p.path.clear();
		p.path.push_back({p.x,p.y});
	}
	else
	{
		p.path.push_back({p.x,p.y});
	}
}

void init_food(int x,int y,int w,int h)
{
	for(int i=x;i<w+x;i++)
	{
		for(int j=y;j<y+h;j++)
		{
			m[{i,j}]=1;
		}
	}
}

void init_home(int x,int y,int w,int h)
{
	for(int i=x;i<w+x;i++)
	{
		for(int j=y;j<y+h;j++)
		{
			n[{i,j}]=1;
		}
	}
}
