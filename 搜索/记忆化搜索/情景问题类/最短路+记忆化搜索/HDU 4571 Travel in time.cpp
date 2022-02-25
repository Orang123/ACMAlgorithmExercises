/*
题意:摘自网上
n个城市，m条路，总时间t，起始城市st，终点城市ed
接下来给出各个城市的浏览时间c[i]，各个城市浏览后的满意程度s[i]。
然后是m条路的信息。要求一个浏览顺序，使得总的满意程度最大，
然后经过一个城市可以选择不去浏览，当前浏览城市的满意度一定要
比前一个浏览城市的满意度高，并且最终要回到城市e。
1<n<100,0<M<1000,0<t<=300,0<=c[i]<=t,0<=s[i]<=100.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4571
思路:对于一个城市可以经过但不浏览,不浏览就不会获得满意程度,那么
满意程度仍然是前一个浏览的城市的满意度,可以floyd预处理出所有城市
间通行花费的时间,实际要想满意度最大,就是要尽可能多地浏览城市,而
浏览城市的结束状态是
1.当满意度不能继续增大
2.或当前浏览的城市在剩余时间k下无法回到终点ed
而且到达当前点影响后续搜索的因素有 上一个城市的满意度和剩余的时间.
因此记忆化搜索,dp[i][j][k]表示到达i点浏览的满意度为j,剩余时间为k时
浏览后续城市并且能回到ed点能获得的最大满意度.
*/
//ac 780ms floyd+记忆化搜索
//dp[i][j][k]表示到达i点浏览的满意度为j,剩余时间为k时浏览后续城市并且能回到ed点能获得的最大满意度.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 310
#define INF -0x3f3f3f3f
using namespace std;

int n,m,t,st,ed,c[N],s[N],dp[N][N][M],dis[N][N];

void floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    }
}

int dfs(int i,int j,int k){
    int &ans=dp[i][j][k];
    if(ans!=-1)
        return ans;
    if(dis[i][ed]>k)//剩下的时间t无法从i点回到ed 返回不合法状态
        return ans=INF;
    ans=0;
    for(int v=0;v<n;v++){//枚举要浏览第v个城市 获取其满意度
        if(s[v]<=j)//满意度不增加
            continue;
        int res=dfs(v,s[v],k-dis[i][v]-c[v]);//dis[i][v]可能中间还经过了别的点但是 不浏览 并不获取其满意度
        if(res!=INF)
            ans=max(ans,res+s[v]);
    }
    //当ans=0时 就是无法再继续浏览下去结束状态了,可能是满意度不再增大,可能是要浏览的城市剩余时间都无法回到ed点
    return ans;
}

int main(){
    int w,u,v,d;
    scanf("%d",&w);
    for(int cas=1;cas<=w;cas++){
        scanf("%d%d%d%d%d",&n,&m,&t,&st,&ed);
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<n;i++)
            scanf("%d",&c[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&s[i]);
        memset(dis,0x3f,sizeof(dis));
        for(int i=0;i<n;i++)
            dis[i][i]=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&d);
            dis[u][v]=dis[v][u]=min(dis[u][v],d);
        }
        floyd();
        printf("Case #%d:\n",cas);
        if(dfs(st,0,t)!=INF)
            printf("%d\n",dp[st][0][t]);
        else
            printf("0\n");
    }
    return 0;
}
