/*
����:��˾��n���ֿ�,��Ҫ����.������m����ӦƸְλ,ÿ�����и�ֵP[i](1 ��P[i]��1000);
���ŵ�i���˿���k���ֿ�,����k���ֿ�İ�ȫֵ��p[i]/k,���һ���Ϊp[i].��˾Ҫ��֤����
�ֿ����С��ȫֵ�����ܵĴ�,������ֵ�����������������С����.
n<=100,m<=30.
����:https://www.luogu.com.cn/problem/UVA10163
˼·:�����Խ�m���ֿ���Ϊ��������,n������Ϊ��Ʒ,��Ʒ�ݻ��ǹ���Ĳֿ����k,
��Ʒ��ֵΪp[i],01����.ֻ����Ʒ���kû�и���,��Ҫ��dp������ö��.
������dp,��һ��dp�����С��ȫֵ,��:dp[i][j]=max(dp[i][j],min(dp[i-1][j-k],p[i]/k)),
�Ƚ���ǰi-1�����й���j-k���ֿ����С��ȫֵ�뵱ǰ��i���˹���k���ֿ�İ�ȫֵ,ȡ��С��
��֮ǰdp[i][j]�Ƚ�ȡ��Сֵ�еĽϴ�ֵ,���dp[i][j]������ǰi-1���˹���j���ֿ�İ�ȫֵ
Ҳ�����ǵ�i���˹���ͬk���ֿ�ʱǰi���˹���j���ֿ�İ�ȫֵ.
�ڶ���dp�����С����,dpʱ��Ҫ�жϵ�ǰ�ڸ��˵İ�ȫֵ�Ƿ�>=��һ�ε���С��ȫֵ��󻯵�ֵ.
dp[i][j]=min(dp[i][j],dp[i-1][j-k]+p[i]);

ʵ�ʾ��Ƿ��鱳��,����������n���ֿ�,��ÿ���˿���һ��,ÿ�����Ʒ�ǵ�ǰ��i���˿���k(1..n)
���ֿ�ĸ����������,���豣֤p[i]/kΪ����.
*/
//ac 0ms ��������Ʒ��� 01����ö����Ʒ��� һά����ʵ��
//ʵ�ʾ��Ƿ��鱳��,���˿�������һ��,ÿ����ƷΪ ��i���˸���1���ֿ⡢��i���˸���2���ֿ⡢...����i���˸���n���ֿ�
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dp[0]=INF;
        //dp[i][j]���� ǰi���˹���j���ֿ�ʱ������С��ȫֵ
        for(int i=1;i<=m;i++){
            //���������Ż�����j������ڵڶ���,���ҽ���,���ܱ�֤ÿ�ε�dp[j-k]��ǰi-1�������˵����Ž�
            for(int j=n;j>=1;j--){
                //ö�ٵ�i���˿��Ը���k���ֿ�,k���Ͻ���min(j,p[i]) ʵ�ʾ��ǵ�i������Ʒ�Ŀ�����
                for(int k=1;k<=j && k<=p[i];k++){//��ΪҪ��p[i]/k��ȫֵΪ����,����k<=p[i]
                    if(dp[j-k]){
                        dp[j]=max(dp[j],min(dp[j-k],p[i]/k));
                    }
                }
            }
        }
        int ans=dp[n];
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        //dp[i][j]����ǰi���˹���j���ֿ�ʱ����С����
        for(int i=1;i<=m;i++){
            for(int j=n;j>=1;j--){
                //ÿ���˵İ�ȫֵ���벻С��֮ǰdp��С�������İ�ȫֵ
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[j]=min(dp[j],dp[j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[n]);
    }
    return 0;
}

/*
//ac 0ms 01����ö����Ʒ��� ��ά����ʵ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[N][M];

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dp[0][0]=INF;
        for(int i=1;i<=m;i++){
            for(int j=0;j<=n;j++)//�̳�ǰi-1��״̬,ע���½���0
                dp[i][j]=dp[i-1][j];
            for(int k=1;k<=p[i];k++){//���ڶ�ά����,����k��j��˳����Եߵ�
                for(int j=n;j>=k;j--){
                    if(dp[i-1][j-k])
                        dp[i][j]=max(dp[i][j],min(dp[i-1][j-k],p[i]/k));
                }
            }
        }
        int ans=dp[m][n];
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=m;i++){
            for(int j=0;j<=n;j++){
                dp[i][j]=dp[i-1][j];
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[i][j]=min(dp[i][j],dp[i-1][j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[m][n]);
    }
    return 0;
}
*/

/*
//TLE ��������dfs
//O(2*n^m)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 35
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p[N],dp[M],ans;
//O(2*n^m)
void dfs(int i,int sum,int pk){
    if(pk<ans)//��֦ �����ǰ��Сֵ���ܱ�ans��,��ô����������ȥ֮���С,��ans�����û�а���
        return;
    if(sum == n){
        ans=max(ans,pk);
        return;
    }
    if(i == m+1)
        return;
    //��i���� ö�ٸ���k���ֿ�
    for(int k=1;k<=n;k++){
        if(sum+k<=n && p[i]>=k)//ֻ�е� p[i]/k�������ǲ��ǺϷ� ��ȫֵ
            dfs(i+1,sum+k,min(pk,p[i]/k));
    }
    //��i����һ���ֿ�Ҳ������
    dfs(i+1,sum,pk);
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        ans=0;
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        memset(dp,0,sizeof(dp));
        dfs(1,0,INF);
        if(!ans){
            printf("0 0\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=m;i++){
            for(int j=n;j>=1;j--){
                //ÿ���˵İ�ȫֵ���벻С��֮ǰdp��С�������İ�ȫֵ
                for(int k=1;k<=j && p[i]/k>=ans;k++)
                    dp[j]=min(dp[j],dp[j-k]+p[i]);
            }
        }
        printf("%d %d\n",ans,dp[n]);
    }
    return 0;
}
*/

/*
//ac 0ms ���ִ�
//���rayluo�������
#include<bits/stdc++.h>
using namespace std;
#define in inline
#define ll long long
const int N=110;
in int read()
{
	int w=0,r=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')r=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar();
	}
	return w*r;
}
int n,m,p[N];
int ans1,ans2;

in int min_(int x,int y)
{
	return x<y?x:y;
}

in int max_(int x,int y)
{
	return x>y?x:y;
}

int mx;
bool check(int x)  //�жϺ���
{
	if(x==0)return true;  //����Ϊ��ᵼ������ʱ������ǰ�жϡ�
	int cnt=0;  //���ɱ��ػ��Ĳֿ�
	for(int i=1;i<=m;i++)
	{
		cnt+=(p[i]/x);
		if(cnt>=n)return true;
	}
	return false;
}

void bs()  //���ִ�
{
	int l=0,r=mx;  //�Ͻ�Ϊ����p������һ��
	ans1=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			l=mid+1;  //���У���˵�������Գ���һ�¸����
			ans1=mid;
		}
		else
		{
			r=mid-1;  //���У��ͱ������
		}
	}
}
int f[N];  //i���ֿ����С����
int solve(int x)
{
	memset(f,0x3f,sizeof(f));
	f[0]=0;  //��ȡ���򻨷�Ϊ0
	for(int i=1;i<=m;i++)
	{
		for(int j=n;j>=1;j--)  //�Ż��ռ�
		{
			for(int k=1;k<=j;k++)
			{
				if(x<=(p[i]/k))  //k�Ƿ����Ҫ��
				{
					f[j]=min_(f[j],f[j-k]+p[i]);  //ת��
				}
			}
		}
	}
	return f[n];
}

int main()
{
	n=read();
	m=read();
	while(n!=0||m!=0)
	{
		ans1=0;
		ans2=0;
		for(int i=1;i<=m;i++)
		{
			p[i]=read();
			mx=max_(mx,p[i]);//ͳ�ƶ����Ͻ�
		}
		bs();
		if(ans1==0)//����
		{
			puts("0 0");
		}
		else
		{
			cout<<ans1<<" "<<solve(ans1)<<endl;
		}
		n=read();
		m=read();
	}
	return 0;
}
*/
