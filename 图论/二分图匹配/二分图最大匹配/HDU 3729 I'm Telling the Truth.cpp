#include<cstdio>
#include<cstring>
#define N 100100
using namespace std;
//ac 218ms 链式前向星建图
//2010 Asia Tianjin Regional Contest
/*
题意:n个学生,每个人都说自己分数所在的排名区间,
但是学生人数有可能是大于排名区间的范围的,可老师不知道
谁说了谎,现在老师想知道最多有多少学生说的是实话,输出
说实话学生的编号,如果有多个可能性,输出最大字典序的一组编号.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3729
思路:可以将学生和排名区间的范围作为两个分开的集合,而一个学生只能
对应一个排名,即每组学生的排名的对应关系是不会重叠的,即没有公共点,
实际就是求解学生和排名对应关系的最大匹配,每个学生都要和对应区间的
排名建学生到排名的有向边,由于要输出最大的字典序学生编号,可以贪心
匈牙利暴力配对时逆序从n依次考虑n-1...1,因为最大匹配的方案可能不唯一,
但是最大匹配的值一定是唯一的.
*/
int n,cnt,head[N],vis[N],match[N],ans,flag[N];
struct Edge{
    int to,next;
}edge[N*60];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(flag,0,sizeof(flag));
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            for(int j=a;j<=b;j++)
                addEdge(i,j);
        }
        for(int i=n;i>=1;i--){
            memset(vis,0,sizeof(vis));
            if(dfs(i)){
                ans++;
                flag[i]=1;
            }
        }
        printf("%d\n",ans);
        int k=0;
        for(int i=1;i<=n;i++){
            if(!flag[i]) continue;
            if(!k){
                k=1;
                printf("%d",i);
            }
            else
                printf(" %d",i);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 187ms 不建图,直接从区间sec的st~ed dfs遍历
#include<cstdio>
#include<cstring>
#define N 100100
using namespace std;

int n,vis[N],match[N],ans,flag[N];
struct Section{
    int st,ed;
}sec[110];

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    memset(flag,0,sizeof(flag));
}

int dfs(int u){
    for(int v=sec[u].st;v<=sec[u].ed;v++){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&sec[i].st,&sec[i].ed);
        for(int i=n;i>=1;i--){
            memset(vis,0,sizeof(vis));
            if(dfs(i)){
                ans++;
                flag[i]=1;
            }
        }
        printf("%d\n",ans);
        int k=0;
        for(int i=1;i<=n;i++){
            if(!flag[i]) continue;
            if(!k){
                k=1;
                printf("%d",i);
            }
            else
                printf(" %d",i);
        }
        printf("\n");
    }
    return 0;
}
*/
