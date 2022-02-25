/*
题意:军团是一个n行m列的矩阵,每个单元是一个血色先锋军的成员.
感染瘟疫的人,每过一个小时,就会向四周扩散瘟疫,直到所有人
全部感染上瘟疫.你已经掌握了感染源的位置,任务是算出血色先
锋军的领主们感染瘟疫的时间,并且将它报告给巫妖王,以便对血色
先锋军进行一轮有针对性的围剿.
输入:四个整数n,m,a,b表示军团矩阵有n行m列.有a个感染源,b为血色敢死队中领主的数量.
1<=n,m<=500.1<=a,b<=10^5.
链接:https://www.luogu.com.cn/problem/P1332
思路:可以将所有感染源同时入队 bfs,这样计算到达别的位置的最短时间即可.
复杂度O(n*m)=2.5*10^5.
*/
//ac bfs 202ms
//复杂度O(n*m)=2.5*10^5.
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
