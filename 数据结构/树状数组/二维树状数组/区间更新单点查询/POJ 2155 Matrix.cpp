/*
题意:摘自网上
给定一个矩阵，初始化为0，现在可以进行两种操作，一种是查询某个点的值是0还是1。
另一种是让这个矩阵的一个子矩阵内的值取反。
链接:http://poj.org/problem?id=2155
思路:二维树状数组,对于最终查询结果通过累加和取模即可.
二维树状数组单点更新 区间查询博客学习:https://blog.csdn.net/qq_41837216/article/details/85041511
*/
//ac 563ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,c[N][N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int y,int d){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=n;j+=lowbit(j)){//这里j 每次都是初始化为y的,之前用while 一直wa就是j没有初始化
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
    int T,p,x1,y1,x2,y2;
    char q;
    scanf("%d",&T);
    while(T--){
        memset(c,0,sizeof(c));
        scanf("%d%d",&n,&p);
        while(p--){
            scanf(" %c",&q);
            if(q == 'C'){
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                //更新要从4个角更新,update(x1,y1,1);会把多余的网格翻转,
                //因此(x2+1,y1) (x1,y2+1) (x2+1,y2+1)要把多余翻转出来的再翻转过去
                update(x1,y1,1);//每次更新累加1 表示当前翻转次数加1
                update(x2+1,y1,1);
                update(x1,y2+1,1);
                update(x2+1,y2+1,1);
            }
            else{
                scanf("%d%d",&x1,&y1);
                printf("%d\n",getsum(x1,y1)%2);//c[x][y]存的是矩阵[1..x][1..y]被翻转的次数,若是偶数则会回到初始0状态,否则则是1状态
            }
        }
        if(T)
            printf("\n");
    }
    return 0;
}
