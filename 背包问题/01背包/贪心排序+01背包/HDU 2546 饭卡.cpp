#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;
//ac 31ms 01����+̰�� �������������ܶ��װ��

/*
����:���ӿƴ󱾲�ʳ�õķ�����һ�ֺܹ�������,���ڹ���֮ǰ�ж����.
�������һ����Ʒ֮ǰ,���ϵ�ʣ������ڻ����5Ԫ,��һ�����Թ���ɹ�
(��ʹ����������Ϊ��),�����޷�����(��ʹ����㹻).���Դ�Ҷ�ϣ����
��ʹ���ϵ��������.ĳ��,ʳ������n�ֲ˳���,ÿ�ֲ˿ɹ���һ��.��֪ÿ�ֲ�
�ļ۸��Լ����ϵ����,�����ٿ�ʹ���ϵ����Ϊ����.
ע��:��ÿһ����Ʒ���豣֤�������>=5,��ʹ��Ʒ�ļ۸�С��5,�����С��5,
��ʱҲ���ܹ���ü���Ʒ.
eg:3����Ʒ�۸�Ϊ1,���ϳ�ʼ���6Ԫ,ʵ��ֻ����2����Ʒ,��Ϊ���������Ʒʱ,
ֻʣ��4Ԫ,����5Ԫ�޷�����,���տ���ʣ��ǮΪ4Ԫ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2546
˼·:�����Կ����������,����01������������û��ֱ��װ��������,������̰����
��͵�5Ԫ������,֮���ʣ�µ���Ʒ��01�����������������Ǯ,��ô����ʣ�µ�
Ǯ����m-5-dp[m-5]+5-tp,m-5-dp[m-5]����ʣ����Ʒ��ʣ���Ǯ,tpΪ�����Ʒ�ļ۸�,
5-tpΪ�������Ʒʣ�µ�Ǯ,m-5-dp[m-5]Ϊ��ʣ����Ʒʣ���Ǯ.
*/
int n,m,dp[N],val[N],tp,id;
int main(){
    while(scanf("%d",&n) && n){
        memset(dp,0,sizeof(dp));
        tp=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            if(tp<val[i]){
                tp=val[i];
                id=i;//��¼�����Ʒ���
            }
        }
        scanf("%d",&m);
        if(m<5){//ע�⿨�ϳ�ʼ��� ��������С��5,��Ҳ�޷�����,ֱ�������ʼ���
            printf("%d\n",m);
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=m-5;j>=val[i];j--){
                if(i!=id)//�����Ʒ��̰�Ĵ���� ���ٹ���
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
        }
        printf("%d\n",m-5-dp[m-5]+5-tp);
    }
    return 0;
}

/*
//ac 15ms 01����+̰�� ��������ǡ��װ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N],val[N],tp,id;
int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-0x3f,sizeof(dp));
        tp=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            if(tp<val[i]){
                tp=val[i];
                id=i;//��¼�����Ʒ���
            }
        }
        scanf("%d",&m);
        if(m<5){//ע�⿨�ϳ�ʼ��� ��������С��5,��Ҳ�޷�����,ֱ�������ʼ���
            printf("%d\n",m);
            continue;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=m-5;j>=val[i];j--){
                if(i!=id)//�����Ʒ��̰�Ĵ���� ���ٹ���
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
        }
        int ans=0;//ans��ʼ��Ϊ0 �п���m-5ʣ�µ�Ǯ �������κ�һ����Ʒ
        for(int i=m-5;i>=1;i--){//ǡ��װ�� �����ǻ�1Ԫ��һԪ����Ʒ ����������1
            if(dp[i]>0){//ֻ��dp[i]>0�Ĳ��ǺϷ�״̬ ǡ��װ��������
                ans=dp[i];
                //ans=i;//ǡ��װ��,dp[i]��i����ȵ�ans=i,ans=dp[i]���ǵȼ۵�
                break;
            }
        }
        //ans����ʼ��Ϊ0,forѭ�������жϵ�0,dp[i]�ж������޸�Ϊdp[i]>=0Ҳ�ǿ��Ե�,����
        //int ans;
        //for(int i=m-5;i>=0;i--)
            //if(dp[i]>=0)
        printf("%d\n",m-5-ans+5-tp);
    }
    return 0;
}
*/

/*
//ac 31ms 01���� �������������ܶ�װ,����,���ķ������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max(i,j) i>j?i:j
int dp[1000],a[1005];
int main(){
    int n,m;
    while(scanf("%d",&n)&&n){
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        sort(a,a+n);//������ȡ����
        scanf("%d",&m);
        if(m<5){
            printf("%d\n",m);
            continue;
        }
        m-=5;
        for(int i=0;i<n-1;i++){//�Ȳ�������
            for(int j=m;j>=a[i];j--)
                    dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        printf("%d\n",m-dp[m]+5-a[n-1]);//����ֵ+5ʣ�µ������Ĳ�ֵ
    }
    return 0;
}
*/

/*
//TLE ����ö������(δ��֦)
#include<cstdio>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,val[N],ans;

//2����֦δд
//��֦1 m-5ȫ������,��ansΪ0ʱ��ֱ�ӷ��ؽ��
//��֦2 ��׺��֦
void dfs(int k,int curV,int sum){
    if(m-5-sum<ans)
        ans=m-5-sum;
    if(k == n) return;//������Ʒ���ٹ���
    if(curV>=val[k])
        dfs(k+1,curV-val[k],sum+val[k]);
    dfs(k+1,curV,sum);
}
int main(){
    while(scanf("%d",&n) && n){
        ans=INF;
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        scanf("%d",&m);
        if(m<5){//ע�⿨�ϳ�ʼ��� ��������С��5,��Ҳ�޷�����,ֱ�������ʼ���
            printf("%d\n",m);
            continue;
        }
        sort(val+1,val+1+n);
        dfs(1,m-5,0);
        printf("%d\n",ans+5-val[n]);
    }
    return 0;
}
*/
