#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll unsigned long long
#define mem(a,b) memset(a,b,sizeof(a))
#define mec(a,b) memcpy(a,b,sizeof(b))
using namespace std;
const int  MAXN=1000+50;
char str[MAXN];
int len;
ll ans;
int hd[MAXN],ect;
struct Edge{int nx,to,w;}ar[MAXN];
void adds(int u,int v,int w){ar[++ect].to=v,ar[ect].w=w,ar[ect].nx=hd[u],hd[u]=ect;}
struct  PAM
{
    int tot,last,n;
    int fa[MAXN],ln[MAXN],s[MAXN],cnt[MAXN];
    void init()
    {
        fa[0]=fa[1]=1;
        ln[tot=1]=-1;ln[last=n=ect=0]=0;
        s[0]=-1;
    }
    int ge(int u,int w)
    {for(int e=hd[u],v=ar[e].to;e;v=ar[e=ar[e].nx].to)if(ar[e].w==w)return v;return 0;}
    int gf(int k){while(s[n-ln[k]-1]^s[n])k=fa[k];return k;}
    inline void extend(int x,int c)
    {
        s[++n]=c;last=gf(last);
        if(!ge(last,c))
        {
            fa[++tot]=ge(gf(fa[last]),c);
            ln[tot]=ln[last]+2;
            adds(last,tot,c);

        }
        cnt[last=ge(last,c)]++;
    }
    void calc()
    {
        for(int i=tot;i>=2;i--)
        {
            cnt[fa[i]]+=cnt[i];
            ans+=cnt[i];
        }
    }
}pam;
int main()
{

    pam.init();
    scanf("%s",str+1);len=strlen(str+1);
    //for(int i=1;i<=len;i++)printf("%c",str[i]);
    for(int i=1,x;i<=len;i++)pam.extend(i,str[i]-'a');
    pam.calc();
    printf("%lld ",ans);
    return 0;

}