/*
题意:有一个由n个结点构成的有m条边的图，我没需要在某
几个点上放置河蟹，河蟹会占领该点上的所有边，相邻的河蟹
之间会发生冲突，我们需要让河蟹占领整个图。
1<=n<=10^4,1<=m<=10^5.
链接:https://www.luogu.com.cn/problem/P1330
思路:dfs,交叉染色,遇到环重复访问过的点判断是否会颜色相同,如果颜色不相同,
则会冲突,即:相邻边两端都会放置河蟹,如果颜色相同则不会冲突.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,ans,head[N],cnt,vis[N],color[N],sum[2];

struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int col){
    if(vis[u]){//当又遍历回之前染过色的点,判断现在的染色是否和当时一样,若不一样则 矛盾,一样正常退出
        if(color[u]!=col)
            return 0;
        return 1;
    }
    vis[u]=1;
    color[u]=col;//u点染色
    sum[col]++;//颜色数目+1
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfs(v,col^1)) return 0;//相邻点染色不能一样 否则就会矛盾 直接退出,重新遍历新的块
    }
    return 1;
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            memset(sum,0,sizeof(sum));
            if(dfs(i,1))
                ans+=min(sum[0],sum[1]);
            else{
                printf("Impossible\n");
                return 0;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

/*
并查集做法
#include<bits/stdc++.h>
using namespace std;
int f[10001],a,b,n,m,t[10001],bj[10001],h[10001],ans;
int find(int x)//模板函数；
{
    if(f[x]!=x) f[x]=find(f[x]);
    return f[x];
}
void xx(int x,int y)//判断函数；
{
    int qq=find(x);
    if(qq!=y)//如果他们父亲不相等将他们合并；
    {
        f[y]=qq;
        t[qq]+=t[y];
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        f[i]=i;
        t[i]=1;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        int x1=find(a),x2=find(b);
        if(x1!=x2)//相邻两点一定异色；
        {
            if(h[a]) xx(h[a],x2);//a的父亲节点一定
            //和a异色，一定和a的异色点同色，所以将他们
            //合并；
            if(h[b]) xx(h[b],x1);//同上；
            h[a]=x2;//h数组存a点异色点；
            h[b]=x1;//同上；
        }
        else//如果他们同色，表示不行；
        {
            cout<<"Impossible";
            return 0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        int q=find(i);
        if(!bj[q])//表示这个集合的答案还没被选过；
        {
            int q1=find(h[i]);
            bj[q]=1;
            bj[q1]=1;
            ans+=min(t[q],t[q1]);//两种情况最小值；
        }
    }
    cout<<ans;
    return 0;
}
*/
