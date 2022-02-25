/*
����:��n������,ÿ�������м�ֵval[i]�����Ӷ�w[i],
�����ܸ��Ӷ�v���������ܹ���õ�����ֵ.
n<=10^5,v<=10^4.
0<=val[i],w[i]<=10.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3732
˼·:��Ŀ�Ǹ�01��������,���Ǹ��Ӷ�O(nv)=10^9,��Ȼ1s
ʱ�޻�TLE,����ÿ�����ʵļ�ֵ�͸��Ӷ���[0,10]֮��,��
�������Χ�¸��ݳ˷�ԭ��������10*10=100�ֲ���ͬ�ĵ���,
��������Ŀ�����������10^5������,Ҳ����˵���кܶ൥��
������ͬ����ĵ���,����ͬ���͵ĵ��ʵ���ͬһ�ֵ��ʶԴ�
��¼���ֵ��ʵ���Ŀ,�����ת�����˶��ر���.������100
�ֵ���,�����ʵ���Ŀ��Ȼ��10^5��,���Ǽ�������,10^5������
����ͬһ�ֵ���,���Ӷ�Ϊ=log(10^5)*10^4=1.7*10^5,����
���ӶȾ��ܽ���,1sʱ�޾Ϳ���.���Ը��ݵ��ʵļ�ֵ�͸��Ӷ�
�����Ƿ�Ϊͬһ�ֵ���.
*/
//ac 249ms 01����ת��Ϊ ���ر���+��ȫ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//kds[i][j]�����ʸ��Ӷ�Ϊi,��ֵΪj���������͵��ʵ���Ŀ
int n,v,kds[N][N],dp[M];

int main(){
    int w,val;
    char str[12];
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(kds,0,sizeof(kds));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%s%d%d",str,&val,&w);
            kds[w][val]++;//��i�����ʶ�Ӧ�ĵ��������е�����Ŀ+1
        }
        int tw,tv;
        for(w=0;w<N;w++){
            for(val=0;val<N;val++){
                if(!kds[w][val]) continue;
                if(v-kds[w][val]*w<w){//��������ȫ�����ж�����
                    for(int j=w;j<=v;j++)
                        dp[j]=max(dp[j],dp[j-w]+val);
                }
                else{
                    for(int k=1;kds[w][val]>0;k<<=1){
                        kds[w][val]-=k;
                        if(kds[w][val]<0)
                            k+=kds[w][val];
                        tw=k*w;
                        tv=k*val;
                        for(int j=v;j>=tw;j--)
                            dp[j]=max(dp[j],dp[j-tw]+tv);
                    }
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
