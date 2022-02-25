/*
����:һ������ĺ�����һ��n��Сש(5<=n<=500).������Щש�齨���˲�ͬ��¥��.
¥�����ϸ��ս������еĲ�ͬ��С��̨�����.¥�ݲ��þ�����ȴ�С��̨��.
ÿ��¥�����ٰ�������̨��,ÿ��̨�����ٰ���һ��ש��.
����:https://acm.timus.ru/problem.aspx?space=1&num=1017
˼·:01����ͳ��ǡ��װ���ķ�����,nΪ��������,����Ҫע��ÿ��̨��ש��
���������,ÿ��¥��������2��̨��,��ô����ÿ��̨�׵����õ�ש�����Ϳ�
����1~(n-1)
*/
//ac 15ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define M 510
typedef long long ll;//���ֺܴ�int�����
using namespace std;

int n;
ll dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d",&n);
    dp[0]=1;
    //ö��ÿ��̨�����õ�ש����,��Ϊ����Ҫ2��̨�׹��� ����Ͻ粻����n
    //��ÿ��̨�׵�ש�������������,���ÿ�� ̨������ש�������ǵ�����.
    for(int i=1;i<n;i++){
        for(int j=n;j>=i;j--)
            dp[j]+=dp[j-i];
    }
    printf("%lld\n",dp[n]);
    return 0;
}

/*
//ac 15ms ĸ��������
#include<iostream>
using namespace std;
long long int ans[510]={1,1};//�����(1+x)0��1��Ϊ1��(1+x^2),(1+x^3),,,�����

int main(){
    int n;
    cin>>n;
    for(int i=2;i<=n;i++) //��(1+x^2)��ʼ�����
        for(int j=n;j>=0;j--) //���³˽�ȥ������п���ϵ��
            if(i+j<=n)  //n�����ϵ��������
                ans[i+j]+=ans[j];
    cout<<ans[n]-1<<endl;
    return 0;
}
*/
