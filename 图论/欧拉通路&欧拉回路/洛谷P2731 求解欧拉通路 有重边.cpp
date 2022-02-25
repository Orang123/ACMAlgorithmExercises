#include<cstdio>
#include<stack>
#include<algorithm>
#define N 550
using namespace std;
int G[N][N],n,de[N];
stack<int> s;
void dfs(int u){
    for(int i=1;i<=n;i++){//这里默认就是按照字典序,较小的点先遍历
        if(G[u][i]){//u到i点之间是否还有边可走
            G[u][i]--;
            G[i][u]--;
            dfs(i);
        }
    }
    s.push(u);
}
int main(){
    int m,a,b;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&a,&b);
        G[a][b]++;
        G[b][a]++;
        de[a]++;
        de[b]++;
        n=max(n,max(a,b));
    }
    int start=1;//若原图是欧拉回路，则以1点为起点开始遍历
    for(int i=1;i<=n;i++){//求解编号最小的奇点作为起点
        if(de[i]&1){
            start=i;
            break;
        }
    }
    dfs(start);
    int v;
    while(!s.empty()){//出栈 输出欧拉回路
        v=s.top();
        printf("%d\n",v);
        s.pop();
    }
    return 0;
}
