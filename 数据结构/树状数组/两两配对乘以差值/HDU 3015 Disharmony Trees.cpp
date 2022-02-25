/*
题意:摘自网上
对于n棵树，给出所在位置和高度，然后分别对它的位置和高度做如下处理：
位置：将位置升序排序，最小的定义等级为 1，次小的定义等级为2，但是，
要是位置相同的，则等级定义要相同；
例如 位置 1，2，1，5，2，3
     等级  1，3，1，6，3，5
对于高度也是做如上处理；
然后，定义f=两树之间的距离差的绝对值，s=两树中最小的高度，求所有树之间f*s和。
n<=100000,x,h<=10^9
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3015
思路:和POJ 1990一样,只不过要先把坐标和高度的等级算出来
*/
//ac 124ms 从大到小排序和编号为1~i-1棵树对比,先查询后加入.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
typedef long long ll;
using namespace std;

int n;
ll c[N],b[N];//c表示小于等于x的个数,b表示小于等于x的坐标之和

struct Ele{
    int x,h;
}a[N];

bool cmp1(Ele u,Ele v){
    return u.x<v.x;
}

bool cmp2(Ele u,Ele v){
    return u.h<v.h;
}

bool cmp3(Ele u,Ele v){
    return u.h>v.h;
}

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,int x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll total,sumc,sumb;
    while(scanf("%d",&n)!=EOF){
        total=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i].x,&a[i].h);
        sort(a+1,a+1+n,cmp1);
        int tp=a[1].x;
        a[1].x=1;
        for(int i=2;i<=n;i++){
            if(a[i].x != tp){
                tp=a[i].x;
                a[i].x=i;
            }
            else
                a[i].x=a[i-1].x;
        }
        sort(a+1,a+1+n,cmp2);
        tp=a[1].h;
        a[1].h=1;
        for(int i=2;i<=n;i++){
            if(a[i].h != tp){
                tp=a[i].h;
                a[i].h=i;
            }
            else
                a[i].h=a[i-1].h;
        }
        sort(a+1,a+1+n,cmp3);
        ll ans=0,res1,res2;
        for(int i=1;i<=n;i++){
            sumc=getsum(c,a[i].x);//小于等于a[i].x的个数
            sumb=getsum(b,a[i].x);//小于等于a[i].x的坐标之和
            res1=a[i].h*(sumc*a[i].x-sumb);//(a[i].x-a[1..i-1].x)*a[i].h
            //total-sumb表示1~i-1中大于a[i].x的坐标之和,
            //(i-1-sumc)表示1~i-1中大于a[i].x的个数
            //坐标差的形式a[1..i-1].x-a[i].x
            res2=a[i].h*(total-sumb-(i-1-sumc)*a[i].x);
            ans+=res1+res2;
            total+=a[i].x;
            update(c,a[i].x,1);//将第i棵树加入树状数组
            update(b,a[i].x,a[i].x);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 140ms 从小到大排序 先加入后查询 更新
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
typedef long long ll;
using namespace std;

int n;
ll c[N],b[N];//c表示小于等于x的个数,b表示小于等于x的坐标之和

struct Ele{
    int x,h;
}a[N];

bool cmp1(Ele u,Ele v){
    return u.x<v.x;
}

bool cmp2(Ele u,Ele v){
    return u.h<v.h;
}

int lowbit(int x){
    return x & -x;
}

void update(ll *c,int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

ll getsum(ll *c,int x){
    ll sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    ll total,sumc,sumb;
    while(scanf("%d",&n)!=EOF){
        total=0;
        memset(c,0,sizeof(c));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i].x,&a[i].h);
        sort(a+1,a+1+n,cmp1);
        int tp=a[1].x;
        a[1].x=1;
        for(int i=2;i<=n;i++){
            if(a[i].x != tp){
                tp=a[i].x;
                a[i].x=i;
            }
            else
                a[i].x=a[i-1].x;
        }
        sort(a+1,a+1+n,cmp2);
        tp=a[1].h;
        a[1].h=1;
        for(int i=2;i<=n;i++){
            if(a[i].h != tp){
                tp=a[i].h;
                a[i].h=i;
            }
            else
                a[i].h=a[i-1].h;
        }
        for(int i=1;i<=n;i++){
    		update(c,a[i].x,1);
        	update(b,a[i].x,a[i].x);
		}
        sort(a+1,a+1+n,cmp2);
        ll ans=0,res1,res2;
    	for(int i=1;i<=n;i++){
        	sumc=getsum(c,a[i].x);//i+1~n中小于等于a[i].x的个数
        	sumb=getsum(b,a[i].x);//i+1~n中小于等于a[i].x的坐标之和
        	res1=a[i].h*(sumc*a[i].x-sumb);
        	//getsum(b,maxn)-getsum(b,a[i].x) i+1~n中大于a[i].x的坐标之和  n是最大的x坐标的等级,树状数组中最大的祖先节点编号
        	//getsum(c,maxn)-getsum(c,a[i].x) i+1~n中大于a[i].x的个数
        	res2=a[i].h*(getsum(b,n)-getsum(b,a[i].x)-(getsum(c,n)-getsum(c,a[i].x))*a[i].x);
        	ans+=res1+res2;
        	update(c,a[i].x,-1);//第i棵树已经和其余所有树对比过了,不再对比,因此删掉
        	update(b,a[i].x,-a[i].x);
    	}
        printf("%lld\n",ans);
    }
    return 0;
}
*/
