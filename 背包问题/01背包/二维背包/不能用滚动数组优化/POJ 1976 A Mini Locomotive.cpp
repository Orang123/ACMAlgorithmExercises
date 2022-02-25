#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 4
using namespace std;
//ac 0ms ��ά01����
//��������Ʒ����һ������װ�� ���ֶεı���
//���dp����ʵ�ʴ�������ᱻ������������hack��
//�����������HDU 3602 ��������������Ƚ���
/*
1
5
35 40 50 10 10
2
�����������135,��©�������һ������10,ʵ�ʴ���5������ȫ
������,����:145
*/
/*
����:n�ڳ���,ÿ�ڳ�������һ�������˿�,��������ͷ����������k������,
����������ͷ���տ������ĳ����г˿�������Ƕ���.
ͨ����������:��һ������������3������Ϊ������k���������������ֵ��
����:http://poj.org/problem?id=1976
˼·:���Խ�ÿ��������k�����ῴ��һ������,���ֵΪk������ĳ˿�������.
��ΪҪ����n������װ��3����ͷ,��3����ͷ�Ϳɿ�����������,��ôdp[i][j]
��ʾǰi���������ӵ�ǰj����ͷ��������ĳ˿���.

�����ù��������Ż���Ϊdp[i-k][j-1] i-kֻ�ж�ά���ܱ�֤��ǰ���״̬
*/
//sum[i]��ʾ���Ϊ (i-k+1)~i������k��������ܳ˿���
//dp[i][j]��ʾǰi���������ӵ�ǰj����ͷ��������ĳ˿���.
int n,k,a[N],dp[N][M],sum[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&k);
        int tp=0;
        for(int i=1;i<=n;i++){
            tp+=a[i];
            if(i>=k){
                sum[i]=tp;
                tp-=a[i-k+1];
            }
        }
        for(int i=k;i<=n;i++){
            for(int j=1;j<=3;j++)
                //dp[i-1][j]��ʾǰi-1���������ӵ�ǰj����ͷ�������ĳ˿���,��(i-k+1)~i�ĳ��᲻���ӵ���j����ͷ
                //dp[i-k][j-1]+sum[i] ��(i-k+1)~i�ĳ������ӵ���j����ͷ,������һ״̬����ǰi-k���������ӵ�ǰj-1����ͷ�������˿���
                dp[i][j]=max(dp[i-1][j],dp[i-k][j-1]+sum[i]);
        }
        printf("%d\n",dp[n][3]);
    }
    return 0;
}

/*
//����dp
//ac 0ms POJ discussģ�������ṩ
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX_N	50000


int n, m;
int cars[MAX_N];
int results[7][MAX_N + 1];


int calc()
{
	for (int i = 1; i < 7; ++i) {
		results[i][0] = 0;

		if (i % 2 == 0) {
			for (int j = 1; j <= n; ++j) {
				results[i][j] = max(results[i][j - 1], results[i - 1][j]);
			}
		}
		else {
			int sum = 0;
			for (int j = 1; j <= n; ++j) {
				if (j <= m) {
					sum += cars[j - 1];
					results[i][j] = sum;
				}
				else {
					sum += cars[j - 1];
					sum -= cars[j - m - 1];
					results[i][j] = sum + results[i - 1][j - m];
				}
			}
		}
	}

	return results[6][n];
}


int main()
{
	int t; scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		scanf("%d", &n);
		while (n < 1 || n > MAX_N) printf("...");

		for (int j = 0; j < n; ++j) {
			scanf("%d", &cars[j]);
		}
		scanf("%d", &m);

		printf("%d\n", calc());
	}
    return 0;
}
*/

/*
//�����߶���
//ac 16ms POJ discussģ�������ṩ
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int Read(){
    int e = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while('0' <= ch && ch <= '9') e = e*10 + (ch-'0'), ch = getchar();
    return e;
}

const int maxn = 1e5 + 7;
int tree[maxn<<2], k[maxn], s[maxn];

inline int max(int u, int v){
    return u>v? u: v;
}

void Buildtree(int l, int r, int key){
    if(l == r){
        tree[key] = k[l];
        return;
    }
    int mid = (l + r) >> 1;
    Buildtree(l, mid, key<<1);
    Buildtree(mid+1, r, key<<1|1);
    tree[key] = max(tree[key<<1], tree[key<<1|1]);
}

int Query(int l, int r, int ls, int rs, int key){
    if(ls <= l && r <= rs) return tree[key];
    int mid = (l + r) >> 1, ans = 0;
    if(ls <= mid) ans = max(ans, Query(l, mid, ls, rs, key<<1));
    if(mid < rs) ans = max(ans, Query(mid+1, r, ls, rs, key<<1|1));
    return ans;
}

int main(){
    int t = Read(), n, len;
    while(t --){
        n = Read();
        for(int i = 1; i <= n; i ++) k[i] = Read();
        len = Read();
        for(int i = 1; i <= n; i ++){
            k[i] += k[i-1];
            s[i] = k[i] - k[max(i-len, 0)];
        }
        for(int i = 1; i <= n; i ++) k[i] = s[i];
        Buildtree(1, n, 1);
        for(int i = len+1; i <= n; i ++) k[i] = Query(1, n, 1, i-len, 1) + s[i];
        Buildtree(1, n, 1);
        int ans = 0;
        for(int i = 2*len+1; i <= n; i ++){
            k[i] = Query(1, n, 1, i-len, 1) + s[i];
            ans = max(k[i], ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}
*/

/*
//ac 32ms ���仯���� ����������Ҳ�ǱȽϴ��ɰ� ��Ϊʵ����������ܲ�����ȫ��������
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50010
int dp[3][N];
int a[N];
int b[N];
int n,k;
int dfs(int num,int l)
{
    if(num<0||l<0||l>=n) return 0;
    if(dp[num][l]) return dp[num][l];
    return dp[num][l]=max(dfs(num,l-1),dfs(num-1,l-k)+b[l]);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(b,0,sizeof(b));
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
            scanf("%d",&k);
        for(int i=k-1;i<n;i++)
                for(int j=i;j>=i-k+1;j--)
            b[i]+=a[j];
        printf("%d\n",dfs(2,n-1));
    }
    return 0;
}
*/
