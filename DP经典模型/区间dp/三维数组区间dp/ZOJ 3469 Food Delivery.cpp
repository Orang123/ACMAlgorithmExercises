#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
����:��һ����������ԱҪȥ�����������ĵ���Xλ�ã������ٶ�Ϊ(1/V)��Ҳ������V�ĵ�λ������Ҫ����V����,
Ȼ��������N����Ҫ����������ֱ�ΪXi�� ��N����ÿ��һ���Ӳ����������Bi��
������������Ҫ���ܵĲ����������,�����ٵĲ�������Ƕ���.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368754
˼·:����dp
dp[i][j][0]��������i~jͣ��i�ͻ�λ�õ����ٲ������
dp[i][j][1]��������i~jͣ��j�ͻ�λ�õ����ٲ������
*/

struct Node{
    int pos,val;
    bool operator < (const Node &x)const{
        return pos<x.pos;
    }
}node[1005];

int dp[1005][1005][2],sum[1005],n,v,x;

int main(){
    while(scanf("%d%d%d",&n,&v,&x)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].pos,&node[i].val);
        node[n+1].pos=x,node[n+1].val=0;//���������λ��,�����Ĳ������,��ԶΪ0
        n++;
        sort(node+1,node+n+1);//���򷽱�dp ״̬ת��ʱ�Ӳ��������ߵĿͻ�ת��
        memset(dp,0x3f,sizeof(dp));
        int st;
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+node[i].val;//sum�����¼������ȵ�ǰ׺��
            if(node[i].pos == x){
                st=i;//��¼������λ��
                dp[i][i][0]=dp[i][i][1]=0;//��С����״̬Ӧ�ǴӲ�����ʼ
            }
        }
        for(int i=st;i>=1;i--){//�Ӳ�����λ�ó�����ʼ��ͻ�λ��ת��
            for(int j=st;j<=n;j++){//�Ҷ˵���С״̬Ҳ�ǴӲ�����ʼ �������״̬����Ҫ��������λ��
                if(i == j) continue;//i==j==st �ڲ��� �Ѿ�����С����״̬��,ȥ��if�ж�Ҳ��Ӱ����
                /*
                dp[i][j][0]�ɴ�dp[i+1][j][0] dp[i+1][j][1]ת�ƶ���,����dp[i+1][j][0] Ҫ��λ��i+1�ٵ���λ��i,֮���·��Ϊnode[i+1].pos-node[i].pos
                �����ڼ����໹û�͵��Ŀͻ�(1~i j+1~n ��Щλ��)������ȶ���ةû������������Ҫ�ò�����Ⱥ� ����ʱ��
                */
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(node[i+1].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(node[j].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(node[j].pos-node[i].pos)*(sum[i-1]+sum[n]-sum[j-1]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(node[j].pos-node[j-1].pos)*(sum[i-1]+sum[n]-sum[j-1]));
            }
        }
        /*
        dp�Ĺ�����û��������ʵ���ٶ�,���Խ����ͳһ����,���Ҫ��dp������V,
        ��Ҫ���� long long ��Ȼ�����,��Ϊ�м�dp�Ľ�����ܹ���,�����յĽ����������С��.
        �����������;�����һ���ͻ�һ����1��n,������������һ���͵Ŀͻ����м�,
        ��ôʵ�����������˵�ʱ���м�Ŀͻ��Ѿ��߹���,������ֱ���������˾����м��ʱ��͸��м��һ����
        �������Ž�һ������͵Ŀͻ���1��n.
        */
        printf("%d\n",min(dp[1][n][0],dp[1][n][1])*v);
    }
    return 0;
}
/*
����dp ö�ٳ��Ⱥ���ʼ��
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Node{
    int pos,val;
    bool operator < (const Node &x)const{
        return pos<x.pos;
    }
}node[1005];

int dp[1005][1005][2],sum[1005],n,v,x;

int main(){
    while(scanf("%d%d%d",&n,&v,&x)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].pos,&node[i].val);
        node[n+1].pos=x,node[n+1].val=0;
        n++;
        sort(node+1,node+n+1);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+node[i].val;
            if(node[i].pos == x)
                dp[i][i][0]=dp[i][i][1]=0;//��С��״ֻ̬�в���������
        }
        //����ʱ�临�Ӷ���ȴӲ���λ�ÿ�ʼת��,���һЩ
        for(int l=1;l<n;l++){//��С�����������ת��,�����������С���仹�ǴӲ���λ�ÿ�ʼ��
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(i == j) continue;
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][0]+(node[i+1].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][0]=min(dp[i][j][0],dp[i+1][j][1]+(node[j].pos-node[i].pos)*(sum[i]+sum[n]-sum[j]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][0]+(node[j].pos-node[i].pos)*(sum[i-1]+sum[n]-sum[j-1]));
                dp[i][j][1]=min(dp[i][j][1],dp[i][j-1][1]+(node[j].pos-node[j-1].pos)*(sum[i-1]+sum[n]-sum[j-1]));
            }
        }
        printf("%d\n",min(dp[1][n][0],dp[1][n][1])*v);
    }
    return 0;
}
*/

/*���仯����
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#define ll long long
#define pr(x) cout << #x << " = " << (x) << '\n';
using namespace std;

const int MAXN = 1e3 + 11;

ll dp[MAXN][MAXN][2];
struct P {
    ll x, b;
    bool operator < (const P &t)const {
        return x < t.x;
    }
}a[MAXN];

int n;
ll X, v, sum[MAXN];

ll dfs(ll l, ll r, int sta) {
    ll &ret = dp[l][r][sta];

    if (ret >= 0) return ret;
    if (l == r) return ret = abs((X - a[l].x)) * v * sum[n];

    if (sta == 0) {
        ll mul = sum[l] + sum[n] - sum[r];
        ret = min(dfs(l + 1, r, 0) + (a[l + 1].x - a[l].x) * v * mul,
                  dfs(l + 1, r, 1) + (a[r].x - a[l].x) * v * mul);
    }
    else {
        ll mul = sum[l - 1] + sum[n] - sum[r - 1];
        ret = min(dfs(l, r - 1, 1) + (a[r].x - a[r - 1].x) * v * mul,
                  dfs(l, r - 1, 0) + (a[r].x - a[l].x) * v * mul);
    }

    return ret;
}

int main()
{
    while (~scanf("%d%d%lld", &n, &v, &X)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", &a[i].x, &a[i].b);
        }
        sort(a + 1, a + n + 1);

        sum[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].b;
        memset(dp, -1, sizeof dp);
        printf("%lld\n", min(dfs(1, n, 0), dfs(1, n, 1)));
    }
    return 0;
}
*/
