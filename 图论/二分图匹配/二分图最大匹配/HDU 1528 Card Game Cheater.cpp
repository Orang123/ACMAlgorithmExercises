#include<cstdio>
#include<cstring>
#include<vector>
#define N 30//Adam和 Eve一个人最多只有26个纸牌
using namespace std;
//ac 0ms 扑克牌数值累加比较大小
/*
题意:Adam和Eve打牌,两个人都各有n张排,牌有13个数字,
2、3、4、5、6、7、8、9、T、J、Q、K、A,大小依次递增,其中A最大,
有4种花色 红桃、黑桃、钻石、梅花分别用H、S、D、C来表示,
在数字相同的条件下由花色来决定大小,即H>S>D>C,现在Adam和Eve要
同时出n次牌,赢得一方得一分,现在问Eve最多可能得几分.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1528
思路:两人打牌拥有的牌刚好可以分为两个集合,而每次出的一对牌,已经出过后
就必然不会出和之前一样的数字花色,也就是每次出的牌连边之后没有公共顶点,
所以每次出的排刚好构成了一个匹配,现在只需要按照Eve纸牌i大于Adam纸牌j的
所有情况建有向边i->j,然后求解Eve集合中的牌到Adam纸牌集合中牌的最大匹配即可.
*/
int n,vis[N],match[N],val1[N],val2[N],ans;
char Adam[N][5],Eve[N][5];
vector<int> G[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
//C<D<S<H 花色大小关系
int cal(char x){
    /*
    因为数字是作为主要的评判大小的依据,而只有当数字相同时,才会用花色去判断大小,
    因此数字的数值要远远大于花色的数值才行如果数字的数值和花色不相上下,
    那么5H的数值和就有可能大于6C,这里对于数字的数值是乘10,而花色数值不大于10.
    */
    if(x>='2' && x<='9') return (x-'0')*10;
    else if(x == 'T') return 100;
    else if(x == 'J') return 110;
    else if(x == 'Q') return 120;
    else if(x == 'K') return 130;
    else if(x == 'A') return 140;

    if(x == 'C') return 1;
    else if(x == 'D') return 2;
    else if(x == 'S') return 3;
    else if(x == 'H') return 4;
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
        for(int i=1;i<=n;i++){
            scanf(" %c%c",&Adam[i][0],&Adam[i][1]);
            val1[i]=cal(Adam[i][0]);
            val1[i]+=cal(Adam[i][1]);
        }
        for(int i=1;i<=n;i++){
            scanf(" %c%c",&Eve[i][0],&Eve[i][1]);
            val2[i]=cal(Eve[i][0]);
            val2[i]+=cal(Eve[i][1]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(val2[i]>val1[j])//Eve牌的等级大于Adam 就建有向边i->j
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms 按照花色规则比较纸牌大小
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

int n,vis[N],match[N],ans;
char Adam[N][5],Eve[N][5];
vector<int> G[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int cal(char x){
    if(x>='2' && x<='9') return x-'0';
    else if(x == 'T') return 10;
    else if(x == 'J') return 11;
    else if(x == 'Q') return 12;
    else if(x == 'K') return 13;
    else if(x == 'A') return 14;
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
            scanf(" %c%c",&Adam[i][0],&Adam[i][1]);
        for(int i=1;i<=n;i++)
            scanf(" %c%c",&Eve[i][0],&Eve[i][1]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(cal(Eve[i][0])>cal(Adam[j][0]))//这里纸牌的数字大小一定要映射成数值,否则直接按照ASCII码比较 T会是最大的
                    G[i].push_back(j);
                else if(Eve[i][0] == Adam[j][0]){//数字相等,比较花色 C<D<S<H 花色大小关系
                    if(Eve[i][1] == 'H' &&  Adam[j][1] != 'H')//H花色最大
                        G[i].push_back(j);
                    else if(Eve[i][1] == 'S' && (Adam[j][1] == 'D' || Adam[j][1] == 'C'))//Eve是S时,Adam是D或C,Eve才赢
                        G[i].push_back(j);
                    else if(Eve[i][1] == 'D' && Adam[j][1] == 'C')//Eve是D时,Adam是C,Eve才赢
                        G[i].push_back(j);
                }
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
