/*
题意:摘自网上
N个士兵，每个士兵有一个学习的能力，学习能力强的可以教学习能力弱的，
现在N个士兵需要学习使用飞行扫帚，每一个士兵在教下一个士兵的时候，
会把自己练习的扫帚给他，问说N个士兵最少需要多少个扫帚。

释义:有n个字符串,求出出现次数最多的字符串的出现次数.
说实话这个题意是真的不知道要干啥,根据样例硬理解的.
n<=3000.字符串长度<=30
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1800
思路:字典树,只是要注意要去掉前导0.
*/

//ac 296ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 90010
using namespace std;

int n,tr[N][10],wordCnt[N],cnt,ans;
char s[40];

int newNode(){
    cnt++;
    for(int i=0;i<10;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(char *s){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'0';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordCnt[rt]++;
    ans=max(ans,wordCnt[rt]);
}

int main(){
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        while(n--){
            scanf("%s",s);
            int i=0;
            while(s[i] == '0') i++;
            insertWord(s+i);
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE stl vector建图 常数时间超时
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3200010
#define M 100010
using namespace std;

int n,tr[N][2],cnt,dp[M],ans;
vector<pair<int,int> > G[M];

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int son,rt=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;//val 第i位为son(0或1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val){
    int son,rt=0,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){
            res|=1<<i;
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

void dfs(int u,int fa){
    insertWord(dp[u]);
    int v,w;
    for(int i=0;i<G[u].size();i++){
        v=G[u][i].first;
        w=G[u][i].second;
        if(v == fa)
            continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        for(int i=0;i<n;i++)
            G[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back(make_pair(v,w));
            G[v].push_back(make_pair(u,w));
        }
        dfs(0,-1);
        for(int i=0;i<n;i++)
            ans=max(ans,findWord(dp[i]));
        printf("%d\n",ans);
    }
    return 0;
}
*/
