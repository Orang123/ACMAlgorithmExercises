/*
题意:n*m的网格,'X'是墙不可以穿越,'S'是出发点
'D'是终点,问能否从出发点出发在T时刻恰好到达D点.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1010
思路:因为是恰好T时刻到达D点,没要求最短时间,因此dfs搜索.
2个剪枝.剪枝1:最短曼哈顿距离剪枝,剪枝2:奇偶距离一致性剪枝.
*/
//ac 405ms dfs+2剪枝
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
char map[10][10];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
bool visit[10][10];
int n,m,T,x2,y2;
bool judge(int x,int y){
    if(x>=1&&x<=n&&y>=1&&y<=m){
        if((map[x][y]=='.'||map[x][y]=='D')&&!visit[x][y])
            return true;
        return false;
    }
    return false;
}
int dfs(int x,int y,int t){
    //(x,y)到达出口(x2,y2)的最短曼哈顿距离
    int min_s=abs(x-x2)+abs(y-y2);
    if(min_s<=T-t){
        //剪枝2:奇偶距离剪枝
        //从A点到达B点的所有路径长度的奇偶性一定是一致的,长度可以不同,
        //但是偶数就都是偶数,是奇数一定都是奇数.这个和迷宫网格本身的性质有关.
        //这里是比较A到B的最短曼哈顿距离的奇偶性和剩下时间所能走到距离,
        //如果奇偶性 不一致,则一定是不能再(T-t)长度下到达出口的
        if(min_s%2 != (T-t)%2)
            return 0;
        //这个奇偶剪枝 是等效的,即:奇数-奇数=偶数 偶数-偶数=偶数 奇数-偶数=奇数 偶数-奇数=奇数
        //即:如果奇偶性不一致,则所做减法的结果一定是奇数
        //if((T-t-min_s)&1)
            //return 0;
    }
    else//min_s>T-t 剪枝1:曼哈顿距离剪枝:如果最短曼哈顿距离已经比剩下的时间还长,则必然不可能再T-t剩余时间到达出口
        return 0;
    if(t==T&&map[x][y]=='D')
        return 1;
    if(t>T) return 0;
    int xx,yy;
    for(int i=0;i<4;i++){
        xx=x+dir[i][0];
        yy=y+dir[i][1];
        if(judge(xx,yy)){
            visit[xx][yy]=true;
            if(dfs(xx,yy,t+1))
                return 1;
            visit[xx][yy]=false;
        }
    }
    return 0;
}
int main(){
    int x1,y1,min_s;
    while(scanf("%d%d%d",&n,&m,&T)&&n||m||T){
        memset(visit,false,sizeof(visit));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&map[i][j]);
                if(map[i][j]=='S'){
                    x1=i,y1=j;
                    map[x1][y1]='.';
                    visit[x1][y1]=true;
                }
                if(map[i][j]=='D')
                    x2=i,y2=j;
            }
        }
        if(dfs(x1,y1,0))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
