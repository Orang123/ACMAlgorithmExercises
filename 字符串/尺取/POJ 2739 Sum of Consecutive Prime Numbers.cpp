/*
题意:摘自网上.
给定一个10000以内的数字，判断这个数字是否可以由几个连续的素数（例如：2,3,5,7...）相加得到，
并且给出这个数可以有几组这样的解。
链接:http://poj.org/problem?id=2739
思路:尺取法,先将素数筛选出来再进行常规的尺取.
只是尺取的结束条件是当前的总和小于n,并且最右端的数比sum还大,
后面就不可能再出现连续素数之和为n的连续序列(串)了.
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
