/*
����:������һ��n��m�еľ���,ÿ����Ԫ��һ��Ѫɫ�ȷ���ĳ�Ա.
��Ⱦ���ߵ���,ÿ��һ��Сʱ,�ͻ���������ɢ����,ֱ��������
ȫ����Ⱦ������.���Ѿ������˸�ȾԴ��λ��,���������Ѫɫ��
����������Ǹ�Ⱦ���ߵ�ʱ��,���ҽ��������������,�Ա��Ѫɫ
�ȷ������һ��������Ե�Χ��.
����:�ĸ�����n,m,a,b��ʾ���ž�����n��m��.��a����ȾԴ,bΪѪɫ������������������.
1<=n,m<=500.1<=a,b<=10^5.
����:https://www.luogu.com.cn/problem/P1332
˼·:���Խ����и�ȾԴͬʱ��� bfs,�������㵽����λ�õ����ʱ�伴��.
���Ӷ�O(n*m)=2.5*10^5.
*/
//ac bfs 202ms
//���Ӷ�O(n*m)=2.5*10^5.
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 510
using namespace std;

int n,m,a,b,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N];
struct State{
    int x,y,m;
    State(int x=0,int y=0,int m=0):x(x),y(y),m(m){}
};
vector<pair<int,int>> V;
queue<State> Q;

int bfs(){
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny] == -1){
                mp[nx][ny]=tp.m+1;
                Q.push(State(nx,ny,tp.m+1));
            }
        }
    }
    return -1;
}

int main(){
    int x,y;
    V.clear();
    memset(mp,-1,sizeof(mp));
    scanf("%d%d%d%d",&n,&m,&a,&b);
    for(int i=1;i<=a;i++){
        scanf("%d%d",&x,&y);
        mp[x][y]=0;
        Q.push(State(x,y,0));
    }
    for(int i=1;i<=b;i++){
        scanf("%d%d",&x,&y);
        V.push_back(make_pair(x,y));
    }
    bfs();
    for(pair<int,int> &tp : V)
        printf("%d\n",mp[tp.first][tp.second]);
    return 0;
}
