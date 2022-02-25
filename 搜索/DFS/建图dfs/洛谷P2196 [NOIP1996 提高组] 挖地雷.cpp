/*
题意:在一个地图上有n个地窖(n≤20)，每个地窖中埋有一定数量的地雷。
同时，给出地窖之间的连接路径。当地窖及其连接的数据给出之后，
某人可以从任一处开始挖地雷，然后可以沿着指出的连接往下挖（仅能选择一条路径），
当无连接时挖地雷工作结束。设计一个挖地雷的方案，使某人能挖到最多的地雷。
注意:给出的连接是单向连接.
链接:https://www.luogu.com.cn/problem/P2196
思路:暴力枚举每个点作为起点 进行dfs.
*/
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n,a[30],vis[30],cnt,ans=-1,b[30],c[30],num;
vector<int> edge[30];

void dfs(int u,int k,int sum){
    int flag=1;
    b[k]=u;
    vis[u]=1;
    //直接在这里记录最大的sum
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        flag&=vis[v];
        if(!vis[v])
            dfs(v,k+1,sum+a[v]);
    }
    if(flag){
        if(sum>ans){
            ans=sum;
            for(int i=1;i<=k;i++)
                c[i]=b[i];
            num=k;
        }
    }
    vis[u]=0;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int tmp;
    for(int i=n-1;i>=1;i--){//i=1..n-1
        for(int j=i-1;j>=0;j--){//j=i+1
            scanf("%d",&tmp);
            if(tmp)
                edge[n-i].push_back(n-j);//给出的是单向连接
        }
    }
    for(int i=1;i<=n;i++)
        dfs(i,1,a[i]);
    printf("%d",c[1]);
    for(int i=2;i<=num;i++)
        printf(" %d",c[i]);
    printf("\n");
    printf("%d\n",ans);
    return 0;
}
