/*
����:ժ������
������һ����������Ϊ�������֣�����˺����Ҷ�����ͬ�ģ�
��˺��м���ǻ��ģ��м���Ҷ����ǻ��ġ���������������Ƕ��١�
�ַ�������<=100000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5371
˼·:manacher.û̫�������.
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
//ac 1092ms ժ�Բ���:https://blog.csdn.net/Timeclimber/article/details/79182884
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
