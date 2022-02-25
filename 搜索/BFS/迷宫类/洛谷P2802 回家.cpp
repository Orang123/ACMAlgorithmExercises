/*
����:С H ��һ�����ֳ��� n*m ������ĳ����η������ϡ� ÿ�����������������ĸ������ƶ�һ��
����ȻС H �����Ծ�ֹ�������� �������뿪�����ߣ�����ͱ������ˡ� �տ�ʼʱ������Ѫ 6 �㣬
ÿ�ƶ�һ����Ҫ���� 1 ��Ѫ����һ��С H �� Ѫ������ 0�� ������ȥ�� ��������·ͨ��ʰȡ���
��ʲô��������������Ѫ����ֻҪ���ߵ������ĸ��ӣ�������Ҫ�κ�ʱ�伴��ʰȡ�������ϵ����
����˲�䲹��������ÿ�ξ���������Ӷ�����ꡣ���㵽��ĳ�������ĸ��Ӳ���ȥ�� ��Ҳ����ͨ��
ʰȡ��겹�� HP�� ��ʹ�ڼ��ſ���ȥ�� ��Ҳ�������������ص����С�
��ͼ���� 5 �ָ��ӣ�
���� 0�� �ϰ��
���� 1�� �յأ� С H �����������ߡ�
���� 2�� С H �����㣬 Ҳ��һƬ�յء�
���� 3�� С H �ļҡ�
���� 4�� �����������Ŀյء�
С H �ܷ�ȫ�ؼң�����ܣ� �����Ҫ�೤ʱ���أ�
n,m<10
����:https://www.luogu.com.cn/problem/P2802
˼·:bfs.
*/
//ac 36ms bfs
//vis[x][y][hp]=0/1��ʾ��(x,y)������ֵΪhp������Ƿ��߹�
#include<cstdio>
#include<queue>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,mp[N][N],vis[N][N][7];

struct State{
    int x,y,hp,t;
    State(int x=0,int y=0,int hp=0,int t=0):x(x),y(y),hp(hp),t(t){}
};

int check(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && mp[x][y])
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,6,0));
    vis[sx][sy][6]=1;
    State tp;
    int nx,ny,np;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(!tp.hp)
            continue;
        if(mp[tp.x][tp.y] == 3)
            return tp.t;
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny,tp.hp-1)){
                if(mp[nx][ny] == 4 && tp.hp-1)
                    np=6;
                else
                    np=tp.hp-1;
                if(!vis[nx][ny][np]){
                    vis[nx][ny][np]=1;
                    Q.push(State(nx,ny,np,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&mp[i][j]);
            if(mp[i][j] == 2) sx=i,sy=j;
        }
    }
    printf("%d",bfs(sx,sy));
    return 0;
}

/*
//ac 41ms bfs
//vis[x][y]=hp��ʾ�ߵ�(x,y)����������ֵΪhp
#include<cstdio>
#include<queue>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,mp[N][N],vis[N][N];

struct State{
    int x,y,hp,t;
    State(int x=0,int y=0,int hp=0,int t=0):x(x),y(y),hp(hp),t(t){}
};

int check(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && mp[x][y])
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,6,0));
    State tp;
    int nx,ny,np;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(!tp.hp)
            continue;
        if(mp[tp.x][tp.y] == 3)
            return tp.t;
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny,tp.hp-1)){
                if(mp[nx][ny] == 4 && tp.hp-1)
                    np=6;
                else
                    np=tp.hp-1;
                //�����ǰ�ߵ�(nx,ny)�������ֵ���ܱ�֮ǰ����,�����,��Ϊʱ��ÿ��ֻ����1,֮
				//ǰ��ʱ�������̵�,���ڵ�ʱ��ֻ����ڵ���֮ǰ��,�������ֵ���ܱ�֮ǰ�Ĵ� �Ͳ�������չ
                if(np>vis[nx][ny]){
                    vis[nx][ny]=np;
                    Q.push(State(nx,ny,np,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&mp[i][j]);
            if(mp[i][j] == 2) sx=i,sy=j;
        }
    }
    printf("%d",bfs(sx,sy));
    return 0;
}
*/

/*
//ac dfs
//��Ϊ�������Ƚ���,�������,ֻ��hpΪ0��Ϊ��������
#include<cstdio>
int n,m,map0[11][11],ans=200;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 &&y<=m && map0[x][y]) return 1;
    else return 0;
}

void dfs(int x,int y,int hp,int k){
    if(k>=ans) return;
    if(map0[x][y] == 4 && hp) hp=6;
    if(!hp) return;
    if(map0[x][y] == 3){
        if(k<ans) ans=k;
        return;
    }
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0))
            dfs(x0,y0,hp-1,k+1);
    }
}

int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&map0[i][j]);
            if(map0[i][j] == 2) x=i,y=j;
        }
    }
    dfs(x,y,6,0);
    if(ans!=200)
        printf("%d\n",ans);
    else
        printf("-1\n");
    return 0;
}
*/

/*
//ac dfs
//vis[x][y][hp]=0/1��ʾ��(x,y)������ֵΪhp������Ƿ��߹�
#include<cstdio>
int n,m,map0[11][11],vis[11][11][7],ans=200;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int judge(int x,int y,int hp){
    if(x>=1 && x<=n && y>=1 &&y<=m && map0[x][y] && !vis[x][y][hp]) return 1;
    else return 0;
}

void dfs(int x,int y,int hp,int k){
    if(k>m*n || k>ans) return;
    if(map0[x][y] == 4 && hp) hp=6;
    if(!hp) return;
    if(map0[x][y] == 3){
        if(k<ans)
            ans=k;
        return;
    }
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0,hp-1)){
            vis[x0][y0][hp-1]=1;
            dfs(x0,y0,hp-1,k+1);
            vis[x0][y0][hp-1]=0;
        }
    }
}

int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&map0[i][j]);
            if(map0[i][j] == 2) x=i,y=j;
        }
    }
    vis[x][y][6]=1;
    dfs(x,y,6,0);
    if(ans!=200)
        printf("%d\n",ans);
    else
        printf("-1\n");
    return 0;
}
*/
