#include<cstdio>
#include<cstring>
#include<vector>
#define N 350
using namespace std;
//ac 16ms
/*
题意:n门课程,一周7天,每天可以开设12门课,现在如何
安排课程的排放时间使得不同课程间时间不冲突,同时李明
所能在一周内选的课程数最多.
链接:http://poj.org/problem?id=2239
思路:可以将n门课程作为左集合,课程的安排时间次序作为
右集合,每门课程可开放的时间和对应的时间次序连边,要使得
课程安排没有冲突,显然连边不能有公共点,并且要使得所能选的
课程数最多,就是求解最大匹配.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int a,b;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){//课程i
            scanf("%d",&m);//课程i可安置在m个时间段内
            while(m--){
                scanf("%d%d",&a,&b);//a-天数,b-这天内第几门课
                G[i].push_back((a-1)*12+b);//一天可开设12门课,所以课程编号就为(a-1)*12+b
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
