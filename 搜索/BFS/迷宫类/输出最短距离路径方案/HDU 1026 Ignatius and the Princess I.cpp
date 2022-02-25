/*
//����ժ������
����:��һ��n*m������ͼ,'.'��ʾ������,'X'��ʾ��ǽ,��������,
'1~9'����������һ��Ѫ��Ϊn�Ĺ���,��ܹ�����ʱn,ÿ��һ����ʱ1.
Ҫ�����Ͻ�(0,0)�ߵ����½�(n-1,m-1),����ܵ���,�������Сʱ��
�����·���ķ���.��֤���û�й���Ҳ������ǽ,�յ㲻��ǽ,�����й���.
2<=n,m<=100.1<=n<=9.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1026
˼·:��Ϊ���������Ҫ���ʱ,���Բ������ȶ���bfs.
���������State�Ķ�ά����洢��һ״̬����.
*/
//ac 15ms bfs���ȶ���+������·������
#include<cstdio>
#include<queue>
#include<cstring>
#define N 110
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N],t;
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
}pre[N][N];

int check(int x,int y){
    if(x<0 || x>=n || y<0 || y>=m || mp[x][y] == 'X')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.top();
        if(tp.x == n-1 && tp.y == m-1)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            if(mp[nx][ny] == '.' && !vis[nx][ny]){
                vis[nx][ny]=1;
                pre[nx][ny]=tp;
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny]>='1' && mp[nx][ny]<='9' && !vis[nx][ny]){
                vis[nx][ny]=1;
                pre[nx][ny]=tp;
                Q.push(State(nx,ny,tp.t+mp[nx][ny]-'0'+1));
            }
        }
    }
    return -1;
}

void print(int x1,int y1,int x2,int y2){
    if(!x2 && !y2)//������� ����,��㿪ʼ�ĵ�һ�����ߵ�����һ��Ҳ�����й���
        return;
    print(pre[x1][y1].x,pre[x1][y1].y,x1,y1);
    t++;
    printf("%ds:(%d,%d)->(%d,%d)\n",t,x1,y1,x2,y2);
    if(mp[x2][y2]>='1' && mp[x2][y2]<='9'){
        int cnt=mp[x2][y2]-'0';
        while(cnt){
            t++;
            printf("%ds:FIGHT AT (%d,%d)\n",t,x2,y2);
            cnt--;
        }
    }
}


int main(){
    int ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        t=0;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                scanf(" %c",&mp[i][j]);
        }
        ans=bfs(0,0);
        if(ans!=-1){
            printf("It takes %d seconds to reach the target position, let me show you the way.\n",ans);
            print(pre[n-1][m-1].x,pre[n-1][m-1].y,n-1,m-1);
        }
        else
            printf("God please help our poor hero.\n");
        printf("FINISH\n");
    }
    return 0;
}
