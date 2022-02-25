/*
题意:一颗n个节点的苹果树,每个节点上都有val[i]个苹果,当你经过这个点时就能获得
这个节点的所有苹果,重复走相同节点,这个节点的苹果也只能取一次,问你走k步限制内
能得到的最多苹果数.从节点1出发.
n<=100,k<=200,val[i]<=1000.
链接:http://poj.org/problem?id=2486
思路:要遍历更多的点,先遍历的分支必然会返回去再重复走一遍,只有最后一个分支只遍历一遍.
所以需要枚举每个点出发是否回到这个点与不会到这个点的情况.背包容量为步数限制k.
dp[i][j][0/1]表示以i为根节点的子树根节点i出发在长度j限制下最多能遍历子树节点权值和.
dp[i][j][0]表示不返回i点,dp[i][j][1]表示返回i点.
因为可能总边数小于k步限制,所以要尽可能多地装满背包,因此初始状态dp[i][0..k]=val[i].

dp[i][j][0/1]不能表示从以i为根节点的子树i点出发经过节点的权值和恰好为j时最少走过的距离.
为每个点的权值最大可达1000,所以权值和作为背包容量会炸,时间、空间复杂度会炸.
时间复杂度O(n*M^2)=100*10^5*10^5=10^12
空间复杂度O(n*m)=100*10^5=10^7
*/
//ac 63ms
//时间复杂度O(n*k^2)=100*200^2=4*10^6
//空间复杂度O(nk)=100*200=20000
//dp[i][j][0/1]表示以i为根节点的子树根节点i出发在长度j限制下最多能遍历子树节点权值和.
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-1][1]+dp[v][t][0]);
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-2][0]+dp[v][t][1]);
//dp[u][j][1]=max(dp[u][j][1],dp[u][j-t-2][1]+dp[v][t][1]);
//尽可能多地装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=1;j--){
            for(int t=0;t<=j-1;t++){
                //dp的决策是
                //1.在能遍历节点数相同的情况下,尽量选择路径距离较小的分支去遍历
                //2.以及最后走哪一个分支只走一遍路径长度,总体所走距离较短.其余分支实际都走了两遍.
                //3.所选节点的权值尽可能大
                //这样在k长度下才能将经过的点的权值和尽可能大
                //v子树不返回v点,u遍历的兄弟子树要返回u点,少走u->v 1步
                dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-1][1]+dp[v][t][0]);
                if(j-t-2>=0)
                    //v子树返回v点,u遍历的兄弟子树要不返回u点,先走的v子树每条边走了两遍,再走的u的其它兄弟子树,少走u->v v->u 2步
                    dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-2][0]+dp[v][t][1]);
                if(j-t-2>=0)
                    //v子树返回v点,u遍历的兄弟子树要返回u点,不区分先走哪个子树,不管走哪个每条边都得走两遍,少走u->v v->u 2步
                    dp[u][j][1]=max(dp[u][j][1],dp[u][j-t-2][1]+dp[v][t][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        //注意 起点是会影响实际k步限制内的结果的 题目要求从1节点出发
        dfs(1,-1);
        //k步限制内不返回获得的权值和肯定较大 只需输出dp[1][k][0] 不返回根节点1的即可 无需考虑返回根节点1的dp[1][k][1]
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}

/*
//ac 63ms 另一种转移方式
//dp[i][j][0/1]表示以i为根节点的子树根节点i出发在长度j限制下最多能遍历子树节点权值和.
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][1]+dp[v][t-1][0]);
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][0]+dp[v][t-2][1]);
//dp[u][j][1]=max(dp[u][j][1],dp[u][j-t][1]+dp[v][t-2][1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=1;j--){
            for(int t=1;t<=j;t++){
                dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][1]+dp[v][t-1][0]);
                if(t-2>=0)
                    dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][0]+dp[v][t-2][1]);
                if(t-2>=0)
                    dp[u][j][1]=max(dp[u][j][1],dp[u][j-t][1]+dp[v][t-2][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}
*/

/*
//ac 79ms 另一种转移方式
//dp[i][j][0/1]表示以i为根节点的子树根节点i出发在长度j限制下最多能遍历子树节点权值和.
//dp[u][j+t+1][0]=max(dp[u][j+t+1][0],dp[u][j][1]+dp[v][t][0]);
//dp[u][j+t+2][0]=max(dp[u][j+t+2][0],dp[u][j][0]+dp[v][t][1]);
//dp[u][j+t+2][1]=max(dp[u][j+t+2][1],dp[u][j][1]+dp[v][t][1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=0;j--){
            for(int t=0;t+j+1<=k;t++){
                dp[u][j+t+1][0]=max(dp[u][j+t+1][0],dp[u][j][1]+dp[v][t][0]);
                if(t+j+2<=k)
                    dp[u][j+t+2][0]=max(dp[u][j+t+2][0],dp[u][j][0]+dp[v][t][1]);
                if(t+j+2<=k)
                    dp[u][j+t+2][1]=max(dp[u][j+t+2][1],dp[u][j][1]+dp[v][t][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}
*/

/*
//MLE TLE 因为每个点的权值最大可达1000
//所以权值和作为背包容量会炸
//时间复杂度O(n*M^2)=100*10^5*10^5=10^12
//空间复杂度O(n*m)=100*10^5=10^7
//siz[i]表示以i为根节点的子树所有节点的权值和(包括i点)
//dp[i][j][0/1]表示从以i为根节点的子树i点出发经过的节点的权值和恰好为j时(不回到i点或回到i点)最少走过的距离.
//dp[i][j][0]表示不回到i点,dp[i][j][1]表示回到i点.
//恰好装满背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

int cnt,head[N],n,k,val[N],siz[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
	dp[u][val[u]][0]=dp[u][val[u]][1]=0;
	siz[u]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //实际这里有依赖关系,考虑v必然是已经走到u点了,那必须保证先拿了u点的权值,才能拿v点的权值
		//因此j下限val[u],t下限val[v]
        for(int j=siz[u];j>=val[u];j--){
            for(int t=val[v];t<=siz[v];t++){
                dp[u][j+t][0]=min(dp[u][j+t][0],dp[u][j][1]+dp[v][t][0]+1);
                dp[u][j+t][0]=min(dp[u][j+t][0],dp[u][j][0]+dp[v][t][1]+2);
                dp[u][j+t][1]=min(dp[u][j+t][1],dp[u][j][1]+dp[v][t][1]+2);
            }
        }
        siz[u]+=siz[v];
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        memset(dp,0x3f,sizeof(dp));
        dfs(1,-1);
        //1节点权值和 降序 只要步数不超过k即合法 输出最大权值和
        for(int i=siz[1];i>=0;i--){
            //不返回的步数肯定较小 只需判断dp[1][i][0] 不返回根节点1的
        	if(dp[1][i][0]<=k){
        		printf("%d\n",i);
        		break;
			}
		}
    }
    return 0;
}
*/
