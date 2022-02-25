/*
����:r*c�����ӹ��ɵ��Թ�,'#'����ǽ,'.'�����ͨ�и���,'F'�����Ż��,'J'����Joe�ĳ�ʼλ��,
'F'�Ż��ÿ��������������4������ĸ�������,Joeÿ����Ҳ������������4������Ŀ�ͨ��û�Ż�
�ĸ�������,�������Joe�߳��Թ���Ҫ������ʱ��.ע������г�ʼ���Ż������жദ.
1<=r,c<=1000.
����:https://www.luogu.com.cn/problem/UVA11624
˼·:2��bfs����.��һ��bfs�ǶԳ�ʼ�Ż�������չ,���ÿ��'.'(x,y)��ʼ�Ż���Ҫ������ʱ��f[x][y].
�ڶ���bfs�Ƕ�Joe��ʼλ�ý���������չ,��չ��������ǵ�����(nx,ny)��'.'�ҵ�ǰ���ߵ�ʱ��С��(nx,ny)
�Ż���Ҫ������ʱ��.

ע��:����ͬ��������dfs����,��Ϊ��������޷���֤������ȱ�����״̬����ʱ�����ٵ�,���ֻὫ�߹���״̬
���,�������������� �ֲ�����֮ǰ֮ǰ�����ĵ�,�����ͻ�wa.
*/
//ac 310ms 2��bfs 1����չ�Ż��״̬,1����չJoe���ߵ�״̬
//ʱ�临�Ӷ�O(rc)=10^6 �������չ��״̬���Թ��������������
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int r,c,f[N][N],vis[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,m;
    State(int x=0,int y=0,int m=0):x(x),y(y),m(m){}
};
queue<State> Q;

void bfs1(){
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nx][ny]!='#' && f[nx][ny] == INF){
                //���״̬��ֵҪ����for�ڲ�,���ܷ���pop����֮ǰ,���������ʼ�Ż���״̬��չ�����Ǳ�ĳ�ʼ�Ż��,��ô��ĳ�ʼ�Ż�㱾��ʱ����0,�ͻᱻ��ֵΪ���ֵ
                f[nx][ny]=tp.m+1;//bfs����������״̬һ������С��ʱ��
                Q.push(State(nx,ny,tp.m+1));
            }
        }
    }
}

int bfs2(int sx,int sy){
    vis[sx][sy]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x<1 || tp.x>r || tp.y<1 || tp.y>c)
            return tp.m;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(!vis[nx][ny] && mp[nx][ny]!='#' && tp.m+1<f[nx][ny]){
                vis[nx][ny]=1;
                Q.push(State(nx,ny,tp.m+1));
            }
        }
    }
    return -1;
}

int main(){
    int T,sx,sy,ans;
    scanf("%d",&T);
    while(T--){
        memset(mp,'.',sizeof(mp));
        memset(f,0x3f,sizeof(f));
        scanf("%d%d",&r,&c);
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'F'){
                    f[i][j]=0;//��ʼ�Ż�� ��������Ż��� ��Ҫʱ��Ϊ0
                    Q.push(State(i,j,0));//���ܺ��ж���Ż�� Ҫȫ�����
                }
                else if(mp[i][j] == 'J'){
                    sx=i;
                    sy=j;
                }
            }
        }
        bfs1();
        memset(vis,0,sizeof(vis));
        ans=bfs2(sx,sy);
        while(!Q.empty()) Q.pop();
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}

/*
//ac 220ms ����bfs
//ʵ�ʿ��Խ����г�ʼ�Ż���Joeһͬ���,���Ż���Joeͬʱ��չ,�Ż��Ҫ�����,
//�����Ż����չ����״̬,��Ϊ�Ż���Joe�ǰ��ն���ͬʱ����չ��,ʱ����Ҳ��ͬʱ�̵�,
//�Ż����չ����״̬Ҫ����Ϊ'#',Joe�϶��ǲ����ߵ�,ͬ��Joe��չ����״̬Joe�϶�Ҳ�������ߵ����״̬��,����Ϊ'#'
//��Ϊʱ���Ͽ϶��������ٵ�.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int r,c,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,m,flag;
    State(int x=0,int y=0,int m=0,int flag=0):x(x),y(y),m(m),flag(flag){}
};
queue<State> Q;

int bfs(int sx,int sy){
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0,1));//Joe������
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x<1 || tp.x>r || tp.y<1 || tp.y>c)
            return tp.m;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            //�Ż����չ����״̬ ����Ϊ'#' �Ż�㲻����չ���Թ�֮��
            if(!tp.flag && nx>=1 && nx<=r && ny>=1 && ny<=c && mp[nx][ny]!='#'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,0,0));
            }
            //Joe �߹���״̬ Ҫ����Ϊ'#' ��Ϊ�����ܱȵ�ǰ��ʱ���� ������չ���Թ�֮�������жϱ߽�
            else if(tp.flag && mp[nx][ny]!='#'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.m+1,1));
            }
        }
    }
    return -1;
}

int main(){
    int T,sx,sy,ans;
    scanf("%d",&T);
    while(T--){
        memset(mp,'.',sizeof(mp));
        scanf("%d%d",&r,&c);
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'F'){
                    mp[i][j]='#';//��ʼ�Ż�� ֱ������Ϊ'#'��������
                    Q.push(State(i,j,0,0));
                }
                else if(mp[i][j] == 'J'){
                    sx=i;
                    sy=j;
                }
            }
        }
        //�����Ż��F��Joeͬʱ���,Joe������
        ans=bfs(sx,sy);
        while(!Q.empty()) Q.pop();
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}
*/

/*
1<=r,c<=1000 ��ͨ��dfs�͵�������dfs����TLE ��������ļ�֦Ҫö������4��������Թ���ʱ�䶼���ڸ�����ʱ���򷵻�,��֦Ч�ʲ�����
*/
