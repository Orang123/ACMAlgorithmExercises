#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 1100
using namespace std;
//ac 0ms һά����ʵ�� 01���� �����ܶ��װ������������
//�����n��ʼö��װ���µ���Ʒ �Ż����ʱ�临�Ӷ�O(nv)
//��ǳ̸���۱������⡷ ��ֺ� pdf�н���POJ 3093�����
/*
����:n����Ʒ,ÿ����Ʒ�����Ϊw[i],��������Ϊv�ı���,
�ʱ�����Ҳװ�����κ���Ʒ�ķ�����,��:�����ܶ��װ������
�ķ�����.
����:http://poj.org/problem?id=3093
˼·:���������ǡ��װ����������������ͳ��,��:dp[v]+=dp[v-w],
ֻ�ǳ���״̬����1,��ô�����һ����Ʒ���2,dp[2]+=dp[2-2],dp[2]=1+1=2,��Ȼ����Ǵ��.
����01�������������ֻ��ͳ��ǡ��װ�������,���Ծͳ��԰Ѿ����ܶ��װ���ķ���ת��Ϊǡ��
װ����������ķ���ͳ��,����������ǡ��װ���ֲ�֪��������Щ������ǡ��װ��.���Խ���Ʒ����
����Ӵ�С����,ö�ټ����i����Ʒ��ǡ��װ����ȥ��(����ʣ�������ȵ�i����Ʒ�������С1),
��ô���Ϊ1~(i-1)����Ʒ�϶���ȫ�����뱳����,���ʱ��Ա���ʣ�������ڱ��Ϊn~(i+1)��Ʒ��
��01��������װ��һЩ��Ʒʹ�ñ���ʣ����������װ�µ�i����Ʒ,ʹ��֮ǰ�ļ������,��n~i+1��
ʣ��δװ�뱳������Ʒ������ȵ�i����Ʒ�����,������Щʣ�µ���ƷҲȫ���޷�װ�뱳��,���Դ�ʱ
װ�뱳������Ʒʹ�ñ�����Ҳװ���±����Ʒ,�ﵽ�˾����ܶ��װ������.���Ծ����������װ�뱳��
����Ʒ��Ҫ���������������Ʒn��ʼװ.

dp[i][v]��ʾ����n~(i+1)����Ʒ��ǡ��װ������Ϊv�����ķ����� ʵ�ʹ��������Ż����˵�һλ��i ֻ��dp[v]
*/
int n,v,w[N],dp[M],sum,ans;

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        ans=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sort(w+1,w+1+n);
        //��,n=6,v=4,w[i]={8,9,8,7,16,5}
        //������dpʱi==1ʱ,ans�ۼӵ�ѭ����,j�½�=0,�Ͻ�=4 ans���ۼ�dp[0]=1,��������1
        if(w[1]>v){
            printf("%d 0\n",t);
            continue;
        }
        dp[0]=1;//��ʼ״̬ ֻ��0Ϊ1,������ǡ��װ������
        //��������������Ʒ��ʼö��,����i��ǡ�ò���װ�뱳������Ʒ
        for(int i=n;i>=1;i--){
            sum-=w[i];//sum��ʾ1~(i-1)��ƷԤ��װ�뱳����ռ�ݵ��ݻ�
            //v-sum��1~(i-1)��Ʒװ�뱳����ʣ����ݻ�
            //������ö��n~(i+1)��Ʒ����ռ�ݵĵ�ǰ����ʣ������
            //v-sum-w[i]+1��ʾ��ѡ���n~(i+1)��Ʒ��������ǡ��װ��v-sum-w[i]+1ʣ�౳������
            //v-sum-w[i] ��ʾ����ʣ��������ȥ��i����Ʒռ�ݵ�������ʣ�µ�����,+1��Ϊ��ʹ��
            //ʣ�µı����������ٱȵ�i����Ʒ�������1,�������ܱ�֤��i����Ʒ����װ�뱳��.��֤ö�ټ������ȷ��.
            //����v-sum-w[i]+1��ö��n~(i+1)ǡ��װ���������½�,�Ͻ�Ϊv-sum.
            //���½�Ҫ��֤����Ϊ����,��Ϊv-sum����Ϊ��,����ʵ��1~(i-1)����Ʒ������ȫ�����뱳��
            //��ô��ǰ�ļ�����ǲ�������,����v-sum-w[i]+1<0,��0ȡ����j=0,v-sum<0���ܱ�֤ans���ۼ��κ�dp[j]
            //���ߵ�i == n,v-sumʵ�ʱ�w[i]Сʱ,��ôʵ��ֻ��w[i]��װ���µ�,��ʱmax����j�½�Ϊ0,��dp[0]=1������һ�ַ���
            //eg:n=3,v=3 w[i]={1,2,4} ������Ϊ1 ֻ��{1,2}���ַ������
            for(int j=max(v-sum-w[i]+1,0);j<=v-sum;j++)
                //�ۼ�n~(i+1)��Ʒ��ǡ��װ��������j�ķ�����,j���ڵ�ǰʣ�౳��������ռ�ݵ�����,
                //����v-sum-j<w[i],�ܱ�֤��ǰװ��n~(i+1)��Ʒ��ʣ�µı����ݻ�Ҳװ���µ�i����Ʒ,�Ӷ���֤�������ȷ��.
                ans+=dp[j];//��һ״̬dp[j] ѡ��n~(i+1)����Ʒװ������Ϊj�ı���ǡ��װ���ķ�����
            //����һ״̬n~(i+1)����Ʒ���Ž�����Ϸ����i����Ʒ,�����Ϊn~i����Ʒ��01���������Ž�
            //��Ϊ����ʣ���ݻ���ȷ��,������ȡ��ʼ�����ݻ�
            for(int j=v;j>=w[i];j--)
                dp[j]+=dp[j-w[i]];
        }
        printf("%d %d\n",t,ans);
    }
    return 0;
}
/*
//ac 0ms ��ά����ʵ�� �����n��ʼö��װ���µ���Ʒ ʱ�临�Ӷ�O(nv)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 1100
using namespace std;

int n,v,w[N],dp[N][M],sum,ans;

int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        ans=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sort(w+1,w+1+n);
        if(w[1]>v){
            printf("%d 0\n",t);
            continue;
        }
        for(int i=n+1;i>=2;i--)
            dp[i][0]=1;
        for(int i=n;i>=1;i--){
            sum-=w[i];
            for(int j=max(v-sum-w[i]+1,0);j<=v-sum;j++)
                ans+=dp[i+1][j];
            for(int j=w[i];j<=v;j++)//���� ���򶼿�
                //����д��dp[i][j]+=dp[i+1][j-w[i]],��Ϊֻ������dp[i+1][j-w[i]],
                //ԭ��ǰn~i+1��Ʒ���뱳������Ϊjǡ��װ���ķ�����dp[i+1][j]û����
                //HDU 2126�����ǹ��������Ż����ά,û�Ż�֮ǰӦ������ά����dp,���������д����һ����,����"+="
                dp[i][j]=dp[i+1][j]+dp[i+1][j-w[i]];
        }
        printf("%d %d\n",t,ans);
    }
    return 0;
}
*/

/*
ժ�Բ���:https://blog.csdn.net/ayyyyy_zc/article/details/88887718
//ac 0ms �ӵ�1����Ʒ��ʼö��װ���� dp ���Ӷ�O(n^2*v)
//֮���Ը��Ӷȶ�һ��ά������Ϊ ͬһ����Ʒ��α����Ƿ��뱳��,���������
//ʱ����˷�,�۲�õ���i����Ʒ��������i-1��.ÿһ��ѭ��������һ����Ʒ.���
//����ӵ�n����Ʒ��ʼö����Ϊ���ܷ��뱳������Ʒ,�ڶ�n~(i-1)��Ʒ����01����
//���ù��������Ż�һ����Ʒ�Ϳ�ֻ����һ��,������O(nv)���Ӷ������dp ���ԡ�ǳ̸���౳�����⡷ ��ֺ�
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 2e3;
int dp[maxn],s[50];
int main()
{
    ios::sync_with_stdio(false);
//    freopen("in.txt", "r", stdin);
    int T,cas=1;
    cin>>T;
    while(T--)
    {
        int n,sum=0,v,ans = 0;
        cin>>n>>v;
        s[0] = 0;
        for(int i = 1; i<=n; i++) cin>>s[i];
        sort(s+1,s+1+n);
        for(int i = 1; i<=n; i++)
        {
            memset(dp,0,sizeof(dp));
            sum+=s[i-1];
            dp[sum] = 1;//��ʼ״̬��1~(i-1)����Ʒ��ռ���ݻ�
            //ÿ��i����Ҫ��һ�� (i+1)~n��01���� O(nv)
            //��(i+1)~n��01����,���ۼ��ϱ����sum(1~(i-1)��������Ʒ)
            for(int j = i+1; j<=n; j++)//����ÿ����ö�ٵ���Ʒ�����Ʒ
                for(int k = v-s[j]; k>=sum; k--) dp[k+s[j]]+=dp[k];
            //v-s[i] �������Ѿ�װ�����Ʒ��ռ�ݻ� �����j�����Ҳ��1~i-1ȫ����Ʒ��i+1~n�Ĳ�����Ʒ��ռ�ݻ�
            for(int j = max(1,v-s[i]+1); j<=v; j++) ans+=dp[j];//+1��Ϊ��װ����s[i]
        }
        cout<<cas++<<" "<<ans<<endl;
    }
    return 0;
}
*/

/*
//ժ�Բ���:http://www.cppblog.com/csu-yx-2013/archive/2012/08/30/188748.html
//ac 16ms ���仯����
//�������ⲻ�����ü��仯����ȥ��,���ܻ��,��Ϊ���仯�������������Էֽ�ö��������ı�����������
//��Щ������ı�����������ͨ���ֽ�õ� ���𰸿��ܻ����
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long INT;
INT nAns[40][1010];
INT nValue[100];
INT nSum[100];
INT nN, nM;

INT GetAns(INT nNum, INT nMoney)
{
    if (nAns[nNum][nMoney] == -1)
    {
        if (nNum == 0)
        {
            nAns[nNum][nMoney] = 1;
            if (nMoney == nM)
            {
                nAns[nNum][nMoney] = 0;
            }
        }
        else
        {
            INT nRet = 0;

            if (nMoney - nSum[nNum - 1] >= nValue[nNum])
            {
                nRet = GetAns(nNum - 1, nMoney - nValue[nNum]);
            }
            else
            {
                if (nMoney >= nValue[nNum])
                {
                    nRet += GetAns(nNum - 1, nMoney - nValue[nNum]);
                }
                nRet += GetAns(nNum - 1, nMoney);
            }

            nAns[nNum][nMoney] = nRet;
        }
    }
    return nAns[nNum][nMoney];
}

int main()
{
    INT nT;

    scanf("%I64d", &nT);
    for (INT i = 1; i <= nT; ++i)
    {
        scanf("%I64d%I64d", &nN, &nM);
        for (INT j = 1; j <= nN; ++j)
        {
            scanf("%I64d", &nValue[j]);
        }
        memset(nAns, -1, sizeof(nAns));
        sort(nValue + 1, nValue + nN + 1);
        nSum[0] = 0;
        for (INT j = 1; j <= nN; ++j)
        {
            nSum[j] = nSum[j - 1] + nValue[j];
        }
        printf("%I64d %I64d\n", i, GetAns(nN, nM));
    }

    return 0;
}
*/

/*
ֱ�ӱ���ö������ ģ�� ��̫��ʵ��
ÿ�ζ���Ҫ�ж�ʣ��δ���뱳������С��Ʒ�Ƿ��ܷ��뱳��,���ܷ����ʱ���˵�������ٲ��ܷ�����Ʒ�� Ҳ��TLE
*/
