/*
题意:给出m个圆的半径，这组圆排成一排，要求都切于底面，
求要用最少长为多少的长方形能装下它们.
m<=8.
链接:https://www.luogu.com.cn/problem/UVA10012
思路:需要考虑m个圆的所有可能排放位置,因此枚举m个圆
的全排列,对每个排列中圆心距离矩形左端的距离并不是
在上一个圆相切的位置,因为有可能两个大圆之间间隔着很多
小圆,和上一个圆相切有可能和上上个圆相交,因此当前圆的圆心
位置是距离和之前所有圆相切时加上相切圆圆心坐标位置的最大值,
两圆相切的水平距离计算公式为sqrt((r1+r2)^2-(r1-r2)^2)
*/
//ac 40ms 回溯枚举全排列
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 10
#define INF 1e40
using namespace std;

int m,vis[N];
//b[i]表示生成排列中第i个圆圆心距离矩形左端的位置
//a[i]表示生成排列中第i个圆的半径
double r[N],a[N],b[N],ans;

double getDis(double r1,double r2){
    return 2*sqrt(r1*r2);//(r1+r2)^2-(r1-r2)^2 平方差公式开方
}

void dfs(int k){
    if(k == m+1){
        b[1]=a[1];//第一个圆的圆心位置就是其半径
        for(int i=2;i<=m;i++){
            //如果b[i]初始为0,有可能和上个圆相切,但是和墙壁却相交显然是不合法的
            b[i]=a[i];//这里要初始化为a[i],有可能第i个圆是紧贴矩形左端(即使不是第一个圆),此时本身半径才是最大的,而前面都是较小的圆(并没有紧贴墙壁)
            for(int j=1;j<i;j++)//枚举第i个圆和前面位置圆相切时圆心的最大位置 保证和之前所有圆都不相交
                b[i]=max(b[i],b[j]+getDis(a[i],a[j]));
        }
        double res=0;
        //同理和矩形右端相切的圆也不一定是最后一个圆,因此要求出m个圆心坐标加上其半径的最大距离,最大的那个圆才是和矩形右端相切的
        for(int i=1;i<=m;i++){
            if(b[i]+a[i]>res)
                res=b[i]+a[i];
        }
        if(res<ans)//记录最小的矩形的总长度
            ans=res;
    }
    for(int i=1;i<=m;i++){
        if(!vis[i]){
            a[k]=r[i];
            vis[i]=1;
            dfs(k+1);
            vis[i]=0;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(vis,0,sizeof(vis));
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%lf",&r[i]);
        dfs(1);
        printf("%.3f\n",ans);
    }
    return 0;
}

/*
//ac 30ms stl next_permutation
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 10
#define INF 1e40
using namespace std;

int m;
double r[N],b[N],ans;

double getDis(double r1,double r2){
    return 2*sqrt(r1*r2);//(r1+r2)^2-(r1-r2)^2 平方差公式开方
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%lf",&r[i]);
        sort(r+1,r+1+m);
        do{
            b[1]=r[1];
            for(int i=2;i<=m;i++){
                b[i]=r[i];
                for(int j=1;j<i;j++)
                    b[i]=max(b[i],b[j]+getDis(r[i],r[j]));
            }
            double res=0;
            for(int i=1;i<=m;i++){
                if(b[i]+r[i]>res)
                    res=b[i]+r[i];
            }
            if(res<ans)
                ans=res;
        }while(next_permutation(r+1,r+1+m));
        printf("%.3f\n",ans);
    }
    return 0;
}
*/
