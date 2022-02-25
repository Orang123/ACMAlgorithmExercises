/*
题意:
给出n个文本串s和m个模式串p，求每个文本串中出现的模式串次数总和.
注意:这里是所有模式串出现次数总和,而不是出现了几个模式串,同一个
模式串重复出现也要计算.
n,m<=10^5.|s|,|p|<=10^4.所有模式串长度和<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5384
思路:AC自动机,n个文本串每个都查询一次.
*/
//ac 140ms s[N][M]输入文本串,预开空间太大,这个能开出编译没报错,也是出乎意料了
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100010
#define M 10010
using namespace std;

int n,m,tr[N][26],fail[N],wordCnt[N],cnt;
char p[M],s[N][M];//这里n*m有10*9,因为先输入的是文本串,不过编译能通过,尽量用string保存下每个文本串

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordCnt[rt]++;
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<26;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            son=tr[node][i];
            if(son){
                fail[son]=tr[fail[node]][i];
                Q.push(son);
            }
            else
                tr[node][i]=tr[fail[node]][i];
        }
    }
}

int query(int id){
    int rt=0,sum=0,len=strlen(s[id]);
    for(int i=0;i<len;i++){
        rt=tr[rt][s[id][i]-'a'];
        for(int j=rt;j;j=fail[j])
            sum+=wordCnt[j];
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%s",p);
            insertWord();
        }
        build();
        for(int i=1;i<=n;i++)
            printf("%d\n",query(i));
    }
    return 0;
}

/*
//ac 249ms 用string存储n个文本串,因为string[100000],无需预开出每个文本串的长度
//而所有文本串的长度和不超过10^5
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<string>
#include<algorithm>
#define N 100010
#define M 10010
using namespace std;

int n,m,tr[N][26],fail[N],wordCnt[N],cnt;
char p[M];
string s[N];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordCnt[rt]++;
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<26;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            son=tr[node][i];
            if(son){
                fail[son]=tr[fail[node]][i];
                Q.push(son);
            }
            else
                tr[node][i]=tr[fail[node]][i];
        }
    }
}

int query(int id){
    int rt=0,sum=0,len=s[id].length();
    for(int i=0;i<len;i++){
        rt=tr[rt][s[id][i]-'a'];
        for(int j=rt;j;j=fail[j])
            sum+=wordCnt[j];
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            cin >> s[i];
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%s",p);
            insertWord();
        }
        build();
        for(int i=1;i<=n;i++)
            printf("%d\n",query(i));
    }
    return 0;
}
*/
