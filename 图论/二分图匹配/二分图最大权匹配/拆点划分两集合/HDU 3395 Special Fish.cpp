#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//ac 78ms slack数组松弛优化
//还可用最大费用流来做
/*
题意:n只鱼,每种鱼都会认为自己是雄性,它会去攻击它认为是
雌性的鱼,而且每条鱼只可被攻击一次,也只能攻击别的鱼一次,
注意不管一条鱼被攻击与否,它仍然可以尝试攻击另一条被它
认为是雌性的鱼,即即使一条鱼被攻击,它也仍然可以攻击它认为是
雌性的鱼,每条鱼被攻击后,会产一些卵,一次攻击所产卵的数量是
攻击与被攻击的鱼的值相异或值,现在要求出所有可能攻击后所能
产卵的最大数量.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3395
思路:一条鱼有两种状态(拆点),攻击与被攻击,可以将n条鱼攻击作为一个集合,
n条鱼被攻击作为一个集合,因为每条鱼只可被攻击一次,也只能攻击别的
鱼一次,那么所有的攻击显然构成了匹配,而攻击所产生的卵的数量就为
这个匹配的边权,现在问题转化为了求解最大匹配权值和.输入为一个存储
矩阵,其中自己不能攻击自己,所以对角线为0,当mp[i][j]=1时,就代表鱼i
认为鱼j为雌性,鱼i可攻击鱼j,设置mp[i][j]=val[i]^val[j].但是在跑
匈牙利时,是仍然按照X集合每个点和Y集合每个点有连边,因为实际不能攻击
的边权也是0,这样能保证KM算法X集合中的点永远能和Y集合中点匹配,对于
实际不存在的匹配,因为边权为0,结果也不受影响,可避免KM死循环
(因为实际可能存在某个鱼不能攻击别的鱼,找不到匹配的现象).但是不知为何,
如果只考虑存在边 即在dfs离判断if(!mp[u][v]) continue,就会TLE,目测是KM
X集合点找不到匹配点进入死循环.
*/
int n,val[N],mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;//这里实际处理是X集合每个点均和Y集合中每个点有连边,实际不存在的边,边权为0,结果不影响,可以避免KM死循环
        int tp=lx[u]+ly[v]-mp[u][v];
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
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
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
                else slack[j]-=d;//实际没有slack[j]-=d这个操作也能78ms ac
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    char x[N];
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            scanf("%s",x+1);
            for(int j=1;j<=n;j++){
                if(x[j]!='0')//代表鱼i可攻击鱼j,权值为i j值的异或值
                    mp[i][j]=val[i]^val[j];
                else
                    //不存在的边权设置为0,匹配边权和结果不受影响,这样可保证KM算法 X集合每个点都能找到Y中匹配点,避免死循环
                    mp[i][j]=0;
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}

/*
//ac 62ms 最小差值d放在dfs里求解
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,val[N],mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    char x[N];
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            scanf("%s",x+1);
            for(int j=1;j<=n;j++){
                if(x[j]!='0')
                    mp[i][j]=val[i]^val[j];
                else
                    mp[i][j]=0;
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}
*/

/*
//ac 109ms 最小差值d放在KM while(1)循环内,两层for循环求解
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,val[N],mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visx[j]) continue;
                for(int k=1;k<=n;k++)
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    char x[N];
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            scanf("%s",x+1);
            for(int j=1;j<=n;j++){
                if(x[j]!='0')
                    mp[i][j]=val[i]^val[j];
                else
                    mp[i][j]=0;
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}
*/

/*
最大费用流 貌似是最大费用可行流
*/

/*
//TLE 不考虑 mp[u][v]是否存在,即不存在边也考虑匹配,因为边权是0,也不会影响结果,但是dfs不考虑不存边在边就会 TLE 不知道啥原因
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,val[N],mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(!mp[u][v] || visy[v]) continue;//这里如果不考虑 mp[u][v]是否存在,即不存在边也考虑匹配,因为边权是0,也不会影响结果,但是dfs不考虑不存边在边就会 TLE
        int tp=lx[u]+ly[v]-mp[u][v];
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
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++){
            if(mp[i][j])
                lx[i]=max(lx[i],mp[i][j]);
        }
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
            if(d == INF) break;
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
        ans+=mp[match[i]][i];
    }
    return ans;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    char x;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x!='0')
                    mp[i][j]=val[i]^val[j];
                else
                    mp[i][j]=0;
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}
*/
