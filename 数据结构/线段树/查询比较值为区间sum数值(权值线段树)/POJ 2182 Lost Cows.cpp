/*
题意:摘自网上
有一个1-n的序列，第i个数知道在它前面且比它小的数的个数，求该序列。
n<=8000.
链接:http://poj.org/problem?id=2182
思路:和POJ 2828一样,sum[rt]表示当前区间的空位.
从n降序更新线段树,当a[i]比a[i+1]小时,a[i]的编号
肯定较小,会考虑线段树的左子树空位的个数,当a[i]比
a[i+1]大时,a[i+1]之前放置时肯定减少了空位个数,放置
a[i]时自然就会往较右边的区间搜索,实际放置的位置就偏向
右子树.
*/
//ac 94ms
#include<cstdio>
#define N 8100

int n,sum[N<<2],a[N],ans[N];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int rt,int l,int r,int val,int pos){
    if(l == r){
        sum[rt]=0;
        ans[pos]=l;
        return;
    }
    int mid=(l+r)/2;
    if(val<=sum[rt<<1])
        update(rt<<1,l,mid,val,pos);
    else
        update(rt<<1|1,mid+1,r,val-sum[rt<<1],pos);
    pushup(rt);
}

int main(){
    scanf("%d",&n);
    build(1,1,n);
    a[1]=0;
    for(int i=2;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n;i>=1;i--)
        update(1,1,n,a[i]+1,i);//a[i]+1是因为 实际要放置的位置是a[i]+1
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}

/*
//ac 375ms 暴力
//摘自博客:https://blog.csdn.net/qq_34374664/article/details/62216201
//这个暴力的做法没怎么看懂
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int main()
{
    int n , j,cow[8005] ={0}, book[8005] = {0} ,  b[8005] = {0};
    cin >> n;
    for(int i = 2 ; i <= n; i++)  cin >> cow[i];
    b[n] = cow[n] + 1;
    book[b[n]] = 1;
    for(int i = n - 1; i >= 1 ; i--)
    {
        int count = 0 ;
        for(j = 1 ; j <= n - 1 ; j++)
        {
            if(book[j] == 0)  count++;
            if(count == cow[i] + 1)  break;
        }
        b[i] = j;
        book[j]  =1;
    }
    for(int i = 1; i <= n ;i++)
        cout << b[i] <<endl;
    return 0;
}
*/
