/*
找边双
做法1
在请出Tarjan之前，我们先介绍另外一种做法：第一次dfs找出割边，然后第二次dfs在不经过割边的情况下遍历所有点，每一次遍历经过的一个子图就是一个边双。

做法2
用类似找点双的做法，但是栈里面压点，不压边。
*/

int dfn[maxn],low[maxn],belong[maxn],id=0,cnt=0;
int zhan[maxn],t=0;
void dfs(int x,int from)
{
	dfn[x]=low[x]=++id;zhan[++t]=x;
	for(int i=first[x];i;i=e[i].next)
	{
		if(i==(from^1))continue;
		int y=e[i].y;
		if(!dfn[y])
		{
			dfs(y,i);
			if(low[y]<low[x])low[x]=low[y];
		}
		else if(dfn[y]<low[x])low[x]=dfn[y];
	}
	if(dfn[x]==low[x])
	{
		cnt++; int xx;
		do{
			xx=zhan[t--];
			belong[xx]=cnt;
		}while(xx!=x);
	}
}
