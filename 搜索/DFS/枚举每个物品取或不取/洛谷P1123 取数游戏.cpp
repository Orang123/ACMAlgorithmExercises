/*
题意:一个N×M的由非负整数构成的数字矩阵，你需要在其中取出若干个数字，
使得取出的任意两个数字不相邻（若一个数字在另外一个数字相邻8个格子中
的一个即认为这两个数字相邻），求取出数字和最大是多少。
n,m<=6.
链接:https://www.luogu.com.cn/problem/P1123
思路:枚举每个格子取或不取,需要标记取到的格子的8个方向都是不能取的.
*/
#include<cstdio>
#include<cstring>
int a[8][8],n,m,vis[8][8],maxs;

int judge(int x,int y){
    if(!vis[x][y-1]&&!vis[x-1][y] &&!vis[x][y+1]&&!vis[x+1][y]&&!vis[x-1][y-1]&&!vis[x-1][y+1]&&!vis[x+1][y-1]&&!vis[x+1][y+1])
        return 1;
    else
        return 0;
}
//可以尝试++mark[x+d[fx][0]][y+d[fx][1]];
void dfs(int x,int y,int sum){
    if(x>n){
        if(sum>maxs) maxs=sum;
        return;
    }
    if(y>m)
        x++,y=1;
    if(judge(x,y)){//也可以取完某个数,就把8个方向标记为不可取,dfs(x,y+1)vis判断当前(x,y)是否还能取,
        vis[x][y]=1;
        dfs(x,y+1,sum+a[x][y]);//y+1,回溯时也是再考虑后面的结果,只不过这个数不再选取,那么相邻元素的影响也会改变
        vis[x][y]=0;
    }
    dfs(x,y+1,sum);//y+1,前面的不会再试探,因为dfs深度遍历已经将包含前面的位置遍历过了,会重复遍历的.
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        maxs=0;
        memset(a,0,sizeof(a));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        dfs(1,1,0);
        printf("%d\n",maxs);
    }
    return 0;
}
