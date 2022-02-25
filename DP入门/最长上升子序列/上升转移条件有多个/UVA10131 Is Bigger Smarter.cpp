/*
题意:摘自网上
求n个大象从重量递增且智商递减的序列的最长,并打印最长序列
n<=1000(实际n要开到1200).
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1072
思路:LIS,O(n^2)算法,转移条件应是,重量增大,智商减少.
没太搞懂这题为啥要先按重量增加预处理一遍,然后输出方案 还是按照原先的编号输出方案.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1200//开到1200才能过,1100会wa
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
    sort(a+1,a+1+n);//要先预处理按重量增大排序才能过
    ans=0;
    memset(pre,-1,sizeof(pre));
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            //转移条件应是,重量增大,智商减少.
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
