//ac 15ms 二维完全背包
//dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t])
/*
题意:最近xhd正在玩一款叫做FATE的游戏,为了得到极品装备,xhd在不停的杀怪做任务.
久而久之xhd开始对杀怪产生的厌恶感,但又不得不通过杀怪来升完这最后一级.现在的问题是,
xhd升掉最后一级还需n的经验值,xhd还留有m的忍耐度,每杀一个怪xhd会得到相应的经验a[i],并减掉相应的忍耐度b[i].
当忍耐度降到0或者0以下时,xhd就不会玩这游戏.xhd还说了他最多只杀s只怪,请问他能升掉这最后一级吗？
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2159
思路:每种怪物可以杀多个,显然完全背包,但又两个费用维度的限制一个是杀个怪物个数一个是忍耐度,
将经验值作为要求解的最优值.初始状态,恰好装满背包或尽可能多地装满背包都可解.
dp[t][i][j]表示前t种怪物在最多能杀i个所减少忍耐度为j时能获得的最大经验值
dp[t][i+1][j+b[t]]=max(dp[t-1][i+1][j+b[t]],dp[t][i][j]+a[t]);
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;//因为最多能杀s个怪物,而所减少的忍耐度是恰好装满的,所以初始状态是dp[0..s][0]=0
        for(int t=1;t<=k;t++){
            for(int i=0;i<s;i++){//i+1最多只能杀s个怪物,因此i的上界是s-1
                for(int j=0;j+b[t]<=m;j++){//能减少的忍耐度最多是m
                    if(dp[i][j]<0) continue;
                    dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){//这里正序逆序都可,只是逆序要判断到最后m=1的时候才结束
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 686ms 暴力枚举dfs搜索+剪枝
//不设置dp[N][N]状态的最优决策会tle
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k代表在杀怪数为i,减少的忍耐度为j时最多能获得经验值为k.
//如果将dp[i][j]=k表示为获得经验值i,减少忍耐度j时的最少杀怪数为k,这样搜索就会tle.因为剪枝不能从dp的2个维度去剪枝
int n,m,k,s,a[N],b[N],dp[N][N],ans;

void dfs(int num,int sumb,int suma){
    //n m 最大也只有100,而每种怪物的较少的忍耐度最高可达20,这个剪枝就比较高效
    if(num>s || sumb>m)//剪枝1
        return;
    //如果当前的状态获得经验值不能比之前搜索过同等状态下的最优值更优 则不必重复搜索下去
    if(suma<=dp[num][sumb])//剪枝2(必须要,要不会tle)
        return;
    dp[num][sumb]=suma;
    if(suma>=n)
        ans=max(ans,m-sumb);
    for(int i=1;i<=k;i++)
        dfs(num+1,sumb+b[i],suma+a[i]);
}

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        ans=-1;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=-1;
        dfs(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 327ms bfs广度搜索枚举状态
//bfs也基本是类似的,剪枝和dfs是相同的,如果当前状态不能比之前的更优就不入队
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
using namespace std;

//dp[i][j]=k代表在杀怪数为i,减少的忍耐度为j时最多能获得经验值为k.
//如果将dp[i][j]=k表示为获得经验值i,减少忍耐度j时的最少杀怪数为k,这样搜索就会tle.因为剪枝不能从dp的2个维度去剪枝
int n,m,k,s,a[N],b[N],dp[N][N],ans;

struct State{
    int num,sumb,suma;
    State(int num=0,int sumb=0,int suma=0):num(num),sumb(sumb),suma(suma){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.suma>=n)
            ans=max(ans,m-tp.sumb);
        Q.pop();
        for(int i=1;i<=k;i++){
            if(tp.num+1>s || tp.sumb+b[i]>m)
                continue;
            if(tp.suma+a[i]<=dp[tp.num+1][tp.sumb+b[i]])
                continue;
            Q.push(State(tp.num+1,tp.sumb+b[i],tp.suma+a[i]));
            dp[tp.num+1][tp.sumb+b[i]]=tp.suma+a[i];
        }
    }
}

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        ans=-1;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=-1;
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms
//dp[t][i][j]表示前t种怪物不限制每种杀的个数在最多能杀i个所剩忍耐度为j时能获得的最大经验值
//dp[i+1][j-b[t]]=max(dp[i+1][j-b[t]],dp[i][j]+a[t]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][m]=0;
        for(int t=1;t<=k;t++){
            for(int i=0;i<s;i++){
                for(int j=m;j>=b[t];j--){
                    if(dp[i][j]<0) continue;
                    dp[i+1][j-b[t]]=max(dp[i+1][j-b[t]],dp[i][j]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=m-1;i>=0;i--){
            if(dp[s][i]>=n){
                ans=i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 46ms
//dp[t][i][j]表示在前t种怪物中杀怪所得经验为i,所减少忍耐度为j时所能杀的最少的怪物个数
//dp[t][i+a[t]][j+b[t]]=min(dp[t-1][i+a[t]][j+b[t]],dp[t][i][j]+1);
//这个做法的状态转移方程如果写成这样dp[t][i][j]]=min(dp[t-1][i][j],dp[t][i-a[t]][j-b[t]]+1)
//就不能确定实际获得价值超过n,超过了多少,当然可以定义n的上界为n+30,因为超过的情况最多是超过20
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100//杀怪最多能获得的经验值是 假设每个怪物减少的忍耐度都是1,100种怪物每个怪物的经验值都是20,那么实际能杀100个经验值为20的怪物,即:100*20=2000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[M][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=0;//只有一个怪物没有杀 经验值和忍耐度没减少时才是合法状态
        for(int t=1;t<=k;t++){
        	//杀怪获得经验值可以超过n,但是dp状态在刚超过后,就不再继续杀怪,
			//因为继续杀怪忍耐度只会不断下降,而此时获得的经验值已经达到了要求.
			//因此i的上界如果已经达到了n,就不再从n接着转移使得经验值再增大.
            for(int i=0;i<n;i++){
                for(int j=0;j+b[t]<=m;j++){
                    if(dp[i][j] == INF) continue;
                    //如果不杀第i种怪物,那么杀怪个数就是dp[t-1][i+a[t]][j+b[t]] 前t-1种怪物时的杀怪数
					//如果杀第i种怪物,杀怪个数就是dp[t][i][j]+1,就是在前t种怪物杀怪基础上再杀一个第t种怪物,决策方案是满足经验值和忍耐度的最小杀怪数.
                    dp[i+a[t]][j+b[t]]=min(dp[i+a[t]][j+b[t]],dp[i][j]+1);
                }
            }
        }
        int flag=0,ans=-1;
        for(int i=n;i<M;i++){//实际最多能保留的忍耐度 可能获得经验值超过n 因此需要考虑所有情况 求取最大保留忍耐度
            for(int j=1;j<=m;j++){
                if(dp[i][j]!=INF && dp[i][j]<=s)
                    ans=max(ans,m-j);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms 二维完全背包
//dp[t][i][j]表示前t种怪物在最多能杀i个所减少忍耐度为j时能获得的最大经验值
//dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int t=1;t<=k;t++){
            for(int i=1;i<=s;i++){//最多杀s个怪物 i的上界是s
                for(int j=b[t];j<=m;j++){//对第i种怪物能减少的忍耐度至少是b[t],j的下界是b[t]
                    if(dp[i-1][j-b[t]]<0) continue;
                    dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 46ms dp时 s、j在前两层循环 物品种类在第三层循环
//dp[t][i][j]表示前t种怪物在最多能杀i个所减少忍耐度为j时能获得的最大经验值
//dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int i=1;i<=s;i++){
            for(int j=0;j<=m;j++){
                for(int t=1;t<=k;t++){
                    if(j<b[t] ||dp[i-1][j-b[t]]<0) continue;
                    dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t]);
				}
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms dp时 s、j在前两层循环 物品种类在第三层循环
//dp[t][i][j]表示前t种怪物在最多能杀i个所减少忍耐度为j时能获得的最大经验值
//dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int i=0;i<s;i++){
            for(int j=0;j<=m;j++){
                for(int t=1;t<=k;t++){
                    if(j+b[t]>m ||dp[i][j]<0) continue;
                    dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t]);
				}
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
