/*
题意:摘自网上
平面上有k个障碍点。 从(0,0)点出发，第一次走1个单位，第二次走2个单位，……，
第n次走n个单位，恰好回到(0,0)。 要求只能沿着东南西北方向走，且每次必须转弯90°
（不能沿着同一个方向继续走，也不能后退）。 走出的图形可以自交，但不能经过障碍点。
输出所有可走的方向路径序列。
注意:每次走i步后,会停留在该点参观,但是该点只会参观一次.
n<=20.实际网格
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=161
思路:dfs每次走的步数要加1,其次要记录上次走的方向,不能走的方向和上次方向一样,
以及不能往回走.每次走s步,需要单独每一步每一步判断所走的位置是否存在障碍物,以及是否
超过边界.有可能障碍点坐标为负,但数组下标不能为负,所以记录和判断障碍点坐标(x,y)
时要对坐标加上105,整个网格所能走的最大长度为1+2+..20=20*21/2=210,但实际因为所走
方向不能朝着一个方向一直走,因此大概105是最大直线长度.
还有一个基于曼哈顿距离的剪枝,如果当前位置(x,y)距离原点的曼哈顿距离abs(x)+abs(y)大于
剩下所能走的距离sum[n]-sum[s]时 结束.
sum[i]表示前i次所能走的最大距离.
此题因为并没有求取最短距离,因此采用bfs也是可以实现的.
*/
//ac 280ms dfs+剪枝
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 250
#define maxn 105
using namespace std;

int n,k,sum[21],dir[4][2]={{1,0},{0,1},{0,-1},{-1,0}},mp[N][N],ans;
char path[21],pathDir[4]={'e','n','s','w'};//要按字典序 记录路径因此是ensw东北南西

int exceed(int x,int y){
    if(abs(x)>maxn || abs(y)>maxn)
        return 1;
    return 0;
}

int check(int x,int y,int d,int s){
    for(int i=1;i<=s;i++){
        x+=dir[d][0];
        y+=dir[d][1];
        if(exceed(x,y) || mp[x+maxn][y+maxn] == -1)//走s步过程中遇到障碍点 要结束
            return 0;
    }
    //剪枝:如果当前位置(x,y)距离原点的曼哈顿距离abs(x)+abs(y)大于剩下所能走的距离sum[n]-sum[s]时 结束.
    if(abs(x)+abs(y)>sum[n]-sum[s])//不加曼哈顿距离剪枝760ms,加上这个剪枝280ms
        return 0;
    return 1;
}

void dfs(int x,int y,int d,int s){
    if(s == n+1){//第n次的n步走完
        if(!x && !y){
            ans++;
            for(int i=1;i<=n;i++)
                printf("%c",path[i]);
            printf("\n");
        }
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        if(i == d || i+d == 3)//不能朝着和上次方向一致方向走 也不能往回走
            continue;
        if(!check(x,y,i,s))
            continue;
        nx=x+dir[i][0]*s;
        ny=y+dir[i][1]*s;
        if(!mp[nx+maxn][ny+maxn]){//走s步后,停留在的(nx,ny)点 只会停留一次
            mp[nx+maxn][ny+maxn]=1;//标记该点已访问
            path[s]=pathDir[i];//记录方向
            dfs(nx,ny,i,s+1);
            mp[nx+maxn][ny+maxn]=0;
        }
    }
}

int main(){
    int T,x,y;
    for(int i=1;i<=20;i++)
        sum[i]=sum[i-1]+i;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(mp,0,sizeof(mp));
        scanf("%d%d",&n,&k);
        while(k--){
            scanf("%d%d",&x,&y);
            if(exceed(x,y))
                continue;
            mp[x+maxn][y+maxn]=-1;
        }
        dfs(0,0,-1,1);
        printf("Found %d golygon(s).\n\n",ans);
    }
    return 0;
}
