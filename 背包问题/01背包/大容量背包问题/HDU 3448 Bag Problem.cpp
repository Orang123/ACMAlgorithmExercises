#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
using namespace std;
//ac 0ms 大容量指定物品个数上限的01背包转化为暴力枚举搜索
/*
题意:k个物品,每个物品有对应重量,背包最大承重为m,
求最多装n个物品的最大重量.
k<=40,m<=10^9.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3448
思路:这个问题对应的背包模型是HDU 3496的装入背包指定物品
个数获得的最大价值,但是因为本题并不是指定一定要装入n个物品,
可以小于n个,只是要重量最大化,所以还不能用HDU 3496那个二维01
背包的模型去做,因为背包容量最大可达10^9,dp数组无法开,
会MLE,但n<=40,可暴力枚举搜索.注意一个剪枝点,贪心先将所有物品
降序排序,如果前n大的物品重量和不超过背包容量,则这前n个
最大的物品都能装入背包,直接输出这个值即可.

疑惑:这个题后缀重量和剪枝,会wa.不知何原因.
*/
int n,k,m,w[N],ans,sufxw[N],sum;

void dfs(int i,int num,int sum){
    if(sum>m) return;
    //if(sum+sufxw[i]<ans)//后缀剪枝 会wa
        //return;
    if(sum>ans)
        ans=sum;
    if(num == n || i == k+1)
        return;
    dfs(i+1,num+1,sum+w[i]);
    dfs(i+1,num,sum);
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        sum=ans=0;
        scanf("%d",&k);
        sufxw[k+1]=0;
        for(int i=1;i<=k;i++)
            scanf("%d",&w[i]);
        sort(w+1,w+1+k,greater<int>());
        for(int i=1;i<=n;i++)
            sum+=w[i];
        if(sum<=m){//前n大的物品重量和小于背包容量,直接输出.
            printf("%d\n",sum);
            continue;
        }
        for(int i=k;i>=1;i--)
            sufxw[i]+=sufxw[i+1]+w[i];
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
