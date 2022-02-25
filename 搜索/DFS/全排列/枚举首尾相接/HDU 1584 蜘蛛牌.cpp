/*
题意:
蜘蛛牌是windows xp操作系统自带的一款纸牌游戏，游戏规则是这样的：
只能将牌拖到比她大一的牌上面（A最小，K最大），如果拖动的牌上有
按顺序排好的牌时，那么这些牌也跟着一起移动，游戏的目的是将所有
的牌按同一花色从小到大排好，为了简单起见，我们的游戏只有同一花
色的10张牌，从A到10，且随机的在一行上展开，编号从1到10，把第i号
上的牌移到第j号牌上，移动距离为abs(i-j)，现在你要做的是求出完成游戏的最小移动距离。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1584
思路:总共移动的次数必然是9次,移动的方式的不同主要在于,先把哪一段
按照顺序移动累成一堆,这样后续在移动时 就可以将一堆一个整体同时移动
到另一堆上面.因此可以dfs枚举线性移动的位置顺序.
*/
//ac 109ms dfs
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;

//a[x]=i,表示编号为x的纸牌在位置i
int a[N],vis[N],ans;

void dfs(int num,int sum){
    if(num == 9){
        if(sum<ans)
            ans=sum;
        return;
    }
    if(sum>=ans)//剪枝 如果当前距离和 已经不小于之前记录的最优值 则结束
        return;
    for(int i=1;i<10;i++){//移动第num次时 将i移动到j的上面,这里j只能等于i+1
        if(vis[i])
            continue;
        vis[i]=1;
        for(int j=i+1;j<=10;j++){
            //注意有可能j 已经不在原先的最初试位置,j已经移动到某一堆的最上面,这时i要移动到j所在堆最小面纸牌的位置
            //即:第一个vis[j]未标记的 就是最下面的纸牌
            if(vis[j])//j不做标记是因为,放在最下层的j,可以拖着i作为一个整体再放在j+1的上面
                continue;
            dfs(num+1,sum+abs(a[i]-a[j]));
            break;//回溯后直接结束,因为i只能刚好放在i+1的上面
        }
        vis[i]=0;
    }
}

int main(){
    int T,x;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        for(int i=1;i<=10;i++){
            scanf("%d",&x);
            a[x]=i;//表示编号为x的纸牌在位置i
        }
        dfs(0,0);
        printf("%d\n",ans);
    }
    return 0;
}
