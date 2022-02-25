#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:将n个数排位环状，将其分为k个部分，k个部分对10取模,然后累乘起来，
求其最大和最小的值.
链接:https://www.luogu.com.cn/problem/P1043
思路:其实就是环状的整数划分问题,需要扩展数组到2n.
dp1[i][j][k],dp2[i][j][k]分别代表将[i,j]区间内的数划分为k个部分的乘积的最小值和最大值.
*/
int dp1[110][110][10],dp2[110][110][10],n,m,a[110],sum[110];
//x%10 对于负数结果大于-10,再加10后为正数之后再取余
//这里根据题意-1%10=9,应该是使得负数取模为正数,所以先取模后加10位正数后再取模(再取模是应对正数的对10取模)
int mod(int x){
    return (x%10+10)%10;
}

int main(){
    int ans1=0x3f3f3f3f,ans2=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n-1;i++)//构成前缀和方便dp[i][j][1]的求解
        sum[i]=sum[i-1]+a[i];
    memset(dp1,0x3f,sizeof(dp1));//dp1求解最小值,初始化成无穷大
    for(int i=1;i<=2*n-1;i++){//初始化dp[i][j][1]
        for(int j=i;j<=2*n-1;j++){
            dp1[i][j][1]=dp2[i][j][1]=mod(sum[j]-sum[i-1]);
        }
    }
    for(int t=2;t<=m;t++){//枚举分割成几部分,有t部分向t+1部分转移
        for(int l=t-1;l<n;l++){//枚举区间长度,起始值为t-1,因为j-i+1必须至少为t个,才能分为t部分
            for(int i=1;i+l<2*n;i++){//枚举区间起始点
                int j=i+l;
                for(int k=i+t-2;k<j;k++){//每局分割点k,k代表k部分,那么初始值需要为i+t-2,这样k-i+1才能为t-1个部分 因为是环状,最少要有t-1个数才能分成t-1部分
                    dp1[i][j][t]=min(dp1[i][j][t],dp1[i][k][t-1]*dp1[k+1][j][1]);
                    dp2[i][j][t]=max(dp2[i][j][t],dp2[i][k][t-1]*dp2[k+1][j][1]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){//求解环状的 n个可能的线性区间的最小最大值作为答案
        ans1=min(ans1,dp1[i][i+n-1][m]);
        ans2=max(ans2,dp2[i][i+n-1][m]);
    }
    printf("%d\n",ans1);
    printf("%d\n",ans2);
    return 0;
}

/*
二维数组 整数划分 转移做法
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//dp1[i][j] dp2[i][j] 分别代表前i个数分成j个部分的乘积的最小值和最大值
int dp1[60][10],dp2[60][10],n,m,a[110],sum[110];

int mod(int x){
    return (x%10+10)%10;
}

int main(){
    int ans1=0x3f3f3f3f,ans2=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]=sum[i-1]+a[i];
    for(int s=1;s<=n;s++){//枚举n个可能的长度为n的线性区间即 [s~s+n-1]
        memset(dp1,0x3f,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        for(int i=1;i<=n;i++)//初始化 前i个数分成1个部分的值 m有可能等于1,所以要计算到前n个数作为1部分的值
            dp1[i][1]=dp2[i][1]=mod(sum[i+s-1]-sum[s-1]);
        for(int t=2;t<=m;t++){//分成t部分
            for(int i=t;i<=n;i++){//枚举右边界 t部分右边界至少为t
                for(int j=t-1;j<i;j++){//t-1部分右边界至少为t-1
                    dp1[i][t]=min(dp1[i][t],dp1[j][t-1]*mod(sum[i+s-1]-sum[j+s-1]));
                    dp2[i][t]=max(dp2[i][t],dp2[j][t-1]*mod(sum[i+s-1]-sum[j+s-1]));
                }
            }
        }
        ans1=min(ans1,dp1[n][m]);//当前线性区间[s,s+n-1]求解最值
        ans2=max(ans2,dp2[n][m]);
    }
    printf("%d\n",ans1);
    printf("%d\n",ans2);
    return 0;
}
*/

/*
//ac 55ms 暴力dfs 摘自dingcx网友
#include<cstdio>
#include<algorithm>//算法库，有max和min
using namespace std;
const int MAXN=110;
const int INF=0x3f3f3f3f;//定义成2e9或2147483647也行
const int n9[9]={9,81,729,6561,59409,531441,4782969,43046721,387420489};//m<=9，打个表就好了
int n,m;
int a[MAXN];
int ansmin=INF,ansmax=0;//最小和最大，都要初始化
int mod10(int x){//计算模10的函数
	return (x%10+10)%10;
}
void dfs(int depth,int now,int value){//重磅dfs
	if(value>=ansmin&&value*n9[m-depth]<=ansmax) return;//剪枝
	int sum=0;
	if(depth==m){
		for(int i=now;i<=n;i++) sum+=a[i];//计算和
		ansmin=min(ansmin,value*mod10(sum));//比较
		ansmax=max(ansmax,value*mod10(sum));
		return;
	}
	for(int i=now;i<=(n-m+depth);i++){//遍历下一个点
		sum+=a[i];//前缀和
		dfs(depth+1,i+1,value*mod10(sum));//下一步计算
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i+n]=a[i];//破环成链
	}
	for(int i=1;i<=n;i++){//枚举初始点
		dfs(1,1,1);//都是1，只是巧合
		for(int j=1;j<=2*n;j++) a[j]=a[j+1];//往前挪
	}
	printf("%d\n%d\n",ansmin,ansmax);//输出
	return 0;//华丽结束
}
*/
