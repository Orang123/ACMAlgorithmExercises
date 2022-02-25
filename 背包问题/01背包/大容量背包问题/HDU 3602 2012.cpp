#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
//ac 31ms 01����+��ֵ���������� ǡ��װ������
//�����һ�����������˱����ֹ��һ�ѷ�ͧ�� ��������˼ά��POJ 1976������
/*
����:��n�����Һ�m�ҷ�ͧ,ÿ�ҷ�ͧ�������k��,ÿ�����ҵ�����Ϊa[i]������+1����ͳ,
Ҫ��ÿ�����ҵ������˱�����ͬһ�ҷ�ͧ��,�ظù��ҵ��˿ɻ�b[i]��Ԫ,����Ҫ�����ʹ��
ǿ���ȵ��Ϸ�ͧ,�������,ʵ�ʵ�һ����������ǿ��,��������ǿ�ȵݼ�.����n�����ҵ���
����ܻ�ö��ٽ�Ǯ.
n,m<=100,k<=100000,a[i]<=100000,b[i]<=100.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3602
˼·:��Ϊm�ѷ�ͧ�������������ɴ�100*100000=10^7,��Ȼ������Ϊ��������,
���Խ�ÿ�����һ�õĽ�Ǯ��Ϊ��������,�����������������100*100=10^4.
Ȼ������ڻ�ý�Ǯ��ͬ�����,���ٳ��ض�����,��������01�������,����״̬��INF,
��ʼ״̬dp[0]=0.�����Ǯ���������,��ǰdp[i]�Ƿ��ǺϷ�״̬����.
*/
//dp[i][j] ���ǰi�����ҳ�����m�ѷɴ��ϻ�ý�Ǯj,������Ҫ���ص�����
//ʵ�ʹ��������Ż���һά.ֻ��dp[j]
int n,m,k,a[N],b[N],dp[M],sum;

//num���Ѿ�����m�ѷ�ͧ�еĶ�����������,ʵ�ʲ����������������������,������Ϊ����װ��һ�����ҵ��� �������
int cal(int num,int curp){
    int tp=(num+k-1)/k;//�����ǰ���ص�����������Ҫ���ҷ�ͧ �����һ�ѷ�ͧ�ı��
    //int tp=ceil(1.0*num/k);//ceil ��double����ȡ��
    if(num+curp<=tp*k)//�ж��Ѿ����ص����������һ�ѷ�ͧ�Ƿ���װ�µ�i�����ҵ�������,����װ��ֱ�ӷ���num+curp
        return num+curp;
    else//�������һ�ѷ�ͧtp����ȫ��װ�� ��i�����ҵ���,����Ҫ�ѵ�i�����ҵ��˵������ڵ�tp+1�ѷ�ͧ,����ʵ�����õ�����������Ϊtp*k+curp
        return tp*k+curp;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            a[i]++;
            sum+=b[i];
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=b[i];j--)
                dp[j]=min(dp[j],cal(dp[j-b[i]],a[i]));
        }
        int ans=0;
        for(int i=sum;i>=1;i--){
            if(dp[i]<=m*k){//���� ��һ��i��õĽ�Ǯi dp[i]�ǺϷ��� �����¼����õĽ�Ǯ
                ans=i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//��������Ϊ�����ݻ� ��ý�Ǯ��Ϊ��Ʒ��ֵ ��� ������Ҫ��Ҳ����������10^7��ô������
//dp[i][j] ���ǰi�����ҳ�����m�ѷɴ��ϳ�������Ϊjʱ,����õĽ�Ǯ
//ʵ�ʹ��������Ż���һά.ֻ��dp[j]
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,k,a[N],b[N],dp[M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            a[i]++;
            sum+=a[i];
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=a[i];j--){
                if(dp[j-a[i]]<0) continue;
                if(k-(j-a[i])%k>=a[i])
                    dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
                else
                    dp[(int)(ceil(1.0*(j-a[i])/k*k+a[i]))]=max(dp[(int)(ceil(1.0*(j-a[i])/k*k+a[i]))],dp[j-a[i]]+b[i]);
            }
        }
        int ans=0;
        for(int i=sum;i>=1;i--){
            if(dp[i]>0){
                ans=dp[i];
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

