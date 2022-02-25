#include<cstdio>
#include<ctype.h>
#include<cmath>
#include<algorithm>
#define N 100100
#define M 2000100
using namespace std;
int st[N][20],lg[N];//lg[i]表示不超过i的最大2次幂指数（就是2的lg[i]次方不超过i）

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init(int n){
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=lg[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
}

//O(1) 计算出区间长度的对数 O(1)回答每个询问
int query(int l,int r){
    int k=lg[r-l+1];//O(1)
    return max(st[l][k],st[r-(1<<k)+1][k]);
}

int main(){
    int n,m,l,r;
    n=read();m=read();
    for(int i=1;i<=n;i++) st[i][0]=read();
    init(n);
    while(m--){
        l=read(),r=read();
        printf("%d\n",query(l,r));
    }
    return 0;
}
