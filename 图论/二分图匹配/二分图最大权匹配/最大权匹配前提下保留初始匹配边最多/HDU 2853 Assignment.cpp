#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//ac 0ms 最优匹配 slack数组优化
/*
题意:n个部队,每个任务,m>=n,一个部队只能得到一个任务,
一个任务只能分配给一个部队,每个部队执行每个任务有对应的
效率值,现在要求出每个部队都分配任务下的最大执行效率值总和,
因为每个部队初始时有原始分配的任务,还要使得改变原始任务的数量
最少,输出最少改变的原始任务数量和最终最大能提高的效率值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2853
思路:很明显是二分图最大权匹配,可用KM算法求解,只是要在权值和最大
条件下,尽可能采用原始匹配任务,这样改变初始匹配数目更少.
可以将初始匹配边权扩大(n+1)倍再+1,其余边权扩大(n+1)倍.因为只有这样,
当初始匹配边权和别的边权相等时,因为初始匹配边权扩大(n+1)倍后多加1,那么扩大后的初始边权就大一点,
KM算法配对时就会优先选择初始边作为可行边加入;当初始匹配边权和别的边权不等时,
那么扩大(n+1)倍后,初始匹配边权再加1,大小关系依旧是没扩大之前的关系,结果也不受影响,
而之所以加1,如果加的值过大,可能会影响扩大后大小关系改变,这样最终求出的结果就会出错.
这样KM算法求出最大权匹配ans后,其权值和可以提取出公因子(n+1),那么ans%(n+1),
所求得的余数就是维持原先初始匹配边不变的数目,之所以要取余(n+1),是因为这里
即使KM求出最大匹配所有匹配边依旧是原先初始匹配,也最多有n个1多余,这样对(n+1)取余
结果还是n,如果取余小于n,结果就会出错.而改变边数目就为n-ans%(n+1).
而ans/(n+1),因为是整除,结果就是KM求解出的就是正常权值的最大权匹配,
这里之所以除(n+1),是因为即使n个部队依旧采用初始匹配,那也只会多出n,而n/(n+1)=0,
并不会影响正常结果,所以最终增加的效率总和就是res-ans/(n+1),res为初试匹配任务的
效率值和.
*/
int n,m,link[N],visx[N],visy[N];
ll tp[N][N],mp[N][N],lx[N],ly[N],slack[N],d,res,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=m;v++){
        if(visy[v]) continue;
        ll tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!link[v] || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=0;
        for(int j=1;j<=m;j++){
            lx[i]=max(lx[i],mp[i][j]);
            ly[j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=m;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j])
                    lx[j]-=d;
            }
            for(int j=1;j<=m;j++){
                if(visy[j])
                    ly[j]+=d;
                else
                    slack[j]-=d;//不加这个 会变成15ms 实际也不懂为啥要操作这个
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(!link[i]) continue;
        ans+=mp[link[i]][i];
    }

}

void init(){
    ans=res=0;
    memset(link,0,sizeof(link));
}

int main(){
    int v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%lld",&mp[i][j]);
                tp[i][j]=mp[i][j];
                mp[i][j]*=(n+1);//所有边权扩大(n+1)倍
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&v);
            res+=tp[i][v];//res是初试匹配任务效率值和
            mp[i][v]++;//初试匹配任务边权扩大(n+1)倍后,为方便取余、相除,还需再加1
        }
        KM();
        //ans%(n+1)原先初始匹配边数目 ans/(n+1)最大权匹配
        printf("%lld %lld\n",n-ans%(n+1),ans/(n+1)-res);
    }
    return 0;
}

/*
//ac 15ms 最小差值d放在匈牙利dfs里求解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,link[N],visx[N],visy[N];
ll tp[N][N],mp[N][N],lx[N],ly[N],d,res,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=m;v++){
        if(visy[v]) continue;
        ll tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!link[v] || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=0;
        for(int j=1;j<=m;j++){
            lx[i]=max(lx[i],mp[i][j]);
            ly[j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(visx[j])
                    lx[j]-=d;
            }
            for(int j=1;j<=m;j++){
                if(visy[j])
                    ly[j]+=d;
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(!link[i]) continue;
        ans+=mp[link[i]][i];
    }

}

void init(){
    ans=res=0;
    memset(link,0,sizeof(link));
}

int main(){
    int v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%lld",&mp[i][j]);
                tp[i][j]=mp[i][j];
                mp[i][j]*=(n+1);
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&v);
            res+=tp[i][v];
            mp[i][v]++;
        }
        KM();
        printf("%lld %lld\n",n-ans%(n+1),ans/(n+1)-res);
    }
    return 0;
}
*/

/*
//ac 15ms 最小差值d放在KM while(1)里求解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,link[N],visx[N],visy[N];
ll tp[N][N],mp[N][N],lx[N],ly[N],d,res,ans;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=m;v++){
        if(visy[v]) continue;
        ll tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!link[v] || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=0;
        for(int j=1;j<=m;j++){
            lx[i]=max(lx[i],mp[i][j]);
            ly[j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visx[j]) continue;
                for(int k=1;k<=m;k++){
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
                }
            }
            for(int j=1;j<=n;j++){
                if(visx[j])
                    lx[j]-=d;
            }
            for(int j=1;j<=m;j++){
                if(visy[j])
                    ly[j]+=d;
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(!link[i]) continue;
        ans+=mp[link[i]][i];
    }

}

void init(){
    ans=res=0;
    memset(link,0,sizeof(link));
}

int main(){
    int v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%lld",&mp[i][j]);
                tp[i][j]=mp[i][j];
                mp[i][j]*=(n+1);
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&v);
            res+=tp[i][v];
            mp[i][v]++;
        }
        KM();
        printf("%lld %lld\n",n-ans%(n+1),ans/(n+1)-res);
    }
    return 0;
}
*/
