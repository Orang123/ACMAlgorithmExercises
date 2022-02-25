/*
题意:摘自网上
一个棋盘，横竖线都是从1到100标号（竖线从左到右标，横线从下到上标），
输入n表示有n个被标记的格子，是给出这个格子的左下角坐标，然后输入m，
在输入m个数，表示在这些竖线的地方切开棋盘（其实只切了m-2刀，因为2刀
必须是1和100，相当于没有），然后输入A，表示你要在横上上切A刀（其实也
只是A-2刀，因为2刀必须在横线的1和100）。那么就可以把棋盘很多个大小不
一的方块（矩形），只要这些方块中有被标记的小格子（1个或多个），那么这
个方块就是一个选区，我们是要使到选区的个数最多
链接:https://www.luogu.com.cn/problem/UVA10558
思路:先预处理出 行与行之间和已有竖线分割所包含标记小格子的选区个数,
在记忆化搜索枚举每个行与行之间分配几个横线 来求取含有标记格子最多的选区个数,
实际较好的分割情况是对于行与行之间所含标记格子较多的 应该多分配横线,这样
包含标记格子的选区矩形就多,如果行与行之间包含标记格子较少,就分配较少的横线
这样含有较少标记格子的选区矩形本身就少了,从而不必浪费太多的横线.

//思路详细博客可参考:https://www.cnblogs.com/scau20110726/archive/2012/10/04/2711436.html
*/
//ac 30ms 记忆化搜索
//dp[i][j]表示行在[i,100)中分配j个横线所能获得含有标记格子最多个矩形选区的个数
//path[i][j]=k表示[i,100)行的分割横线是第k行,并且当前剩下j-1个横线未分配
//复杂度O(100*100)=10^4
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

//flag[i][j]=1表示在第i行被竖线分割的第j个部分含有标记格子
//f[i][j]表示前i行被被竖线分割的第j个部分含有标记的格子数目
//num[i][j]表示第i行和第j行之间被竖线分割含有标记格子的选区矩形的数目
int n,s,a,mp[N][N],col[N],dp[N][N],flag[N][N],f[N][N],num[N][N],path[N][N];

void init(){
    for(int i=1;i<100;i++){
        for(int j=1;j<s;j++){
            for(int k=col[j];k<col[j+1];k++){
                if(mp[i][k]){
                    flag[i][j]=1;
                    break;
                }
            }
            f[i][j]=flag[i][j];//标记i行第j个部分含有标记格子
            f[i][j]+=f[i-1][j];//累加前i行第j个部分含有标记格子的选区矩形数目
        }
    }
    //计算左闭右开区间[i,j) 第i行到第j行之间(不含第j行)含有标记格子的选区矩形的个数
    for(int i=1;i<100;i++){
        for(int j=i+1;j<=100;j++){
            for(int k=1;k<s;k++){//枚举每个部分j的含有标记格子选区
                if(f[j-1][k]-f[i-1][k])
                    num[i][j]++;
            }
        }
    }
}

int dfs(int i,int j){
    if(dp[i][j]!=-1)
        return dp[i][j];
    if(!j)
        return dp[i][j]=num[i][100];
    dp[i][j]=0;
    int res;
    for(int k=i+1;k<100;k++){//枚举第j条航线分割第i行到第k行
        if(100-k-1<j-1)//如果剩下的行 不够j-1条横线分割则结束
            break;
        res=dfs(k,j-1)+num[i][k];
        if(dp[i][j]<res){
            dp[i][j]=res;
            path[i][j]=k;
        }
    }
    return dp[i][j];
}

void print(int i,int j){
    printf("%d ",a);
    printf("1");
    while(j){
        printf(" %d",path[i][j]);
        i=path[i][j];//下一个分割线
        j--;//剩下的未分配的横线数减一
    }
    printf(" 100\n");
}

int main(){
    int x,y;
    while(scanf("%d",&n) && n!=-1){
        memset(dp,-1,sizeof(dp));
        memset(mp,0,sizeof(mp));
        memset(flag,0,sizeof(flag));
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&y,&x);//输入坐标是颠倒的
            mp[x][y]=1;
        }
        scanf("%d",&s);
        for(int i=1;i<=s;i++)
            scanf("%d",&col[i]);
        scanf("%d",&a);
        init();
        dfs(1,a-2);//1和100行横线分配已经用掉了2条
        print(1,a-2);
    }
    return 0;
}
