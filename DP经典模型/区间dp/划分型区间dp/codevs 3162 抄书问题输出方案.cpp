#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//�������������������е�����
/*
����:����Ҫ��M����˳�����ָ�K���˸��ƣ���д����ÿһ���˵ĳ�д�ٶȶ�һ����
һ���鲻����������������ϣ����˳�д���ָ�ÿһ���˵��飬�����������ģ����粻�ܰѵ�һ�����������ı�����ͬһ���˳�д��
�����������һ�ַ�����ʹ�ø���ʱ����̡�����ʱ��Ϊ��дҳ����������ȥ��ʱ�䡣
����ж�⣬�򾡿�����ǰ������ٳ�д��
����:https://blog.csdn.net/qq_34374664/article/details/68953181
˼·:dp[i][j]����ǰi���齻��j����ȥ��д һ���˳�д������ҳ��
*/

int dp[110][110],m,k,a[110],sum[110],pos[110];

int main(){
    scanf("%d%d",&m,&k);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
        sum[i]=sum[i-1]+a[i];
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=m;i++)
        dp[i][1]=sum[i];
    for(int t=2;t<=k;t++){
        for(int i=t;i<=m;i++){
            for(int j=t-1;j<i;j++)
                //һ���˳�д����ҳ��Ϊ�ܳ�дʱ��,����ָ��Ҫʹ�������д����ʱ����С
                dp[i][t]=min(dp[i][t],max(dp[j][t-1],sum[i]-sum[j]));//sum[i]-sum[j]Ϊ��t���˳�д��ҳ�� ��ǰ���t-1���˳�д�����ҳ���Ƚ�
        }
    }
    pos[1]=0;
    pos[k+1]=m;//���һ�������д�õ�ҳ��Ϊm
    int tmp=0,p=k;
    for(int i=m;i>=1;i--){
        if(a[i]+tmp<=dp[m][k])//��Ϊһ���˳����������������,����ֻҪ������һ���˳�д������ҳ��,�Ȿ���������˳���,������˾����ܶ೭
            tmp+=a[i];
        else{//���Ȿ�鳬��һ���˳������ҳ��ʱ,˵���ǵ�t-1���˳���
            tmp=a[i];
            pos[p--]=i;//����p-1���˵����һ����д�����ż�¼
        }
    }
    for(int i=2;i<=k+1;i++)
        printf("%d %d\n",pos[i-1]+1,pos[i]);
    return 0;
}

/*
����dp ��ȷ�������������
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int INF =0x3f3f3f3f;
const int maxn=100    ;


int dp[maxn+5][maxn+5],a[maxn+5];
int n,m;
int sum[maxn+5];
int ans;

void print(int num ,int v)
{

    int best;

    if(num==1)   {printf("%d %d\n",1,v);return;}
    for(int k=num-1;k<v;k++)
    {

        int ret=max(dp[num-1][k],sum[v]-sum[k]);
        if(ret<=ans  )
        {
            best=k;
            break;
        }
    }


   print(num-1,best);
    printf("%d %d\n",best+1,v);


}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0)
        {
            continue;
        }
        sum[0]=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
            dp[1][i]=sum[i];
        }


        for(int i=2;i<=n;i++)//i����
        {
            for(int j=i;j<=m-(n-i);j++)//j����
            {
                dp[i][j]=INF;
                for(int k=i-1;k<j;k++  )
                {
                    int ret=max(dp[i-1][k], sum[j]-sum[k] );
                    if(  ret<dp[i][j]   )
                    {
                        dp[i][j]=ret;
                    }
                }

            }
        }
        ans=dp[n][m];
        print(n,m);


    }


   return 0;
}
*/


/*
�������ֵ��С������ҳ������
inline bool check(int limit) {
    memset(pageCount, 0, sizeof(pageCount));

    int j = k - 1, lastEnd = m - 1;
    for (int i = m - 1; i >= 0; i--) {
        if (pageCount[j] + a[i] <= limit) {
            pageCount[j] += a[i];
        } else {
            if (j == 0) {//˵�����ĳ���ҳ��̫С��
                return false;
            }

            lastEnd = i;
            pageCount[--j] += a[i];
        }
    }

    return sum(0, lastEnd - 1) <= limit;//���ܲ���k���� ����ҳ��̫����
}

inline int binaryDivide() {
    int l = max, r = sum(0, m - 1);
    while (l < r) {
        int mid = l + ((r - l) >> 1);
        if (check(mid)) r = mid;//˵�������ҳ��̫����,�����ֹܷ�k���� ��С�ұ߽�
        else l = mid + 1;//˵�����ĳ���ҳ��̫С�� ������߽�
    }

    return l;
}
*/
