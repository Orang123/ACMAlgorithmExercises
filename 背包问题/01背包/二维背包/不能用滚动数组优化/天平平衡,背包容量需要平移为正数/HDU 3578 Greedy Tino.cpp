#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 4100
using namespace std;
//ac 124ms ���󱳰�����Ϊ��������01���� ģ��ⵣƽ��
//��һ���������Ӷ�Ҫ����
/*
����:n������,ÿ��������һ������w[i],��Ҫ��һ���ⵣ��
����,ʹ�ñⵣ����������ͬ,���ʹ�ñⵣƽ����������,
���һ�������.
n<=100,w[i]<=2000,w[1]+w[2]+...+w[n]<=2000
ע��:������ÿ�����Ӷ�Ҫ�ñⵣ������,���������Ӳ���.
��Ϊ�������Ӷ��Ų�һ����ƽ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3578
˼·:�� POJ 1837 ��ͬ,��ͬ���Ǳ��ⲻһ��Ҫ���������Ӷ�����,
��POJ 1837 Ҫ���������붼����,ƽ������[-2000,2000],ƽ���Ϊ0��
��������������Ϊ��,������������ƽ��2000����λ,��[0,4000],
��ʱƽ���Ϊ2000.��ʼ״̬Ϊdp[0][2000]=0.����״̬-INF,��Ҫ
ǡ��װ������.
*/
int cas,n,w[N],dp[N][M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];//sum��ʾ�������ӷ��ڱⵣһ���ܲ������������
        }
        sum<<=1;//sum��2��������ƽ�ƺ� ����Ϊ֮ǰ����.
        dp[0][sum/2]=0;//��ʼ״̬ƽ���Ϊsum/2
        //dp[i][j] ������i�����ӷ��ñⵣ������,�ⵣ����������Ϊj-sum/2ʱ�ⵣ������������������
        for(int i=1;i<=n;i++){
            //ע�ⲻ���ù��������Ż�,��Ϊ����j�����ǽ���,dp[i-1][j+w[i]] dp[i-1][j-w[i]]ͬһʱ�̱�Ȼ��һ�����ܱ�ʾǰi-1��״̬
            for(int j=0;j<=sum;j++){
                dp[i][j]=dp[i-1][j];//�̳���һ״̬
                //ǰi-1��״̬������� j+w[i]-sum/2<=sum-sum/2
                if(j+w[i]<=sum)//��Ϊdp[i-1][j+w[i]]����Ϳ��ܲ��Ϸ�,����Ҫ�ж�
                    //�������ӷ��ڱⵣ���
                    //��j+w[i]<sum/2 ��ǰi-1��״̬������,��ô����i�����ӷ��ڱⵣ���,��ʹ��������������.j-sum/2<j+w[i]-sum/2,jһ��С��sum/2,j-sum/2<0 ǰ�߾���ֵ�ϴ�
                    //��j+w[i]>sum/2 ��ǰi-1��״̬�Ҳ����,��ô����i�����ӷ��ڱⵣ���,j-sum/2 j+w[i]-sum/2,j����<sum/2 ��Ϊw[i]��ȷ��,����2�߾����ߴ�С����,������������ܼ�СҲ��������
                    dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);//dp[i][j]��֮ǰ dp[i-1][j]����ǰi-1��״̬û�з����i������
                //ǰi-1��״̬������� j-w[i]-sum/2>=0-sum/2
                if(j-w[i]>=0)
                    //�������ӷ��ڱⵣ�Ҳ�
                    //��j-w[i]<sum/2 ��ǰi-1��״̬������,��ô����i�����ӷ��ڱⵣ�Ҳ�,j-sum/2 j-w[i]-sum/2,j����>sum/2 ��Ϊw[i]��ȷ��,����2�߾����ߴ�С����,������������ܼ�СҲ��������
                    //��j-w[i]>sum/2 ��ǰi-1��״̬�Ҳ����,��ô����i�����ӷ��ڱⵣ�Ҳ�,��ʹ��������������.j-sum/2>j-w[i]-sum/2,j-sum/2>0 ǰ�߽ϴ�
                    dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);//����dp[i][j]������ǰi-1��״̬Ҳ�����ǵ�i�����ӷ�������״̬
            }
        }
        printf("Case %d: ",cas);
        if(dp[n][sum/2]>0)//�Ϸ�״̬
            printf("%d\n",dp[n][sum/2]/2);//���������,sum/2����ƽ��״̬
        else{//�����Ϸ� ��������������Ϊ0,���ǻ�ʹ�ñⵣƽ��,�����Я������,���������0
            int flag=0;
            for(int i=1;i<=n;i++){
                if(!w[i]){
                    flag=1;
                    printf("0\n");
                    break;
                }
            }
            if(!flag)
                printf("-1\n");
        }
    }
    return 0;
}

/*
//ac 124ms ��һ��ת�Ʒ�ʽ
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 4100
using namespace std;

int cas,n,w[N],dp[N][M],sum,flag;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i]) flag=1;
            sum+=w[i];
        }
        sum<<=1;
        dp[0][sum/2]=0;
        for(int i=1;i<=n;i++){
            //���������ǰ�̳�ǰi-1���������Ž��״̬
            //��Ϊ״̬ת�Ʒ�������dp[i-1][j]��dp[i][j-w[i]],��һ��״̬��dp[i][j-w[i]] ����dp[i][j]
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
            	if(dp[i-1][j]<0) continue;
            	//���dp[i-1][j]�ǺϷ���,��ôj-w[i]/j+w[i]һ����[0,sum]��Χ��
                dp[i][j-w[i]]=max(dp[i][j-w[i]],dp[i-1][j]+w[i]);
                dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);

            }
        }
        printf("Case %d: ",cas);
        if(dp[n][sum/2]>0){
            printf("%d\n",dp[n][sum/2]/2);
        }
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/

/*
//ac 78ms ��������������
//dp[i][j]��ʾ����i�����ӷ��ñⵣ������,�ⵣ����������Ϊjʱ�ⵣ������������������
//���ﲢ�����ֵ�������ػ����Ҳ���
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100
using namespace std;

int cas,n,w[N],dp[N][M],sum,flag;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i]) flag=1;
            sum+=w[i];
        }
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
            	if(dp[i-1][j]<0) continue;
                dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
                dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);

            }
        }
        printf("Case %d: ",cas);
        if(dp[n][0]>0){
            printf("%d\n",dp[n][0]/2);
        }
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/

/*
//ac 93ms һά����dp����
//һά����˼· ��HDU 5616�����Ƶ�
#include <map>
#include <stack>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#define N 4005
#define M
#define E
#define INF 0x3f3f3f3f
#define eps 1e-8
#define LL long long
#define D(a) ((a)*(a))
using namespace std;

int dp[N],n,a[N],b[N];

void re(void)
{
	scanf("%d",&n);
}

void run(void)
{
	memset(dp,-1,sizeof(dp));
	dp[2000]=0;
	int flag=0;
	for(int i=0;i<n;i++)
	{
	    int v;
	    scanf("%d",&v);
	    if(v==0)flag++;
	    memset(a,-1,sizeof(a));
	    memset(b,-1,sizeof(b));
	    for(int i=0;i<=4000;i++)
	        if(~dp[i])
                a[i-v]=max(dp[i-v],dp[i]+v),
                b[i+v]=max(dp[i+v],dp[i]+v);
        for(int i=0;i<=4000;i++)
            dp[i]=max(dp[i],max(a[i],b[i]));
	}
	if(dp[2000]==0&&flag<1)printf("-1\n");
	else printf("%d\n",dp[2000]/2);
}

int main()
{
	int ncase;
	scanf("%d",&ncase);
	for(int i=1;i<=ncase;i++)
	{
		re();
		printf("Case %d: ",i);
		run();
	}
	return 0;
}
*/

/*
//MLE Ӧ��Ҳ��TLE ����ö������+��֦
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100
using namespace std;

//vis[k][l][r]=1���� ǰk�����ӷűⵣ����,�������l,�Ҳ�����r������Ѿ�������
int cas,n,w[N],ans,flag,vis[N][M][M];

//O(3^n) n<=100,n^100 ÿ����������ſ��Է��������Ҳ�,���߲���
void dfs(int k,int l,int r){
    //��֦ ǰk������ ���Ҳ�����Ϊl��r�����֮ǰ�ѱ�����,
    //�����k+1��k+2��...��n�����ӵ�ö�ٷŵ�λ�û򲻷�����ͬ�Ĺ���,�����ظ�ö�ٿ������
    if(vis[k][l][r])
        return;
    vis[k][l][r]=1;
    if(l == r && l>ans)
        ans=l;
    if(k == n+1)
        return;
    dfs(k+1,l+w[k],r);//��i�����ӷ����
    dfs(k+1,l,r+w[k]);//��i�����ӷ��Ҳ�
    dfs(k+1,l,r);//���ŵ�i������
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        flag=ans=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            if(!w[i])
                flag=1;
        }
        dfs(1,0,0);
        if(ans!=-1)
            printf("Case %d: %d\n",cas,ans);
        else{
            if(flag)
                printf("0\n");
            else
                printf("-1\n");
        }
    }
    return 0;
}
*/
