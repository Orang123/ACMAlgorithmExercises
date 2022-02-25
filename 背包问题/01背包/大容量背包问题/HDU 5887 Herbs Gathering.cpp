#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//ac 109ms 贪心排序+暴力+剪枝
/*
题意:n个物品,时间限制m,给出每个物品的价值和时间,求在m限制内,最多的价值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5887
思路:
该题实际就是大容量的01背包问题,但因为总时间最大有10^9,而价值最大也有10^9,
所以也无法将价值和背包容量调换求解得到相同价值时最小时间 逆序判定最大价值.
所以只好贪心排序+dfs暴力搜索+后缀剪枝
在n m都较小时,暴力和01背包都能解决此问题,但是01背包效率明显比暴力要快.
当n较大m较小时,暴力基本会超时,而01背包依旧很高.
因为时间和得分 都较大,所以也不好用标记数组记录最优解进行剪枝
*/
int n,m;
ll all[120],ans;
struct Node{
    int cost,score;
    bool operator <(const Node &x)const{
        /*
        这里需要按照时间消耗从大到小排序,根据输入样例,花费时间较多的,基本得分也较多,
        这样dfs时会首先选取得分较多的物品,那么后续的dfs回溯暴力,
        根据sum+all[num]<ans return也可以避免无意义的搜索.这题直接根据得分降序排列会超时,不太懂...
        总之这个贪心预处理排序也很玄学吧,一般物品的体积和价值可能是没有直接排序的,之间按照体积或
        价值排序,剪枝的效率也不会高.
        */
        return cost>x.cost;
    }
}node[120];

//109ms 效率较高 不懂
void dfs(int num,int time,ll sum){
    if(sum>ans) ans=sum;
    if(sum+all[num]<ans) return;//当当前选择的物品总得分加上后续所有的得分还小于之前搜索得到的最大得分时,剪枝,结束搜索.
    if(num == n+1) return;
    if(node[num].cost<=time)
        dfs(num+1,time-node[num].cost,sum+node[num].score);
    dfs(num+1,time,sum);
}

/*//592ms
貌似对于这种组合非排列性质(不需要vis标记)的dfs循环的方式会比较耗时.
可能是循环结构吧,要说起来下面这种dfs调用次数较少,开的栈也越少.
void dfs(int st,int time,ll sum){
    if(sum+all[st]<ans) return;
    if(sum>ans)
        ans=sum;
    for(int i=st;i<=n;i++){
        if(node[i].cost<=time)
            dfs(i+1,time-node[i].cost,sum+node[i].score);
    }
}
*/

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(all,0,sizeof(all));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].cost,&node[i].score);
        sort(node+1,node+1+n);
        for(int i=n;i>=1;i--)//计算后缀和
            all[i]=all[i+1]+node[i].score;
        ans=-1;
        dfs(1,m,0);
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 15ms 按照得分*时间的积从大到小来排序 比较强的剪枝
https://www.cnblogs.com/TnT2333333/p/7695729.html 0ms val/ti排序剪枝
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
const int N = 108;

struct data{
    LL w, val;
    bool operator<(const data &tp)const{
        return val * tp.w > tp.val * w;
    }
}pk[N];

int n;
LL lim,ans;

void dfs(int d, LL w, LL val){
    if(val > ans) ans =  val;
    if(d >= n) return;
    //这里是如果当前价值+假设后续所有物品都是当前第d个物品的价值 还不大于之前最优价值 就剪枝
    //就是lim-w是还剩下多少时间(lim - w)/(LD)pk[d].w 是还能选几个第d个物品 后面d个物品都假定为第d个物品的时间、价值
    //因为按照时间和价值乘积排序,当前第d个 在时间和价值因素的平衡因素上来讲 一定是最划算的,所以后面物品都按照最理想情况都当做第d个物品
    if(val + (LD)pk[d].val / (LD)pk[d].w * (lim - w)<= ans) return;
    if(w + pk[d].w <= lim) dfs(d + 1, w + pk[d].w, val + pk[d].val);
    dfs(d + 1, w, val);

}

int main(){
    while(~scanf("%d %I64d", &n, &lim)){
        for(int i = 0; i < n; i++) scanf("%I64d %I64d", &pk[i].w, &pk[i].val);
        sort(pk, pk + n);
        ans = 0;
        dfs(0, 0, 0);
        printf("%I64d\n", ans);
    }
    return 0;
}
*/

