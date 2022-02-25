/*
����:ժ������
����һ������Ϊn�����У�ÿ������v[i]��Ȼ���ٸ���n����a[i],��ʾ�ϳ�i�����Ĵ��ۡ�
ÿ�ο��Խ������������кͳ�һ��������Ϊ�����и�����ĺ͡�
Ҫ�󽫸�������n�����б��һ�����Ĵ���һ������ֻ�ܱ��ϳ�һ�Ρ�
����ϲ�����С����.
n<=5000,v[i]<=10^9,a[i]<=10^4.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4960
˼·:��ΪҪ��ɻ���,����Ҫö����˿�ʼ�����������Ƿ���Ҷ˿�ʼ�������������.
��Ϊ�ϲ���ͬ����������������Ҫ�Ļ��Ѳ�ͬ,�޷�̰�Ŀ���,��Ҫö�����п��ܺϲ���
���,�����Ⱥϲ�2��,�ٺϲ�5��,�����ֱ�Ӻϲ�7��������Ⱥϲ�3��,�ٺϲ�4���ȵ�.
Ȼ�����ڲ�ͬ����ϲ��������ɵ�������,ʵ�����п�����ͬ��,Ҳ����˵,����(l,r)��
�������п����ظ���,������ö�����������еĹ����в������ص�������,�����������
��������Ҫ��¼���ص�����������Ž�,���ٴγ����ص�������ʱ,ֱ�ӷ���������.
���仯���� dp[l][r]��ʾ��������������[l,r]ʱ�ϲ��ɻ��Ĵ�ʱ������С����
*/
//ac 624ms ���仯����
//ʱ�临�Ӷ���O(n*n*cnt),��Ϊdp[i][j]ֻ�����һ��
//dp[l][r]��ʾ��������������[l,r]ʱ�ϲ��ɻ��Ĵ�ʱ������С����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
typedef long long ll;
using namespace std;

int n,v[N],a[N],dp[N][N];
ll sum[N];//sum[i]��ʾ1~i���е�ǰ׺��

int dfs(int l,int r){
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    //�Ӵ�(l,r)�ϲ��ɻ��Ĵ��ĳ�ʼ״̬��ֱ�ӽ�����Ϊr-l+1�������Ӵ��ϲ���һ�����ֵĻ���
    //��Ϊ������ж����������Ӵ�������������,������״̬��Ҫ��������.
    dp[l][r]=a[r-l+1];
    int ll=l,rr=r;
    //ö������������ȵ������Ӵ����ϲ�,��ö�ٳ��Ƚ�С���Ӵ��ϲ�,���ݺ�,��ö�ٳ��Ƚϳ����Ӵ��ϲ�
    while(ll<rr){
        if(sum[ll]-sum[l-1]<sum[r]-sum[rr-1])//��˵�ǰ׺���Ҷ˵ĺ�׺С,�������ǰ׺�ĳ���
            ll++;
        else if(sum[ll]-sum[l-1]>sum[r]-sum[rr-1])//��˵�ǰ׺���Ҷ˵ĺ�׺��,�����Ҷ�ǰ׺�ĳ���
            rr--;
        else{//��˵�ǰ׺���Ҷ˵ĺ�׺�������ʱ,���������˺ϲ��жϼ����ж��м䲿�ֵ��Ӵ�(ll+1,rr-1)��Ҫ�ϲ������ٻ���
            dp[l][r]=min(dp[l][r],a[ll-l+1]+dfs(ll+1,rr-1)+a[r-rr+1]);
            ll++;
            rr--;
        }
    }
    return dp[l][r];
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            scanf("%d",&v[i]);
            sum[i]+=sum[i-1]+v[i];
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("%d\n",dfs(1,n));
    }
    return 0;
}

/*
//ac 514ms Ԥ��������Ӷ�����+���仯����
//dp[l][r]��ʾ��������������[l,r]ʱ�ϲ��ɻ��Ĵ�����С����
//ʱ�临�Ӷ���O(n*n*cnt),��Ϊdp[i][j]ֻ�����һ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
typedef long long ll;
using namespace std;

int n,v[N],a[N],dp[N][N],cnt;
ll sum[N];
struct Section{
    int l,r;
    Section(int l=0,int r=0):l(l),r(r){}
}sec[N/2];//��������Ӵ���󳤶���N/2

int dfs(int l,int r,int i){
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    dp[l][r]=a[r-l+1];
    while(i<=cnt){//i��������������Ӵ����±�,��ö�ٽ�С���Ӵ�i�ϲ�,���ݻ�����ö�ٽϴ���Ӵ�i+1
        dp[l][r]=min(dp[l][r],a[sec[i].l-l+1]+dfs(sec[i].l+1,sec[i].r-1,i+1)+a[r-sec[i].r+1]);
        i++;
    }
    return dp[l][r];
}

int main(){
    while(scanf("%d",&n) && n){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            scanf("%d",&v[i]);
            sum[i]+=sum[i-1]+v[i];
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int l=1,r=n;
        while(l<r){//Ԥ�������������Ӵ����������
            if(sum[l]<sum[n]-sum[r-1])
                l++;
            else if(sum[l]>sum[n]-sum[r-1])
                r--;
            else{
                sec[++cnt]=Section(l,r);
                l++;
                r--;
            }
        }
        printf("%d\n",dfs(1,n,1));
    }
    return 0;
}
*/

/*
//ac 109ms ����dp û��ȫ���,������Ŀ����Ķ�̬�滮����Ҫ��ȫ�����⿴͸����,��������,
//��Ϊ��ʼ״̬����ȷ��,���ǽ��� д���仯�����ĵݹ�汾
//ժ�Բ���:https://www.cnblogs.com/zibaohun/p/4046801.html
//�ȼ�¼ǰi���ĺͺͺ�n  - j������ͬ��(i,j)�ԣ�Ȼ�����dp��
//dp[i]��ʾ�ϲ�ǰi���ͺϲ���n - g[i]���ͺϲ�������С���ۣ�
//��ô�е��ƹ�ʽdp[i] = min(dp[j] + b[i-j] + b[k - t]);
//����ans��Ϊmin(dp[i] + b[g[i] - i - 1]);
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include<set>
#include <iostream>
#include <algorithm>
using namespace std;
#define RD(x) scanf("%d",&x)
#define RD2(x,y) scanf("%d:%d",&x,&y)
#define clr0(x) memset(x,0,sizeof(x))
typedef long long LL;
#define N 10005
int n , m , K;
int a[N] , b[N];
LL sum[N];
int f[N] , g[N];

void work(){
    int i , j , k , t;
    int ans;
    sum[0] = 0;
    a[0] = 0;
    for (i=1;i<=n;++i) scanf("%d",&a[i]) , sum[i] = sum[i-1] + a[i];
    for (i=1;i<=n;++i) scanf("%d",&b[i]); ans = b[n]; b[0] = 0;
    j = n;
    for (i=1;i<=n;++i){
        while (sum[n] - sum[j-1] < sum[i]) --j;
        if (sum[n] - sum[j-1] == sum[i])
            g[i] = j;
        else g[i] = -1;
    }
    memset(f,0x3f,sizeof(f));
    g[0] = n+1; f[0] = 0;
    for (i=1;i<=n;++i){
        if (g[i] == -1) continue;
        t = g[i];
        for (j=0;j<i;++j){
                if (g[j] == -1) continue;
                k = g[j];
                if (t <= i) continue;
                f[i] = min(f[i],f[j]+b[i-j]+b[k-t]);
                ans = min(ans,f[i]+b[t-i-1]);
        }
    }
    printf("%d\n",ans);
}

int main(){
    while (~scanf("%d",&n) && n)
            work();
    return 0;
}
*/

/*
//ac 31ms ����dp
//ժ�Բ���:https://blog.csdn.net/u013840081/article/details/48231977
//˼·�����������Ҫת���ɻ������У����ǿ��Դ����˿�ʼģ�⣬�����ߵ���С���ұߵ�����
��ô��߼�����һ�����������ߴ����ұߣ���ô�ұ߼�����һ������ֱ��������ȣ���ô�ⲿ�־���Ϊһ�����壬
�ֱ��¼����ߺ��ұߺϲ��˶������֡�����������Ҹ���len�����֣�����len�����ֻ����Դ����˻��м�ϲ����õ���С�Ļ��ѣ�
��������dpһ�£�dp��i��Ϊ���ҶԳ�ǰi�����ֺϲ�����С���ۣ���ôdp��i��=min(,dp��j��+cost�����j��i ���ֺϲ��ĸ�����+cost���ұ�j��i ���ֺϲ��ĸ�����)��
���Ǵ����˵���С���ѡ����м�ϲ���ʱ�򣬷ֱ��ȥ���˺ϲ��ĸ������ټ����м�ϲ��Ļ��Ѿ����ˡ�
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include<climits>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

#define PB push_back
#define MP make_pair

#define REP(i,x,n) for(int i=x;i<(n);++i)
#define FOR(i,l,h) for(int i=(l);i<=(h);++i)
#define FORD(i,h,l) for(int i=(h);i>=(l);--i)
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define RI(X) scanf("%d", &(X))
#define RII(X, Y) scanf("%d%d", &(X), &(Y))
#define RIII(X, Y, Z) scanf("%d%d%d", &(X), &(Y), &(Z))
#define DRI(X) int (X); scanf("%d", &X)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define DRIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define OI(X) printf("%d",X);
#define RS(X) scanf("%s", (X))
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))
#define LEN(X) strlen(X)
#define F first
#define S second
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)
#define Dpoint  strcut node{int x,y}
#define cmpd int cmp(const int &a,const int &b){return a>b;}

const int MOD = 1e9+7;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;
//#define HOME

int Scan()
{
	int res = 0, ch, flag = 0;

	if((ch = getchar()) == '-')				//�ж�����
		flag = 1;

	else if(ch >= '0' && ch <= '9')			//�õ���������
		res = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9' )
		res = res * 10 + ch - '0';

	return flag ? -res : res;
}



int a[5005];
int cost[5005];
int dp[5005];
int ll[5005];
int rr[5005];
int main()
{ int n;
while(RI(n)!=EOF)
{   if(!n)
break;
     for(int i=1;i<=n;i++)
      RI(a[i]);
     for(int i=1;i<=n;i++)
        RI(cost[i]);
    int len=0;
    for(int i=1,j=n;i<j;i++,j--)
    {
        long long int lsum=a[i];
        long long int rsum=a[j];
        int lnum=1;
        int rnum=1;

        while(lsum!=rsum)
        {
            if(lsum<rsum)
            {
                lsum+=a[++i];
                lnum++;
            }
            else
            {
                rsum+=a[--j];
                rnum++;
            }
        }
        if(lsum==rsum)
        {len++;
         ll[len]=lnum;
         rr[len]=rnum;
        }


    }
    dp[0]=0;
    for(int i=1;i<=len;i++)
    {
        dp[i]=INT_MAX;
        int lt=0,rt=0;
        for(int j=i;j>=1;j--)
        {  lt+=ll[j];
           rt+=rr[j];

            dp[i]=min(dp[i],dp[j-1]+cost[lt]+cost[rt]);}
    }
    int ans=cost[n];
    for(int i=1;i<=len;i++)
    {
        n-=ll[i]+rr[i];
        ans=min(ans,dp[i]+cost[n]);
    }
    printf("%d\n",ans);

}



        return 0;
}
*/
