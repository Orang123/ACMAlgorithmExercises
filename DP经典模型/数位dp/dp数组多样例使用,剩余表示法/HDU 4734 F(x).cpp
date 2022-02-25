/*
����:ժ������
��һ����A (ʮ���Ʊ�ʾ��ʽΪAnAn-1An-2 ... A2A1�����庯��
F(x) = An * 2^n-1 + An-1 * 2^n-2 + ... + A2 * 2 + A1 * 1��
��һ��B,��B���ڵ�i,����F(i)<=F(A).
A,B<10^9.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4734
˼·:��λdp.ֻ��T<=10^4������,dp����Ҫ�ܹ�����ʹ��,����
ÿ�ζ���ʼ��,���Ҫ��¼ʣ�¿����ۼӵ�ֵ,���ܼ�¼�Ѿ��ۼ�
��ֵ,��Ϊÿ��������A����ͬ.
*/
//ac 15ms ���仯����+��֦
//dp[k][val]��ʾ��λ��len��k-1λ��A��sum��ȥʣ��val���ۼ�(�������������λ�±�)
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ�����㲻��ʹ��ʣ��valС��0����Ŀ
//�ռ临�Ӷ�O(10*20736)=207360
//ʱ�临�Ӷ�O(10*10*20736)=2073600
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736//2568*9*9

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val>=0;
    //���������֦Ӱ��Ҳ����
    if(val<0)//�����ǰʣ��val�Ѿ������ٵ�С��0 ����� ����0������֦,��Ϊ��������λ���ֿ���ȡ0,����������valʹ��С��0
        return 0;
    if(!limit && dp[k][val]!=-1)
        return dp[k][val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val-i*b[k],limit && i == last);//������val��ȥ��ǰλ��ֵ,������ʾ��dp״̬���ܶԶ����������м��仯
    if(!limit)
        dp[k][val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    memset(dp,-1,sizeof(dp));//dp����ֻ��ʼ��һ��
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,sum,1));//��ʼ�ܼ��ٵ�ֵΪsum(A��f(x)�ܺ�)
    }
    return 0;
}

/*
//ac 15ms ���仯��¼ dp[k][sum-val],��Ȼ���ۼ�
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val<=sum;
    if(val>sum)
        return 0;
    if(!limit && dp[k][sum-val]!=-1)
        return dp[k][sum-val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val+i*b[k],limit && i == last);
    if(!limit)
        dp[k][sum-val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,0,1));
    }
    return 0;
}
*/

/*
//TLE
//dp[k][val]��ʾ��λ��len��k-1λȨֵ�ۼӺ�Ϊval(�������������λ�±�)
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ�����㲻��ʹ��val<=sum����Ŀ
//����ֻ�ܶ�һ���������м��仯,��Ϊÿ������A��sumֵ�ǲ�ͬ��,����ֱ��ʹ����һ��������¼��dpֵ
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val<=sum;
    if(val>sum)
        return 0;
    if(!limit && dp[k][val]!=-1)
        return dp[k][val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val+i*b[k],limit && i == last);
    if(!limit)
        dp[k][val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-1,sizeof(dp));
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,0,1));
    }
    return 0;
}
*/
