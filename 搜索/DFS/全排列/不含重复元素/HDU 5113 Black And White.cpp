/*
题意:有一个n*m的网格,有k种颜色,每种颜色有ci瓶,
需要将相邻的网格涂成不同颜色,并且需要将所有颜料用完.
问是否可行.输出染色方案.
0<n,m<=5.0<k<=n*m.
c[1]+c[2]+..c[k]==n*m,所有颜色的个数恰好等于格子数目.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5113
思路:dfs枚举每个格子可能涂的颜色,一个剪枝:当剩余未染色
的格子数目+1的一半小于某种颜色剩余个数时,这种颜色要想
全部涂上去,必然会出现相邻颜色同色,结束.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k,cas,mp[5][5],c[30];
int dfs(int num){
    if(num == n*m) return 1;
    /*
    剪枝,当剩余未染色的格子数目+1的一半小于某种颜色剩余个数时,
    这种颜色要想全部涂上去,必然会出现相邻颜色同色,结束.
    eg:3x3方阵中只染一种色时不相邻时,最多只能染5个格子,4*4方阵用一种颜色最多涂8个格子,
    也就是只用一种颜色,最多有棋盘剩余未染色的一半+1个位置可以涂保证相邻位置不同色.
    */
    for(int i=1;i<=k;i++)
        if((n*m-num+1)/2<c[i]) return 0;
    int x=num/m,y=num%m;
    for(int i=1;i<=k;i++){
        if(!c[i]) continue;
        if(x>0 && i==mp[x-1][y]) continue;//判断上面
        if(y>0 && i==mp[x][y-1]) continue;//判断左面
        c[i]--;
        mp[x][y]=i;
        if(dfs(num+1)) return 1;
        c[i]++;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&c[i]);
        printf("Case #%d:\n",cas);
        if(dfs(0)){
            printf("YES\n");
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(j) printf(" ");
                    printf("%d",mp[i][j]);
                }
                printf("\n");
            }
        }
        else
            printf("NO\n");
    }
    return 0;
}
