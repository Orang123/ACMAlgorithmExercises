/*
//����ժ������
����:��n������,ÿ�����Ӵ����Ұڷ���num������,ÿ���������ж�Ӧ�ļ�ֵ.
���ڹ��������,������m�����,ÿ�μ����ζ�Ż���һ��������ˤ��.����
ÿ��ֻ����ĳ������������߻������ұߵ�һ��,����ʧ������ֵΪ����?
n<=100,num[i]<=100,m<=10000
����:http://codeforces.com/problemset/problem/148/E
˼·:01���������ܰ�������ģ��ֻȡ�������˴���.��Ҫ�÷��鱳����ÿ������г����ܵ�ȡ��
��������ֵ�����.
��CF 946D Timetable��������һ��.
���鱳��,����ȡ�Ĵ�������m��Ϊ��������.ÿ�����ӵ�����Ϊһ��,���ڵ���Ʒ
�ֱ�Ϊȡ����������������˹�1��2��3��..min(m,num[i])����������ʧ������ֵ.
��Ϊ��Ŀ˵�����д����ĸ������ٻ���m,���Ա�֤�˱���һ����װ��,���԰��վ����ܶ�
��װ��������ʼ��ȫ0����.
*/
//ac 78ms ����Ԥ����+���鱳��
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define M 10010
using namespace std;

//prefx[i][j]�����i��������ǰj�������ļ�ֵ�� ǰ׺��
//sufx[i][j]�����i�������Ϻ�j�������ļ�ֵ�� ��׺��
int a[N],prefx[N][N],sufx[N][N];
//num[i]��i�������ϴ����ĸ���
//val[i][j]��i��������ȡ���������˹�j���������ܵõ�������ֵ��
//dp[i][j]����ǰi�������ϰ���ֻȡÿ�������������˹�j����������ܻ�õļ�ֵ��
int n,m,num[N],val[N][N],dp[M];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d",&a[j]);
        for(int j=1;j<=num[i];j++)
            prefx[i][j]=prefx[i][j-1]+a[j];
        for(int j=num[i];j>=1;j--)
            //����num[i]-j+1���Ǻ�׺�͵Ĵ����ĸ���
            sufx[i][num[i]-j+1]=sufx[i][num[i]-j]+a[j];
    }
    for(int i=1;i<=n;i++){
        int k=min(num[i],m);
        for(int j=1;j<=k;j++){
            if(j == num[i]){//ȡ�����д���,��ֱֵ�Ӿ���ǰ׺�� ���������ѭ������
                val[i][j]=prefx[i][j];
                break;
            }
            for(int l=0;l<=j;l++){
                int r=j-l;
                val[i][j]=max(val[i][j],prefx[i][l]+sufx[i][r]);
            }
        }
    }
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            int tp=min(num[i],j);//��i�����������ȡ�ߵĺϷ��Ĵ�������tp
            for(int k=1;k<=tp;k++)
                //dp[j-k]��ǰi-1������ȡ��j-k����������ܻ�õļ�ֵ��
                dp[j]=max(dp[j],dp[j-k]+val[i][k]);
        }
    }
    printf("%d",dp[m]);
    return 0;
}

/*
//ac 109ms Ԥ����+���鱳�� ��ǰ׺�͵Ĳ��ʾ����׺��
//ժ��������
#include<iostream>
#include<vector>
using namespace std;
int n,m,N,ans,dp1[105][105],sum[105][105],dp2[105][10005];
vector<int> a[105];
int cal(int k,int i,int j) //�� k ��ȡ��ǰ i ���ͺ� j �����ܼ�ֵ
{
	int N=a[k].size();
	return sum[k][N]-sum[k][N-j]+sum[k][i];
}
int main()
{
	int N,x;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>N;
		for(int k=1;k<=N;k++)
			cin>>x,a[i].push_back(x),sum[i][k]=sum[i][k-1]+x;//��Ϊÿһ�㳤�Ȳ�������һ��vector���棬ͬʱ����ǰ׺��
	}
	for(int k=1;k<=n;k++)
		for(int l=1;l<=a[k].size();l++)
			for(int i=0;i<=l;i++) {int j=l-i;dp1[k][l]=max(dp1[k][l],cal(k,i,j));}//dp1ת��
	for(int k=1;k<=n;k++)
		for(int i=0;i<=m;i++)
			for(int j=0;j<=a[k].size() && j<=i;j++)
				dp2[k][i]=max(dp2[k][i],dp2[k-1][i-j]+dp1[k][j]);//dp2ת��
	cout<<dp2[n][m];
	return 0;
}
*/
