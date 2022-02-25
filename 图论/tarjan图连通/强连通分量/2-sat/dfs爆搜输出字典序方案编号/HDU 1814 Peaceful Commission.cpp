#include<iostream>
#include<stdio.h>
#include<math.h>
#include <string>
#include<string.h>
#include<map>
#include<queue>
#include<set>
#include<utility>
#include<vector>
#include<algorithm>
#include<stdlib.h>
using namespace std;
#define eps 1e-8
#define inf 0x3f3f3f3f
#define rd(x) scanf("%d",&x)
#define rd2(x,y) scanf("%d%d",&x,&y)
#define ll long long int
#define mod 1000000007
#define maxn 20000
#define maxm 20000
/*
题意:给1~n*2个人,两两为一组,每组选一人,
求在满足m个限制条件的情况下输出字典序最小的数列.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1814
思路:典型的2-sat问题,因为是字典序最小问题,暴力解决便可;
若是判断能否存在,则用判断强连通分量的方法判断.
只有dfs 爆搜能完成字典序输出这种方案
*/

vector<int> f[maxn];
int col[maxn];
int ans[maxn],cnt;
int n,m,x,y;
const int R=1;
const int B=2;
const int W=0;
//只有dfs 爆搜能完成字典序输出这种方案
bool dfs(int x){
    if(col[x]==R) return true;
    if(col[x]==B) return false;
    col[x]=R;
    col[x^1]=B;
    ans[cnt++]=x;
    for(int i=0;i<f[x].size();i++)
        if(!dfs(f[x][i])) return false;
    return true;
}
bool solve(){
    memset(col,0,sizeof(col));
    for(int i=0;i<n;i+=2)
    {
        if(col[i]) continue;
        cnt=0;
        if(!dfs(i)){//先尝试该组字典序小的，不存在解再试大的
            for(int j=0;j<cnt;j++)
                col[ans[j]]=W,col[ans[j]^1]=W;
            if(!dfs(i^1)) return false;
        }
    }
    return true;
}
int main()
{
    while(~rd2(n,m)){
        n*=2;
        for(int i=0;i<n;i++) f[i].clear();
        for(int i=1;i<=m;i++)
        {
            //输入的是点的编号,范围1~2n,并不是对数的编号,所以不必转换2i+1或i+n
            //但要注意x^1,这种点的编号一定只能从0开始,所以x--,y--.
            rd2(x,y);
            x--;y--;
            f[x].push_back(y^1);//保存对应的限制条件
            f[y].push_back(x^1);
        }
        if(solve()){
            for(int i=0;i<n;i+=2)
                if(col[i]==R) printf("%d\n",i+1);
            else printf("%d\n",(i^1)+1);
        }
        else printf("NIE\n");
    }
    return 0;
}
