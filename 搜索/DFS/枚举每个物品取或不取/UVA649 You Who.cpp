/*
题意:摘自网上
给出n个人，每个人有自己认识的一些人，现在要将这些人分成两堆，
两堆人的人数差不能大于1。每个时刻，一个人可以认识另一个人，
但是不是相互的，即不满足传递性:a认识b,b认识c，但是a并不认识c，
即可能a用第一个时刻去认识b，而b可能用第一个时刻去认识c。
你的任务是要分配所有人，要求两堆人中互相认识，并且耗时最小。
n<=24.
链接:https://www.luogu.com.cn/problem/UVA649
思路:可以求解出一堆的人组成情况,每个人都有选和不选两种可能,
因为n<=24所以可以用位运算二进制状压表示选取的状态.对于每一次选取
的状态要统计出每一堆中第i个人,除过本身i认识的人外 还要多花的时间
认识的人,求取出最大值,便是两堆人互相认识的最小耗时.

不用位运算表示选取集合状态也是可以的,只是慢点.
*/
//ac 380ms dfs回溯+位运算状压
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
    int s1Num=bitCount(sta);//第一堆选的人数
    int s2=(1<<n)-1 ^ sta;//第二堆的状态
    int s2Num=bitCount(s2);//第二堆的人数
    int res=0;
    for(int i=0;i<n;i++){
        if(sta & 1<<i)//第一堆选了第i个人
            //注意a[i]有可能包含第二堆的人,因此要sta & a[i]
            res=max(res,s1Num-bitCount(sta & a[i]));//计算第一堆中除了第i个人除了认识的人外,还需要花费时间认识的人
        if(s2 & 1<<i)
            res=max(res,s2Num-bitCount(s2 & a[i]));
        if(res>=ans)//不加这个剪枝 2.78s 加上380ms
            return res;
    }
    return res;
}

void dfs(int k,int num,int sta){
    if(num>(n+1)/2 || k-num>(n+1)/2)//已选的堆中 人数相差超过1时 返回
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
