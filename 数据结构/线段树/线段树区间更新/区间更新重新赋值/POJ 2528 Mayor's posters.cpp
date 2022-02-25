/*
题意:摘自网上
城市里要竞选市长，然后在一块墙上可以贴海报为自己拉票，
每个人可以贴连续的一块区域，后来帖的可以覆盖前面的，问
到最后一共可以看到多少张海报。
n张海报,n<=10^4,贴海报的覆盖的左右区间范围<=10^7.
链接:http://poj.org/problem?id=2528
思路:是线段树区间染色问题,但是区间范围为10^7,直接开会MLE.
可以将区间范围离散化,但是直接离散化成连续区间会出问题,
下述样例来自:https://blog.csdn.net/zezzezzez/article/details/80230026
如三张海报为：1~10 1~4 6~10
离散化时 X[ 1 ] = 1, X[ 2 ] = 4, X[ 3 ] = 6, X[ 4 ] = 10
第一张海报时：墙的1~4被染为1；
第二张海报时：墙的1~2被染为2，3~4仍为1；
第三张海报时：墙的3~4被染为3，1~2仍为2。
最终，第一张海报就显示被完全覆盖了，于是输出2，但实际上明显不是这样，正确输出为3。
新的离散方法为：在相差大于1的数间加一个数，例如在上面1 4 6 10中间加5
（算法中实际上1，4之间，6，10之间都新增了数的）
X[ 1 ] = 1, X[ 2 ] = 4, X[ 3 ] = 5, X[ 4 ] = 6， X[ 5 ] = 10
这样之后，第一次是1~5被染成1；第二次1~2被染成2；第三次4~5被染成3
最终，1~2为2，3为1，4~5为3，于是输出正确结果3。
*/
//ac 110ms 线段树区间染色更新 离散化
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//离散化左右坐标个数为N<<1,线段树实际节点数为N<<1<<2=N<<3,
//但因为要在本身坐标之间插入间隔,实际线段树的区间右边界会扩大,
//因此线段树节点编号开至N<<4,tp数组也是同样道理,本身只需存储左右坐标N<<1,但因为中间要插入值,所以开到N<<2.
int n,sum[N<<4],vis[N],cnt,maxn,tp[N<<2];
struct Node{
    int l,r;
}node[N];

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])
        sum[rt]=sum[rt<<1];
    else
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=-1;
    }
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

void query(int rt,int l,int r){
    if(sum[rt]!=-1){
        if(!vis[sum[rt]]){
            cnt++;
            vis[sum[rt]]=1;
        }
        return;
    }
    if(l == r)//有可能叶子节点 没贴过海报
        return;
    int mid=(l+r)/2;
    if(l<=mid)
        query(rt<<1,l,mid);
    if(r>mid)
        query(rt<<1|1,mid+1,r);
}

int main(){
    int T,k;
    scanf("%d",&T);
    while(T--){
        k=cnt=0;
        memset(sum,-1,sizeof(sum));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&node[i].l,&node[i].r);
            tp[++k]=node[i].l;
            tp[++k]=node[i].r;
        }
        sort(tp+1,tp+1+k);
        maxn=unique(tp+1,tp+1+k)-(tp+1);
        int len=maxn;
        for(int i=2;i<=len;i++){
            if(tp[i]-tp[i-1]>1)//连续坐标值之间相差大于1的,在中间插入一个值,避免离散化后 rnk刚好紧邻只差1
                tp[++maxn]=tp[i-1]+1;
        }
        sort(tp+1,tp+1+maxn);//tp数组后面插入了新值,重新排序.
        for(int i=1;i<=n;i++){
            //lower_bound二分查找的是<=node[i].l的地址,直接作差 实际的rnk排名会少一,因此还要多加1
            node[i].l=lower_bound(tp+1,tp+1+maxn,node[i].l)-(tp+1)+1;
            node[i].r=lower_bound(tp+1,tp+1+maxn,node[i].r)-(tp+1)+1;
            update(node[i].l,node[i].r,1,1,maxn,i);
        }
        query(1,1,maxn);
        printf("%d\n",cnt);
    }
    return 0;
}
