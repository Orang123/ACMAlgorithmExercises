/*
题意:摘自网上
n种立方体，每种有无限个，让你以长宽为底，一个个搭起来（下面的立方体的长和宽
必须大于上面的长和宽）求能得到的最长高，立方体能翻来覆去交换长宽高来用。
n<=30.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=378
思路:每种立方体有无限个,但实际根据摆放方式,每种有3!=6个状态.
分别是:(x,y,z)、(y,x,z)、(y,z,x)、(z,y,x)、(x,z,y)、(z,x,y).
然后可以将所有的6*n个立方体按照底面积x*y从小到达排序,这个问题
就转化成了求解6*n个立方体的LIS的累加高.
其中LIS上升的条件是 排在后面的立方体的长和宽要分别大于排在前面
的立方体.
*/
//ac 0ms 每个立方体有6种状态
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
using namespace std;

int n,m,dp[N],ans;
struct S{
    int x,y,z;
    S(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
    bool operator < (const S &p)const{
        return x*y<p.x*p.y;
    }
}a[N*6];

int main(){
    int cas=0,x,y,z;
    while(scanf("%d",&n) && n){
        cas++;
        m=0;
        while(n--){
            scanf("%d%d%d",&x,&y,&z);
            a[++m]=S(x,y,z);a[++m]=S(y,x,z);
            a[++m]=S(y,z,x);a[++m]=S(z,y,x);
            a[++m]=S(x,z,y);a[++m]=S(z,x,y);
        }
        sort(a+1,a+1+m);
        ans=0;
        for(int i=1;i<=m;i++){
            dp[i]=a[i].z;
            for(int j=1;j<i;j++){
                //下面的立方体的长和宽 要分别大于上面的立方体
                if(a[i].x>a[j].x && a[i].y>a[j].y)
                    dp[i]=max(dp[i],dp[j]+a[i].z);
            }
            ans=max(ans,dp[i]);
        }
        printf("Case %d: maximum height = %d\n",cas,ans);
    }
    return 0;
}

/*
//ac 0ms 每个立方体枚举3个状态,分别以x、y、z作为高
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
using namespace std;

int n,m,dp[N],ans;
struct S{
    int x,y,z;
    S(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
    bool operator < (const S &p)const{
        return x*y<p.x*p.y;
    }
}a[N*3];

int main(){
    int cas=0,x,y,z;
    while(scanf("%d",&n) && n){
        cas++;
        m=0;
        while(n--){
            scanf("%d%d%d",&x,&y,&z);
            a[++m]=S(x,y,z);
            a[++m]=S(y,z,x);
            a[++m]=S(x,z,y);
        }
        sort(a+1,a+1+m);
        ans=0;
        for(int i=1;i<=m;i++){
            dp[i]=a[i].z;
            for(int j=1;j<i;j++){
                //x为长 y为宽 或颠倒长宽 x为宽 y为长
                if((a[i].x>a[j].x && a[i].y>a[j].y) || (a[i].x>a[j].y && a[i].y>a[j].x))
                    dp[i]=max(dp[i],dp[j]+a[i].z);
            }
            ans=max(ans,dp[i]);
        }
        printf("Case %d: maximum height = %d\n",cas,ans);
    }
    return 0;
}
*/

/*
//ac 0ms DAG最长路问题,还没看
//摘自博客:https://blog.csdn.net/vv494049661/article/details/50752318
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 200;
int n,num;
bool g[maxn][maxn];
int dp[maxn];

struct node {
    int x,y,z;
    void f(int a,int b,int c) {
        x = a;
        y = b;
        z = c;
    }
}st[200];
bool check(int i,int j) {
    if(st[i].x < st[j].x && st[i].y < st[j].y || (st[i].y < st[j].x && st[i].x < st[j].y))
        return true;
    return false;
}
int d(int k) {
    if(dp[k]!=-1)
        return dp[k];
    dp[k] = st[k].z;
    for(int i =0; i < num; i++)
        if(g[k][i])
            dp[k] = max(dp[k],d(i) + st[k].z);
    return dp[k];
}
int main() {

    int n;
    int x,y,z;
    int T = 1;
    while(scanf("%d",&n) &&n) {
         num = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d %d %d",&x,&y,&z);
            st[num++].f(x,y,z);
            st[num++].f(x,z,y);
            st[num++].f(y,z,x);
        }
        memset(g,0,sizeof(g));
        for(int i = 0 ; i < num; i++) {
            for(int j = i + 1;j < num; j++) {
                g[i][j] = check(i,j);
                g[j][i] = check(j,i);
            }
        }
        int ans = 0;
        memset(dp,-1,sizeof(dp));
        for(int i = 0; i < num; i++)
            ans = max(ans,d(i));
        printf("Case %d: maximum height = %d\n",T++,ans);
    }
    return 0;
}
*/
