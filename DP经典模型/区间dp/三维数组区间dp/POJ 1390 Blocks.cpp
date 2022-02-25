#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


/*
����:����һ����ɫ�飬ÿ�ο���ɾ�����ڵ���ͬ��ɫ�飬���εĻ���Ϊ������ƽ��
�ʽ����е���ɫ������ɾ����,�������Ƕ��٣�
ԭ����һ��OIԭ�� ����
����:http://poj.org/problem?id=1390
˼·:���Գ���ͳ�Ƴ�����������ͬ��ɫ�����Ŀ,dp[i][j][k],i~j֮�䶼����ɫһ������ɫ��,
k��ʾj֮���ּ�����ɫ����j�����ɫ��ͬ,����һ����м��������,��ͳһ����j�ͺ������ͬ��ɫ��.
��Ȼdp[i][j][k]��kҲ���Դ����i����߿���ͬ��ɫ����Ŀȥ���

�������ֻ���ü��仯�����ݹ���,�����dp ��Ϊ���ڵ���ά��k��С�Ŀ�ʼת�ƴ������,k�ǲ�ȷ����,
���ǿ��Ƕ�ά����ת��,С����������Ž�ʵ�ʲ��ܺ��Ǹ���˺͸��Ҷ���û����ͬ��ɫ�õ���,��Ҳ���������.
*/
int dp[210][210][210],a[210],col[210],num[210],n;

int cal(int x){
    return x*x;
}

int dfs(int i,int j,int k){
    if(dp[i][j][k]) return dp[i][j][k];
    if(i == j) return dp[i][j][k]=cal(num[j]+k);//ʣ��һ����ɫʱ������������Ŀ���ұ���ͬ��ɫ�����Ŀһ��ɾ��
    //if(i>j) return 0;��Ϊ���ڵ���������ɫ��Զ����ͬ ���Բ����ܳ���t=j-1ʱ ��������ݹ�dfs(t+1,j-1) ����i>j
    //ֱ���Ƚ�j����ɫ��ͺ����k����ͬ��ɫ��ɾ��
    dp[i][j][k]=dfs(i,j-1,0)+cal(num[j]+k);
    //����i~j-2���Ƿ��к�j��ɫ��ͬ��,����,�����Ƚ�t+1~j-1�м�Ŀ�ɾ��,��һ��ɾ�����ߵ���ͬ��ɫ�Ŀ�
    for(int t=i;t<j-1;t++)//<j-1����Ϊ j-1��j��ɫʱ�϶���ͬ��
        if(col[t] == col[j])
            dp[i][j][k]=max(dp[i][j][k],dfs(i,t,k+num[j])+dfs(t+1,j-1,0));
    return dp[i][j][k];
}

int main(){
    int T,tmp,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%d",&n);
        len=0;
        tmp=-1;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]!=tmp){
                tmp=col[++len]=a[i];//num��¼���ڿ���ͬ��ɫ����Ŀ
                num[len]++;
            }
            else
                num[len]++;
        }
        printf("Case %d: %d\n",cas,dfs(1,len,0));
    }
    return 0;
}
