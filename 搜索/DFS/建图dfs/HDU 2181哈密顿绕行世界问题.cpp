/*
题意:就是20个点 模拟哈密顿回路,输出遍历路径 所有点都遍历一次还能回到起点。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2181
思路:dfs.记录遍历的个数,访问过的点不再访问.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int m,fa[30],vis[30],mp[30][30],cnt;

void printPath(int u){
    if(u!=m) printPath(fa[u]);
    else{
        printf("%d:  %d",cnt,u);
        return;
    }
    printf(" %d",u);
}

void dfs(int u,int num){
    vis[u]=1;
    for(int i=1;i<=20;i++){
        if(!mp[u][i]) continue;
        if(i == m && num!=20) continue;//起始点若不是在所有点都遍历完了 就不要访问
        if(vis[i] && i!=m) continue;//遍历过的点除了起始点 都不遍历
        if(i == m){//回到了起始点 打印路径
            cnt++;
            printPath(u);
            printf(" %d",i);
            printf("\n");
            break;
        }
        fa[i]=u;//记录父节点
        dfs(i,num+1);
    }
    vis[u]=0;
}

int main(){
    int a,b,c;
    for(int i=1;i<=20;i++){
        scanf("%d%d%d",&a,&b,&c);
        mp[i][a]=mp[i][b]=mp[i][c]=1;
        mp[a][i]=mp[b][i]=mp[c][i]=1;
    }
    while(scanf("%d",&m) && m){
        cnt=0;
        dfs(m,1);
    }
    return 0;
}
