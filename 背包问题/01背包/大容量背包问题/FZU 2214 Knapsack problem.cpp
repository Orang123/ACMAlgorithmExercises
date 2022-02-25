#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 01���� ǡ��װ������ �����ݻ��ͼ�ֵ���������������ֵ
//FZUOJ ��������һֱQueuing...
/*
����:n(n<=500)����Ʒ,ÿ����Ʒ��һ�����w[i](w[i]<=10^9)
�ͼ�ֵval[i],�����б�������Ϊv(v<=10^9)�ı���,���ڱ�����
��v�������������װ����Ʒ������ֵ��,����������ֵ��.
val[1]+val[2]+...+val[n]<=5000.
����:http://acm.fzu.edu.cn/problem.php?pid=2214
˼·:��Ȼ��01��������,ֻ�Ǳ�������v���ɴ�10^9,����ռ�dp����
�޷�������,��˿�������˼ά,��ö�Ӧ��ֵ����С���ݻ�,��dp[i]��ʾ
�ܼ�ֵΪi����С�ݻ��Ƕ���,��dp[j]=min(dp[j],dp[j-val[i]]+w[i]);
����sum(��Ʒ�ܼ�ֵ��ʼ�ж�)��ʼ,�ҵ���һ��С�ڵ���v(����)��v����.
*/
int n,v,w[N],val[N],dp[M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&w[i],&val[i]);
            sum+=val[i];//����ֵ�ܺ���Ϊ �����ݻ�
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=val[i];j--)
                dp[j]=min(dp[j],dp[j-val[i]]+w[i]);
        }
        for(int i=sum;i>=0;i--){//���� �ж�dp[i],��ֵi�����dp[i]�Ƿ�Ϸ�,�������ֵi
            if(dp[i]<=v){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
