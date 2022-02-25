#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;
//ac 0ms match用二维数组
//还可用最大流去做
/*
题意:n个人分发5种尺寸类型的衣服,分别是"S M L X T",
分别代表小号,中号,大号,特大号,特大特大号.每个人都要
自己满意的尺寸类型范围,如MX代表M和X之间的尺寸M、L、X
三种尺寸都适合自己,每种尺寸类型的衣服有一定数量,
现在把这些衣服分发给这n个人,能否每个人都能分到适合自己
尺寸的衣服,如果可以输出"T-shirts rock!",
否则输出"I'd rather not wear a shirt anyway...".
注意:最多有20人,每种类型衣服数量最多20份.
链接:http://poj.org/problem?id=2584
思路:经典二分图多重匹配.
*/
char str[10],siz[6]={'S','M','L','X','T'};
int n,st,ed,vis[6],num[6],cnt[6],match[6][N];
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(cnt[v]<num[v]){
            match[v][++cnt[v]]=u;
            return 1;
        }
        else{
            for(int j=1;j<=cnt[v];j++){
                if(dfs(match[v][j])){
                    match[v][j]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}
//确定某个人想穿的衣服尺寸范围 "SMLXT"分别对应尺寸编号"12345"
void siz_range(){
    for(int i=0;i<5;i++){
        if(str[0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(str[1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            siz_range();
            for(int j=st;j<=ed;j++)
                G[i].push_back(j);
        }
        for(int i=1;i<=5;i++)
            scanf("%d",&num[i]);
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}

/*
//ac 0ms match用vector迭代器遍历
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

char str[10],siz[6]={'S','M','L','X','T'};
int n,st,ed,vis[6],num[6];
vector<int> G[N],match[6];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(num[v]){
            num[v]--;
            match[v].push_back(u);
            return 1;
        }
        else{
            //因为递归会开出很多dfs 迭代器不能放在全局,否则会导致it指针指向位置错误.
            vector<int>::iterator it;
            for(it=match[v].begin();it!=match[v].end();it++){
                if(dfs(*it)){
                    match[v].erase(it);//删掉原先v点配对的点
                    match[v].push_back(u);//加入v点新配对的点
                    return 1;
                }
            }
        }
    }
    return 0;
}

void siz_range(){
    for(int i=0;i<5;i++){
        if(str[0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(str[1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    for(int i=1;i<=5;i++) match[i].clear();
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            siz_range();
            for(int j=st;j<=ed;j++)
                G[i].push_back(j);
        }
        for(int i=1;i<=5;i++)
            scanf("%d",&num[i]);
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}
*/

/*
//ac 0ms 多重匹配转化为最大匹配的做法,不看衣服的尺寸,按照衣服的数量给衣服编号,
//每个所有衣服都有编号,相同尺寸衣服有多个时,其编号也是不一样,这个人和所有适合的衣服建边
//这是因为这题数据量很小,像HDU 3605 n<=100000,暴力建边将多重匹配转化为最大匹配肯定会TLE
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

char str[10],s[N][2],siz[6]={'S','M','L','X','T'};
//最多有5*20=100件衣服
//num[i]表示前i个尺寸衣服数量的累加和
int n,st,ed,vis[101],num[6],match[101];
vector<int> G[N];

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

void siz_range(int id){
    for(int i=0;i<5;i++){
        if(s[id][0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(s[id][1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]);
        for(int i=1;i<=5;i++){
            scanf("%d",&num[i]);
            num[i]+=num[i-1];//num[i]表示前i个尺寸衣服数量的累加和
        }
        for(int i=1;i<=n;i++){
            siz_range(i);
            //num[st-1]是st前面衣服尺寸的总数量,+1才是st尺寸衣服的起始编号
            for(int j=num[st-1]+1;j<=num[ed];j++)
                G[i].push_back(j);//每个人适合的尺寸衣服最多有5*20=100,边集数据量并不大
        }
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}
*/
