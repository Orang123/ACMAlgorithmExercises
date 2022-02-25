/*
题意:n个点的一颗树，每一个点代表一个字符，给你一个字符串S，
问你能否有一个A,B，使得A->B的最短路径是该字符串S表示的。
n,|s|<=10^4.
注意:不同点的字母有可能相同.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5469
思路:树形dp.枚举每个点字母和字符串第一个字母s[1]相等的点,
开始dfs搜索子树分支匹配字符.有一个剪枝.
可以预处理出以1位根节点的每个点的最长分支的儿子个数即最深深度,
当搜索匹配到当前字符串的st位时,如果剩下未匹配的字符比当前节点v的
最长的分支儿子数还多,则匹配肯定不成功无需再搜索当前分支.但要注意
这个剪枝应用的条件在预处理中u的父节点不能是v,否则v的最大分支深度
是朝着当前搜素的祖先节点的方向.
*/
//ac 780ms 树形dp
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
using namespace std;

int n,cnt,head[N],len,dep[N],fa[N];
char C[N],S[N];
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//记录这v点的子树中最长的路径长度
void dfs1(int u,int fath){
    dep[u]=1;
    fa[u]=fath;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fath) continue;
        dfs1(v,u);
        if(dep[v]+1>dep[u]) dep[u]=dep[v]+1;
    }
}
//按照S字符串的出现的字母顺序对应的点去搜索
int dfs2(int u,int fath,int st){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //记录遍历的条件必须是该点代表的字符和S字符串顺序中相等
        if(v == fath || C[v]!=S[st+1]) continue;
        /*
        因为dfs1中记录的结点的子树最大深度是以1结点作为根节点的,
        而每次dfs2根节点不一定满足是以1为根节点的,所以在剪枝之前
        要判断v不是u结点的父亲,否则dep[v]就代表v点之前已经遍历的
        最大深度了,而不是未遍历的.如果S中未比对的字符数比v结点开始的子树最大深度还大,
        则不可能找到路径,剪枝.
        */
        if(v!=fa[u] && len-st>dep[v]) continue;
        if(st+1 == len)
            return 1;
        if(dfs2(v,u,st+1)) return 1;//只要发现一条相等的最短路径就结束
    }
    return 0;
}

int main(){
    int T,a,b,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;//前向星数组下标要初始化0,否则会数组越界异常,个别值记录错误没有-1标志,导致dfs无法正常结束,Runtime Error(STACK_OVERFLOW)
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        //memset是按1字节(8 bit)赋值的,只有0和-1有效因为对应的8bit是0(00000000) -1(11111111) 扩展成32位后还是0和-1的32位补码
        scanf("%s",C+1);
        scanf("%s",S+1);
        len=strlen(S+1);
        dfs1(1,0);
        int flag=0;
        /*
        字符串最多有10^4个,而字母只有26个,所以不同点代表的字母可能相同,
        S字符串中也会有重复序列,所以要点所代表的字符为S[1]的点开始遍历,
        只要发现一条路径就结束.
        */
        for(int i=1;i<=n;i++){
            if(C[i] == S[1]){
                if(dfs2(i,0,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) printf("Case #%d: Find\n",cas);
        else printf("Case #%d: Impossible\n",cas);
    }
    return 0;
}
/*u不是v父亲也能剪枝,共2种剪枝
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
using namespace std;
int n,cnt,head[N],len,dep[N],fa[N];
char C[N],S[N];
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs1(int u,int fath){
    dep[u]=1;
    fa[u]=fath;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fath) continue;
        dfs1(v,u);
        if(dep[v]+1>dep[u]) dep[u]=dep[v]+1;
    }
}

int dfs2(int u,int fath,int st){
    if(st == len) return 1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fath || C[v]!=S[st+1]) continue;
        if(fa[v] == u && len-st<=dep[v]){
            if(dfs2(v,u,st+1)) return 1;
        }
        //n-dep[v]将未遍历的v结点也包括进去了,+1是加上v结点,
        //n-dep[v]+1代表v结点总结点减去已经遍历过的子树中的最大深度,
        //剩下为遍历的所有子树的结点数,当然这个剪枝实际作用并不怎么大.
        else if(fa[v]!=u && len-st<=n-dep[v]+1){
            if(dfs2(v,u,st+1)) return 1;
        }
    }
    return 0;
}

int main(){
    int T,a,b,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        //memset是按1字节(8 bit)赋值的,只有0和-1有效因为对应的8bit是0(00000000) -1(11111111) 扩展成32位后还是0和-1的32位补码
        scanf("%s",C+1);
        scanf("%s",S+1);
        len=strlen(S+1);
        dfs1(1,0);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(C[i] == S[1]){
                if(dfs2(i,0,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) printf("Case #%d: Find\n",cas);
        else printf("Case #%d: Impossible\n",cas);
    }
    return 0;
}
*/
