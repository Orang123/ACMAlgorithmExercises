/*
题意:n*n网格,由'O'和'X'组成,'X'不能走,'O'能走,
可以朝东、南、西、北、上、下6个方向走,没走一步花费是1,
求从(sx,sy,sz)走到(ex,ey,ez)的最小花费,如果不能走到输出-1.
1<=n<=10.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1240
思路:基础三维网格 bfs.只是注意输入的mp格式是mp[x][y][z],而不是mp[z][x][y],
起点终点坐标给出的是(z,y,x).
*/
//ac 0ms bfs 三维空间mp[x][y][z]
#include<cstdio>
#include<queue>
#include<cstring>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;

int n,dir[6][3]={{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,1},{0,0,-1}},ex,ey,ez;
char mp[N][N][N];
struct State{
    int x,y,z,s;
    State(int x=0,int y=0,int z=0,int s=0):x(x),y(y),z(z),s(s){}
};

int bfs(int sx,int sy,int sz){
    queue<State> Q;
    mp[sx][sy][sz]='X';
    Q.push(State(sx,sy,sz,0));
    State tp;
    int nx,ny,nz;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.x == ex && tp.y == ey && tp.z == ez)
            return tp.s;
        Q.pop();
        for(int i=0;i<6;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            nz=tp.z+dir[i][2];
            if(nz>=0 && nz<n && nx>=0 && nx<n && ny>=0 && ny<n && mp[nx][ny][nz]!='X'){
                mp[nx][ny][nz]='X';
                Q.push(State(nx,ny,nz,tp.s+1));
            }
        }
    }
    return -1;
}

int main(){
    int sz,sx,sy,ans;
    char str[10];
    while(scanf("%s%d",str,&n)!=EOF){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++)
                    scanf(" %c",&mp[i][j][k]);
            }
        }
        scanf("%d%d%d",&sz,&sy,&sx);
        scanf("%d%d%d",&ez,&ey,&ex);
        scanf("%s",str);
        ans=bfs(sx,sy,sz);
        if(ans!=-1)
            printf("%d %d\n",n,ans);
        else
            printf("NO ROUTE\n");
    }
    return 0;
}
