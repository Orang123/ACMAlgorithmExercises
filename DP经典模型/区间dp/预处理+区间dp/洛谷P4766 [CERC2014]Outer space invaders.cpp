#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
/*
题意:来自外太空的外星人（最终）入侵了地球。保卫自己，或者解体，被他们同化，或者成为食物。
迄今为止，我们无法确定。外星人遵循已知的攻击模式。有n个外星人进攻，第i个进攻的外星人会在时间a[i]
​出现，距离你的距离为d[i]，它必须在时间b[i]前被消灭，否则被消灭的会是你。
你的武器是一个区域冲击波器，可以设置任何给定的功率。如果被设置了功率R，它会瞬间摧毁与你的距离在R
以内的所有外星人（可以等于），同时它也会消耗R单位的燃料电池。
求摧毁所有外星人的最低成本（消耗多少燃料电池），同时保证自己的生命安全。
链接:https://www.luogu.com.cn/problem/P4766
思路:题目的输入时间点过大,为避免dp的时空复杂度过大,需要先对时间离散化.
dp[i][j]代表要消灭所有出现时间和死亡时间段在i~j内外星人消耗的最少燃料.
*/
struct Node{
    int a,b,d;
}node[350];
int dp[1500][1500],tmp[10010];

int main(){
    int T,n,cnt;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(tmp,0,sizeof(tmp));
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&node[i].a,&node[i].b,&node[i].d);
            tmp[node[i].a]=tmp[node[i].b]=1;
        }
        for(int i=1;i<10010;i++)
            if(tmp[i]) tmp[i]=++cnt;//cnt代表最大的离散化后最大时间上界
        for(int i=1;i<=n;i++){
            node[i].a=tmp[node[i].a];//对时间重新赋值
            node[i].b=tmp[node[i].b];
        }
        for(int l=1;l<cnt;l++){
            for(int i=1;i+l<=cnt;i++){
                int j=i+l;
                int id=-1;
                //确定i~j时间内距离最大的外星人编号 这样对于在同时时间区间内出现和死亡的外星人可以一同消灭,节约燃料
                for(int k=1;k<=n;k++)
                    if(node[k].a>=i && node[k].b<=j && (id == -1||node[k].d>node[id].d)) id=k;
                if(id == -1) continue;//若i~j时间内没有外星人则进行下一个区间
                dp[i][j]=INF;
                //枚举距离最大外星人的出现时间到死亡时间内选取某一时刻k消灭这个外星人id
                for(int k=node[id].a;k<=node[id].b;k++)
                    /*
                    将时间分割,较优得到情况是消灭的外星人id的时刻k刚好也在[i,k-1] [k+1,j]区间内,
                    这样就可一同将两边区间内的所有外星人同时消灭,当然这个两个dp[i][k-1]dp[k+1][j]可能是0,
                    也可能是其它时间区间的消耗燃料,外星人存活的,求解消灭所有外星人的最少要消耗的燃料.
                    */
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+node[id].d+dp[k+1][j]);
            }
        }
        printf("%d\n",dp[1][cnt]);
    }
    return 0;
}

/*
lower_bound离散化
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
struct Node{
    int a,b,d;
}node[350];
int dp[1500][1500],tmp[10010];

int main(){
    int T,n,cnt;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(tmp,0,sizeof(tmp));
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&node[i].a,&node[i].b,&node[i].d);
            tmp[++cnt]=node[i].a;
            tmp[++cnt]=node[i].b;
        }
        sort(tmp+1,tmp+cnt+1);
    	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
    	for(int i=1;i<=n;++i) node[i].a=lower_bound(tmp+1,tmp+1+cnt,node[i].a)-tmp,node[i].b=lower_bound(tmp+1,tmp+1+cnt,node[i].b)-tmp;
        for(int l=1;l<cnt;l++){
            for(int i=1;i+l<=cnt;i++){
                int j=i+l;
                int id=-1;
                for(int k=1;k<=n;k++)
                    if(node[k].a>=i && node[k].b<=j && (id == -1||node[k].d>node[id].d)) id=k;
                if(id == -1) continue;
                dp[i][j]=INF;
                for(int k=node[id].a;k<=node[id].b;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+node[id].d+dp[k+1][j]);
            }
        }
        printf("%d\n",dp[1][cnt]);
    }
    return 0;
}
*/


