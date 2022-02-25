/*
题意:摘自网上
维护一个序列，支持三种操作。
操作1：区间加。
操作二：区间开根号（向下取整）。
操作3：区间求和。
n<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5828
思路:摘自博客:https://blog.csdn.net/qq_21057881/article/details/52186751
HDU4027的升级版，多了一个区间add的操作，考虑一下显然开根号的递减速度是很快的，
2^64最多不超过8次就能减到1，而且会出现很多区间的数字都是一样的情况，那么可以在线段树多维护一个flag值，
表示区间里面是否所有数都是相等的，如果是的话那么开根号就只开到这里就行了，具体实现细节还是蛮多的....
后来HDU加数据了，比如2 3 2 3 2 3然后整体加6然后开根号，又会变回2 3 2 3 2 3相当于不会出现区间数字一样的情况了，
这样就相当于没剪枝，变成了n^2...后来发现只有极差为1的时候才会出现这种情况，极差>1的话是不可能维持原来的序列的，
那么就可以维护一个最大值和最小值，如果极差为1的话那么区间开根号其实相当于区间减去了x-sqrt(x)，再加上第一个版本的剪枝就可以2000MS左右过去了

*/
//ac 1684ms
//摘自博客:https://blog.csdn.net/qq_21057881/article/details/52186751
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000+50;
#define LL long long
#define eps 1e-8
#define LL long long
#define lson i<<1,l,mid
#define rson i<<1|1,mid+1,r
LL sum[maxn<<2],lazy[maxn<<2],maxx[maxn<<2],minn[maxn<<2];
const int read()
{
	char ch = getchar();
	while (ch<'0' || ch>'9') ch = getchar();
	int x = ch - '0';
	while ((ch = getchar()) >= '0'&&ch <= '9') x = x * 10 + ch - '0';
	return x;
}

void push_up(int i)
{
	maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
	minn[i]=min(minn[i<<1],minn[i<<1|1]);
    sum[i]=sum[i<<1]+sum[i<<1|1];
}
void pushdown(int r,int m)
{
	 if(lazy[r])
	 {
		 lazy[r<<1]+=lazy[r];
		 maxx[r<<1]+=lazy[r];
		 maxx[r<<1|1]+=lazy[r];
		 minn[r<<1]+=lazy[r];
		 minn[r<<1|1]+=lazy[r];
		 lazy[r<<1|1]+=lazy[r];
		 sum[r<<1]+=lazy[r]*(m-m/2);
		 sum[r<<1|1]+=lazy[r]*(m/2);
		 lazy[r]=0;
	 }
     if(minn[r]==maxx[r])
	 {
		 minn[r<<1]=maxx[r<<1]=minn[r<<1|1]=maxx[r<<1|1]=minn[r];
		 sum[r<<1]=minn[r]*(m-m/2);
		 sum[r<<1|1]=maxx[r]*(m/2);
	 }
}
void build(int i,int l,int r)
{
     lazy[i]=0;
	 if(l==r)
	 {
		 scanf("%d",&sum[i]);
		 minn[i]=sum[i];
		 maxx[i]=sum[i];
		 return;
	 }
	 int mid = (l+r)>>1;
	 build(lson);
	 build(rson);
	 push_up(i);
}

void update(int ql,int qr,int v,int i,int l,int r)
{
     if(ql<=l && qr>=r)
	 {
		 minn[i]+=v;
		 maxx[i]+=v;
		 sum[i]+=1LL*(r-l+1)*v;
		 lazy[i]+=v;
		 return;
	 }
	 pushdown(i,r-l+1);
	 int mid = (l+r)>>1;
	 if(ql<=mid)
		 update(ql,qr,v,lson);
	 if(qr>mid)
		 update(ql,qr,v,rson);
	 push_up(i);
}

void update1(int ql,int qr,int i,int l,int r)
{
     if(ql<=l && qr>=r)
	 {
		 if((int)sqrt(minn[i]) == (int)sqrt(maxx[i]))
		 {
			 minn[i]=maxx[i]=(int)sqrt(minn[i]);
			 sum[i]=minn[i]*(r-l+1);
		 }
		 else if(minn[i]+1==maxx[i])
		 {
			 int k = maxx[i]-(int)sqrt(maxx[i]);
			 update(ql,qr,-k,i,l,r);
		 }
		 else
		 {
	         pushdown(i,r-l+1);
			 int mid = (l+r)>>1;
			 if(ql<=mid)update1(ql,qr,lson);
			 if(qr>mid)update1(ql,qr,rson);
			 push_up(i);
		 }
		 return;
	 }
	 pushdown(i,r-l+1);
	 int mid = (l+r)>>1;
	 if(ql<=mid)
		 update1(ql,qr,lson);
	 if(qr>mid)
		 update1(ql,qr,rson);
	 push_up(i);
}
LL query(int ql,int qr,int i,int l,int r)
{
    if(ql<=l && qr>=r)
		return sum[i];
	pushdown(i,r-l+1);
	int mid = (l+r)>>1;
	LL ans = 0;
	if(ql<=mid)
		ans+=query(ql,qr,lson);
	if(mid<qr)
		ans+=query(ql,qr,rson);
	return ans;
}

int main()
{
    int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,q;
		scanf("%d%d",&n,&q);
	//	n = Scan();
	//	q = Scan();
		build(1,1,n);
		while(q--)
		{
			int x,y,w,op;
			scanf("%d",&op);
			if(op==1)
			{
				scanf("%d%d%d",&x,&y,&w);
			//	x = Scan();
			//	y = Scan();
			//	w = Scan();
				update(x,y,w,1,1,n);
			}
			if(op==2)
			{
				scanf("%d%d",&x,&y);
			//	x = Scan();
			//	y = Scan();
				update1(x,y,1,1,n);
			}
			if(op==3)
			{
				scanf("%d%d",&x,&y);
			//	x = Scan();
			//	y = Scan();
				printf("%lld\n",query(x,y,1,1,n));
			}
		}
	}
}
