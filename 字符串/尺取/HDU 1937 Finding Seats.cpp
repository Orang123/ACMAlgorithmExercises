/*
题意:摘自网上
给定一个n*m的矩阵，选择一个面积最小的子矩阵，使得其内部‘.’的个数>=k。
n,m<=300.k<=n*m.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1937
思路:按照容斥原理如果直接枚举行列,需要O(n^4)复杂度,显然TLE.
可以用尺取优化行或列成线性时间.
*/
//ac 483ms
//尺取线性时间枚举列
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;

//sum[i][j]表示(1,1)到(i,j)含有'.'的个数.
int n,m,k,sum[N][N],ans;

int main(){
    char x;
    int l,r;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        memset(sum,0,sizeof(sum));//不初始化sum会wa,按道理是不用初始化的
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '.')
                    sum[i][j]=1;
                else
                    sum[i][j]=0;
                sum[i][j]+=sum[i][j-1];//累加同一行左侧的'.'的个数
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                sum[i][j]+=sum[i-1][j];//累加同一列上面'.'的个数
        }
        ans=n*m;
        for(int i=1;i<=n;i++){//枚举行
            for(int j=i;j<=n;j++){
                l=r=1;//应用尺取 线性时间枚举列
                while(r<=m){
                    //这里是容斥原理 sum[i-1][l-1]被多减了一次因此要再加上
                    //如果比k小,就增大列的范围r 尝试扩大矩形
                    while(r<=m && sum[j][r]-sum[j][l-1]-sum[i-1][r]+sum[i-1][l-1]<k)
                        r++;
                    if(sum[j][r]-sum[j][l-1]-sum[i-1][r]+sum[i-1][l-1]>=k)
                        ans=min(ans,(j-i+1)*(r-l+1));
                    l++;//增大左边界列的范围尝试缩小矩形
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 592ms
//尺取线性时间枚举行
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
using namespace std;

int n,m,k,sum[N][N],ans;

int main(){
    char x;
    int l,r;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
    	memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '.')
                    sum[i][j]=1;
                else
                    sum[i][j]=0;
                sum[i][j]+=sum[i][j-1];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                sum[i][j]+=sum[i-1][j];
        }
        ans=n*m;
        for(int i=1;i<=m;i++){//枚举列
            for(int j=i;j<=m;j++){
                l=r=1;//应用尺取 线性时间枚举行
                while(r<=n){
                    while(r<=n && sum[r][j]-sum[r][i-1]-sum[l-1][j]+sum[l-1][i-1]<k)
                        r++;
                    if(sum[r][j]-sum[r][i-1]-sum[l-1][j]+sum[l-1][i-1]>=k)
                        ans=min(ans,(j-i+1)*(r-l+1));
                    l++;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
