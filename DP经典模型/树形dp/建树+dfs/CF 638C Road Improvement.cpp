/*
题意:由一棵树构成的城市道路,现在要修路,同一天内
所修的道路不能相邻,问最少需要几天才能修完.其实侧重
的不是最少的天数,而是每天具体修哪条道路.
n<=200000.
链接:https://codeforces.ml/problemset/problem/638/C
思路:n<=20000,很明显树形dp,对于节点u与子节点相连的边
都不能在同一天修,因此依次编号为1,2,3..,在编号时要注意,
也不能与u的父节点相邻的边在同一天修,编号需不同,因此需要
记录每个节点u与父节点相连的边的编号.
*/
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200100
using namespace std;
int n,head[N],cnt,maxDay;
vector<int> ans[N];
struct Node{
    int to,next,id;
}edge[N<<1];

void addEdge(int from,int to,int id){
    edge[cnt]=(Node){to,head[from],id};
    head[from]=cnt++;
}

//day表示与父节点相连的边的编号
void dfs(int u,int fa,int day){
    int day0=0;//每次遍历day0都从第一天开始,对于u节点与子树相连的边的编号都从1,2,3..依次编号
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        day0++;
        if(day0 == day) day0++;//不能和其父节点的相邻边在同一天修,因此要放到下一天修
        ans[day0].push_back(edge[i].id);//小于day相邻边的,都从第一天修开始分配.
        dfs(v,u,day0);
    }
    maxDay=max(maxDay,day0);//记录最多修了多少天
}

int main(){
    int u,v;
    memset(head,-1,sizeof head);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v,i);
        addEdge(v,u,i);
    }
    dfs(1,0,-1);
    printf("%d\n",maxDay);
    for(int i=1;i<=maxDay;i++){
        printf("%d",ans[i].size());
        for(int j=0;j<ans[i].size();j++)
            printf(" %d",ans[i][j]);
        printf("\n");
    }
    return 0;
}
