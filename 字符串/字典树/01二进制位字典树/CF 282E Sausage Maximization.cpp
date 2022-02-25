/*
题意:摘自网上
给定一个n个数的序列，记 a 为序列任意前缀的异或和，b 为序列任意后缀的异或和，
求 a 异或 b 的最大值，前缀和后缀可以为空。
n<=10^5,每个数值<=10^12.
链接:http://codeforces.com/problemset/problem/282/E
思路:将前缀异或和插入01字典树,用后缀查找最大值,注意要
插入数值0,有可能查找后缀本身 就是最大值,还要注意移位时,
1要强制转换为LL,否则会数值溢出,默认的1是int.
*/
//ac 248ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6000010
#define M 100010
using namespace std;
typedef long long ll;

int n,tr[N][2],cnt;
ll a[M],prefix[M],suffix[M],ans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(ll val){
    int rt=0,son;
    for(int i=60;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

ll findWord(ll val){
    int rt=0,son;
    ll res=0;
    for(int i=60;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){
            res|=1LL<<i;//1要强制转换为LL,否则会数值溢出,默认的1是int.
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

int main(){
    cnt=-1;
    newNode();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    insertWord(0);//如果只有一个数,异或和最大是其本身,除了本身是1时,会走0,本身是0,字典树中没有1,最终的最大值恰好就是本身
    for(int i=1;i<=n;i++){
        prefix[i]=prefix[i-1]^a[i];
        insertWord(prefix[i]);
    }
    for(int i=n;i>=1;i--){
        suffix[i]=suffix[i+1]^a[i];
        ans=max(ans,findWord(suffix[i]));
    }
    printf("%lld",ans);
    return 0;
}
