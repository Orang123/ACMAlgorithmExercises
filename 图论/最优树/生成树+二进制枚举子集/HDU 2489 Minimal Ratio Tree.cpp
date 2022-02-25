#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 20
#define M 400
using namespace std;
//15ms 数据比较水,只按比率排序,也能过
/*
题意:定义一个比率树,其比率=树上边权和/点权和,
现在有n个节点的完全图,要选取k个节点构成比率树,求最小的比率树,
按照编号从小到大输出节点编号,如果有多个比率树比率相等,
则输出字典序最小的那个节点序列.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2489
思路:最小比率树,在选取节点固定的情况下,显然要边权和最小,
才能使得比率最小,显然就是枚举选取k个节点组合下的树求取mst,
记录最小比率树.
因为n<=15,2<=k<=n
2种思路:dfs搜素枚举k个节点的可能组合(本身就是字典序)进行kruskal,或者二进制枚举k个节点的子集
对选取了k个节点的情况进行kruskal,最后在用stl运算符重载进行字典序排序.
*/

int n,m,k,fa[N],vis[N];
double val[N],sum1,sum2;//sum1点权和,sum2边权和

struct List{
    int id[N];
    double rat;
    bool operator < (const List &x)const{
        if(rat != x.rat) return rat<x.rat;//比率不同,按比率排
        else{//必须相同 按编号序列排
            for(int i=1;i<=k;i++)//当前位相同考虑比较下一位,否则就按当前位排
                if(id[i]!=x.id[i]) return id[i]<x.id[i];
            return 1;
        }
    }
};

vector<List> seq;

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        if(!vis[edge[i].u] || !vis[edge[i].v]) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            cnt++;
            sum1+=edge[i].w;
            if(cnt == k-1) break;
        }
    }
}

int judge(int x){
    int cnt=0;
    while(x){
        if(x&1) cnt++;
        x>>=1;
    }
    return cnt;
}

int main(){
    double w;
    while(scanf("%d%d",&n,&k) && n+k){
        m=0;
        seq.clear();
        for(int i=1;i<=n;i++)
            scanf("%lf",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%lf",&w);
                if(j>i) edge[++m]=Edge(i,j,w);
            }
        }
        sort(edge+1,edge+1+m);
        List tmp;
        int num;
        //因为k<=2最少选2个,选取2个的二进制位中最小的是3 0011
        for(int s=3;s<(1<<n);s++){
            if(judge(s) != k) continue;//判断当前二进制位是否选取了k个
            memset(vis,0,sizeof(vis));
            num=sum1=sum2=0;
            for(int i=0;i<n;i++){
                if(s & (1<<i)){
                    vis[i+1]=1;
                    tmp.id[++num]=i+1;
                    sum2+=val[i+1];
                }
            }
            kruskal();
            tmp.rat=sum1/sum2;
            seq.push_back(tmp);//将这次组合序列和比率存下来
        }
        //因为按照二进制位的10进制枚举出的状态,编号是随机的并不是字典序,因此要排序
        sort(seq.begin(),seq.end());
        printf("%d",seq[0].id[1]);
        for(int i=2;i<=k;i++)
            printf(" %d",seq[0].id[i]);
        printf("\n");
    }
    return 0;
}
/*
//dfs爆搜枚举k个可能组合序列
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define M 400
#define INF 1e18
using namespace std;

int n,m,k,fa[N],vis[N];
double val[N];

struct List{
    int id[N];
    double rat;
}tmp,ans;

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

double kruskal(){
    init();
    int x,y,cnt=0;
    double sum=0;
    for(int i=1;i<=m;i++){
        if(!vis[edge[i].u] || !vis[edge[i].v]) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            cnt++;
            sum+=edge[i].w;
            if(cnt == k-1) break;
        }
    }
    return sum;
}

void dfs(int st,int num,int sum){
    if(n-st+1<k-num) return;//剪枝 当剩下的数小于还需要选取的个数时 结束
    if(num == k){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=k;i++)
            vis[tmp.id[i]]=1;
        tmp.rat=kruskal()/sum;
        //当前选取出的组合构造出的比率树小于所记录的最小的时才更新,等于时先前记录的字典序本身就是最小的,不更新
        if(tmp.rat<ans.rat){
            ans=tmp;
        }
        return;
    }
    tmp.id[num+1]=st;
    dfs(st+1,num+1,sum+val[st]);
    dfs(st+1,num,sum);
}

int judge(int x){
    int cnt=0;
    while(x){
        if(x&1) cnt++;
        x>>=1;
    }
    return cnt;
}

int main(){
    double w;
    while(scanf("%d%d",&n,&k) && n+k){
        m=0;
        for(int i=1;i<=n;i++)
            scanf("%lf",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%lf",&w);
                if(j>i) edge[++m]=Edge(i,j,w);
            }
        }
        sort(edge+1,edge+1+m);
        ans.rat=INF;
        dfs(1,0,0);
        printf("%d",ans.id[1]);
        for(int i=2;i<=k;i++)
            printf(" %d",ans.id[i]);
        printf("\n");
    }
    return 0;
}
*/
