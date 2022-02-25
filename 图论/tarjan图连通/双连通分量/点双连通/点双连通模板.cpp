/*
找点双
这个时候就要请出伟大的 Tarjan 了！
我们依然考虑使用上面的 d f n dfndfn 和 l o w lowlow 来求，我们将深搜时遇到的所有边加入到栈里面，
当找到一个割点的时候，就将这个割点往下走到的所有边弹出，而这些边所连接的点就是一个点双了。
*/
int dfn[maxn],low[maxn],id,t;
edge zhan[(maxn*maxn)<<1];//存边的栈
int belong[maxn],cnt;//belong记录每个点属于哪一个点双，cnt记录点双个数
bool cut[maxn];
set<int> s[maxn];//记录每个点双包含哪些点，如果题目不需要也可以不求
void dfs(int x,int from)
{
	dfn[x]=low[x]=++id; int son=0;
	for(int i=first[x];i;i=e[i].next)
	{
		if(i==(from^1))continue;
		int y=e[i].y;
		if(!dfn[y])
		{
			zhan[++t]=e[i]; dfs(y,i); son++;//先压栈再遍历
			if(low[y]<low[x])low[x]=low[y];
			if(low[y]>=dfn[x])//发现x是割点
			{
				cnt++; edge xx; cut[x]=true;
				do{
					xx=zhan[t--];//弹出
					belong[xx.x]=belong[xx.y]=cnt;//标记
					s[cnt].insert(xx.x);s[cnt].insert(xx.y);//记录
				}while(xx.x!=x||xx.y!=y);//假如已经弹到 x到y 这条边了，就停下来
			}
		}
		else if(dfn[y]<low[x])low[x]=dfn[y];
	}
	if(from==-1&&son==1)cut[x]=false;
}
