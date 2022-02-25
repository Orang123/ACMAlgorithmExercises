/*
����:һ��С͵,���ı�������k����Ʒ,�̵���n����Ʒ,ÿ����Ʒ�������޶��.
ÿ����Ʒ��ֵ��a[i],����Ҫ���С͵����͵�ߵ���Ʒ��ֵ֮�͵�������������.
1<=n,k<=1000,1<=a[i]<=1000
����:http://codeforces.com/contest/632/problem/E
˼·:ֱ���ö�ά����ָ����Ʒ�����ļ�ֵ֮�Ϳ϶���mle,tle,�����������ɴ�10^6,
n*k���10^6,�ܸ��Ӷ�O(10^12)��Ȼ������.���Կ��ǽ���Ʒ����,�ѳ���һ����С��Ʒ
���������Ʒ��ֵ����ȥ�����Ʒ�ļ�ֵ,�ñ��Ϊ2~n����Ʒ����ȫ����,dp[j]=i��ʾ
�õ���Ʒ��ֵ�ܺ�Ϊjʱ����Ҫ͵����Ʒ����.����ж�ֻҪdp[j]<=k,��ʵ��͵�õ���Ʒ��ֵ
Ϊj+a[i]*k,������������ô���,��Ϊ������,������Щ��ֵ����û�к���һ����С����Ʒ
��,������dp[j]͵�õ���Ʒ��С��k,��ô����취����һЩ��Ʒ����ﵽk����Ʒ,ԭ��͵�õ�
��Щ��Ʒ��ֵ���ټ��˸���һ����Ʒ�ļ�ֵ,��Щ����Ҫȫ������a[1],�ܹ���dp[j]����Ʒ,ʣ��
k-dp[j]����Ʒ�ǵ���û��ѡ��һ����Ʒ,��ʣ�µ���Ʒȫ��ѡ�ɵ�һ����Ʒ,�����ʹճ���k����Ʒ,
����ʵ��õļ�ֵ��Ϊj+a[1]*k.���dp[j]�պõ���k,��ʵ����Щ��Ʒ�ļ�ֵ��ֻҪ��ԭ��ÿ����Ʒ
ȱ�ٵ�a[1]����ͺ�,���Լ�ֵ�Ծ���j+a[1]*k.
*/
//ac 545ms ��ȫ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;

int n,k,a[N],dp[M],sum;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(int i=2;i<=n;i++)
        a[i]-=a[1];
    dp[0]=0;
    for(int i=2;i<=n;i++){
        //dpÿ���׶εı��������ǵ�����,��i���׶α�������Ϊֻѡk����i����Ʒ�ļ�ֵ��
        sum=a[i]*k;
        for(int j=a[i];j<=sum;j++)
            dp[j]=min(dp[j],dp[j-a[i]]+1);
    }
    sum=a[n]*k;
    //�����½���0,
    for(int i=0;i<=sum;i++){
        if(dp[i]<=k)
            printf("%d ",i+a[1]*k);
    }
    return 0;
}

/*
//��ά������ȫ���� TLE MLE
//dp[k][j]=1����ѡk����Ʒ���ɼ�ֵΪj����������Ǵ��ڵ�
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;

int n,k,a[N],dp[N][M],sum;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    dp[0][0]=1;//��ʼ״̬
    for(int i=1;i<=n;i++){
    	sum=a[i]*k;
        for(int j=a[i];j<=sum;j++){//��ȫ�������ﱳ������������
        	for(int t=1;t<=k;t++)//�������� ���򶼿���
            	if(dp[t-1][j-a[i]])//��һ��״̬�Ϸ� �ſ���ת��,�����ǺõĺϷ�״̬����³ɲ��Ϸ���
                	dp[t][j]=dp[t-1][j-a[i]];
		}
    }
    //ѡ��Ʒ�����ͱ����������Եߵ�ѭ��
    //for(int i=1;i<=n;i++){
        //for(int t=1;t<=k;t++){//��ȫ�������ﱳ������������
    		//sum=a[i]*t;
        	//for(int j=a[i];j<=sum;j++){//���������򡢽��򶼿�
            	//if(dp[t-1][j-a[i]])//��һ��״̬�Ϸ� �ſ���ת��,�����ǺõĺϷ�״̬����³ɲ��Ϸ���
                	//dp[t][j]=dp[t-1][j-a[i]];
			//}
		//}
    //}
    sum=a[n]*k;
    //����ѡk����Ʒ�� ��Ʒ��ֵ����Щ����Ǵ���
    for(int i=1;i<=sum;i++){
        if(dp[k][i])
            printf("%d ",i);
    }
    return 0;
}
*/

/*
//ac 1294ms ���ɺ�������
//ժ�Բ���:https://www.cnblogs.com/Memory-of-winter/p/9718254.html
#include <cstdio>
#include <algorithm>
#define maxn 1 << 20 | 3
const int G = 3;
int mod, ans;
int lim, ilim, s, rev[maxn], Wn[maxn];
inline int pw(int base, long long p) {
    base %= mod, p %= mod - 1;
    int ans = 1;
    for (; p; p >>= 1, base = 1ll * base * base % mod) if (p & 1) ans = 1ll * ans * base % mod;
    return ans;
}
inline int Inv(int x) {
    return pw(x, mod - 2);
}
inline void up(int &a, int b) {if ((a += b) >= mod) a -= mod;}
inline void NTT(int *A, int op) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int t = lim / mid >> 1;
        for (int i = 0; i < lim; i += mid << 1) {
            for (int j = 0; j < mid; j++) {
                int W = op ? Wn[t * j] : Wn[lim - t * j];
                int X = A[i + j], Y = 1ll * A[i + j + mid] * W % mod;
                up(A[i + j], Y), up(A[i + j + mid] = X, mod - Y);
            }
        }
    }
    if (!op) for (int i = 0; i < lim; i++) A[i] = 1ll * A[i] * ilim % mod;
}
inline void init(int n, int mod) {
    ::mod = mod;
    lim = 1, s = -1; while (lim < n) lim <<= 1, s++; ilim = Inv(lim);
    for (int i = 0; i < lim; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    int W = pw(G, (mod - 1) / lim);
    Wn[0] = 1; for (int i = 1; i <= lim; i++) Wn[i] = 1ll * Wn[i - 1] * W % mod;
}
int n, k;
int a[maxn], b[maxn];
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0, tmp; i < n; i++) scanf("%d", &tmp), a[tmp] = b[tmp] = 1;
    init(1 << 20, 998244353);
    NTT(a, 1);
    for (int i = 0; i < lim; i++) a[i] = pw(a[i], k);
    NTT(a, 0);
    init(1 << 20, 1004535809);
    NTT(b, 1);
    for (int i = 0; i < lim; i++) b[i] = pw(b[i], k);
    NTT(b, 0);
    for (int i = 0; i < lim; i++) if (a[i] | b[i]) printf("%d ", i);
    return 0;
}
*/
