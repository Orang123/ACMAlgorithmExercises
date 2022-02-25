/*
����:ժ������
��n��������������������̵ݼ������е��,����ӡ�����
n<=1000(ʵ��nҪ����1200).
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1072
˼·:LIS,O(n^2)�㷨,ת������Ӧ��,��������,���̼���.
û̫�㶮����ΪɶҪ�Ȱ���������Ԥ����һ��,Ȼ��������� ���ǰ���ԭ�ȵı���������.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1200//����1200���ܹ�,1100��wa
using namespace std;

int n,dp[N],pre[N],ed,ans;
struct Ele{
    int w,p,id;
    Ele(int w=0,int p=0,int id=0):w(w),p(p),id(id){}
    bool operator < (const Ele &x)const{
        return w<x.w;
    }
}a[N];

void print(int i){
    if(i == -1)
        return;
    print(pre[i]);
    printf("%d\n",a[i].id);
}

int main(){
    int w,q;
    while(scanf("%d%d",&w,&q)!=EOF){
        ++n;
        a[n]=Ele(w,q,n);
    }
    sort(a+1,a+1+n);//Ҫ��Ԥ������������������ܹ�
    ans=0;
    memset(pre,-1,sizeof(pre));
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            //ת������Ӧ��,��������,���̼���.
            if(a[i].w>a[j].w && a[i].p<a[j].p && dp[i]<dp[j]+1){
                dp[i]=dp[j]+1;
                pre[i]=j;
            }
        }
        if(ans<dp[i]){
            ans=dp[i];
            ed=i;
        }
    }
    printf("%d\n",ans);
    print(ed);
    return 0;
}
