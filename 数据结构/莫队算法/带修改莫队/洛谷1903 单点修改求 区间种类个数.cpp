#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 150000
#define maxn 1000100
using namespace std;
//qnum为询问的标号,bnum为修改记录的标号
int a[N],pos[N],qnum,bnum,cnt[maxn],ans[N],res;
/*
这里只有88分(两个样例TLE),改成快速输入94分(一个样例TLE) 感觉这个数据卡的没啥意义,代码是没问题的,后面那份二维数组的代码100分
在普通莫队的基础上 加上一维时间维度,则可进行单点修改,区间修改不支持,可采用线段树.
共有6种可能的转移情况:[l-1,r,t],[l+1,r,t],[l,r-1,t],[l,r+1,t],[l,r,t-1],[l,r,t+1].
*/

struct seq{
    int l,r,id,t;
    bool operator < (const seq &x)const{//这里用奇偶化排序效率较低.
        /*
        若左端点所在块不同,则按左端点块排,
        否则考虑右端点所在块,若不在同一块,则按右端点块排,否则按照时间戳排
        都是升序排列.
        */
        if(pos[l] != pos[x.l]) return l<x.l;
        if(pos[r] != pos[x.r]) return r<x.r;
        return t<x.t;
    }
}q[N];
struct Node{
    int x,y;
}b[N];

void add(int x){
    if(!cnt[x])
        res++;
    cnt[x]++;
}

void sub(int x){
    cnt[x]--;
    if(!cnt[x])
        res--;
}

void change(int t,int i){
    //若要修改的单点在询问的区间内,则区间的res会受到影响,需要修改
    if(b[t].x>=q[i].l && b[t].x<=q[i].r){
        //若待修改的位置画笔出现的次数减1后为0,则种类个数减1
        if(!--cnt[a[b[t].x]])
            res--;
        //若待修改的画笔所修改成的颜色出现的次数本身是0,则修改后种类个数加1
        if(!cnt[b[t].y]++)
            res++;
    }
    /*
    将待修改的位置的画笔颜色与要修改成的颜色交换,方便下次当时间戳大于当前询问的时间戳时,
    将修改还原,即将之前修改后的颜色再还原成未修改之前的颜色,也方便后面的询问区间 对修改后颜色种类的计算.
    */
    swap(a[b[t].x],b[t].y);
}
int main(){
    int n,m,siz;
    char c;
    scanf("%d%d",&n,&m);
    siz=pow(n,2.0/3.0);//块的大小为n^(2/3),块的个数为n^(1/3)
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[i]=(i-1)/siz+1;
    }

    while(m--){
        scanf(" %c",&c);
        if(c == 'Q'){
            qnum++;
            scanf("%d%d",&q[qnum].l,&q[qnum].r);
            q[qnum].id=qnum;
            q[qnum].t=bnum;//设置该询问的时间戳为bnum,bnum为0时还没有修改
        }
        else{
            bnum++;
            scanf("%d%d",&b[bnum].x,&b[bnum].y);
        }
    }
    sort(q+1,q+1+qnum);
    int l=1,r=0,t=0;//t=0 默认开始是没有修改的
    //离线转移时间复杂度 O(n^(5/3)) =n*n^(2/3)
    for(int i=1;i<=qnum;i++){
        /*
        这个做法一定要先计算区间和,再去修改,如果先修改,会导致修改后的颜色,后面计算区间颜色种类时,
        出现的次数重复计算cnt多出来,而且待修改的颜色若之前没有再询问区间内,则会减少成-1.
        */
        while(l<q[i].l) sub(a[l++]);
        while(l>q[i].l) add(a[--l]);
        while(r<q[i].r) add(a[++r]);
        while(r>q[i].r) sub(a[r--]);
        //若当前的时间戳小于这条询问所对应的时间戳,则将t+1~q[i].t对应的修改加上
        while(t<q[i].t) change(++t,i);//从t+1开始 修改
        //将下标在q[i]+1~t内的修改还原 t本身也超出了询问的时间戳,因此也还原
        while(t>q[i].t) change(t--,i);//从t开始递减 修改
        ans[q[i].id]=res;
    }
    for(int i=1;i<=qnum;i++)
        printf("%d\n",ans[i]);
    return 0;
}
/*
洛谷 Qiuly用户
这种做法二维数组的做法100分
Q[i][0] 表示第i次操作需更改的位置
Q[i][1] 表示第i次操作更改位置的现在颜色
Q[i][2] 表示第i次操作要改成的颜色
注意,Q[i][1]在之前的更改操作中可能已经被改过，而我们有要记录这个点现在的值，
所以我维护了一个C数组来随时记录每次操作的变化，原序列数组为val数组，
显然是不能用原序列数组来记录的(不然到莫队时就乱了).
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define A printf("A")
#define P(x) printf("V %d V",x);
#define S 1000003
using namespace std;
const int N=15e4+5;
template<typename _Tp>inline void read(_Tp&dig){
    char c;dig=0;
    while(c=getchar(),!isdigit(c));
    while(isdigit(c))dig=dig*10+c-'0',c=getchar();
}
int n,m,Be,c1,c2,ans,C[N],val[N],Ans[N],sum[S],Q[N][3];
struct Node{
	int l,r,c,id;
	bool operator < (const Node a)const {
	    if(l/Be==a.l/Be){
            if(r/Be==a.r/Be)return id<a.id;
            return r<a.r;
        }return l<a.l;
	}
}q[N];char opt[10];
inline void Add(int x){if(!sum[x])ans++;sum[x]++;}
inline void Del(int x){sum[x]--;if(!sum[x])ans--;}
int main(){
    read(n);read(m);Be=pow(n,(double)2/(double)3);
    for(register int i=1;i<=n;++i)read(val[i]),C[i]=val[i];
    for(int i=1,a,b;i<=m;i++)
       if(scanf("%s",opt),read(a),read(b),opt[0]=='Q')
          q[c1].l=a,q[c1].r=b,q[c1].id=c1,q[c1].c=c2,c1++;
       else Q[c2][0]=a,Q[c2][1]=C[a],Q[c2][2]=C[a]=b,c2++;
    sort(q,q+c1),Add(val[1]);int l=1,r=1,lst=0;
    for(register int i=0;i<c1;++i){
    	 for(;lst<q[i].c;lst++){
    		 if(l<=Q[lst][0]&&Q[lst][0]<=r)
    			Del(Q[lst][1]),Add(Q[lst][2]);
    		 val[Q[lst][0]]=Q[lst][2];
    	 }
    	 for(;lst>q[i].c;lst--){
    		 if(l<=Q[lst-1][0]&&Q[lst-1][0]<=r)
    			Del(Q[lst-1][2]),Add(Q[lst-1][1]);
    		 val[Q[lst-1][0]]=Q[lst-1][1];
    	 }
    	 for(++r;r<=q[i].r;r++)Add(val[r]);
         for(--r;r>q[i].r;r--)Del(val[r]);
         for(--l;l>=q[i].l;l--)Add(val[l]);
         for(++l;l<q[i].l;l++)Del(val[l]);
    	 Ans[q[i].id]=ans;
    }for(register int i=0;i<c1;++i)printf("%d\n",Ans[i]);
	return 0;
}
*/
