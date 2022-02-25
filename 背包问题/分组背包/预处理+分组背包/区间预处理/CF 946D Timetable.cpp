/*
题意:n天的课程,每天有m个时间单位.会给出n个m个长度01字符串,0代表
第i填当前时间点没课,1代表有课.每天在学校的学习时间为这天第一节课
的时间点i到最后一节课时间j的时间差,即j-i+1.现在最多能翘k节课,问最少
能在学校待多少时间.
链接:https://codeforces.ml/problemset/problem/946/D
思路:分组背包.背包容量为能翘课的次数上限k,将每一天单独作为一组,每组
的物品分别为在该天内可能翘课次数对应最多能节省的时间.在dp之前需要预
处理出每天可能翘课次数下最多能节省的时间,那么实际假设第i填要翘k门课,
那么只有选择敲掉全天内两端点边缘的课程才能使得节省出更多的时间.所以
具体做法就是枚举要翘课的次数j,再枚举具体在左端翘l门课,那么右端就是翘
j-l门课.之后分组背包求解出前n天在翘课次数最大为k下最多能节省的时间即可,
最终答案就是n*m-dp[k].这个做法可以优化掉一维空间复杂度.

注意:采用dp[i][j]代表前i天翘j门课最大能节省的时间的做法时,如果要用一维
滚动数组优化,对于每一天的翘课次数 必须是升序枚举0..num才能保证,dp[j-k]
是前i-1天 dp[i-1][j-k]的状态,如果降序,那么对于最后该天翘课次数为0时,
dp[j-0]=dp[j],dp[j] 已经被前面第i天翘课次数 num..1 更新过了,到翘课次数
为0时,dp[j]已经是前i天翘课的状态了.
*/
//ac 62ms 一维数组实现 优化空间做法 预处理+分组背包
//dp[i][j]代表前i天翘j门课最大能节省的时间 实际滚动数组可以优化一维空间dp[j]
//dp[j]=max(dp[j],dp[j-t]+val[i][t]);
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 510
#define M 510
#define INF 0x3f3f3f3f
using namespace std;

//val[i][j]代表第i天翘j门课最大能节省的时间
//pos[i][j]=t代表第i天第j+1门课在第i天的第t个时间点上
//dp[i][j]代表前i天翘j门课最大能节省的时间 实际滚动数组可以优化一维空间dp[j]
int n,m,k,w[N][M],val[N][M],dp[M];
vector<int> pos[N];

int main(){
    char str[N];
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        for(int j=1;j<=m;j++){
            if(str[j] == '1')
                //第i天第j个时间点是上课时间
                pos[i].push_back(j);
        }
    }
    //计算val[i][j] 枚举第i天
    for(int i=1;i<=n;i++){
        //第i天共上siz门课
        int siz=pos[i].size();
        //在翘课次数上限为k时,最多能翘num门课
        int num=min(k,siz);
        int mint=INF;
        //枚举第i天翘j门课
        for(int j=0;j<=num;j++){
            if(j == siz){//第i天课全翘完,最多能节省m时间点,需要单独计算 pos[i][siz-r-1]-pos[i][l]+1公式会出错,siz-r-1=-1.
                val[i][j]=m;
                break;
            }
            //m字符串左端翘l门课,右端翘r=j-l门课
            for(int l=0;l<=j;l++){
                int r=j-l;
                //右端敲掉r门课,实际第i天上的最后一门课时间点是pos[i][siz-r-1]
                //左端敲掉l门课,实际第i天上的第一门课时间点是pos[i][l]
                //因此实际上课时间为pos[i][siz-r-1]-pos[i][l]+1
                //mint 记录第i天翘j门课情况下最少上课时间
                mint=min(mint,pos[i][siz-r-1]-pos[i][l]+1);
            }
            //实际第i天翘j门课最多能节省时间就是 m时间点减去最少上课时间
            val[i][j]=m-mint;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=k;j>=0;j--){//k翘课次数可能为0,j下界是0
            //第i天最多能翘课次数为j和这天上课门数最小值 num
            int num=min(j,(int)pos[i].size());
            //这里滚动数组优化 必须保证t升序,才能保证dp[j-k]是前i-1天的状态,否则t=0时,dp[j-0]已经是前i天翘课的状态了
            for(int t=0;t<=num;t++)
                //注意这里仍然是dp[j-t],因为n天的所有上课门数 可能比k小,这里是尽可能多地装满背包
                dp[j]=max(dp[j],dp[j-t]+val[i][t]);
        }
    }
    printf("%d",n*m-dp[k]);
    return 0;
}

/*
//ac 77ms 二维数组实现 预处理+分组背包
//之所以不能用滚动数组优化是因为,这个是求解最小值,实际k=0时,一节课不翘,dp[i][0]上课时间也是一直累加增大的
//dp[i][j]代表前i填翘j门课最少的上课时间
//dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 510
#define M 510
#define INF 0x3f3f3f3f
using namespace std;

//val[i][j]代表第i天翘j门课最大能节省的时间
//pos[i][j]=t代表第i天第j+1门课在第i天的第t个时间点上
//dp[i][j]代表前i填翘j门课最少的上课时间
int n,m,k,val[N][M],dp[N][M];
vector<int> pos[N];

int main(){
    char str[N];
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        for(int j=1;j<=m;j++){
            if(str[j] == '1')
                pos[i].push_back(j);
        }
    }
    memset(val,0x3f,sizeof(val));
    for(int i=1;i<=n;i++){
        int siz=pos[i].size();
        int num=min(k,siz);
        for(int j=0;j<=num;j++){
            if(j == siz){
                val[i][j]=0;
                break;
            }
            for(int l=0;l<=j;l++){
                int r=j-l;
                val[i][j]=min(val[i][j],pos[i][siz-r-1]-pos[i][l]+1);
            }
        }
    }
    memset(dp,0x3f,sizeof(dp));
    //实际仍然是尽可能多地装满背包,因为实际k翘课次数比所有的上课门数还多,忽悠剩余
    //因此初始状态dp[0][0..k]均合法
    for(int i=0;i<=k;i++)
        dp[0][i]=0;
    //之所以不能用滚动数组优化是因为,这个是求解最小值,实际k=0时,一节课不翘,dp[i][0]上课时间也是一直累加增大的
    //所以第i天的状态必须全是INF无穷大才行.
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            int num=min(j,(int)pos[i].size());//第i填最多翘课次数
            for(int t=0;t<=num;t++)
                dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
        }
    }
    printf("%d",dp[n][k]);
    return 0;
}
*/

/*
//ac 140ms 预处理+分组背包
//另一种预处理 上课时间点前缀和
//摘自博客:https://blog.csdn.net/noone0/article/details/79466057
//dp[i][j]代表前i填翘j门课最少的上课时间
//dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e2+5,inf=0x3f3f3f3f;
int f[N][N],d[N][N];
int n,m,k,p[N];
char s[N][N];
int main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
	cin>>n>>m>>k;
	memset(d,inf,sizeof(d));
	memset(f,inf,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		p[0]=0;
		for(int j=1;j<=m;j++)
			p[j]=p[j-1]+(s[i][j]=='1');
		f[i][p[m]]=0;
		for(int l=1;l<=m;l++)
		{
			for(int r=l;r<=m;r++)
			{
				int tot=p[l-1]+(p[m]-p[r]);
				if(p[r]-p[l-1])
					f[i][tot]=min(f[i][tot],r-l+1);
				else
					f[i][tot]=0;
			}
		}

	//	for(int j=0;j<=m;j++)
	//		cout<<i<<' '<<j<<' '<<f[i][j]<<'\n';
	}
	for(int j=0;j<=k;j++)
		d[0][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int p=0;p<=j;p++)
				d[i][j]=min(d[i][j],d[i-1][p]+f[i][j-p]);
	cout<<d[n][k]<<'\n';
	return 0;
}
*/
