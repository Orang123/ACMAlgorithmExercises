/*
//题意摘自网上
题意:输入s、n和m三个数,分别代表可乐和2个杯子的容量,三个容器可以互相倒,
只是在倒的时候,要么只能把当前容器彻底倒完,要么只能把目标容器倒满,
问能不能把s中的可乐平分,能的话输出最小倒杯子的次数,不能就输出NO.
s<101,n+m=s.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1495
思路:可以bfs,因为可乐和杯子可以相互倒,倒水时有6个状态转移.
s->n,s->m,n->s,n->m,m->s,m->n;
状态标记用三维数组vis[tp.s][tp.n][tp.m],标明当前三个容器中可乐容量的状态
是否出现过.
*/
//ac 546ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

int s,n,m,vis[N][N][N];
struct State{
    int s,n,m,cnt;
    State(int s=0,int n=0,int m=0,int cnt=0):s(s),n(n),m(m),cnt(cnt){}
};

int bfs(){
    queue<State> Q;
    vis[s][0][0]=1;
    Q.push(State(s,0,0,0));
    int des=s/2;
    State tp,sta;
    while(!Q.empty()){
        tp=Q.front();
        if((tp.s == tp.n && tp.s == des) || (tp.s == tp.m && tp.s == des) || (tp.n == tp.m && tp.n == des))
            return tp.cnt;
        Q.pop();
        //s->n 从可乐到进容量为n的杯子,可乐瓶子还有剩余可乐(tp.s>0),容量为n的杯子还未倒满(n-tp.n>0)
        if(tp.s && n-tp.n>0){
            if(tp.s>n-tp.n)//可乐瓶子剩余的容量可以将 容量为n的杯子倒满
                //可乐瓶剩余可乐为tp.s-(n-tp.n),容量为n的瓶子 可乐刚好倒满容量为n,容量为m的瓶子可乐容量不变
                sta=State(tp.s-(n-tp.n),n,tp.m,tp.cnt+1);
            else//可乐瓶子剩余的容量不能将 容量为n的杯子倒满,也就是说可乐瓶会被倒完,而容量为n的瓶子不会满
                //可乐为0,容量为n的瓶子为tp.n+tp.s,容量为m的瓶子不变
                sta=State(0,tp.n+tp.s,tp.m,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
        //s->m
        if(tp.s && m-tp.m>0){
            if(tp.s>m-tp.m)
                sta=State(tp.s-(m-tp.m),tp.n,m,tp.cnt+1);
            else
                sta=State(0,tp.n,tp.m+tp.s,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
        //n->s
        if(tp.n && s-tp.s>0){
            if(tp.n>s-tp.s)
                sta=State(s,tp.n-(s-tp.s),tp.m,tp.cnt+1);
            else
                sta=State(tp.s+tp.n,0,tp.m,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
        //n->m
        if(tp.n && m-tp.m>0){
            if(tp.n>m-tp.m)
                sta=State(tp.s,tp.n-(m-tp.m),m,tp.cnt+1);
            else
                sta=State(tp.s,0,tp.m+tp.n,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
        //m->s
        if(tp.m && s-tp.s>0){
            if(tp.m>s-tp.s)
                sta=State(s,tp.n,tp.m-(s-tp.s),tp.cnt+1);
            else
                sta=State(tp.s+tp.m,tp.n,0,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
        //m->n
        if(tp.m && n-tp.n>0){
            if(tp.m>n-tp.n)
                sta=State(tp.s,n,tp.m-(n-tp.n),tp.cnt+1);
            else
                sta=State(tp.s,tp.n+tp.m,0,tp.cnt+1);
            if(!vis[sta.s][sta.n][sta.m]){
                vis[sta.s][sta.n][sta.m]=1;
                Q.push(sta);
            }
        }
    }
    return -1;
}

int main(){
    int ans;
    while(scanf("%d%d%d",&s,&n,&m) && s+n+m){
        if(s & 1)
            printf("NO\n");
        else{
            memset(vis,0,sizeof(vis));
            ans=bfs();
            if(ans == -1)
                printf("NO\n");
            else
                printf("%d\n",ans);
        }
    }
    return 0;
}

/*
//ac 31ms 数论找规律 最大公因数做法
//摘自网上:https://cloud.tencent.com/developer/article/1086892
//设两个小瓶子容积分别为a,b，问题转化成通过两个小瓶子的若干次倒进或倒出操作得到(a+b)/2体积的可乐，
//设两个小瓶子被倒进或倒出x次和y次（这里的x和y是累加后的操作，即x=第一个瓶子倒出的次数-倒进的次数，
//y=第二个瓶子倒出的次数-倒进的次数）
#include <bits/stdc++.h>
using namespace std;
int gcd(int a,int b)
{
     return b==0?a:gcd(b,a%b);
}
int main()
{
     int a,b,c;
     while(cin>>a>>b>>c&&(a&&b&&c))
     {
         a/=gcd(b,c);
         if(a&1)
             cout<<"NO"<<endl;
         else
             cout<<a-1<<endl;
     }
     return 0;
 }
*/
