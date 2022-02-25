/*
题意:
给出一块长为x,宽为y的矩形巧克力，每次操作可以沿一条直线把一块巧克力
切割成两块长宽均为整数的巧克力（一次不能同时切割多块巧克力）。
问:是否可以经过若干次操作得到n块面积分别为 a1, a2,...,an的巧克力。
n<=15.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3540
思路:n只有15,状压dp.需要用到二进制枚举集合状态的子集.
需要考虑将初始的r*c的矩形分割,如果最终能分割成a[1..n]中的任意一块,则这种分割就是可行的.
而且再分割过程中必然存在重复的状态,存在重叠子问题.
sum[s]表示当前所拼成巧克力的状态为s实际的面积.
dp[x][s]=0/1表示矩形巧克力拼成的状态为s,最短边为x这个状态是否合法.
*/
//ac 230ms 记忆化搜索
//复杂度(32768*100=3276800)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
using namespace std;

int n,r,c,a[N],sum[1<<N],dp[M][1<<N];

int bitcount(int val){
    return val == 0?0:bitcount(val>>1)+(val&1);
}

int dfs(int x,int s){
    if(dp[x][s] != -1)
        return dp[x][s];
    if(bitcount(s) == 1)//初始状态为 当前矩形巧克力只由a[1..n]中的任一个构成,则说明当前这种拆分是合法的
        return dp[x][s]=1;
    int y=sum[s]/x;//当前矩形巧克力的宽
    //枚举s集合的子集,即:枚举当前巧克力的拆分方案的集合
    //每次s0-1,s0-1 里的二进制位的1有可能是s中没有的,因此需要与s按位与,这样本身没有的1,绝对不会有,就生成了s的子集
    //注意初始状态也是需要按位与s,s0=(s-1)&s,s等于(n<<1)-1时,即所有位都是1,此时不按位与s也是s的子集
    for(int s0=(s-1)&s;s0;s0=(s0-1)&s){
        //沿着长x切割,sum[s0]%x==0表示合法
        //dfs(min(x,sum[s0]/x),s0)表示分割成的第一部分,面积为s0,为了表示唯一的dp[x][s]的状态,边取最小的min(x,sum[s0]/x)
        //dfs(min(x,sum[s0^s]/x),s0^s)表示分割成的第二部分,面积为s-s0=s0^s.
        if(!(sum[s0]%x) && dfs(min(x,sum[s0]/x),s0) && dfs(min(x,sum[s0^s]/x),s0^s))
            return dp[x][s]=1;
        //沿着宽y切割,sum[s0]%y==0表示合法
        if(!(sum[s0]%y) && dfs(min(y,sum[s0]/y),s0) && dfs(min(y,sum[s0^s]/y),s0^s))
            return dp[x][s]=1;
    }
    return dp[x][s]=0;//上面s的子集都不合法,则dp[x][s]不合法.
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        memset(sum,0,sizeof(sum));
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&r,&c);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(i & 1<<j)
                    sum[i]+=a[j];
            }
        }
        if(sum[(1<<n)-1]!=r*c)//n个巧克力拼成的面积必须刚好构成初始r*c的矩形
            printf("Case %d: No\n",cas);
        else{
            if(dfs(r,(1<<n)-1))
                printf("Case %d: Yes\n",cas);
            else
                printf("Case %d: No\n",cas);
        }
    }
    return 0;
}
