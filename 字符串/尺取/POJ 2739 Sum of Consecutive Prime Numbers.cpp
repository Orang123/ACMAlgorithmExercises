/*
����:ժ������.
����һ��10000���ڵ����֣��ж���������Ƿ�����ɼ������������������磺2,3,5,7...����ӵõ���
���Ҹ�������������м��������Ľ⡣
����:http://poj.org/problem?id=2739
˼·:��ȡ��,�Ƚ�����ɸѡ�����ٽ��г���ĳ�ȡ.
ֻ�ǳ�ȡ�Ľ��������ǵ�ǰ���ܺ�С��n,�������Ҷ˵�����sum����,
����Ͳ������ٳ�����������֮��Ϊn����������(��)��.
*/
//ac 16ms
#include<cstdio>
using namespace std;
int prime[10010];
bool flag[10010];
void prim(){
    for(int i=2;i<5005;i++){
        for(int j=i*2;j<10010;j+=i)
            flag[j]=true;
    }
    for(int i=2,j=0;i<10010;i++){
        if(!flag[i]){
            prime[j++]=i;
        }
    }
}
int main(){
    int n,l,r,sum,ans;
    prim();
    while(scanf("%d",&n)&&n){
        l=r=ans=sum=0;
        while(1){
            if(sum<n && prime[r]>n)
                break;
            while(sum<n)
                sum+=prime[r++];
            if(sum == n)
                ans++;
            sum-=prime[l++];
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 16ms
#include<cstdio>
using namespace std;
int prime[10010];
bool flag[10010];
void prim(){
    for(int i=2;i<5005;i++){
        for(int j=i*2;j<10010;j+=i)
            flag[j]=true;
    }
    for(int i=2,j=0;i<10010;i++){
        if(!flag[i]){
            prime[j++]=i;
        }
    }
}
int main(){
    int n,l,r,sum,ans;
    prim();
    while(scanf("%d",&n)&&n){
        l=r=ans=sum=0;
        while(1){
            if(sum>=n)
                sum-=prime[l++];
            else{
                    if(prime[r]<=n)
                        sum+=prime[r++];
                    else
                        break;
            }
            if(sum==n) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
