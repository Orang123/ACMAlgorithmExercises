#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<vector>
#include<algorithm>
#include<string.h>
//ac 144ms
//https://blog.csdn.net/qq_30974369/article/details/74025251 题意 思路参考
//https://www.cnblogs.com/Aa1039510121/p/8617755.html 标程参考
/*
题意:一个牧师要给n个婚礼进行一个仪式,给定婚礼开始的时间和结束的时间
仪式要么在婚礼刚刚开始的时候进行,要么进行完婚礼正好结束,
问牧师能否参加所有的婚礼,并输出方案.
链接:http://poj.org/problem?id=3683
思路:跟POJ 3207神似的一道题目,依旧是把题目转化为2-sat来做
这题的时间也是一个媒介,如果某两个婚礼进行仪式的时间有重合，
那么就存在了矛盾关系,通过这些关系连边Tarjan缩点,判断
拓扑排序染色(把仪式在 开始/结束 进行染色)最后输出解即可.
*/

typedef long long ll;
typedef unsigned long long LL;
using namespace std;
const int INF=0x3f3f3f3f;
const double eps=0.0000000001;
const int N=2000+10;
const ll mod=1e9+7;
struct Node{
    int x,y;
}a[N];
struct node{
    int to,next;
}edge[N*N];
struct NODE{
    int to,next;
}Edge[N*N];
int Head[N];
int head[N],low[N],dfn[N];
int vis[N*10],belong[N*10];
int opp[N*10];
int cnt,t,tot;
stack<int>st;
void init(){
    tot=0;
    t=0;
    cnt=0;
    memset(belong,-1,sizeof(belong));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
}
void add(int u,int v){
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
void ADD(int u,int v){
    Edge[tot].to=v;
    Edge[tot].next=Head[u];
    Head[u]=tot++;
}
void tarjan(int u){
    vis[u]=1;
    st.push(u);
    dfn[u]=low[u]=++t;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        cnt++;
        int vv;
        do{
            vv=st.top();
            st.pop();
            belong[vv]=cnt;
            vis[vv]=0;
        }while(vv!=u);
    }
}
int n;
int in[N];
void topsort(){
    queue<int>q;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=cnt;i++)if(in[i]==0)q.push(i);
    while(q.empty()==0){
        int u=q.front();
        q.pop();
        if(vis[u]==0){
            vis[u]=1;
            vis[opp[u]]=-1;
        }
        for(int i=Head[u];i!=-1;i=Edge[i].next){
            int v=Edge[i].to;
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
}
int check(int i,int j){
    if(a[i].y<=a[j].x){//感觉这里是刚好时间不会重叠的时候 为什么会作为矛盾条件返回1
       return 1;
    }

    if(a[i].x>=a[j].y){
        return 1;
    }
    return 0;
}
char str1[100];
char str2[100];
int main(){
    while(scanf("%d",&n)!=EOF){
        int val;
        init();
        memset(in,0,sizeof(in));
        for(int i=0;i<(n<<1);i=i+2){
           scanf("%s%s%d",str1,str2,&val);
           int x=(str1[0]-'0')*60*10+(str1[1]-'0')*60+(str1[3]-'0')*10+str1[4]-'0';
           int y=(str2[0]-'0')*60*10+(str2[1]-'0')*60+(str2[3]-'0')*10+str2[4]-'0';
           a[i].x=x;
           a[i].y=x+val;
           a[i+1].x=y-val;
           a[i+1].y=y;
        }
        for(int i=0;i<(n<<1);i=i+2){
            for(int j=0;j<(n<<1);j=j+2){
                if(i==j)continue;
                if(check(i,j)==0)add(i,j^1);
                if(check(i,j^1)==0)add(i,j);
                if(check(i^1,j)==0)add(i^1,j^1);
                if(check(i^1,j^1)==0)add(i^1,j);
            }
        }
        for(int i=0;i<(n<<1);i++){
            if(dfn[i]==0)tarjan(i);
        }
        int flag=0;
        for(int i=0;i<(n<<1);i=i+2){
            opp[belong[i]]=belong[i^1];
            opp[belong[i^1]]=belong[i];
            if(belong[i]==belong[i^1])flag=1;
        }
        if(flag){
            cout<<"NO"<<endl;
            continue;
        }
        cout<<"YES"<<endl;
        memset(Head,-1,sizeof(Head));
        tot=0;
        for(int u=0;u<(n<<1);u++){
            for(int i=head[u];i!=-1;i=edge[i].next){
                int v=edge[i].to;
                if(belong[u]!=belong[v]){
                    ADD(belong[v],belong[u]);
                    in[belong[u]]++;
                }
            }
        }

        topsort();
        int aa,b,c,d;
        for(int i=0;i<n;i++){
            if(vis[belong[i<<1]]==1){
                aa=a[i*2].x/60;
                b=a[i*2].x%60;
                c=a[i*2].y/60;
                d=a[i*2].y%60;
                //cout<<a[i*2].x<<" "<<a[i*2].y<<endl;
                printf("%02d:%02d %02d:%02d\n",aa,b,c,d);
            }
            else{
                aa=a[i*2+1].x/60;
                b=a[i*2+1].x%60;
                c=a[i*2+1].y/60;
                d=a[i*2+1].y%60;
                //cout<<a[i*2+1].x<<" "<<a[i*2+1].y<<endl;
                printf("%02d:%02d %02d:%02d\n",aa,b,c,d);
            }
        }
    }
}
