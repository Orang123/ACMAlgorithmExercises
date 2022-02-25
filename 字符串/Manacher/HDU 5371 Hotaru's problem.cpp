/*
题意:摘自网上
定义了一个序列它分为三个部分，最左端和最右端是相同的，
左端和中间的是回文，中间和右端又是回文。求这样的序列最长是多少。
字符串长度<=100000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5371
思路:manacher.没太看懂题解.
*/
//wa
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,s1[N],s2[N<<1],p[N<<1],id,mx,ans;

void manacher(){
    int k=-1;
    s2[++k]=-1;
    for(int i=0;i<n;i++){
        s2[++k]=-2;
        s2[++k]=s1[i];
    }
    s2[++k]=-2;
    s2[++k]=-3;
    n=k;
    mx=0;
    for(int i=1;i<n;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        ans=0;
        cas++;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&s1[i]);
        manacher();
        for(int i=2;i<n;i++){
            if(p[i] <= p[i+p[i]-1])
                ans=max(ans,p[i]-1+(p[i]-1)/2);
        }
        printf("Case #%d: %d\n",cas,ans);
    }
    return 0;
}

/*
//ac 1092ms 摘自博客:https://blog.csdn.net/Timeclimber/article/details/79182884
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=200005;
int N,a[maxn],b[maxn],maxr[maxn];
void init(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        b[i*2+1]=-1;
        b[i*2+2]=a[i];
    }
    N=2*i+1;
    b[0]=-2,b[N]=b[N+1]=-1;
}
void manacher()
{
    int id,maxn=0;
    for(int i=1;i<=N;i++)
    {
        maxr[i]=i<maxn?min(maxn-i,maxr[2*id-i]):1;
        while(b[i+maxr[i]]==b[i-maxr[i]]) maxr[i]++;
        if(i+maxr[i]>maxn) maxn=maxr[i]+i,id=i;
    }
}
int main()
{
    int t,n,cas=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        init(n);
        manacher();
        int ans=0;
        for(int i=3;i<=N;i+=2)
        {
           for(int j=ans;j<=maxr[i]-1;j+=2)
           {
               if(maxr[i+j]-1>=j)
               {
                   ans=j;
               }
           }
        }
        printf("Case #%d: %d\n",cas++,ans/2*3);

    }
    return 0;
}
*/
