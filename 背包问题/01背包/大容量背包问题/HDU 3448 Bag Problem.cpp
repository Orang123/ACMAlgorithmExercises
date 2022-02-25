#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
using namespace std;
//ac 0ms ������ָ����Ʒ�������޵�01����ת��Ϊ����ö������
/*
����:k����Ʒ,ÿ����Ʒ�ж�Ӧ����,����������Ϊm,
�����װn����Ʒ���������.
k<=40,m<=10^9.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3448
˼·:��������Ӧ�ı���ģ����HDU 3496��װ�뱳��ָ����Ʒ
������õ�����ֵ,������Ϊ���Ⲣ����ָ��һ��Ҫװ��n����Ʒ,
����С��n��,ֻ��Ҫ�������,���Ի�������HDU 3496�Ǹ���ά01
������ģ��ȥ��,��Ϊ�����������ɴ�10^9,dp�����޷���,
��MLE,��n<=40,�ɱ���ö������.ע��һ����֦��,̰���Ƚ�������Ʒ
��������,���ǰn�����Ʒ�����Ͳ�������������,����ǰn��
������Ʒ����װ�뱳��,ֱ��������ֵ����.

�ɻ�:������׺�����ͼ�֦,��wa.��֪��ԭ��.
*/
int n,k,m,w[N],ans,sufxw[N],sum;

void dfs(int i,int num,int sum){
    if(sum>m) return;
    //if(sum+sufxw[i]<ans)//��׺��֦ ��wa
        //return;
    if(sum>ans)
        ans=sum;
    if(num == n || i == k+1)
        return;
    dfs(i+1,num+1,sum+w[i]);
    dfs(i+1,num,sum);
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        sum=ans=0;
        scanf("%d",&k);
        sufxw[k+1]=0;
        for(int i=1;i<=k;i++)
            scanf("%d",&w[i]);
        sort(w+1,w+1+k,greater<int>());
        for(int i=1;i<=n;i++)
            sum+=w[i];
        if(sum<=m){//ǰn�����Ʒ������С�ڱ�������,ֱ�����.
            printf("%d\n",sum);
            continue;
        }
        for(int i=k;i>=1;i--)
            sufxw[i]+=sufxw[i+1]+w[i];
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
