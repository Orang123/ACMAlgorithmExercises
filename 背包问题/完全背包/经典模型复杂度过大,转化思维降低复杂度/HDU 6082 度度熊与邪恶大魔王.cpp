//ac 124ms ��ö�ٹ�����ʽ ��ö��j����ֵ
/*
����:�ȶ���Ϊ�����ȿɰ��Ĺ���,������а���ħ��ս������.
а���ħ����������n������,ÿ��������a[i]������ֵ,�Լ�b[i]�ķ�����.
�ȶ���һ��ӵ��m�ֹ�����ʽ,��i�ֹ�����ʽ,��Ҫ����k[i]�ľ�ʯ,���p[i]���˺�.
��Ȼ,����ȶ���ʹ�õ�i�����ܴ��ڵ�j����������Ļ�,��ʹ�õ�j�����޵�����ֵ
����p[i]-b[j],��Ȼ����˺�С�ڷ���,��ô�����Ͳ�����Ч.������޵�����ֵ��Ϊ
0������,��ô���޾ͻᱻ����.��Ȼÿ�����ܶ�����ʹ�����޴�.���ʶȶ�������Я��
���پ�ʯ,�Ϳ����������еĹ���.
1<=n<=100000
1<=m<=1000
1<=a[i]<=1000
0<=b[i]<=10
0<=k[i]<=100000
0<=p[i]<=1000
����:http://acm.hdu.edu.cn/showproblem.php?pid=6082
˼·:���Խ�n�����޿���n������,��������Ϊ���޵�����ֵ,m��������ʽ����������
���Ƶ���Ʒ,��Ʒ����Ϊ���ܵ��˺�ֵp[i],��Ʒ��ֵΪ���ľ�ʯ��Ŀk[i].������n��
��ȫ����������.
�������ص���ȫ�������Ӷ� n*O(mv)=10^5*10^3*10^3=10^11,���Ӷ�̫��.��ʵ�ϲ�ͬ
����������ֵ��������϶���ͬһ�ֹ���,Ҳ����������ֵ��������ݻ�ά������ʵ��
ֻ����һ����ȫ��������,���ֲ�ͬ��������Ĺؼ������ڹ��޼�ķ�����b[i],��Ϊb[i]
��ֱ��Ӱ��û���������Ĺ��޵�����ֵΪ����,��ʵ��0<=b[i]<=10,Ҳ����˵ʵ�����ֻ��
11�ֹ���,��ôʵ�����ֻ��11�ֱ���,������ȫ�����ĸ��Ӷ����Ϊ 11*O(mv)=1.1*10^7.
���Զ���dp[i][j]������޷�����Ϊiʱ,��������ֵΪj�Ĺ���������Ҫ�ľ�ʯ.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f//long long��64λ,����INF 16������16λ ��Ȼ�ж�INF�����
typedef long long ll;
using namespace std;

int n,m,a[N],b[N],p[M];
//dp[i][j]������޷�����Ϊiʱ,��������ֵΪj�Ĺ���������Ҫ�ľ�ʯ.
ll dp[11][M],k[M];

int main(){
    int maxa,maxb;
    while(scanf("%d%d",&n,&m)!=EOF){
        maxa=1,maxb=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            //����dpʱ��dp[i][j] i��j��ά��
            maxa=max(maxa,a[i]);//�����������ֵ j
            maxb=max(maxb,b[i]);//������Ĺ��޷����� i
        }
        for(int i=1;i<=m;i++)
            scanf("%d%d",&k[i],&p[i]);
        memset(dp,0x3f,sizeof(dp));
        //ÿ�ַ�������Ӧһ�����͵Ĺ���,һ���µ����͵ı���
        //ÿ��������ʼ״̬���� ��������ֵΪ0ʱ��Ҫ��ʯΪ0
        for(int i=0;i<=maxb;i++)
            dp[i][0]=0;
        for(int i=0;i<=maxb;i++){
            for(int t=1;t<=m;t++){
                if(p[t]<=i) continue;//�˺�ֵp[t]�����ڷ�����iʱ �޷�������������ֵ
                for(int j=1;j<=maxa;j++){
                    //���ٵ�����ֵ��p[t]-i(�˺�ֵ-������)
                    if(j-(p[t]-i)<0)//��t�ּ����˺�ֵԶ��������ֵ,��ô��һ״̬������Ϊ�� ����ֵΪ0 ��ʯΪ0
                        dp[i][j]=min(dp[i][j],k[t]);
                    else
                        dp[i][j]=min(dp[i][j],dp[i][j-(p[t]-i)]+k[t]);
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;i++){
            if(dp[b[i]][a[i]]!=INF)
                ans+=dp[b[i]][a[i]];
            else{//ֻҪ��һ�ֹ���û������ �����-1
                ans=-1;
                break;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 156ms ��ö��j����ֵ ��ö�ٹ�����ʽ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;

int n,m,a[N],b[N],p[M];
ll dp[11][M],k[M];

int main(){
    int maxa,maxb;
    while(scanf("%d%d",&n,&m)!=EOF){
        maxa=1,maxb=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            maxa=max(maxa,a[i]);
            maxb=max(maxb,b[i]);
        }
        for(int i=1;i<=m;i++)
            scanf("%d%d",&k[i],&p[i]);
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<=maxb;i++)
            dp[i][0]=0;
        for(int i=0;i<=maxb;i++){
            for(int j=1;j<=maxa;j++){
                for(int t=1;t<=m;t++){
                    if(p[t]<=i) continue;
                    if(j-(p[t]-i)<0)
                        dp[i][j]=min(dp[i][j],k[t]);
                    else
                        dp[i][j]=min(dp[i][j],dp[i][j-(p[t]-i)]+k[t]);
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;i++){
            if(dp[b[i]][a[i]]!=INF)
                ans+=dp[b[i]][a[i]];
            else{
                ans=-1;
                break;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
