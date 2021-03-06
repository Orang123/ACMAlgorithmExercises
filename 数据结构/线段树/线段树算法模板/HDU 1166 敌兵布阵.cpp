/*
题意:第一行一个整数T，表示有T组数据。
每组数据第一行一个正整数N（N<=50000）,表示敌人有N个工兵营地，
接下来有N个正整数,第i个正整数ai代表第i个工兵营地里开始时有ai个人（1<=ai<=50）。
接下来每行有一条命令，命令有4种形式：
(1) Add i j,i和j为正整数,表示第i个营地增加j个人（j不超过30）
(2)Sub i j ,i和j为正整数,表示第i个营地减少j个人（j不超过30）;
(3)Query i j ,i和j为正整数,i<=j，表示询问第i到第j个营地的总人数;
(4)End 表示结束，这条命令在每组数据最后出现;
每组数据最多有40000条命令
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1166
思路:线段树或树状数组,单点修改操作,查询操作.
*/

/*
线段树学习详解博客:
https://blog.csdn.net/douboomfly/article/details/71075977(下述代码参考该博客)
https://blog.csdn.net/qq_26071477/article/details/51636464
https://blog.csdn.net/metalseed/article/details/8039326

线段树空间复杂度O(4*n)的证明博客:
https://blog.csdn.net/gl486546/article/details/78243098#comments
https://www.pianshen.com/article/74391959426/
https://blog.csdn.net/Monster_Day/article/details/52214711

线段树降空间复杂度,从O(4n)降到O(2n) zkw线段树
https://blog.csdn.net/qwb492859377/article/details/51410438
*/
//ac 249ms 线段树单点更新区间查询,构建树赋予点权值
#include<cstdio>
#define N 50010

struct{
    int l, r;
    int sum;
}seg_tree[N<<2];//线段树空间复杂度为区间节点数的4倍

void Pushup(int l,int r,int rt){
    seg_tree[rt].sum = seg_tree[l].sum + seg_tree[r].sum;//根节点的值代表区间(l,r)的和
}

//线段树是一棵完全二叉树 故而深度为log(n) 这是它区间更新查询高效性的关键
//线段树叶子的个数恰好为区间长度n.
void Build_segtree(int l, int r, int rt){//建立线段树 O(nlog(n)) n为区间长度 n也是叶子节点的个数
    seg_tree[rt].l = l, seg_tree[rt].r = r;
    if (l == r){//直到划分到叶子结点将待输入数据存入
        scanf("%d", &seg_tree[rt].sum);
        return;
    }
    int mid = (l + r) >> 1;//找到下一个区间二分的中点
    Build_segtree(l, mid, rt<<1);//左区间
    Build_segtree(mid + 1, r, rt<<1 | 1);//右区间
    Pushup(rt << 1, rt << 1 | 1, rt);//合并区间的和
}

//单点更新 时间复杂度为O(log(n)),因为找到一个叶子节点需要递归的深度为log(n)
//而不加懒惰标记的区间更新复杂度为 O((r-l+1)*log(n)),[l,r]为要修改的区间,(r-l+1)实际就是要修改的叶子节点的个数.
//而加上懒惰标记并不会真的全部都递归到所有的叶子节点,故而时间降低.
void update(int pos, int change,int rt){//更新线段树 O(log(n)) n为区间长度
    if (seg_tree[rt].l==seg_tree[rt].r){//从叶子结点开始更新
        seg_tree[rt].sum += change;
        return;
    }
    int mid = (seg_tree[rt].l + seg_tree[rt].r) >> 1;
    if (pos <= mid) update(pos,  change,rt<<1);
    else update(pos, change,rt<<1|1);
    Pushup(rt << 1, rt << 1 | 1, rt);//再依次更新父结点
}

//严格分3种情况查询 包含关系判断
int query(int l, int r, int rt){//查询任意区间的和 O(log(n)) n为区间长度
    if (l <= seg_tree[rt].l && seg_tree[rt].r <= r){//当现在区间被待查找区间包含时
        return seg_tree[rt].sum;
    }
    int mid = (seg_tree[rt].l + seg_tree[rt].r) >> 1;
    if (r <= mid) return query(l, r, rt << 1);//待查找区间在二分中点左边,递归左子树
    else if (l > mid) return query(l, r, rt << 1 | 1);//待查找区间在二分中点右边,递归右子树
    else return query(l, r, rt << 1) + query(l, r, rt << 1 | 1);//二分中点在待查找区间内,即左右子树都被包含在待查找区间内
}

/*
//ac 3种情况混合res+=,实际还是三种情况 包含关系判断
int query(int l, int r, int rt){//查询任意区间的和
    if (l <= seg_tree[rt].l && seg_tree[rt].r <= r){//当现在区间被待查找区间包含时
        return seg_tree[rt].sum;
    }
    int mid = (seg_tree[rt].l + seg_tree[rt].r) >> 1;
    int res=0;
    if (l <= mid) res+=query(l, r, rt << 1);//待查找区间一部分在二分中点左边,递归左子树
    if (r > mid) res+=query(l, r, rt << 1 | 1);//待查找区间一部分在二分中点右边,递归右子树
    return res;
}
*/

/*
//严格分3种情况 区间相等判别法 ac
int query(int l, int r, int rt){
    //正好相等时说明找到了待查找区间的一部分
    if (l == seg_tree[rt].l && r == seg_tree[rt].r)
        return seg_tree[rt].sum;
    int mid = (seg_tree[rt].l + seg_tree[rt].r) >> 1;
    //只能严格区分3种情况这样 才能精确区分待查找区间范围
    if(r<=mid)//待查找区间右端点 在当前区间rt mid左侧,进入左子树 待查找区间 仍然是[l,r]
        return query(l, r, rt << 1);
    else if(l>mid)//待查找区间左端点 在当前区间rt mid右侧,进入右子树 待查找区间 仍然是[l,r]
        return query(l, r, rt << 1 | 1);
    else//待查找区间左端点在mid左侧,右端点在mid右侧,待查找区间分布同时在左右子树 待查找区间更新为[l,mid]+[mid+1,r]
        return query(l, mid, rt << 1)+query(mid+1, r, rt << 1 | 1);
}
*/

int main(){
    int T,n,pos,change,l,r,cnt=1;
    char cmd[6];
    scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        Build_segtree(1, n, 1);
        printf("Case %d:\n", cnt);
        cnt++;
        while (scanf("%s",cmd)&&*cmd!='E'){
            getchar();
            switch (*cmd){
            case 'A'://pos位置节点增加change
                scanf("%d%d", &pos, &change);
                update(pos, change, 1); break;
            case 'S'://pos位置节点减少change
                scanf("%d%d", &pos, &change);
                update(pos, -change, 1); break;
            case 'Q'://查询区间[cur_l,cur_r]的累加和
                scanf("%d%d", &l, &r);
                printf("%d\n", query(l, r, 1));
            }
        }
    }
    return 0;
}

/*
//ac 265ms 线段树精简版
#include<cstdio>
#include<cstring>
#define N 50010

int sum[N<<2];

void update(int pos, int change,int l,int r,int rt){//更新线段树
    if (l == r){//从叶子结点开始更新
        sum[rt] += change;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(pos,change,l,mid,rt<<1);
    else update(pos, change,mid+1,r,rt<<1|1);
    sum[rt]=sum[rt<<1]+sum[rt<<1 | 1];
}

int query(int cur_l, int cur_r, int l,int r,int rt){//查询任意区间的和
    if (cur_l <= l && r <= cur_r){//当现在区间被待查找区间包含时
        return sum[rt];
    }
    int mid = (l + r) >> 1,res=0;
    if (cur_l <= mid) res+=query(cur_l,cur_r,l,mid,rt << 1);//待查找区间一部分在二分中点左边,递归左子树
    if (cur_r > mid) res+=query(cur_l,cur_r,mid+1,r,rt << 1 | 1);//待查找一部分区间在二分中点右边,递归右子树
    return res;
}

int main(){
    int T,n,pos,change,cur_l,cur_r,cnt=1,x;
    char cmd[6];
    scanf("%d", &T);
    while (T--){
        memset(sum,0,sizeof(sum));
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            update(i,x,1,n,1);
        }
        printf("Case %d:\n", cnt);
        cnt++;
        while (scanf("%s",cmd)&&*cmd!='E'){
            getchar();
            switch (*cmd){
            case 'A'://pos位置节点增加change
                scanf("%d%d", &pos, &change);
                update(pos,change,1,n,1); break;
            case 'S'://pos位置节点减少change
                scanf("%d%d", &pos, &change);
                update(pos,-change,1,n,1); break;
            case 'Q'://查询区间[cur_l,cur_r]的累加和
                scanf("%d%d", &cur_l, &cur_r);
                printf("%d\n", query(cur_l,cur_r,1,n,1));
            }
        }
    }
    return 0;
}
*/

/*
//ac 218ms 树状数组
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50010
using namespace std;

int n,a[N],c[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    char str[20];
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(c,0,sizeof(c));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            update(i,a[i]);
        }
        printf("Case %d:\n",cas);
        int i,j;
        while(scanf("%s",str) && str[0]!='E'){
            scanf("%d%d",&i,&j);
            if(str[0] == 'A')
                update(i,j);
            else if(str[0] == 'S')
                update(i,-j);
            else{
                printf("%d\n",getsum(j)-getsum(i-1));
            }
        }
    }
    return 0;
}
*/
