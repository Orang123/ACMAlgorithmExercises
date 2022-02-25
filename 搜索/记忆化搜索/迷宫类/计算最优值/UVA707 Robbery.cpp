/*
题意:摘自网上
一个n*m的城市，有小偷会偷银行，小偷偷东西t分钟后，城市会被全部封锁，
然后会有q次排查，每次排查的范围是一个矩形，给出左上角坐标（a,b)和右
下角坐标(c,d)，格式为t a,b,c,d，表示这个范围该时间小偷不再，输出所有
小偷可能在的位置和时间.
此题一开始没看明白意思.
链接:https://www.luogu.com.cn/problem/UVA707
思路:摘自网上
一共有三种情况，确定小偷所在的位置和时间，小偷逃离城市，一无所获，
要描述一个状态，至少要有三个量，(x,y,t),因为不知道小偷在哪，所以要尝试
t=1的时候小偷所有可能的位置，-1表示该状态还未确定，0表示不在，1表示可能在，
那么从开始搜就行了,如果一个状态的后继状态不全部在不可能区域，说明他可能在该位置，
记录每个时间可能的坐标，如果一个时间可能的坐标只有一个，那么久确定了小偷的位置.
记忆华搜索,dp[x][y][t]表示在t时刻x，y时有没有可能存在盗贼
*/
//ac 10ms 记忆化搜索
//dp[x][y][t]表示在t时刻x，y时有没有可能存在盗贼
//复杂度O(10^6)
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

//注意小偷可以停留在原地不动
int w,h,t,q,dp[N][N][N],dir[5][2]={{-1,0},{1,0},{0,-1},{0,1},{0,0}},cnt;
vector<pair<int,int>> ans[N];

int dfs(int x,int y,int tt){
    int &res=dp[x][y][tt];
    if(res!=-1)
        return res;
    if(tt>=t){//超过t时刻 城市就会被封锁
        cnt++;
        ans[tt].push_back(make_pair(x,y));
        return res=1;
    }
    res=0;
    int nx,ny;
    for(int i=0;i<5;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>w || ny<1 || ny>h)
            continue;
        if(dfs(nx,ny,tt+1))
            res=1;
    }
    if(res)
        ans[tt].push_back(make_pair(x,y));
    return res;
}

int main(){
    int cas=0,tt,x1,y1,x2,y2;
    while(scanf("%d%d%d",&w,&h,&t) && w+h+t){
        cas++;
        cnt=0;
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=t;i++)
            ans[i].clear();
        scanf("%d",&q);
        while(q--){
            scanf("%d%d%d%d%d",&tt,&x1,&y1,&x2,&y2);
            for(int i=x1;i<=x2;i++){
                for(int j=y1;j<=y2;j++)
                    dp[i][j][tt]=0;//矩形范围内tt时刻 不能有小偷
            }
        }
        for(int i=1;i<=w;i++){//枚举小偷的初始点,时刻是从1开始的
            for(int j=1;j<=h;j++){
                if(dp[i][j][1])
                    dfs(i,j,1);
            }
        }
        printf("Robbery #%d:\n",cas);
        if(!cnt)
            printf("The robber has escaped.\n");
        else{
            int k=0;
            for(int i=1;i<=t;i++){
                if(ans[i].size() == 1){//i时刻只有一个位置 就能确定
                    k=1;
                    printf("Time step %d: The robber has been at %d,%d.\n",i,ans[i][0].first,ans[i][0].second);
                }
            }
            if(!k)//有多个位置不能确定
                printf("Nothing known.\n");
        }
        printf("\n");
    }
    return 0;
}
