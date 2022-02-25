#include<cstdio>
#include<stdlib.h>//poj abs() cmath库不能识别需要stdlib.h标准库
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 235ms 最大独立集
/*
题意:老师带领n个学生出去郊游,担心他们
彼此之间成为配偶,现在规定以下4条只要满足
其中任意一条则两人成为配偶的可能性就较低:
(1).两人身高相差超过40cm.
(2).两人性别相同.
(3).两人喜欢的音乐风格不同.
(4).两人喜欢的运动相同.
现在问老师最多能带领多少学生出去郊游,使得
任意两个人必须满足上述要求的任意一个即可.
链接:http://poj.org/problem?id=2771
思路:上述四条关系是彼此不能成为配偶的条件,那么与其相反
的条件都成立就是两同学成为配偶必须要满足的4个条件,
因此若学生i、j满足取反的四个条件,则学生i、j可能成为配偶,
建立i-j的无向边,因为性别只有男女两种属性,相邻点性别必定不同,
满足交叉染色法,不存在奇环,因此最终建成的图一定是二分图,
那么最终要求的集合两两之间不能有连边(不会成为配偶),
因此这个最大的集合一定是最大独立集,而最大独立集=顶点数-最大匹配.
因为所有点都跑匈牙利所以,结果除2.

注意:此题也可按照性别男女分成2个集合 只建立男->女的有向边,
只计算一个集合出发的配对点求解最大匹配,这样结果无需除2.

*/
int n,vis[N],match[N],ans;
vector<int> G[N];
struct Node{
    int h;
    char sex,music[20],sport[20];
}node[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d %c %s %s",&node[i].h,&node[i].sex,node[i].music,node[i].sport);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                //身高差不超过40,性别不同,音乐相同,体育运动不同 是成为配偶必要满足的条件
                if(abs(node[i].h-node[j].h)<=40 && node[i].sex != node[j].sex &&
                   !strcmp(node[i].music,node[j].music) && strcmp(node[i].sport,node[j].sport)){
                    G[i].push_back(j);
                    G[j].push_back(i);
                   }
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans/2);
    }
    return 0;
}

/*
//ac 172ms 按男女关系分成2个集合,只考虑男集合中的点求取匹配,最大独立集
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<vector>
#define N 550
using namespace std;

int n,vis[N],match[N],ans,color[N];
vector<int> G[N];
struct Node{
    int h;
    char sex,music[20],sport[20];
}node[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d %c %s %s",&node[i].h,&node[i].sex,node[i].music,node[i].sport);
        for(int i=1;i<=n;i++){
            if(node[i].sex == 'F') color[i]=1;//标记i 为男
            for(int j=i+1;j<=n;j++){
                if(abs(node[i].h-node[j].h)<=40 && node[i].sex != node[j].sex &&
                   !strcmp(node[i].music,node[j].music) && strcmp(node[i].sport,node[j].sport)){
                    if(color[i])//只建立男到女的单向边
                        G[i].push_back(j);
                    else
                        G[j].push_back(i);
                   }
            }
        }
        for(int i=1;i<=n;i++){
            if(!color[i]) continue;//只考虑男集合中的点求取配对点
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);
    }
    return 0;
}
*/
