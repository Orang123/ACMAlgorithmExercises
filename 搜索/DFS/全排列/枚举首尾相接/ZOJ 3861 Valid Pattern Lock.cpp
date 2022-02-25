/*
题意:摘自网上
手机锁屏，共9个数，然后给出规定，只能用给定的n个数做密码，
点与点之间的划线除了相隔的情况划出的必须是3点共线,即:中间
点必须经过,而其余的点都能直接相连成一条线.
对于一个点可以走向其他相邻8个方向，对于中间有相互隔开的情况，
例如1到3，如果2已经访问过，那么方案是可行的，求不同的锁屏方法有几种，
输出所有锁屏方案路径。
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369953
思路:因为密码最多只有10个数字,可以枚举接下来滑动密码的数字,这样就有两种情况,
一种是紧邻的数字可以直接滑动,一种是三个数字从一端滑动另一端,必然会经过中间的
点,此时要求中间的点之前也必须已经划过了.若1->2->3,从1滑到3,2必须划过才行.
*/
//ac 339ms dfs
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 10
using namespace std;

int n,a[N],mp[N][N],vis[N],cnt,path[N],ans[150000][N];

void init(){
    mp[1][3]=mp[3][1]=2;//1 3之间相隔2
    mp[4][6]=mp[6][4]=5;//4 6之间相隔5
    mp[7][9]=mp[9][7]=8;//7 9之间相隔8
    mp[1][7]=mp[7][1]=4;//1 7之间相隔4
    mp[2][8]=mp[8][2]=5;
    mp[3][9]=mp[9][3]=6;
    mp[1][9]=mp[9][1]=5;
    mp[3][7]=mp[7][3]=5;
}

void dfs(int x,int k){
    if(k == n+1){
        cnt++;
        for(int i=1;i<k;i++)
            ans[cnt][i]=path[i];
        return;
    }
    for(int i=1;i<=n;i++){//枚举x点接下来可以滑动的密码点
        if(vis[a[i]]) continue;
        //要么mp[x][a[i]]为0 表示a[i]点是与x相邻的点 可以直接滑动
        //要么mp[x][a[i]]不为0,表示x与a[i]之间有间隔点,那么必须保证间隔点mp[x][a[i]]之前已经滑过才行
        if((!mp[x][a[i]]) || (vis[mp[x][a[i]]])){
            vis[a[i]]=1;
            path[k]=a[i];
            dfs(a[i],k+1);
            vis[a[i]]=0;
        }
    }
}

int main(){
    int T;
    init();
    scanf("%d",&T);
    while(T--){
        cnt=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);//按照字典序输出滑动顺序
        dfs(0,1);//初始的0点不在滑动数字内
        printf("%d\n",cnt);
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=n;j++){
                if(j == 1)
                    printf("%d",ans[i][j]);
                else
                    printf(" %d",ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
