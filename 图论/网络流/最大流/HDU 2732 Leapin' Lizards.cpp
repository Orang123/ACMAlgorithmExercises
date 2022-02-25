#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define N 1000
#define M 1600000
#define INF 0x3f3f3f3f
using namespace std;
//ac 0ms dinic
/*
题意:给你一个网格,网格上的一些位置('L')上有一只蜥蜴,所有蜥蜴的最大跳跃距离是d,
如果一只蜥蜴能跳出网格边缘,那么它就安全了.且每个网格有一个最大跳出次数x,
即最多有x只蜥蜴从这个网格跳出,这个网格就再也不能有蜥蜴进来了.问你最少有多
少只蜥蜴跳不出网格.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2732
思路:因为每个位置有最大跳出次数,所以直接爆搜需要枚举所有可能跳出位置的可能性,
记录最大能跳出网格的蜥蜴个数,这并不是一个多项式时间.现在可以将每个网格的点(i-1)*m+j,
拆点分为(i-1)*m+j和(i-1)*m+j+n*m两个点代表入点和出点,构造源点0,汇点n*m*2+1,每个'L'(有蜥蜴)
的点建0->(i-1)*m+j,容量为1(每个网格最多只能有一个蜥蜴),代表该点的蜥蜴能跳出当前网格,
入点到出点建容量为s1[i][j]-'0'的边,即:(i-1)*m+j->(i-1)*m+j+n*m,每个出点若能在跳跃距离
d之内跳出网格,则建立和汇点容量为INF的连边,即:(i-1)*m+j+n*m->n*m*2+1,否则建立能跳到的d距离
之内其余网格入点的连边,之后跑最大流就是最多有多少只蜥蜴能跳出网格,则答案就为原先所有蜥蜴数-最大流.

注意:任意时刻每个柱子上最多只有1只蜥蜴在上面,那么我们上面的解法会不会与这个要求冲突呢?
不会的,假设有k只蜥蜴能出去,那么一定存在一个符合上面要求的解,使得这k只蜥蜴按顺序出去,
在任意时刻每个柱子上最多只有1只蜥蜴.(假设在某个时刻,蜥蜴j想出去,它跳到了柱子h上,
但是柱子h上已经有蜥蜴了,那么这样就违反了上面的要求. 其实我们可以这么想,我们为什么不让
柱子h上的蜥蜴先按照蜥蜴j以前的逃跑路线出去,然后再让蜥蜴j到柱子h上去替代之前的蜥蜴,
那么这样既不违反规则,也得到了解)
*/
int cas,n,m,d,cnt,head[N],st,ed,dis[N],sum,ans;
char s1[30][30],s2[30][30];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed) return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow) break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    while(bfs(st))
        ans+=dfs(st,INF);
    return ans;
}

void init(){
    cas++;
    ans=sum=st=cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&d);
        for(int i=1;i<=n;i++){
            scanf("%s",s1[i]+1);
            if(i == 1){
                m=strlen(s1[1]+1);//m=网格有多少列
                ed=n*m*2+1;//汇点编号
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%s",s2[i]+1);
            for(int j=1;j<=m;j++){
                if(s2[i][j] == 'L'){//代表该点网格有蜥蜴
                    sum++;//记录个数
                    addEdge(0,(i-1)*m+j,1);//和源点建容量为1的边
                }
                if(s1[i][j] == '0') continue;//如果该网格最大跳出次数为0,则不建立入点和出点以及和汇点的连边
                addEdge((i-1)*m+j,(i-1)*m+j+n*m,s1[i][j]-'0');
                if(i+d>n || i-d<1 || j+d>m || j-d<1)//若当前点能在d距离内跳出网格,则建立出点到汇点的连边
                    addEdge((i-1)*m+j+n*m,ed,INF);
                else{//否则枚举该点d距离内能跳到的点,建立当前点出点到其余点入点的连边,容量为INF
                    for(int x=1;x<=n;x++){
                        for(int y=1;y<=m;y++){
                            if(s1[x][y] == '0') continue;
                            if(x == i && y == j) continue;
                            if(abs(x-i)+abs(y-j)<=d)//曼哈顿距离小于d则建边
                                addEdge((i-1)*m+j+n*m,(x-1)*m+y,INF);
                        }
                    }
                }
            }
        }
        max_flow();
        if(sum-ans == 0)
            printf("Case #%d: no lizard was left behind.\n",cas);
        else if(sum-ans == 1)
            printf("Case #%d: 1 lizard was left behind.\n",cas);
        else
            printf("Case #%d: %d lizards were left behind.\n",cas,sum-ans);
    }
    return 0;
}
