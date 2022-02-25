/*
//2014 ACM/ICPC Asia Regional Guangzhou Online
//����ժ������
����:����վ�ʦ��,һ��n*n������,'K'��ʾ�����,'T'��ʾ��ɮ,
'#'��ʾǽ,'.'��ʾ·,����'1'~'9'��ʾԿ��,'S'��ʾ�߹�.
����տ������������ƶ�,ÿ�ƶ�һ�񻨷�1����ʱ��,��������߹�,
�����߹����⻨��1����,�����5���߹�,�����Ҫ����m��Կ�ײ��ܾȳ�ʦ��,
����ȡԿ����һ������,ֻ��ȡ��ǰi��Կ��,����ȡ��i+1��Կ��,����ճ���ǽ
����,�κ�λ�ö����Ե���,��ɮ��λ��Ҳ����ȥ,����Կ��û�м��뼴ʹ����'T'��
Ҳ�޷��ȳ���ɮ,��ȳ���ɮ������ʱ��,��Ȳ������"impossible".
0<=n<=100.0<=m<=9.
ע��:ÿ��Կ��i,�����ڶ��λ���д��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5025
˼·:��Ϊɱ���߻�໨1����,����ʹ�����ȶ��а�����ʱ���ٳ���.
����ΪԿ��ʵ����ȡ��ʱ����밴��˳��ȡ,��ô�Ͳ���״̬ѹ��,
����Ҫȡ��i��Կ��,������״̬������жϵ�ǰȡ��Կ�׵������Ƿ�ﵽ��i-1.
�������߹ֵ�λ��,���֮ǰ��������,��ô�ٴ��߹���ʱ��Ͳ����ٶ໨1����ȥ
����,Ҳ����˵��Ҫ�ж�ÿ���ߵ�λ���Ƿ�֮ǰ����� ����������ʱ����1����2,
��ô����Ҫ״̬ѹ��,�����봦��ʱ����'S'���´���Ϊ'A'��'B'��'C'��'D'��'E',
�����5����.
*/
//ac 343ms bfs���ȶ���+��ά����״̬ѹ��
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

//���5����,��������ֵΪ2^5-1=31.
//vis[x][y][key][sk]=0/1 ��ʾ(x,y)λ����Я��Կ������Ϊǰkey��,�����ߵ�������Ϊsk��״̬�Ƿ���ֹ�.
int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][10][32];
char mp[N][N];
struct State{
    int x,y,key,sk,t;
    State(int x=0,int y=0,int key=0,int sk=0,int t=0):x(x),y(y),key(key),sk(sk),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>n || mp[x][y] == '#')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy][0][0]=1;
    Q.push(State(sx,sy,0,0,0));
    State tp;
    int nx,ny;
    char ch;
    while(!Q.empty()){
        tp=Q.top();
        //����'T'��,����Я��Կ�������ﵽm ���ص�ǰ���õ�����ʱ��
        if(mp[tp.x][tp.y] == 'T' && tp.key == m)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            ch=mp[nx][ny];
            //'.' 'T' 'K' ����ʵ��Я��Կ�׺������ߵ���ϲ�ͬ �����ٴ��ظ�����
            if((ch == '.' || ch == 'T' || ch == 'K') && !vis[nx][ny][tp.key][tp.sk]){
                vis[nx][ny][tp.key][tp.sk]=1;
                Q.push(State(nx,ny,tp.key,tp.sk,tp.t+1));
            }
            //�����߹�,�ж��Ƿ��Ѿ�������õ����
            else if(ch>='A' && ch<='E' && !vis[nx][ny][tp.key][tp.sk]){
                vis[nx][ny][tp.key][tp.sk]=1;
                if(tp.sk & 1<<(ch-'A')){//�Ѿ�������õ����,�ٴε���ʱ ��ʱ1
                    vis[nx][ny][tp.key][tp.sk]=1;
                    Q.push(State(nx,ny,tp.key,tp.sk,tp.t+1));
                }
                else{//��δ����õ����,����ʱ ��ʱ2
                    vis[nx][ny][tp.key][tp.sk|1<<(ch-'A')]=1;//���õ��ߵ�״̬ѹ��
                    Q.push(State(nx,ny,tp.key,tp.sk|1<<(ch-'A'),tp.t+2));
                }
            }
            //����Կ��
            else if(ch>='1' && ch<='9' && !vis[nx][ny][tp.key][tp.sk]){
                int nk;
                vis[nx][ny][tp.key][tp.sk]=1;//��ǵ���õ�ʱ ��δ��ȡԿ��ʱ��״̬,�����ظ������״̬�ٴ����
                if(tp.key == ch-'1')//�ж�ǰ���Ƿ������ ǰch-'1'��Կ��,���������,��ô��ǰλ�õ�ch��Կ�ױ��Я��
                    nk=tp.key+1;//Կ����+1
                else//������Я��Կ������ch-'1'С����ڵ���ch,Я��Կ������������ԭ����״̬.
                    nk=tp.key;
                vis[nx][ny][nk][tp.sk]=1;//������Կ���µ�״̬һ����Ϊ��ӹ���,��Ϊvis[nx][ny][tp.key][tp.sk]=0
                Q.push(State(nx,ny,nk,tp.sk,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy,ans,k;
    while(scanf("%d%d",&n,&m) && n+m){
        k=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'K')
                    sx=i,sy=j;
                else if(mp[i][j] == 'S'){//���ߵ�λ����������Ϊ'A'��'B'��'C'��'D'��'E',��Ҫ״̬ѹ���жϲ�ͬ״̬�ߵ��õ�ʱ����ʱΪ1����2
                    mp[i][j]='A'+k;
                    k++;
                }
            }
        }
        ans=bfs(sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("impossible\n");
    }
    return 0;
}

/*
//ac 46ms bfs+��ά����״ѹ
//ժ�Բ���:https://blog.csdn.net/yuanjunlai141/article/details/50954656
#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
const int maxn=115;
char map[maxn][maxn];
struct Point
{
    int x,y;
}d;
struct PT
{
    int x,y,t,snake,key;
    PT()
    {
        ;
    }
    PT(int xx,int yy,int tt,int s,int k)
    {
        x=xx,y=yy,t=tt,snake=s,key=k;
    }
    friend bool operator<(const PT a,const PT b)
    {
        return a.t>b.t;
    }
};
int n,Key;
int dx[4]= {0,-1,0,1};
int dy[4]= {-1,0,1,0};
bool vis[maxn][maxn][15];
int dis[maxn][maxn][15];
int Snake[maxn][maxn];
bool check(int x,int y)
{
    if(x<0||x>=n||y<0||y>=n||map[x][y]=='#')
        return false;
     return true;
}
priority_queue<PT>que;
int bfs(Point start)
{
    int nx,ny;
    memset(vis,false,sizeof(vis));
    nx=start.x,ny=start.y;
    while(!que.empty())
    {
        que.pop();
    }
    vis[nx][ny][0]=true;
    que.push(PT(nx,ny,0,0,0));
    while(!que.empty())
    {
        PT now;
        now=que.top();
        que.pop();
        if(map[now.x][now.y]=='T'&&now.key==Key)  ///Կ�״��벢���ҵ���ɮ
            return now.t;
        for(int i=0; i<4; i++)
        {
            nx=now.x+dx[i];
            ny=now.y+dy[i];
            bool flag=check(nx,ny);
            if(!flag||vis[nx][ny][now.key])
                continue;
             if(now.key+1+'0'==map[nx][ny])///�պ�����һ��Ҫ�ҵ�Կ��
            {
                    vis[nx][ny][now.key+1]=true;
                    que.push(PT(nx,ny,now.t+1,now.snake,now.key+1));
            }
            else if(map[nx][ny]=='S')///������
            {
                if(!(now.snake&(1<<Snake[nx][ny])))///ûɱ��������
                {
                    vis[nx][ny][now.key]=true;
                    que.push(PT(nx,ny,now.t+2,now.snake|(1<<Snake[nx][ny]),now.key));
                }
                else
                {
                    vis[nx][ny][now.key]=true;
                    que.push(PT(nx,ny,now.t+1,now.snake,now.key));
                }
            }
            else///�����������������....
            {
                vis[nx][ny][now.key]=true;
                que.push(PT(nx,ny,now.t+1,now.snake,now.key));
            }

        }

    }
    return -1;
}
int main()
{
    int tot;
    while(cin>>n>>Key)
    {
        if(n==0)
            break;
        tot=0;
        for(int i=0; i<n; i++)
        {
            cin>>map[i];
            for(int j=0; j<n; j++)
            {
                if(map[i][j]=='K')
                {
                    d.x=i,d.y=j;
                }
                if(map[i][j]=='S')
                {
                    Snake[i][j]=tot++;
                }
            }
        }
        int ans=bfs(d);
        if(ans==-1)
            cout<<"impossible"<<endl;
        else
            cout<<ans<<endl;
    }
    return 0;
}
*/
