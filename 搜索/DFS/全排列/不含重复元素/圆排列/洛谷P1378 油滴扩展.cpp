/*
题意:在一个长方形框子里，最多有n个相异的点，在其中任何一个
点上放一个很小的油滴，那么这个油滴会一直扩展，直到接触到其
他油滴或者框子的边界。必须等一个油滴扩展完毕才能放置下一个油滴。
那么应该按照怎样的顺序在这n个点上放置油滴，才能使放置完毕后所
有油滴占据的总面积最大呢？（不同的油滴不会相互融合）。
结果输出长方形盒子剩余的最小空间（结果四舍五入输出）。
n<=6.
链接:https://www.luogu.com.cn/problem/P1378
思路:需要枚举放入油滴的所有可能顺序,求取所有顺序中油滴最大的扩展面积.
每次开始扩展某个油滴时需要计算其能扩展的最大半径,首先需要和矩阵的
两对角顶点比较,求取最小和墙壁相切半径,其次还需和之前已经扩展的油滴
的圆的最小相切半径,计算方式为计算两圆心距离,减去之前扩展圆的半径,就是
当前圆相切时的半径.
要注意:有可能之前扩展圆的圆心距离要小于之前圆半径,此时当前圆是完全被
包括在之前的已经扩展圆内的,所以当前圆半径为0.
*/
//ac 38ms dfs枚举全排列
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 10
#define Pi 3.141592653
using namespace std;

//定义为x1,y1,x2,y2 洛谷就会报int y1’被重新声明为不同意义的符号 编译错误,不知何原因
int n,xx1,yy1,xx2,yy2,x[N],y[N],vis[N];
double r[N],ans;

double calR(int i){
    double R,d;
    R=min(fabs(xx1-x[i]),fabs(yy1-y[i]));
    R=min(R,min(fabs(xx2-x[i]),fabs(yy2-y[i])));
    for(int j=1;j<=n;j++){
        if(vis[j] && j!=i){
            d=sqrt(fabs(x[i]-x[j])*fabs(x[i]-x[j])+fabs(y[i]-y[j])*fabs(y[i]-y[j]));
            /*
            有可能之前扩展圆的圆心距离要小于之前圆半径,此时当前圆是完全被
            包括在之前的已经扩展圆内的,所以当前圆半径为0.
            */
            R=min(R,max(d-r[j],0.0));
        }
    }
    return R;
}

void dfs(int k){
    if(k == n+1){
        double sum=0;
        for(int i=1;i<=n;i++)
            sum+=Pi*r[i]*r[i];
        if(sum>ans)
            ans=sum;
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            r[i]=calR(i);//注意这里不是r[k]=calR(i),而是根据枚举排列的顺序 确定第i个油滴的半径.方便calR(i)时 和之前圆对比半径
            dfs(k+1);
            vis[i]=0;
        }
    }
}

int main(){
    int s;
    scanf("%d",&n);
    scanf("%d%d",&xx1,&yy1);
    scanf("%d%d",&xx2,&yy2);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    dfs(1);
    s=abs(xx1-xx2)*abs(yy1-yy2);
    printf("%.0f",round(s-ans));
    return 0;
}

/*
一组测试数据
input
3
-98 5 30 30
-42 11
-51 17
-11 22

output
2547

如果当前扩展圆半径不和0对比,有些圆是扩展不了的,R=min(R,max(d-r[j],0.0));
输出结果为
2542(wa)
*/
