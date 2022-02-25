/*
����:ժ������
��x-y������������������������ĸ����������ǡ�õ���k�������b��������֮��
����:��x--y������ת��Ϊ b ���� 1 �ĸ���Ϊ k �����ĳ��ִ�����
x,y<=2^31-1.
����:https://vjudge.net/problem/URAL-1057
˼·:��λdp.
dp[k][num]��ʾ��λ��len��k-1λ��λ(�������������λ�±�)ʣ��num�������ܹ�����BΪ�׵��ݴ�K����
�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ǡ�ù���k�����ĸ���.
Ϊ��dpֻ��ʼ��һ��,ʹ�ö�����,num��ʾ��һ����ʣ��ĸ���,��Ϊÿ������kֵ�ǲ�ͬ��.
*/
//ac 1ms ���仯����
//dp[k][num]��ʾ��λ��len��k-1λ��λ(�������������λ�±�)ʣ��num�������ܹ�����BΪ�׵��ݴ�K����
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ǡ�ù���k�����ĸ���.
#include<cstdio>
#include<cstring>
#define N 33

int len,a[N];
int X,Y,B,K,dp[N][N];

int dfs(int k,int num,int limit){
    if(!k)
        return num == 0;
    if(num<0)
        return 0;
    if(!limit && dp[k][num]!=-1)
        return dp[k][num];
    int last=limit?a[k]:B-1;
    int ans=0;
    //����ֻ�ж�B����������1�ĸ���,ʵ��ֻ����ȡ01 ���Զ��ڲ�ͬ���� ��ȻB���Ʋ�ͬ,��i���Ҳֻȡ��1,���dpֵ�����������Թ���
    for(int i=0;i<=last && i<=1;i++)
        ans+=dfs(k-1,num-i,limit && i == last);
    if(!limit)
        dp[k][num]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%B;
        val/=B;
    }
    return dfs(len,K,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&X,&Y);
    scanf("%d%d",&K,&B);
    printf("%d",solve(Y)-solve(X-1));
    return 0;
}
