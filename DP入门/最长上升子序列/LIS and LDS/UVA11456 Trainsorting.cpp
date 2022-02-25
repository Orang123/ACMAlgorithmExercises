/*
����:ժ������
����n����ʾ��n�ڳ��ᣬȻ���i�ڳ�������Ϊt[i]��λ�ڵ�i����վ��
�г�������ǿ��֢��һ��Ҫ��˵�г��ĳ���Ҫ���������Ӵ�С����
�������������һ�ξ���ÿһ����վ�����Կ����Ƿ����λ�ڸó�վ�ĳ��ᣬ
��ӵĻ�Ҳֻ�ܷ������г��е�ǰ�˺ͺ�ˣ�����˵���м���룬��˵�г�������ж೤��
n<=2000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2451
˼·:˼·ժ��:https://www.iteye.com/blog/haierboos-1939734
�����һ������ѡ���i���Ž�ȥ����ô������������i���ұߵ�һ���Ǳ�i������С�ģ�
Ϊ�����ұ߷�����������Ҫ�������е�i�������һ��ѡ��ݼ����е�˳��š�Ҫ����i����ߵģ�
һ���Ǳ�i������Ҫ��ģ�ͬ��Ϊ������߷���������Ӧ������iΪ��һ��(��������������)�������
���С�
������Ҫ��������LCS��LDS.��ô�𰸾���LIS(i)+LDS(i)-1,��1����Ϊ��i�������ظ�����һ��.
*/
//ac 10ms
#include<cstdio>
#include<algorithm>
#define N 2100
using namespace std;

//dp1[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�LIS�ĳ���
//dp2[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�LDS�ĳ���
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=1;
        scanf("%d",&n);
        if(!n){
            printf("0\n");
            continue;
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
            ans=max(ans,dp1[i]+dp2[i]-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}

