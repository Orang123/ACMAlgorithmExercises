/*
����:����һ��n,��1��n�Ĳ�ͬ��ֵ��Ӳ�Ҳ��������ж��ٷ�ʽ�ճ�n,����ָ���һ��l1,
������С�ڵ���l1�����Ĵ�1��n��ֵ��Ӳ���ж��ٷ�ʽ�ճ�n,����ָ���l2������������
����l1С�ڵ���l2�����Ĵ�1��n��ֵ��Ӳ���ж����ַ�ʽ���n.
0<=n<=300,0<=l1,l2<=1001
����:https://www.luogu.com.cn/problem/UVA10313
˼·:��ά������ȫ����ͳ��ָ����Ŀ��Ʒװ������������.
dp[k][j]+=dp[k-1][j-i],����ö�ٵڶ���ѭ��,������ѭ������,����Կ�.
*/
//ac 70ms ��ά������ȫ���� ͳ��ָ����Ʒ��Ŀǡ��װ������������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define M 310
typedef long long ll;
using namespace std;

int n,l1,l2;
ll dp[N][M],ans;
char str[20];

int main(){
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<N;i++){
        for(int j=i;j<M;j++){//��������j��ָ����Ʒ����k ˳��˳����Եߵ�
            for(int k=1;k<N;k++)
                dp[k][j]+=dp[k-1][j-i];
        }
    }
    while(gets(str)!=NULL){
        ans=0;
        l1=l2=-1;
        sscanf(str,"%d %d %d",&n,&l1,&l2);
        l1=min(l1,300);
        l2=min(l2,300);
        if(l1 == -1){
            for(int i=0;i<=n;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
        else if(l2 == -1){
            for(int i=0;i<=l1;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
        else{
            for(int i=l1;i<=l2;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
    }
    return 0;
}

/*
//ac 30ms
//f[i][j] += f[i - j][j] + f[i][j - 1] (ʹ����ֵj�Ͳ�ʹ����ֵj)��
//ժ�Բ���:https://blog.csdn.net/hyczms/article/details/41965129
#include <stdio.h>
#include <string.h>
const int N = 305;
int n, l1, l2;
char str[100];
long long f[N][N];

int main() {
	f[0][0] = 1;
	for (int i = 0; i <= 300; i++)
		for (int j = 1; j <= 300; j++) {
			if (i >= j)
				f[i][j] += f[i - j][j];
			if (j >= 1)
				f[i][j] += f[i][j - 1];
		}
	while (gets(str)) {
		int a = sscanf(str, "%d%d%d", &n, &l1, &l2);
		l1 = l1 < 300 ? l1 : 300;
		l2 = l2 < 300 ? l2 : 300;
		if (a == 1)
			printf("%lld\n", f[n][n]);
		else if (a == 2)
			printf("%lld\n", f[n][l1]);
		else
			printf("%lld\n", f[n][l2] - f[n][l1 - 1]);
	}
	return 0;
}
*/
