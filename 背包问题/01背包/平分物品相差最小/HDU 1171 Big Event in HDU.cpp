/*
����:����ÿ���豸�ļ�ֵ�����������,����Ҫ����Щ�豸
�ֱ�ָ�A��B��������,��η�ʹ��A,B���ü�ֵ��ӽ�����A�ļ�ֵ����С��B.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1171
˼·:ʵ�ʾ���Ҫ�����ܵý�A��B���ֵõ��豸��ֵ�����,����A�õ���ֵ�Ͳ��ܱ�B��,
�����������豸������,ʵ�ʿ��Կ�����ηָ�B�����ܶ���豸��ֵʹ���豸��ֵ�ܺͲ�����
�����豸��ֵ�ܺ͵�һ��.��Ϊ�����豸�ļ�ֵ�ܺ�<=50*100*50=250000,�豸����(50*100=5000)
�������,��˿��Խ�һ���豸�����и������ɲ�ͬ����Ʒ,����ת��Ϊ01��������,
��������Ϊ��Ʒ��ֵ�ܺ͵�һ��,��Ʒ����ͼ�ֵ�������ֵ,��⾡���ܶ�ؽ��豸�ָ�B,
�����ܶ��װ������Ϊsum/2�ı���,��ôdp[sum/2]����ŵļ�ֵһ��<=sum/2,����ָ�B,
��һ��sum-dp[sum/2](��ֵ)�ָ�A����,��Ϊsum-dp[sum/2]>=sum/2.
*/
//ac 15ms ���н����� �����Ž��ⷨ
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
#define M 125010
using namespace std;

int n,val[N],num[N],dp[M],sum;

int main(){
    int ans,tp;
    while(scanf("%d",&n) && n>0){
        sum=0;
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&val[i],&num[i]);
            sum+=val[i]*num[i];
        }
        tp=sum/2;
        ans=0;
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=tp;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=val[i])
                    dp[j]=max(dp[j],dp[j-val[i]]-1);
                if(dp[j]!=-1)
                    ans=max(ans,j);
            }
        }
        printf("%d %d\n",sum-ans,ans);
    }
    return 0;
}

/*
//ac 78ms ��ȫ����+�������Ż���01���� �����Ž�
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
#define M 125010
using namespace std;

int n,val[N],num[N],dp[M],sum;

int main(){
    int tp;
    while(scanf("%d",&n) && n>0){
        sum=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&val[i],&num[i]);
            sum+=val[i]*num[i];
        }
        tp=sum/2;
        for(int i=1;i<=n;i++){
            if(num[i]*val[i]>=tp){
                for(int j=val[i];j<=tp;j++)
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
            else{
                int tw;
                for(int k=1;num[i]>0;k<<=1){
                    num[i]-=k;
                    if(num[i]<0)
                        k+=num[i];
                    tw=k*val[i];
                    for(int j=tp;j>=tw;j--)
                        dp[j]=max(dp[j],dp[j-tw]+tw);
                }
            }
        }
        printf("%d %d\n",sum-dp[tp],dp[tp]);
    }
    return 0;
}
*/

/*
//ac 733ms 01���� �������������ܶ��װ
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int dp[250005];//��������������<=50*100*50=250000
//�ö��ر����������Ż���˼��Ч�ʻ��Щ46ms�����700ms
int main(){
    int N,num,x,a[5500],sum,index;
    while(scanf("%d",&N)&&N>0){
        memset(dp,0,sizeof(dp));//�������������ܶ��װ,����״̬���ǺϷ���
        index=sum=0;
        for(int i=1;i<=N;i++){
            scanf("%d%d",&x,&num);
            while(num--){
                a[++index]=x;
                sum+=x;
            }
        }
        for(int i=1;i<=index;i++){
            for(int j=sum/2;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        printf("%d %d\n",sum-dp[sum/2],dp[sum/2]);
    }
    return 0;
}
*/

/*
//ac 1014ms ĸ��������
#include <iostream>
#include <cstring>
using namespace std;
const int maxn=3e5+100;
int n;
int c1[maxn],c2[maxn];
int num[55],data[55];int sum;
void init()
{
    sum=0;
    for(int i=1;i<=n;++i)
    {
        cin>>data[i]>>num[i];
        sum+=data[i]*num[i];
    }
}
void solve()
{
    memset(c1,0,sizeof(c1));
    memcpy(c2,c1,sizeof(c1));
    for(int i=0;i<=num[1];++i)
        c1[i*data[1]]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<=sum/2;++j)
        {
            if(c1[j])
            for(int k=0;k+j<=sum/2&&k/data[i]<=num[i];k+=data[i])
                c2[k+j]+=c1[j];
        }
        memcpy(c1,c2,sizeof(c2));
        memset(c2,0,sizeof(c2));
    }
    int i=1;
    for(i=sum/2;i>=0;--i)
        if(c1[i])
            break;
    cout<<sum-i<<" "<<i<<endl;
}
int main(int argc, const char * argv[])
{
    while(cin>>n&&n>=0)
    {
        init();
        solve();
    }
    return 0;
}
*/
/*
���ر������� ���Ͽ��н��������Ż���01����
*/

/*
//ac 717ms 01���� ������������ǡ��װ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF -0x3f3f3f3f
using namespace std;

int dp[250005];//��������������<=50*100*50=250000
int main(){
    int N,num,x,a[5500],sum,index;
    while(scanf("%d",&N)&&N>0){
        memset(dp,-0x3f,sizeof(dp));//����dp[0]�Ϸ�����״̬�����Ϸ�,��ʼ��Ϊ-INF
        index=sum=0;
        for(int i=1;i<=N;i++){
            scanf("%d%d",&x,&num);
            while(num--){
                a[++index]=x;
                sum+=x;
            }
        }
        dp[0]=0;//0״̬�Ϸ� ������¼ǡ��װ�������
        for(int i=1;i<=index;i++){
            for(int j=sum/2;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        int ans=0;//�п���ֻ��һ���豸,ֻ�ָܷ�A��B������һ��,����ans��ʼ��Ϊ0,��Ϊdp[i]����dp[0]�����Ϸ�
        for(int i=sum/2;i>=1;i--){//ǡ��װ�� �����ǽ���ֵΪ1���豸�ָ�B ����������1
            if(dp[i]>0){//dp[i]>0�Ĳ�����ǡ��װ�� �����ĺϷ�״̬
                ans=i;
                //ans=dp[i];
                break;
            }
        }
        //ans����ʼ��Ϊ0,forѭ�������жϵ�0,dp[i]�ж������޸�Ϊdp[i]>=0Ҳ�ǿ��Ե�,����
        //int ans;
        //for(int i=m-5;i>=0;i--)
            //if(dp[i]>=0)
        printf("%d %d\n",sum-ans,ans);//ans Ϊ0ʱ,���sum��0,��Ϊ��ʱֻ��һ���豸,ֻ�ָܷ�A��B������һ��
    }
    return 0;
}
*/

/*
//TLE ��������ö�� (δ��Ӻ�׺��֦)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 5100
#define INF -0x3f3f3f3f
using namespace std;

int n,num,t,val[N],sum,ans;

int dfs(int k,int res){
    if(res<=sum/2 && res>ans){
        ans=res;
        if(res == sum/2) return 1;
    }
    if(res>sum/2) return 0;
    if(k == num+1) return 0;
    if(dfs(k+1,res+val[k])) return 1;
    if(dfs(k+1,res)) return 1;
    return 0;
}

int main(){
    int x;
    while(scanf("%d",&n) && n>0){
        ans=sum=num=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&t);
            while(t--){
                val[++num]=x;
                sum+=x;
            }
        }
        dfs(1,0);
        printf("%d %d\n",sum-ans,ans);//ans Ϊ0ʱ,���sum��0,��Ϊ��ʱֻ��һ���豸,ֻ�ָܷ�A��B������һ��
    }
    return 0;
}
*/

