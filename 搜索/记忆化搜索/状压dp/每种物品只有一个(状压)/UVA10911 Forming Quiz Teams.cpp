/*
����:ժ������
����2*n��ѡ�ֵ����꣬Ҫ�����е�ѡ�ֳַ�n�飬ÿ�������ˣ�
�������������֮��ľ���֮��Ҫ��С�������Сֵ��
n<=8.
����:https://www.luogu.com.cn/problem/UVA10911
˼·:��Ҫö�ٳ����е�������,�Ƚ������С�����.����һ��ö��1��2����,
ÿ���Ѿ�ȷ�������ö���λ��״̬����ʾ,���Ƕ���ͬ����ѡ�����1��2��3��4
����,������������(1,2),(3,4)Ҳ������(1,3),(2,4)��,Ҳ���Ƕ�����ѡ����ͬ
������ϲ�ͬ�����,����ʣ��δѡ���˼����̾����Ǹ��ص�������,
��˼��仯����+״̬ѹ�����ص�����������.
dp[sta]��ʾ��ѡѧ��������λ״̬Ϊstaʱ,δѡѧ�����ʱ����ѧ����̵ľ���֮��.
����״̬�ǵ������˶����������ʱ,��sta == (1<<n)-1.
*/
//ac 160ms ���仯����+״ѹ
//dp[sta]��ʾ��ѡѡ�ֶ�����λ״̬Ϊstaʱ,δѡѧ�����ʱ����ѧ����̵ľ���֮��
//ʱ�临�Ӷ�O(1<<16-1)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 1e40
using namespace std;

int n;
double dis[N][N],x[N],y[N],dp[1<<16];
char str[N];

double calDis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    if(sta == (1<<n)-1)
        return 0;
    for(int i=0;i<n;i++){//һ��ö������
        if(sta & 1<<i)//��i������ȷ�Ϸ���
            continue;
        for(int j=i+1;j<n;j++){
            if(sta & 1<<j)//��j������ȷ�Ϸ���
                continue;
            dp[sta]=min(dp[sta],dfs(sta|(1<<i)|(1<<j))+dis[i][j]);
        }
    }
    return dp[sta];
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        n<<=1;//n����,����2����������
        for(int i=0;i<(1<<16);i++)
            dp[i]=INF;
        for(int i=0;i<n;i++)
            scanf("%s%lf%lf",str,&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++)
                dis[i][j]=calDis(i,j);//dis[i][j]��ʾѡ��i��ѡ��j֮��ľ���
        }
        printf("Case %d: %.2f\n",cas,dfs(0));//��ʼʱ,һ��ѡ��Ҳûѡ,״̬Ϊ0
    }
    return 0;
}

/*
//ac 160ms ���仯����+״ѹ
//dp[sta]��ʾδѡѡ�ֶ�����λ״̬Ϊstaʱ,δѡѧ�����ʱ�����ѧ����̵ľ���֮��
//ʱ�临�Ӷ�O(1<<16-1)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 1e40
using namespace std;

int n;
double dis[N][N],x[N],y[N],dp[1<<16];
char str[N];

double calDis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    if(!sta)
        return 0;
    for(int i=0;i<n;i++){
        if(!(sta & 1<<i))//����δѡ״̬ ˵����ѡ
            continue;
        for(int j=i+1;j<n;j++){
            if(!(sta & 1<<j))
                continue;
            dp[sta]=min(dp[sta],dfs(sta^(1<<i)^(1<<j))+dis[i][j]);//���ȡ��δѡ״̬
        }
    }
    return dp[sta];
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        n<<=1;
        for(int i=0;i<(1<<16);i++)
            dp[i]=INF;
        for(int i=0;i<n;i++)
            scanf("%s%lf%lf",str,&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++)
                dis[i][j]=calDis(i,j);//dis[i][j]��ʾѡ��i��ѡ��j֮��ľ���
        }
        printf("Case %d: %.2f\n",cas,dfs((1<<n)-1));//��ʼʱһ��ѡ��Ҳδ����,״̬Ϊ(1<<n)-1
    }
    return 0;
}
*/

/*
//ac 70ms ����dp
//�����ϰ�⼯�ϵĹٷ��ⷨ
//ժ�Բ���:https://blog.csdn.net/tianwei0822/article/details/94491501
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1010;
int x[maxn], y[maxn];
double d[1<<16];
double dis(int a,int b){
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
int n, kase;
int main(){
	while(scanf("%d", &n) == 1 && n){
		char s[maxn];
		n <<= 1;
		for(int i = 0; i < n; ++i){scanf("%s%d%d", s, &x[i], &y[i]);}
		d[0] = 0;
		for(int S = 1; S < (1 << n); ++S){
			d[S] = INF;
			int i, j;
			for(i = 0; i < n; ++i) if(S & (1 << i)) break;
			for(j = i + 1; j < n; ++j) if(S & (1 << j)) d[S] = min(d[S], dis(i, j) + d[S ^ (1 << i) ^ (1 << j)]);
		}
		printf("Case %d: %.2lf\n", ++kase, d[(1 << n) - 1]);
	}
	return 0;
}
*/
