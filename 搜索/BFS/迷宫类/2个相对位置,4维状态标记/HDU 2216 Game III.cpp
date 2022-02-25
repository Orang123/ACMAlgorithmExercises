/*
题意:n*m的网格,'.'表示空位,'X'表示墙,'Z'表示Zjt,'S'表示Sara.
如果Zjt移动一个单位,Sara会向相反方向移动一个单位,如果Sara遇到
墙'X'会越界,可以不移动,但是Zjt必须保证移动,如果最终Zjt和Sara会
相遇或相邻,则停止,现在求出Zjt和Sara相遇或相邻需要移动的最少步数,
如果不能相遇或相邻输出"Bad Luck!".
注意:此题的输入有问题,用scanf(" %c",&mp[i][j])会wa 不知何原因.
n,m<=200.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2216
思路:bfs,状态标记需要设置成四维的vis[zx][zy][sx][sy]表示Zjt和Sara
是否到达过当前的相对位置状态,(zx,zy)表示Zjt,(sx,sy)表示Sara.
*/
//ac 15ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][N][N];
char mp[N][N];
struct State{
    int zx,zy,sx,sy,t;
    State(int zx=0,int zy=0,int sx=0,int sy=0,int t=0):zx(zx),zy(zy),sx(sx),sy(sy),t(t){}
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>m || mp[x][y] == 'X')
        return 1;
    return 0;
}

int bfs(int zx,int zy,int sx,int sy){
    queue<State> Q;
    vis[zx][zy][sx][sy]=1;
    Q.push(State(zx,zy,sx,sy,0));
    State tp;
    int nzx,nzy,nsx,nsy;
    while(!Q.empty()){
        tp=Q.front();
        //判断Zjt和Sara是否相邻
        for(int i=0;i<4;i++){
            if((tp.zx+dir[i][0] == tp.sx) && (tp.zy+dir[i][1] == tp.sy))
                return tp.t;
        }
        //判断Zjt和Sara是否相遇
        if(tp.zx == tp.sx && tp.zy == tp.sy)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nzx=tp.zx+dir[i][0];
            nzy=tp.zy+dir[i][1];
            nsx=tp.sx-dir[i][0];//Sara朝相反方向
            nsy=tp.sy-dir[i][1];
            if(check(nzx,nzy))//Zjt必须移动
                continue;
            if(check(nsx,nsy)){//Sara可以不移动
                nsx=tp.sx;
                nsy=tp.sy;
            }
            if(vis[nzx][nzy][nsx][nsy])
                continue;
            vis[nzx][nzy][nsx][nsy]=1;
            Q.push(State(nzx,nzy,nsx,nsy,tp.t+1));
        }
    }
    return -1;
}

int main(){
    int zx,zy,sx,sy,ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            //此题的输入有问题,用scanf(" %c",&mp[i][j])会wa 不知何原因
            scanf("%s",mp[i]+1);
            for(int j=1;j<=m;j++){
                if(mp[i][j] == 'Z')
                    zx=i,zy=j;
                else if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        ans=bfs(zx,zy,sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("Bad Luck!\n");
    }
    return 0;
}
