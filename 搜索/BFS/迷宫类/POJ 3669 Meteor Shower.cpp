/*
����:��m��ը���ֱ���tiʱ������(xi,yi)�㱬ը,��ը�漰������
�������ڵ��������������,��ը���ĵ㲻����,�ʴ�(0,0)����,��
��һ�������ܷ��ܵ���ȫ����.
0<=x,y<=300.t<=1000
����:http://poj.org/problem?id=3669
˼·:bfs,����Ԥ�ȴ����ÿ����(x,y)�ᱻը����ըӰ�쵽������ʱ��mp[x][y].
mp��ʼ��ΪINF(0x3f3f3f3f).
Ȼ���(0,0)�㿪ʼbfs,����������ߵ�(tp.x,tp.y)����ʱ��tp.t+1<mp[x][y]����,
����ߵ��ĵ�(x,y) mp[x][y] == INF,˵���õ��Ѿ����ᱻը������Ӱ�쵽.��ô���Ѿ�
�ִﰲȫ������.
*/
//ac 94ms bfs
//���Ӷ�O(300*300)=90000
#include<cstdio>
#include<queue>
#include<cstring>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;

int m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};

int bfs(){
    queue<State> Q;
    mp[0][0]=0;
    Q.push(State(0,0,0));
    int nx,ny;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<0 || ny<0 || tp.t+1>=mp[nx][ny])
                continue;
            if(mp[nx][ny] == INF)//�ѵ��� û��ը����ը�����ĵ�(nx,ny)�ͷ���  ����ʱ��tp.t+1.
                return tp.t+1;
            mp[nx][ny]=0;//�߹��ĵ� ��������,��Ϊ������ʱ�϶��ȵ�ǰ����. ����Ϊ����ʱ������ɴ�
            Q.push(State(nx,ny,tp.t+1));
        }
    }
    return -1;
}

int main(){
    int x,y,t,nx,ny;
    while(scanf("%d",&m)!=EOF){
        memset(mp,0x3f,sizeof(mp));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&t);
            mp[x][y]=min(mp[x][y],t);//�����
            for(int i=0;i<4;i++){//ը�������� ��������4����
                nx=x+dir[i][0];
                ny=y+dir[i][1];
                if(nx<0 || ny<0)
                    continue;
                mp[nx][ny]=min(mp[nx][ny],t);
            }
        }
        printf("%d\n",bfs());
    }
    return 0;
}
