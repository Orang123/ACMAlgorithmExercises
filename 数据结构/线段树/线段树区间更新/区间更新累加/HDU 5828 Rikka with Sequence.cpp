/*
����:ժ������
ά��һ�����У�֧�����ֲ�����
����1������ӡ�
�����������俪���ţ�����ȡ������
����3��������͡�
n<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5828
˼·:ժ�Բ���:https://blog.csdn.net/qq_21057881/article/details/52186751
HDU4027�������棬����һ������add�Ĳ���������һ����Ȼ�����ŵĵݼ��ٶ��Ǻܿ�ģ�
2^64��಻����8�ξ��ܼ���1�����һ���ֺܶ���������ֶ���һ�����������ô�������߶�����ά��һ��flagֵ��
��ʾ���������Ƿ�������������ȵģ�����ǵĻ���ô�����ž�ֻ������������ˣ�����ʵ��ϸ�ڻ��������....
����HDU�������ˣ�����2 3 2 3 2 3Ȼ�������6Ȼ�󿪸��ţ��ֻ���2 3 2 3 2 3�൱�ڲ��������������һ��������ˣ�
�������൱��û��֦�������n^2...��������ֻ�м���Ϊ1��ʱ��Ż�����������������>1�Ļ��ǲ�����ά��ԭ�������еģ�
��ô�Ϳ���ά��һ�����ֵ����Сֵ���������Ϊ1�Ļ���ô���俪������ʵ�൱�������ȥ��x-sqrt(x)���ټ��ϵ�һ���汾�ļ�֦�Ϳ���2000MS���ҹ�ȥ��

*/
//ac 1684ms
//ժ�Բ���:https://blog.csdn.net/qq_21057881/article/details/52186751
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
