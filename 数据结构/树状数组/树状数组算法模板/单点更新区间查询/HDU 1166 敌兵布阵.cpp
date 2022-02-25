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
思路:树状数组,单点修改操作，查询操作.
*/
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
