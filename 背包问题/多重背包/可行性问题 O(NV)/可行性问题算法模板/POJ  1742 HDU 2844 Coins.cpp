/*
����:����n�ֲ�ͬ��ֵ��Ӳ�ң���ֵΪval[1],val[2]...val[n]��ÿ�ּ�ֵ��Ӳ����num[1],num[2]...num[n]����
��ʹ����n��Ӳ�ҿ��Դ���[1,m]�ڶ��ټ�ֵ�����仰˵�����ǿ���ǡ��֧���ļ۸��ж��٣�
����:http://poj.org/problem?id=1742
˼·:
*/
//ac POJ 1742 2610ms HDU 2844 483ms ��������Ŀ��������� ��ȫ����
//ÿ�������ɼ�����Ʒ�ܷ��������������ı�����,ֻ�뿼�����������Ŀ�����,
//���迼��ÿ����Ʒ�ļ�ֵʱ,��:ʵ����Ʒ����ͼ�ֵ2�����Զ��ǵȼ۵�,���ر������⸴�Ӷȿ�����O(nv)
//���Ӷ�O(n*v)=10^2*10^5=10^7
//ע��:����������O(nv)�����������ر��������Ž�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]��ʾ����ǰi����Ʒ��������Ϊj�ı�����,��໹ʣ�¼�����i����Ʒ����
int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,-1,sizeof(dp));//��ʼ��-1���ǲ��Ϸ�
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=0;//��ʼ״̬0�ǺϷ�
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){//�����½���0,��i����Ʒ���Դ������ݻ����������
                //ע��:dp[j]=0�ǺϷ�״̬����ǰi-1����Ʒ��������Ϊj�ı�����໹ʣ��0����i-1����Ʒ,
                //��:�պðѵ�i-1����Ʒ����,�����ڵ�i����Ʒ������j�����������������ڷ�num[i]����i����Ʒ
                //-1����ʵ��û�дճ��ļ�ֵ
                if(dp[j]!=-1)
                    dp[j]=num[i];
            }
            for(int j=val[i];j<=m;j++)
                //����i����Ʒ���뱳������Ϊj-val[i]�ı���,�Ƿ��ܵõ�֮ǰû�ճ����ļ�ֵ
                //��֮ǰ��ֵû�ճ���,����dp[j]ԭʼ-1,�����º�dp[j]=dp[j-val[i]]-1
                //������֮ǰdp[j]����ʹճ���,�򲻸�����Ϊdp[j]�����Ϊnum[i],������ǰi-1����Ʒ����������num[i]����i����Ʒ
                //��dp[j-val[i]]=0,��˵����i����Ʒ�Ѿ������ٷ��뱳����,���dp[j]�����Ϊ-1,��dp[j]���ֵ����-1,��dp[j]�����ǿɴ����dp[j]>=0.
                dp[j]=max(dp[j],dp[j-val[i]]-1);//dp[j-val[i]]����ܷ����i����Ʒ����-1
            /*
            //ac 2594ms
            for(int j=0;j+val[i]<=m;j++)
                dp[j+val[i]]=max(dp[j+val[i]],dp[j]-1);
            */
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i]!=-1)
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac POJ 1742 2454ms HDU 2844 499ms ������������򻯰汾 ��ȫ����
//���Ӷ�O(n*v)=10^2*10^5=10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]��ʾ����ǰi����Ʒ��������Ϊj�ı�����,��໹ʣ�¼�����i����Ʒ����
int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,-1,sizeof(dp));//��ʼ��-1���ǲ��Ϸ�
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=0;//��ʼ״̬0�ǺϷ�
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=val[i])
                    dp[j]=max(dp[j],dp[j-val[i]]-1);
            }
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i]!=-1)
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/

/*
//ac POJ 1742 1344ms HDU 2844 452ms ������Ʒ��������ȫ��������
//���Ӷ�O(n*v)=10^2*10^5=10^7
//�������������ʱ��wa,����HDU 1059 Dividing,�����ñ����Ž��еİ汾.
//���������������ת��ʱ������С/�����Ŀ POJ 1787,������(Ŀǰû������,Ӧ���ǿ��Ե�).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]=1����ǰi����Ʒ��ֵ��Ϊj�Ǵ��ڵ�
//cnt[i][j]=k����ǰi����Ʒ��ֵ��Ϊjʱ,��i����Ʒ�Ѿ�������k��,k<=num[i],k���ܳ�����i����Ʒ��������
int n,m,val[N],num[N],dp[M],cnt[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=1;//��ʼ״̬
        for(int i=1;i<=n;i++){
            //ÿ�ζ�Ҫ��ʼ��cnt����,��i����Ʒ�տ�ʼ��ûװ�� ��ĿΪ0
            memset(cnt,0,sizeof(cnt));
            for(int j=val[i];j<=m;j++){
                //��һ״̬dp[j-val[i]]�����ǿ��е�,����֮ǰ ǰi-1����ƷΪת�Ƶ�j���״̬,��:dp[j]=0
                //���Ҽ����i����Ʒ���������ܳ�������
                //���dp[j]ǰi-1����Ʒ�Ѿ��Ƴ���,����Ͳ���ת��,��cnt����0,�������ֱ����ǰi-1����Ʒ����������ټ���num[i]����i����Ʒ
                if(dp[j-val[i]] && !dp[j] && cnt[j-val[i]]+1<=num[i]){
                    dp[j]=1;
                    cnt[j]=cnt[j-val[i]]+1;
                }
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++){
            if(dp[i])
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/


/*
//POJ 1742 ��TLE HDU 2844 ac 546ms �������Ż�ö�ٷ�����
//���Ӷ�O(��log(num[i])*v)=100*log(1000)*100000=10^8 s3ʱ�� ��������TLE��,����POJ���ݸ�ǿ
#include<cstdio>
#include<cstring>
#define N 110
#define M 100010

int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=1;
        int tv;
        for(int i=1;i<=n;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tv=val[i]*k;
                for(int j=m;j>=tv;j--){
                    if(dp[j-tv])
                        dp[j]=1;
                }
            }
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i])
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/

/*
//ac HDU 2844 249ms POJ 1742 TLE ���ر���+���������Ż�
//POJ�е����...
//���Ӷ�O(nv)=10^2*10^5=10^7
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int a[110],c[110];
queue<int>q;//����һ��FIFO�Ķ���q(����ĵ�������ֻ������)
bool f[100100];
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)return 0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        memset(f,0,sizeof(f));
        f[0]=1;
        for (int i=1;i<=n;i++)//���½���01��������ȫ���������ر����ķֽ�
        {
            int maxl=a[i]*c[i];
            if (c[i]==1)//���ֻ��һ����Ʒ�� �����01����
            {
                for(int j=m;j>=a[i];j--)
                if(f[j-a[i]])
                f[j]=1;
            }
            else if(m<=maxl)//�����Ʒ����ֵ���������ֵ���������ȫ����
            {
                for(int j=a[i];j<=m;j++)
                if (f[j-a[i]])
                f[j]=1;
            }//���²�����ͷϷ����ȫ�����ĵ��������Ż�
            else for(int j=0;j<a[i];j++)//�����ظ�
            {
                while(q.size()>0) q.pop();//��ն���
                for(int k=j;k<=m;k+=a[i])//������ô�С
                {
                    while(q.size()>0&&k-q.front()>maxl) q.pop();//ʼĩ����֮��ľ���ӦС�ڵ�i����Ʒ���ܼ�ֵ
                    if(!f[k])//�ɴ˶���ö��c[i]��m���˽ϴ������
                    {
                        if(q.size()>0)//ֻ�ж��в�Ϊ�գ������Դ�ĳ�㵽��
                        f[k]=1;
                    }
                    else q.push(k);//�������0�������β
                }
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++)
            if(f[i])ans++;//ͳ�ƿ��е���ֵ��
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 405ms ���ر���+bitset
//��ʱû��bitset
//�ο�����:https://blog.csdn.net/Paulliant/article/details/80837276
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#define FOR(i,x,y) for(int i=(x);i<=(y);i++)
#define DOR(i,x,y) for(int i=(x);i>=(y);i--)
typedef long long LL;
using namespace std;
struct Pack
{
    bitset<100003>dp;
    Pack(){dp.reset();dp[0]=1;}
    void load(int c,int m)
    {
        for(int k=1;k<=m;k<<=1)
        {
            dp|=(dp<<c*k);
            m-=k;
        }
        dp|=(dp<<c*m);
        return;
    }
};

int main()
{
    int m,n;
    while(scanf("%d%d",&m,&n),m||n)
    {
        Pack P;
        int a[103],b[103],ans=0;
        FOR(i,1,m)scanf("%d",&a[i]);
        FOR(i,1,m)scanf("%d",&b[i]);
        FOR(i,1,m)P.load(a[i],b[i]);
        FOR(i,1,n)ans+=P.dp[i];
        printf("%d\n",ans);
    }
    return 0;
}
*/
