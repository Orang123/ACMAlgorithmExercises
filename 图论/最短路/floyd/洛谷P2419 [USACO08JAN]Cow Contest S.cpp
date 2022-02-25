/*
题意:FJ的N(1 <= N <= 100)头奶牛们最近参加了场程序设计竞赛:)。
在赛场上，奶牛们按1..N依次编号。每头奶牛的编程能力不尽相同，
并且没有哪两头奶牛的水平不相上下，也就是说，奶牛们的编程能力有明确的排名。
整个比赛被分成了若干轮，每一轮是两头指定编号的奶牛的对决。
如果编号为A的奶牛的编程能力强于编号为B的奶牛(1 <= A <= N; 1 <= B <= N; A != B) ，
那么她们的对决中，编号为A的奶牛总是能胜出。 FJ想知道奶牛们编程能力的具体排名，
于是他找来了奶牛们所有 M(1 <= M <= 4,500)轮比赛的结果，希望你能根据这些信息，
推断出尽可能多的奶牛的编程能力排名。比赛结果保证不会自相矛盾。
就是问能够确定名次的奶牛的数目.奶牛的输赢关系满足传递性.
链接:https://www.luogu.com.cn/problem/P2419
思路:建一张 赢的图,和一张输的图.分别跑dfs.
如果某个奶牛赢的次数+输的次数==n-1则说明该奶牛的名词是确定的.
注意要用vis标记已经访问过的点,因为有可能1->2->3,1->3,这样3这个点,
会被多算一次.
*/
#include<cstdio>
#include<cstring>
#define N 110
#define M 5000
using namespace std;

int n,m,vis[N],cnt1,cnt2,head1[N],head2[N];
struct Node{
    int to,next;
}edge1[M],edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node){to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node){to,head2[from]};
    head2[from]=cnt2++;
}
//计算牛赢的次数
void dfs1(int u){
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        int v=edge1[i].to;
        if(!vis[v]){
            vis[v]=1;
            cnt1++;
            dfs1(v);//满足传递性
        }
    }
}
//计算牛输的次数
void dfs2(int u){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(!vis[v]){
            vis[v]=1;
            cnt2++;
            dfs2(v);
        }
    }
}

int main(){
    int u,v,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge1(u,v);
        addEdge2(v,u);
    }
    for(int i=1;i<=n;i++){
        cnt1=cnt2=0;
        dfs1(i);
        dfs2(i);
        memset(vis,0,sizeof(vis));
        if(cnt1+cnt2 == n-1) ans++;//某牛赢的次数+输的次数之和为n-1时,它的名次是确定的
    }
    printf("%d\n",ans);
    return 0;
}
/*
//ac floyd做法
#include<cstdio>
#include<cstring>
#define N 110
#define M 5000
using namespace std;
int n,m,a[N][N];

//floyd
int main(){
    int u,v,ans=0;
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        a[u][v]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                a[i][j]|=(a[i][k]&a[k][j]);//根据传递性 计算
    for(int i=1;i<=n;i++){
        int k=1;
        for(int j=1;j<=n;j++)
            if(i!=j)
                k&=(a[i][j]|a[j][i]);//如果i点除了自己本身和其它每个点都有 输赢关系,则它的名词是确定的s
        ans+=k;
    }
    printf("%d\n",ans);
    return 0;
}

*/
