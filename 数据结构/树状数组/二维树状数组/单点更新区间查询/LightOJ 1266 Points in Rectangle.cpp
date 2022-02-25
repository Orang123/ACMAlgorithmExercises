/*
题意:摘自网上
给一个平面，有两个操作
0 x y 在(x,y)处放置一个点
1 x1 y1 x2 y2 查询左下角为(x1,y1)，
右上角为(x2,y2)的矩形区域包含多少个点（包括边界）
n<=1000.
链接:http://lightoj.com/volume_showproblem.php?problem=1266
思路:二维树状数组单点更新,区间查询.
二维树状数组单点更新 区间查询参考博客:https://blog.csdn.net/qq_41837216/article/details/85041511

*/
//ac 408ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,c[N][N],m[N][N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int y,int d){
    for(int i=x;i<N;i+=lowbit(i)){
        for(int j=y;j<N;j+=lowbit(j)){//这里j 每次都是初始化为y的,之前用while 一直wa就是j没有初始化
            c[i][j]+=d;
        }
    }
}

int getsum(int x,int y){
    int sum=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            sum+=c[i][j];
        }
    }
    return sum;
}

int main(){
    int T,q,p,x1,y1,x2,y2;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(c,0,sizeof(c));
        memset(m,0,sizeof(m));
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf("%d",&p);
            if(!p){
                scanf("%d%d",&x1,&y1);
                x1++,y1++;
                //这里不能用c[x1][y1]判断(x1,y1)是否放置过点,因为c[x1][y1]表示的是 (1,1)到(x1,y1)范围内放置的点个数
                if(!m[x1][y1]){
                    update(x1,y1,1);
                    m[x1][y1]=1;
                }
            }
            else{
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                x1++,y1++,x2++,y2++;
                //+getsum(x1-1,y1-1) 是因为-getsum(x1-1,y2)-getsum(x2,y1-1)会将 (x1-1,y1-1)多减一次
                printf("%d\n",getsum(x2,y2)+getsum(x1-1,y1-1)-getsum(x1-1,y2)-getsum(x2,y1-1));
            }
        }
    }
    return 0;
}
