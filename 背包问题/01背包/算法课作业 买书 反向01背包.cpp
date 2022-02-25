#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;

/*
����:Sheldon��Comic book store����,��������Ƴ�������W��Ԫ����������������T���Ļ.
�������n��ͬ��ͼ��,����ÿ��ͼ��ļ۸�������p[i]��ʾ,��p[i]����.Sheldon���������ظ�����.
��Ϊ������㷨,����������ö���Ǯ�����õ�������������T��.
n<=100,p[i]<=10.
����:�㷨��������ҵ
˼·:ʵ�ʾ����ʹ���n����ʹ�û��Ѳ�С��W��Ԫ����С����,�������ܻ���Ϊsum.
��ôԭ�����ж���ʣ��û���������Ǿ����ܴ�Ļ�����,�������������Կ�����
sum-w��Ǯ�����ܶ������,����ܻ��Ѷ���Ǯ,��ô��ʱʣ�µ�û����Ļ���һ������
��֤��С��W,��ôʣ�����ܻ��Ѿ���sum-dp[sum-W].
*/
int n,w,p[N],dp[M],sum;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        sum+=p[i];
    }
    if(sum<w){//������ȫ�򻨷Ѷ�С��w,�����õ�������������T��
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=sum-w;j>=p[i];j--)
            dp[j]=max(dp[j],dp[j-p[i]]+p[i]);
    }
    printf("%d",sum-dp[sum-w]);
    return 0;
}

/*
//��һ������ ��01����ת�ƹ�����,����������ڵ���W����ʱ��¼��С�Ļ���
//dp[j]=1��ʾ��ǰi���黨��jԪ�Ǵ������
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,w,p[N],dp[M],ans;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]);
    ans=INF;
    dp[0]=1;//ǡ��װ������
    for(int i=1;i<=n;i++){
        for(int j=w;j>=0;j--){//�����½���0,��Ϊ�Ǵ�dp[j]��dp[j+p[i]]ת��,�����ٲ�������,��ʼ״̬��dp[0]
            if(dp[j]){//����һ��״̬ �Ϸ� ������һ��״̬������ ���i����
                if(j+p[i]>=w)//������ѳ���w,���¼����Wʱ����С����
                    ans=min(ans,j+p[i]);
                else//����С��W,������״̬,Ϊ�˵õ���һ״̬
                    dp[j+p[i]]=1;
            }
        }
    }
    if(ans != INF)
        printf("%d",ans);
    else//������Ļ��Ѽ�����Ҳ��WС ���-1 �������õ�������������T��
        printf("-1");
    return 0;
}
*/

/*
Ҳ������������ļ۸��ܺ�Ϊ��������,ǡ��װ������,����ж����������ڵ���wʱ,�����С�ĺϷ�״̬���Ǵ�
*/

/*
��������
input
5 8
2 4 7 9 10

output
9

��Ȼ���ŷ���������2 �֣����ٿ�����9Ԫ������Ʒ������͵�������T��
��һ�֣������1����Ʒ�͵�3����Ʒ��2 +7=9>8
�ڶ��֣�ֱ�ӹ����4����Ʒ9> 8
*/
