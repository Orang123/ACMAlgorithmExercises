/*
����:ժ������
����n���������У��������ֵС�ڵ���k������Ը�����
n<=100000,k<=10^9.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5178
˼·:���մ�С���������,�ٳ�ȡ.
��x[r+1]-x[l]>kʱ �����ƶ���ָ��,��ʱ��r-l������������
��:(l,l+1),(l,l+2)...,(l,r).
*/
//ac 202ms
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

int n,k,x[N];
ll ans;

int main(){
    int T,l,r;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        sort(x+1,x+1+n);
        ans=0;
        l=r=1;//��ʼλ�ô�1��ʼ
        while(l<n){//����������l��ָ���Ƶ�n-1λ��,��Ϊ(n,n)��ͬһ����
            while(r+1<=n && x[r+1]-x[l]<=k)
                r++;
            ans+=r-l;
            l++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
