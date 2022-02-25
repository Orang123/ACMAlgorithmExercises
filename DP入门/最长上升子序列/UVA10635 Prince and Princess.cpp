/*
����:ժ������
���������ȷֱ�Ϊp+1��q+1�����У�ÿ��Ԫ���еĸ���Ԫ�ػ�����ͬ��
����1~n^2֮�����������A��B������������С�
n<=250,p,q<=n*n=62500.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1576
˼·:��Ȼ���ֱ����LCS,���Ӷ�=p*q=62500*62500=3.9*10^9.
ʵ����Ϊÿ�������е�Ԫ�ض�����ͬ,���Զ�a�����еĴ�����ӳ��,
mp[a[i]]=i,�ٸ���a�����ӳ��ȥת��b����,b[i]=mp[b[i]].
����ԭ�ȵ�LCS����ʵ�ʾ�ת������,b�����е�LIS����,
����mp[b[i]]=0,��:a�����в����ڵ���,��ӳ��.
*/
//ac 10ms b������aû�е�����ӳ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 63000
#define INF 0x3f3f3f3f
using namespace std;

int n,p,q,a[N],b[N],mp[N],dp[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(mp,0,sizeof(mp));
        scanf("%d%d%d",&n,&p,&q);
        for(int i=1;i<=p+1;i++){
            scanf("%d",&a[i]);
            mp[a[i]]=i;
        }
        n=0;
        for(int i=1;i<=q+1;i++){
            scanf("%d",&b[i]);
            if(mp[b[i]])//a����Ҳ�д��ڵ�����ӳ��
            	a[++n]=mp[b[i]];
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++)
            *lower_bound(dp,dp+q+1,a[i])=a[i];
        printf("Case %d: %d\n",cas,lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
