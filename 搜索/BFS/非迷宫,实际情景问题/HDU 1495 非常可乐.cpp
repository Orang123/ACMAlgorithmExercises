/*
//����ժ������
����:����s��n��m������,�ֱ������ֺ�2�����ӵ�����,�����������Ի��൹,
ֻ���ڵ���ʱ��,Ҫôֻ�ܰѵ�ǰ�������׵���,Ҫôֻ�ܰ�Ŀ����������,
���ܲ��ܰ�s�еĿ���ƽ��,�ܵĻ������С�����ӵĴ���,���ܾ����NO.
s<101,n+m=s.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1495
˼·:����bfs,��Ϊ���ֺͱ��ӿ����໥��,��ˮʱ��6��״̬ת��.
s->n,s->m,n->s,n->m,m->s,m->n;
״̬�������ά����vis[tp.s][tp.n][tp.m],������ǰ���������п���������״̬
�Ƿ���ֹ�.
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
        //s->n �ӿ��ֵ�������Ϊn�ı���,����ƿ�ӻ���ʣ�����(tp.s>0),����Ϊn�ı��ӻ�δ����(n-tp.n>0)
        if(tp.s && n-tp.n>0){
            if(tp.s>n-tp.n)//����ƿ��ʣ����������Խ� ����Ϊn�ı��ӵ���
                //����ƿʣ�����Ϊtp.s-(n-tp.n),����Ϊn��ƿ�� ���ָպõ�������Ϊn,����Ϊm��ƿ�ӿ�����������
                sta=State(tp.s-(n-tp.n),n,tp.m,tp.cnt+1);
            else//����ƿ��ʣ����������ܽ� ����Ϊn�ı��ӵ���,Ҳ����˵����ƿ�ᱻ����,������Ϊn��ƿ�Ӳ�����
                //����Ϊ0,����Ϊn��ƿ��Ϊtp.n+tp.s,����Ϊm��ƿ�Ӳ���
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
//ac 31ms �����ҹ��� �����������
//ժ������:https://cloud.tencent.com/developer/article/1086892
//������Сƿ���ݻ��ֱ�Ϊa,b������ת����ͨ������Сƿ�ӵ����ɴε����򵹳������õ�(a+b)/2����Ŀ��֣�
//������Сƿ�ӱ������򵹳�x�κ�y�Σ������x��y���ۼӺ�Ĳ�������x=��һ��ƿ�ӵ����Ĵ���-�����Ĵ�����
//y=�ڶ���ƿ�ӵ����Ĵ���-�����Ĵ�����
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
