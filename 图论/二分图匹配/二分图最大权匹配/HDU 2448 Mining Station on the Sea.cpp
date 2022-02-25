#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
#define INF 0x3f3f3f3f
using namespace std;
//ac 202ms floyd+最优匹配 slack数组优化
//港口和油井间只能建单向边 不知啥原因,双向边就会wa.
//还可用费用流解决
/*
//题意摘自网上
题意:现在有m个油井和n个港口(n<=m),现在有n条船停在这些油井这里,
第一行输入n个数,输入pos[i]代表第i条船停在pos[i]这个油井这里,
然后接下来有k行,输入u,v,w代表油井u和油井v之间的距离为w,然后又p行,
代表了港口和油井之间的距离,现在这些船全部要回到港口,而且每个港口
只能停一艘船,问这些船返回港口的最短距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2448
思路:就是所有的船和港口的完美匹配最小权问题,首先船要到达港口必须
通过油井和港口之间设置的道路才能抵达,而每个油井和油井之间也有道路相连,
而船停在油井,因为每个油井和各个港口的连接道路长度都不同,也不一定和每个
港口都有道路连接,船如果要到达某个港口距离最短,可能需要从一个油井i先到
达另一个油井j,然后再从油井j到达某个港口,所以这个问题可以转化为所有的油
井和港口之间多源顶点对间的最短距离,可以类似建立分层图最短路,将港口作为
第1层编号1~n,油井作为第2层编号1+n~m+n,港口和油井间连边建立为港口到油井
的单向边,但实际对于这题港口到油井建立成双向边结果应该也是不会错的,不知
何原因,建双向边就会wa,floyd求分层图各个顶点对建最短距离,然后建新的二分图
G[i][j],i表示港口(X集合),j表示船(Y集合),而对应原先的分层图就是mp[i][pos[j]+n],
pos[j]时船开始所在油井编号,pos[j]+n是其第二层油井实际的编号.建立负权KM求解最小权和既可.
*/
int n,m,k,p,mp[N+M][N+M],G[N][N],pos[N],match[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == -INF|| visy[v]) continue;//不加mp[u][v] == -INF 贪心选最小差值也能保证结果正确性
        int tp=lx[u]+ly[v]-G[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=-INF;
        ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],G[i][j]);
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=G[match[i]][i];
    }
    return ans;
}

void floyd(int num){
    for(int k=1;k<=num;k++){
        for(int i=1;i<=num;i++){
            if(mp[i][k] == INF) continue;
            for(int j=1;j<=num;j++){
                if(mp[i][j]>mp[i][k]+mp[k][j])
                    mp[i][j]=mp[i][k]+mp[k][j];
            }
        }
    }
}

void init(int num){
    memset(match,0,sizeof(match));
    for(int i=1;i<=num;i++){
        for(int j=1;j<=num;j++)
            mp[i][j]=(i==j?0:INF);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d%d",&n,&m,&k,&p)!=EOF){//n个港口、船 m个油井
        init(n+m);
        for(int i=1;i<=n;i++)
            scanf("%d",&pos[i]);
        while(k--){//油井间双向道路
            scanf("%d%d%d",&u,&v,&w);
            mp[u+n][v+n]=mp[v+n][u+n]=w;//油井编号1+n~m+n
        }
        while(p--){//港口和油井间单向道路 港口u->油井v+n,但实际建双向道路也不应该wa啊,不知何原因.
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v+n]=w;//港口编号1~n 对应G[i][j]=-mp[i][pos[j]+n];
            //mp[v+n][u]=w//对应G[i][j]=-mp[pos[i]+n][j]
        }
        floyd(n+m);//求解分层图多个顶点对建最短距离
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                /*
                港口和油井只能建mp[u][v+n]=w的单向边,不知何原因,mp[u][v+n]=mp[v+n][u]=w 会wa,
                类似于分层图,层间的连接边之所以单向是因为使用一次免费机会,不可再回到之前的状态,
                但这个题没这个意图,而且G[i][j] 只会用到mp[i][pos[j]+n],这个很明显是不会有港口到港口标号都<=n的点的.
                */
                G[i][j]=-mp[i][pos[j]+n];
                //G[i][j]=-mp[pos[i]+n][j];//港口和油井只能建mp[v+n][u]=w的单向边,不知何原因
        }
        printf("%d\n",-KM());
    }
    return 0;
}
