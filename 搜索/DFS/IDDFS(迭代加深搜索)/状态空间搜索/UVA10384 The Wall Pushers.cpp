/*
����:ժ������
���Թ���S��������ÿ�ο����������ϡ�������4������֮һǰ����
���ǰ����ǽ�ڣ���Ϸ�߿��԰�ǽ����ǰ��һ����������»���
���������ǽ�������ƶ������⣬��Ϸ��Ҳ�����ƶ���Ϸ�����
���ϵ�ǽ�������ٵĲ����߳��Թ����߽紦û��ǽ�ĵط����ǳ��ڣ���
�Թ�������4��6�У����ʱ�������һ���ƶ����м��ɡ�
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1325
˼·:����ʵ��ֻ��4*6��,�������ֱ��dfs������ը.
�������(x,y)λ�õ�״̬�漰��ǽ��״̬,��˲���ֱ����vis[x][y]��ά����
����,��Ҫ����άvis[x][y][mp[x][y]]����.
���ǿ��Կ�����IDA*,����(x,y)λ���ظ����ʵ�����,����ֱ���õ�����
���ȥ��֦,������ѭ��,��֦�ǻ��������پ���ļ�֦,�жϵ�ǰλ��
��������ĳ��������ߵĲ���,�����ǰ������������Ҫ�ߵĲ�������
��ǰ���������,�ͼ�֦.
�������ڵ�ǰ(x,y)���߷�����iǽ,�����ߵ�λ��(nx,ny)�ڸ÷���i��ǽ�����,
Ҫ����(x,y)λ����i������ǽ,(nx,ny)��i������ǽ,(nx+dir[i][0],ny+dir[i][1]),
λ�����Ӧ��i�ķ��������ǽ,�����(nx,ny)�ж�ǽ,nx+dir[i][0],ny+dir[i][1])
��Ȼ�ͻ�����ǽ,�����ð�λ���ʵ��ǽ��״̬�ĸ���.
*/
//ac 50ms IDA*-�����پ����֦
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],rec[4]={2,3,0,1};
vector<pair<int,int> > endPoints;//���ڵ�ļ���
char path[N*N],str[5]="WNES";

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

int dis(int x,int y){
    int d=INF;
    for(pair<int,int> &tp : endPoints)
        d=min(d,abs(x-tp.first)+abs(y-tp.second));
    return d;
}

int dfs(int x,int y,int d,int dep){
    if(d == dep)
        return check(x,y);
    if(d+dis(x,y) > dep)
        return 0;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[x][y] & 1<<i){//(x,y)��i������ǽ
            if((mp[nx][ny] & 1<<i))
                continue;
            if((i==0 && y==1) || (i==1 && x==1) || (i==2 && y==6) || (i==3 && x==4))
                continue;
            mp[x][y]^=1<<i;//��ǰ(x,y)λ��Ҫȡ��i�����ǽ
            mp[nx][ny]^=1<<i;//(nx,ny)���ߵ��ķ���Ҫ����i�����ǽ
            if(judge(nx+dir[i][0],ny+dir[i][1]))//(nx,ny)i������ڵ�λ��(nx+dir[i][0],ny+dir[i][1])��i�ķ�����rec[i]Ҳ����ǽ
                mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
            path[d]=str[i];
            if(dfs(nx,ny,d+1,dep))
                return 1;
            mp[x][y]^=1<<i;
            mp[nx][ny]^=1<<i;
            if(judge(nx+dir[i][0],ny+dir[i][1]))
                mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
        }
        else{//��i������ǽ
            path[d]=str[i];
            if(dfs(nx,ny,d+1,dep))
                return 1;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++){
                scanf("%d",&mp[i][j]);
                if(i == 1 && !(mp[i][j] & 2))
                    endPoints.push_back(make_pair(i,j));
                else if(i == 4 && !(mp[i][j] & 8))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 1 && !(mp[i][j] & 1))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 6 && !(mp[i][j] & 4))
                    endPoints.push_back(make_pair(i,j));
            }
        }
        for(int i=1;;i++){
            if(dfs(sx,sy,0,i)){
                for(int j=0;j<i;j++)
                    printf("%c",path[j]);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
//ac 10ms bfs+vis��ά״̬���
//vis[x][y][mp[x][y]]=1��ʾ(x,y)λ��ǽ��״̬Ϊmp[x][y]�Ѿ�������
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 10
#define M 16
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],rec[4]={2,3,0,1},vis[N][N][M];
vector<pair<int,int> > endPoints;
char str[5]="WNES";

struct State{
    int mp[N][N],x,y,d;
    char path[N*N];
    int vis[N][N][M];
};

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

void bfs(int sx,int sy){
    queue<State> Q;
    State tp,next;
    memset(tp.vis,0,sizeof(tp.vis));
    tp.vis[sx][sy][mp[sx][sy]]=1;
    tp.x=sx,tp.y=sy;
    memcpy(tp.mp,mp,sizeof(mp));
    tp.d=0;
    Q.push(tp);
    while(!Q.empty()){
        tp=Q.front();
        if(check(tp.x,tp.y)){
            for(int i=0;i<tp.d;i++)
                printf("%c",tp.path[i]);
            printf("\n");
            break;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            next.x=tp.x+dir[i][0];
            next.y=tp.y+dir[i][1];
            if(tp.mp[tp.x][tp.y] & 1<<i){
                if(tp.mp[next.x][next.y] & 1<<i)
                    continue;
                if((i==0 && tp.y==1) || (i==1 && tp.x==1) || (i==2 && tp.y==6) || (i==3 && tp.x==4))
                    continue;
                    memcpy(next.path,tp.path,sizeof(tp.path));
                    memcpy(next.mp,tp.mp,sizeof(tp.mp));
                    next.mp[tp.x][tp.y]^=1<<i;
                    next.mp[next.x][next.y]^=1<<i;
                    if(judge(next.x+dir[i][0],next.y+dir[i][1]))
                        next.mp[next.x+dir[i][0]][next.y+dir[i][1]]^=1<<rec[i];
            }
            else{
                memcpy(next.path,tp.path,sizeof(tp.path));
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
            }
            if(!tp.vis[next.x][next.y][next.mp[next.x][next.y]]){
                next.path[tp.d]=str[i];
                next.d=tp.d+1;
                memcpy(next.vis,tp.vis,sizeof(tp.vis));
                next.vis[next.x][next.y][next.mp[next.x][next.y]]=1;
                Q.push(next);
            }
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++)
                scanf("%d",&mp[i][j]);
        }
        bfs(sx,sy);
    }
    return 0;
}
*/

/*
//ac 0ms dfs+�����پ����֦
//vis[x][y][mp[x][y]]=1��ʾ(x,y)λ��ǽ��״̬Ϊmp[x][y]�Ѿ�������
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 10
#define M 16
#define INF 0x3f3f3f3f
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//WNES 1248
int mp[N][N],vis[N][N][M],rec[4]={2,3,0,1},ans;
vector<pair<int,int> > endPoints;
char path[N*N],res[N*N],str[5]="WNES";

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=6)
        return 1;
    return 0;
}

int check(int x,int y){
    return x<1 || x>4 || y<1 || y>6;
}

int dis(int x,int y){
    int d=INF;
    for(pair<int,int> &tp : endPoints)
        d=min(d,abs(x-tp.first)+abs(y-tp.second));
    return d;
}

void dfs(int x,int y,int d){
	if(check(x,y)){
		if(d<ans){
			ans=d;
			memcpy(res,path,sizeof(path));
		}
		return;
	}
    if(d+dis(x,y) > ans)//û�����֦ Ҳ��3000ms
        return;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[x][y] & 1<<i){
            if((mp[nx][ny] & 1<<i))
                continue;
            if((i==0 && y==1) || (i==1 && x==1) || (i==2 && y==6) || (i==3 && x==4))
                continue;
            if(!vis[nx][ny][mp[nx][ny]^1<<i]){
            	mp[x][y]^=1<<i;
            	mp[nx][ny]^=1<<i;
            	if(judge(nx+dir[i][0],ny+dir[i][1]))
                	mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
           	 	path[d]=str[i];
            	vis[nx][ny][mp[nx][ny]]=1;
            	dfs(nx,ny,d+1);
            	vis[nx][ny][mp[nx][ny]]=0;
            	mp[x][y]^=1<<i;
            	mp[nx][ny]^=1<<i;
            	if(judge(nx+dir[i][0],ny+dir[i][1]))
                	mp[nx+dir[i][0]][ny+dir[i][1]]^=1<<rec[i];
			}
        }
        else if(!vis[nx][ny][mp[nx][ny]]){
            vis[nx][ny][mp[nx][ny]]=1;
            path[d]=str[i];
            dfs(nx,ny,d+1);
            vis[nx][ny][mp[nx][ny]]=0;
        }
    }
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&sy,&sx) && sx+sy){
        endPoints.clear();
        ans=INF;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=6;j++){
                scanf("%d",&mp[i][j]);
                if(i == 1 && !(mp[i][j] & 2))
                    endPoints.push_back(make_pair(i,j));
                else if(i == 4 && !(mp[i][j] & 8))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 1 && !(mp[i][j] & 1))
                    endPoints.push_back(make_pair(i,j));
                else if(j == 6 && !(mp[i][j] & 4))
                    endPoints.push_back(make_pair(i,j));
            }
        }
        vis[sx][sy][mp[sx][sy]]=1;
        dfs(sx,sy,0);
        vis[sx][sy][mp[sx][sy]]=0;
        for(int j=0;j<ans;j++)
            printf("%c",res[j]);
        printf("\n");
    }
    return 0;
}
*/
