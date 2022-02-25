/*
题意:n个气球排成一排，从左到右依次编号为1,2,3....N.
每次给定2个整数a b(a <= b),lele便为骑上他的“小飞鸽"
牌电动车从气球a开始到气球b依次给每个气球涂一次颜色。
但是N次以后lele已经忘记了第I个气球已经涂过几次颜色了，
你能帮他算出每个气球被涂过几次颜色吗？
n<=100000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1556
思路:树状数组区间更新单点查询裸题.
*/
//ac 483ms
#include<cstdio>
#include<cstring>
#define N 100010

//c[x]记录的是1~x区间整体被翻转的次数
int n,c[N];

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
    int a,b;
    while(scanf("%d",&n) && n){
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            update(a,1);
            update(b+1,-1);//b祖先节点以上的节点多余加了1,再减到1
        }
        //如果本身更新的是[1,4]单点查询 对于8这个节点,先增加后减少,还是0
        //对于7 6 5这样的节点节点本身是-1,但是儿子节点C[4]是1,累加后仍然是0
        for(int i=1;i<=n;i++){
            if(i!=1)
                printf(" ");
            printf("%d",getsum(i));
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 436ms 差分数组
//参考博客:https://blog.csdn.net/tianwei0822/article/details/81879644
#include<cstdio>
#include<cstring>
#define N 100010

int n,x[N],y[N];

int main(){
    int a,b;
    while(scanf("%d",&n) && n){
        memset(x,0,sizeof(x));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            x[a]++;
            x[b+1]--;
        }
        for(int i=1;i<=n;i++)
        	y[i]=y[i-1]+x[i];
        for(int i=1;i<=n;i++){
            if(i!=1)
                printf(" ");
            printf("%d",y[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
