/*
题意:摘自网上
给定区间[n,m]和d求一个排列使得连续的小于等于d且大于1长度的序列之和为合数。
n,m<=1000,2<=d<=10.
链接:http://poj.org/problem?id=2034
思路:dfs枚举全排列,在枚举的过程中,当枚举的序列已经有2位时,
没枚举一个数 就判断2..d范围内的序列是不是都是合数,如果不是合法则剪枝.
判断合数需要筛素数预处理,否则直接在线判断会TLE.
*/
//ac 891ms 筛素数预处理+dfs枚举全排列+判断合数剪枝
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1100
#define M 10000
using namespace std;

int n,m,d,len,a[N],b[N],vis[N],prim[M],sum[N];

void init(){
    int low=sqrt(M);
    for(int i=2;i<low;i++){
        if(prim[i]) continue;
        for(int j=i*i;j<M;j+=i)
            prim[j]=1;
    }
    /*
    for(int i=2;i<M/2;i++){
        if(prim[i]) continue;
        for(int j=i*2;j<M;j+=i)
            prim[j]=1;
    }
    */
}

int check(int k){
    for(int i=2;i<=min(k,d);i++){
        if(!prim[sum[k]-sum[k-i]])
            return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == len+1)
        return 1;
    for(int i=1;i<=len;i++){
        if(vis[i])
            continue;
        b[k]=a[i];
        sum[k]=sum[k-1]+b[k];
        if(k>=2 && !check(k))
            continue;
        vis[i]=1;
        if(dfs(k+1))
            return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    init();
    while(scanf("%d%d%d",&n,&m,&d) && n+m+d){
        len=0;
        memset(vis,0,sizeof(vis));
        for(int i=n;i<=m;i++)
            a[++len]=i;
        if(dfs(1)){
            for(int i=1;i<=len;i++){
                printf("%d",b[i]);
                if(i != len)
                    printf(",");
            }
            printf("\n");
        }
        else
            printf("No anti-prime sequence exists.\n");
    }
    return 0;
}

/*
//TLE dfs+在线判断合数
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,d,len,a[N],b[N],vis[N];

int check(int k,int x){
    int low,flag;
    for(int i=k-1;i>k-d && i>=1;i--){
        x+=b[i];
        low=sqrt(x);
        flag=0;
        for(int i=2;i<=low;i++){
            if(x%i == 0){
                flag=1;
                break;
            }
        }
        if(!flag) return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == len+1)
        return 1;
    for(int i=1;i<=len;i++){
        if(vis[i])
            continue;
        if(k>=2 && !check(k,a[i]))
            continue;
        vis[i]=1;
        b[k]=a[i];
        if(dfs(k+1))
            return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    while(scanf("%d%d%d",&n,&m,&d) && n+m+d){
        len=0;
        memset(vis,0,sizeof(vis));
        for(int i=n;i<=m;i++)
            a[++len]=i;
        if(dfs(1)){
            for(int i=1;i<=len;i++){
                printf("%d",b[i]);
                if(i != len)
                    printf(",");
            }
            printf("\n");
        }
        else
            printf("No anti-prime sequence exists.\n");
    }
    return 0;
}
*/
