/*
题意:某地发行一套彩票。彩票上写有1到M这M个自然数。
彩民可以在这M个数中任意选取N个不同的数打圈。每个
彩民只能买一张彩票，不同的彩民的彩票上的选择不同。
每次抽奖将抽出两个自然数X和Y。如果某人拿到的彩票上，
所选N个自然数的倒数和，恰好等于X/Y，则他将获得一个
纪念品。已知抽奖结果X和Y。现在的问题是，必须准备多少
纪念品，才能保证支付所有获奖者的奖品。

释义:题目就是问1~m个数取n个数有多少种组合的倒数之和等于x/y,
因为题中对于每张彩票每个彩民的选择不同。

1<=X,Y<=100. 1<=N<=10,1<=M<=50.
链接:https://www.luogu.com.cn/problem/P2236
思路:dfs+后缀剪枝.
*/
//ac 3.99s dfs循环线性枚举
#include<cstdio>
#include<cmath>
const double eps=1e-10;
int n,m,vis[60],cnt;
double val,x,y;

void dfs(int st,int num,double sum){
    if(sum>val+eps) return;//剪枝当前和大于sum时 回溯
    //剪枝 当当前和加上后面 把每一位都当成1/st(分母越小值越大) 即(n-num+1)*1.0/st还小于要求值时 回溯返回
    if(sum+(n-num+1)*1.0/st+eps<val) return;//因为有精度差所以左边还要再加上eps
    //剪枝 当当前和加上后面 把每一位都当成1/m(分母越大值越小) 即(n-num+1)*1.0/m大于要求值时 回溯返回
    if(sum+(n-num+1)*1.0/m>val+eps) return;//因为有精度差所以右边还要再加上eps
    if(num == n+1){
        if(fabs(val-sum)<eps) cnt++;//这里sum因为精度原因 可能会比val大
        return;
    }
    if(st == m+1) return;
    for(int i=st;i<=m;i++){//这里需要开O^2才不会TLE
        if(vis[i]) continue;
        vis[i]=1;
        dfs(i+1,num+1,sum+1.0/i);
        vis[i]=0;
    }
}

int main(){
    scanf("%d%d%lf%lf",&n,&m,&x,&y);
    val=x/y;
    dfs(1,1,0);
    printf("%d\n",cnt);
	return 0;
}

/*
//ac 3.59s dfs枚举每个物品取或不取
#include<cstdio>
#include<cmath>
const double eps=1e-10;
int n,m,vis[60],cnt;
double val,x,y,sum[60];

//提前初始化sum 对1~m的倒数前缀和效率会高一点
void dfs(int st,int num,double sum0){
    if(sum0>val+eps) return;
    double maxs=sum0+sum[st+n-num]-sum[st-1];//取当前st后的n-num的各个位倒数之和 为最大值
    double mins=sum0+sum[m]-sum[m-(n-num+1)];//取从m从后往前取n-num的各个位倒数之和 为最小值
    if(maxs+eps<val) return;
    if(mins>val+eps) return;
    if(num == n+1){
        if(fabs(val-sum0)<eps) cnt++;
        return;
    }
    if(st == m+1) return;
    dfs(st+1,num+1,sum0+1.0/st);
    dfs(st+1,num,sum0);
    //for循环需要开O^2优化才能过,否则会TLE
}

int main(){
    scanf("%d%d%lf%lf",&n,&m,&x,&y);
    val=x/y;
    for(int i=1;i<=m;i++)
        sum[i]=sum[i-1]+1.0/i;
    dfs(1,1,0);
    printf("%d\n",cnt);
	return 0;
}
*/
