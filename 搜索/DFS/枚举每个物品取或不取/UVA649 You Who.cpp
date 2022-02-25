/*
����:ժ������
����n���ˣ�ÿ�������Լ���ʶ��һЩ�ˣ�����Ҫ����Щ�˷ֳ����ѣ�
�����˵�������ܴ���1��ÿ��ʱ�̣�һ���˿�����ʶ��һ���ˣ�
���ǲ����໥�ģ��������㴫����:a��ʶb,b��ʶc������a������ʶc��
������a�õ�һ��ʱ��ȥ��ʶb����b�����õ�һ��ʱ��ȥ��ʶc��
���������Ҫ���������ˣ�Ҫ���������л�����ʶ�����Һ�ʱ��С��
n<=24.
����:https://www.luogu.com.cn/problem/UVA649
˼·:��������һ�ѵ���������,ÿ���˶���ѡ�Ͳ�ѡ���ֿ���,
��Ϊn<=24���Կ�����λ���������״ѹ��ʾѡȡ��״̬.����ÿһ��ѡȡ
��״̬Ҫͳ�Ƴ�ÿһ���е�i����,��������i��ʶ������ ��Ҫ�໨��ʱ��
��ʶ����,��ȡ�����ֵ,���������˻�����ʶ����С��ʱ.

����λ�����ʾѡȡ����״̬Ҳ�ǿ��Ե�,ֻ������.
*/
//ac 380ms dfs����+λ����״ѹ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],ans,staAns;

int bitCount(int x){
    return x == 0?0:bitCount(x>>1)+(x&1);
}

int calTime(int sta){
    int s1Num=bitCount(sta);//��һ��ѡ������
    int s2=(1<<n)-1 ^ sta;//�ڶ��ѵ�״̬
    int s2Num=bitCount(s2);//�ڶ��ѵ�����
    int res=0;
    for(int i=0;i<n;i++){
        if(sta & 1<<i)//��һ��ѡ�˵�i����
            //ע��a[i]�п��ܰ����ڶ��ѵ���,���Ҫsta & a[i]
            res=max(res,s1Num-bitCount(sta & a[i]));//�����һ���г��˵�i���˳�����ʶ������,����Ҫ����ʱ����ʶ����
        if(s2 & 1<<i)
            res=max(res,s2Num-bitCount(s2 & a[i]));
        if(res>=ans)//���������֦ 2.78s ����380ms
            return res;
    }
    return res;
}

void dfs(int k,int num,int sta){
    if(num>(n+1)/2 || k-num>(n+1)/2)//��ѡ�Ķ��� ��������1ʱ ����
        return;
    if(k == n){
        int res=calTime(sta);
        if(res<ans){
            ans=res;
            staAns=sta;
        }
        return;
    }
    dfs(k+1,num+1,sta|1<<k);
    dfs(k+1,num,sta);
}

void print(){
    printf("%d\n",ans);
    int s1Num=bitCount(staAns);
    printf("%d",s1Num);
    for(int i=0;i<n;i++){
        if(staAns & 1<<i)
            printf(" %d",i+1);
    }
    printf("\n%d",n-s1Num);
    for(int i=0;i<n;i++){
        if(!(staAns & 1<<i))
            printf(" %d",i+1);
    }
    printf("\n");
}

int main(){
    int num,tp,x,flag=0;
    while(scanf("%d",&n)!=EOF){
        if(flag)
            printf("\n");
        memset(a,0,sizeof(a));
        ans=INF;
        for(int i=0;i<n;i++){
            scanf("%d%d",&tp,&num);
            a[i]|=1<<i;
            while(num--){
                scanf("%d",&x);
                x--;
                a[i]|=1<<x;
            }
        }
        dfs(0,0,0);
        print();
        flag=1;
    }
    return 0;
}
