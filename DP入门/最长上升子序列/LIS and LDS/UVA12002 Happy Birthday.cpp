/*
����:ժ������
����һ�����У�a[i]��ʾ��i�����ӵĴ�С��һ����n���ӡ�
������Ҫ��1�ߵ�n������ĳЩ���ӣ��������£�
1������û�����ӣ����������һ�����ӡ�Ҳ���Բ��á�
2��������һЩ���ӣ����뱣֤��������ӵĴ�С<=�������ӵĴ�С����
�����������ǰ������Ӵ�С<=��������С�����ӵĴ�С���Ϳ��Էŵ���
���е����ӵ������棬���>=�������������ӵĴ�С����Ϳ��Էŵ������档���Բ��á�
���1�ߵ�n��������߶������ӡ�
n<=500.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3153
˼·:��UVA11456 Trainsortingһ��ֻ�������������������������������ӿ������.
�������UVA11456 Trainsorting�������� ��wa,��Ϊͳ�Ƶ�LIS��LDS�����ظ���ȵ�,�ظ��Ĵ���������ֻ��a[i]һ��,��wa.
�����Ҫö��a[i]��a[j]��֤�䲻�ȵ����,
���
if(a[i]>a[j])//dp2[i]���ǲ���a[i]С������,dp1[j]�Ƕ�����a[j]�������
    ans=max(ans,dp2[i]+dp1[j]);
if(a[i]<a[j])//dp1[i]���ǲ���a[i]�������,dp2[j]�Ƕ�����a[j]С������
    ans=max(ans,dp1[i]+dp2[j]);
*/
//ac 150ms
#include<cstdio>
#include<algorithm>
#define N 5100
using namespace std;

//dp1[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�����½������еĳ���
//dp2[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�������������еĳ���
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    while(scanf("%d",&n) && n){
        ans=1;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<=a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>=a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
        }
        for(int i=n;i>=1;i--){//ö��a[i]��a[j]�����,�������ܱ�֤LIS��LDSû���ظ�ֵ,��ɵ����������м�¼��󳤶�
            //�п���a[i]��ʣ�µ�a[i-1..1]�����,����ans��ʼֵΪmax(dp1[i],dp2[i])
        	ans=max(ans,max(dp1[i],dp2[i]));
        	for(int j=i-1;j>=1;j--){
                //���ﲻ���е���,��Ϊdp2[i] dp1[j]����Ͱ�������,������ʹ���ƫ��
        		if(a[i]>a[j])//dp2[i]���ǲ���a[i]С������,dp1[j]�Ƕ�����a[j]�������
        			ans=max(ans,dp2[i]+dp1[j]);
        		if(a[i]<a[j])//dp1[i]���ǲ���a[i]�������,dp2[j]�Ƕ�����a[j]С������
        			ans=max(ans,dp1[i]+dp2[j]);
			}
		}
        printf("%d\n",ans);
    }
    return 0;
}

/*
//wa ����UVA11456 Trainsorting�������� ��wa,��Ϊͳ�Ƶ�LIS��LDS�����ظ���ȵ�,�ظ��Ĵ���������ֻ��a[i]һ��
#include<cstdio>
#include<algorithm>
#define N 5100
using namespace std;

//dp1[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�����½������еĳ���
//dp2[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�������������еĳ���
int n,a[N],dp1[N],dp2[N],ans;

int main(){
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=n;i>=1;i--){
            dp1[i]=dp2[i]=1;
            for(int j=n;j>i;j--){
                if(a[j]<=a[i])
                    dp1[i]=max(dp1[i],dp1[j]+1);
                if(a[j]>=a[i])
                    dp2[i]=max(dp2[i],dp2[j]+1);
            }
            //�����wa,����n~i�±���ֵ����һ����,��ôdp1[i]��dp2[i]ʵ�ʱ�ʾ������������ͬ��,���ظ������dp1[i]��dp2[i],�����һ��
            ans=max(ans,dp1[i]+dp2[i]-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

