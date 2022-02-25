/*
����:l��,ÿ�㳤��ֱ���r��c����ά����l*r*c,'#'��ʾ�������ߵĵ�Ԫ��,
'.'��ʾ�յ�Ԫ���������.��ʼλ��Ϊ'S',Ŀ�ĵ�λ'E',��ÿ�������������
4����������ڸ����ƶ�,���ҿ��Դӵ�ǰλ�õĵ�ǰ��k����һ��k+1����һ��k-1�ƶ�,
λ��(x,y)����.��6��������ƶ�ÿ����Ҫ����1����,�ʴ�'S'����'E'������Ҫ���ٷ���.
l,r,c<=30
����:http://poj.org/problem?id=2251
˼·:����ά�ȵ�����,��Ӧ����6������������������.
���dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}.
{0,-1,0}��ʾ��ͬһ���(x,y)�ƶ���(x-1,y)
{1,0,0}��ʾ�ڵ�k���(x,y)�ƶ�����k+1���(x,y)
*/
//ac 32ms bfs
//ʱ�临�Ӷ�O(l*r*c)=30^3=2700
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N][N];
struct State{
    int k,x,y,s;
    State(int k=0,int x=0,int y=0,int s=0):k(k),x(x),y(y),s(s){}
};

int bfs(int sk,int sx,int sy,int ek,int ex,int ey){
    queue<State> Q;
    mp[sk][sx][sy]='#';
    Q.push(State(sk,sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.k == ek && tp.x == ex && tp.y == ey)
            return tp.s;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[tp.k][nx][ny]!='#'){
                mp[tp.k][nx][ny]='#';
                Q.push(State(tp.k,nx,ny,tp.s+1));
            }
        }
        if(tp.k<l && mp[tp.k+1][tp.x][tp.y]!='#'){
            mp[tp.k+1][tp.x][tp.y]='#';
            Q.push(State(tp.k+1,tp.x,tp.y,tp.s+1));
        }
        if(tp.k>1 && mp[tp.k-1][tp.x][tp.y]!='#'){
            mp[tp.k-1][tp.x][tp.y]='#';
            Q.push(State(tp.k-1,tp.x,tp.y,tp.s+1));
        }
    }
    return -1;
}

int main(){
    int sf,sx,sy,ef,ex,ey,ans;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ef=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        ans=bfs(sf,sx,sy,ef,ex,ey);
        if(ans!=-1)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}

/*
//ac 32ms bfs ��dir[6][3]��ʾ6������ֱ��Ǳ����ϡ����������ϡ���
//dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}
//ʱ�临�Ӷ�O(l*r*c)=30^3=2700
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}};
char mp[N][N][N];
struct State{
    int k,x,y,s;
    State(int k=0,int x=0,int y=0,int s=0):k(k),x(x),y(y),s(s){}
};

int bfs(int sk,int sx,int sy){
    queue<State> Q;
    mp[sk][sx][sy]='#';
    Q.push(State(sk,sx,sy,0));
    State tp;
    int nk,nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<6;i++){
            nk=tp.k+dir[i][0];
            nx=tp.x+dir[i][1];
            ny=tp.y+dir[i][2];
            if(nk>=1 && nk<=l && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nk][nx][ny]!='#'){
                if(mp[nk][nx][ny] == 'E')
                    return tp.s+1;
                mp[nk][nx][ny]='#';
                Q.push(State(nk,nx,ny,tp.s+1));
            }
        }
    }
    return -1;
}

int main(){
    int sf,sx,sy,ans;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                }
            }
        }
        ans=bfs(sf,sx,sy);
        if(ans!=-1)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}
*/

/*
//TLE dfs
//ʱ�临�Ӷ�O(6^(30*30*30))
#include<cstdio>
#include<queue>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N][N],ans;
int ek,ex,ey;
char mp[N][N][N];

void dfs(int k,int x,int y,int s){
    if(s>=dp[k][x][y])
        return;
    dp[k][x][y]=s;
    if(k == ek && x == ex && y == ey){
        ans=min(ans,s);
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[k][nx][ny]!='#')
            dfs(k,nx,ny,s+1);
    }
    if(k<l && mp[k+1][x][y]!='#')
        dfs(k+1,x,y,s+1);
    if(k>1 && mp[k-1][x][y]!='#')
        dfs(k-1,x,y,s+1);
}

int main(){
    int sf,sx,sy;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ek=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        dfs(sf,sx,sy,0);
        if(ans!=INF)
            printf("Escaped in %d minute(s).\n",ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}
*/

/*
//TLE ������������dfs+�����پ����֦
//���Ӷ�O(6^(30*30*30))
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define INF 0x3f3f3f3f
using namespace std;

int l,r,c,dir[6][3]={{0,-1,0},{0,1,0},{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}},dp[N][N][N];
int ek,ex,ey;
char mp[N][N][N];

int dfs(int k,int x,int y,int s,int tot){
    //��֦1:������ﵱǰ��(x,y)λ������ʱ���ܱ�֮ǰ��¼����ʱ���پͲ�������,��ǰ�Ѿ����ܸ���,�����������ܸ�����.
    if(s>=dp[k][x][y])
        return 0;
    dp[k][x][y]=s;
    //��֦2:�����پ����֦ �����Ŀ�����ͬһ�� ��ǰʱ��s+ʣ����������پ�����Ҫ��ʱ�仹�ȹ涨��ʱ��� �򷵻�
    if(k == ek && abs(ex-x)+abs(ey-y)>tot-s)
        return 0;
    if(k == ek && x == ex && y == ey)
        return 1;
    int nk,nx,ny;
    for(int i=0;i<6;i++){
        nk=k+dir[i][0];
        nx=x+dir[i][1];
        ny=y+dir[i][2];
        if(nk>=1 && nk<=l && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nk][nx][ny]!='#'){
            if(dfs(nk,nx,ny,s+1,tot))
                return 1;
        }
    }
    return 0;
}

int main(){
    int sf,sx,sy;
    while(scanf("%d%d%d",&l,&r,&c) && l+r+c){
        for(int k=1;k<=l;k++){
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    scanf(" %c",&mp[k][i][j]);
                    if(mp[k][i][j] == 'S'){
                        sf=k;
                        sx=i,sy=j;
                    }
                    else if(mp[k][i][j] == 'E'){
                        ek=k;
                        ex=i,ey=j;
                    }
                }
            }
        }
        int flag=0;
        for(int i=1;i<=100;i++){//ʱ������Ϊ30+30+30,�ӵ�1���ߵ�30����Ҫ30-1,��(1,1)�ߵ�(30,30)��Ҫ30-1+30-1
            memset(dp,0x3f,sizeof(dp));
            if(dfs(sf,sx,sy,0,i)){
                flag=1;
                printf("Escaped in %d minute(s).\n",i);
                break;
            }
        }
        if(!flag)
            printf("Trapped!\n");
    }
    return 0;
}
*/
