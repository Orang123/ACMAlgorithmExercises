/*
����:ժ������
�ھ���ĺ�ŵ���Ļ����Ͻ����˸��죬�����������ƶ������������������ƶ�����;
��i���ƶ���j���Ĵ�����t[i][j],�������ƶ�����.
n<=40,1<=t[i][j]<=10000.
����:https://codeforces.com/contest/392/problem/B
˼·:���ں�ŵ��������ͨ���ݹ齫����Ĺ�ģ��С,ͨ�����ݼ�¼�ƶ��ķ�ʽ,ֱ��
�ҵ���С���������������ӵ��ƶ���ʽ��ʼת�ƻ��ݹ�����ϴ��ģ����Ľ�.
����ǰk�������еĵ�k������,��1�ƶ���3,�����ַ�ʽ,
Ҫôֱ���ƶ�,Ҫô������һ������Ϊý���ƶ���:1->3��1->2,2->3
1.��k������ֱ�Ӵ�1�ƶ���3,ǰk-1�����Ӵ�1�ƶ���2,ǰk-1�������ٴ�2�ƶ���3.
2.��k�����Ӵ�1�ƶ���2,ǰk-1�����Ӵ�1�ƶ���3,ǰk-1�������ٴ�3�ƶ���1,
��k�����Ӵ�2���ƶ���3,���ǰk-1�������ٴ�1�ƶ���3.
��Ҫ�Ƚ������ƶ���ʽ ��ȡ��С�ƶ�����.
���ַ�ʽ����С�����ģʱ�����ص�������,��˼��仯����,
dp[k][from][to]��ʾ��ǰk�����Ӵ�from���ƶ���to������Ҫ����С����.
*/
//ac 31ms ���仯����
//dp[k][from][to]��ʾ��ǰk�����Ӵ�from���ƶ���to������Ҫ����С����
//���Ӷ�O(40*3*3)=360
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 45
using namespace std;
typedef long long ll;

int n,t[4][4];
ll dp[N][4][4];

ll dfs(int k,int from,int by,int to){
    if(dp[k][from][to]!=-1)
        return dp[k][from][to];
    if(k == 1)//��ʼ״̬����������� �������ƶ���ʽ,һ��ֱ���ƶ�from->to,һ�ּ���ƶ�from->by,by->to
        return dp[k][from][to]=min(t[from][to],t[from][by]+t[by][to]);
    ll res1,res2;
    res1=dfs(k-1,from,to,by)+t[from][to]+dfs(k-1,by,from,to);
    res2=dfs(k-1,from,by,to)+t[from][by]+dfs(k-1,to,by,from)+t[by][to]+dfs(k-1,from,by,to);
    dp[k][from][to]=min(res1,res2);
    return dp[k][from][to];
}

int main(){
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            scanf("%d",&t[i][j]);
    }
    scanf("%d",&n);
    printf("%lld",dfs(n,1,2,3));
    return 0;
}
/*
//ac 15ms ���仯���� �м丨������ͨ��6-from-to�õ�,��Ϊ�������ӵı��֮��һ��Ϊ6.
//dp[k][from][to]��ʾ��ǰk�����Ӵ�from���ƶ���to������Ҫ����С����
//���Ӷ�O(40*3*3)=360
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 45
using namespace std;
typedef long long ll;

int n,t[4][4];
ll dp[N][4][4];

ll dfs(int k,int from,int to){
    if(dp[k][from][to]!=-1)
        return dp[k][from][to];
    int by=6-from-to;
    if(k == 1)
        return dp[k][from][to]=min(t[from][to],t[from][by]+t[by][to]);
    ll res1,res2;
    res1=dfs(k-1,from,by)+t[from][to]+dfs(k-1,by,to);
    res2=2*dfs(k-1,from,to)+t[from][by]+dfs(k-1,to,from)+t[by][to];
    dp[k][from][to]=min(res1,res2);
    return dp[k][from][to];
}

int main(){
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++)
            scanf("%d",&t[i][j]);
    }
    scanf("%d",&n);
    printf("%lld",dfs(n,1,3));
    return 0;
}
*/

/*
//ac 31ms ����dp
//ժ�Բ���:https://www.cnblogs.com/dmoransky/p/12483477.html
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 45;

typedef long long LL;

int t[3][3], g[3][3], n;
LL f[N][3][3];


int main() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) scanf("%d", &t[i][j]), g[i][j] = t[i][j];
	scanf("%d", &n);
	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			f[1][i][j] = t[i][j];

	for (int i = 2; i <= n; i++) {
		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				if (a == b) continue;
				int c = 3 - a - b;
				f[i][a][b] = min(f[i - 1][a][c] + g[a][b] + f[i - 1][c][b], f[i - 1][a][b] + g[a][c] + f[i - 1][b][a] + g[c][b] + f[i - 1][a][b]);
			}
		}
	}
	printf("%lld\n", f[n][0][2]);
	return 0;
}
*/
