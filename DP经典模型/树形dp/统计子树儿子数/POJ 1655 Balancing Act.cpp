#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
/*
题意:一棵树，找到一个点,其所有的子树中最大的子树节点最少。实际就是找树的重心.
链接:http://poj.org/problem?id=1655
dp[u]代表以u为根节点的子树的儿子数
*/

vector <int> map[20005];
int dp[20005],N,min_n,min_bal;
bool visit[20005];
void dfs(int root){
    int son,balance=-1;
    for(int i=0;i<map[root].size();i++){
        son=map[root][i];
        if(!visit[son]){
            visit[son]=true;
            dfs(son);//按照深度优先的原则优先删除叶子节点计算其平衡的值
            dp[root]+=dp[son]+1;//以root为根的所有子树的节点累加和,为下面计算root以前的父节点而做准备
            balance=max(balance,dp[son]+1);//求出以root为根节点的子树中节点数最大那个子树的平衡
        }
    }
    balance=max(balance,N-dp[root]-1);//在子树最大和之前父节点中选择较大的作为root的平衡
    if(balance<min_bal||(balance==min_bal&&root<min_n)){//求出最小的平衡,在平衡相等的情况下选择节点编号较小的
        min_n=root;
        min_bal=balance;
    }
}
int main(){
    int t,a,b;
    scanf("%d",&t);
    while(t--){
        memset(dp,0,sizeof(dp));
        memset(visit,false,sizeof(visit));
        min_bal=INF;
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            map[i].clear();
        for(int i=1;i<=N-1;i++){
            scanf("%d%d",&a,&b);
            map[a].push_back(b);//建立无向树,为了能将整棵树的每个节点都深度遍历到，但是又为了避免无线深度递归，需设置visit标记
            map[b].push_back(a);
        }
        visit[1]=true;//这里从哪个节点开始搜索都是可以的，但是不知到底有几个节点，这里选择从节点1开始遍历
        dfs(1);
        printf("%d %d\n",min_n,min_bal);
    }
    return 0;
}
