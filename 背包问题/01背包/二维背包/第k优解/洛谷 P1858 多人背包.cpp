#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 5100
using namespace std;
//ac 888ms 01���� ��k�Ž�ǡ��װ�� ���н������ͬ,ǰk�Ž�ĺ�
//ֻ��ʼ��dp[0][1]=0
/*
����:��01����ǰk�Ž�ļ�ֵ��
DD�ͺ�������Ҫȥ��ɽ��������һ����K����,ÿ���˶��ᱳһ����.
��Щ������������ͬ��,����V.����װ���������һ����N����Ʒ,ÿ��
��Ʒ���и���������ͼ�ֵ.��DD����,����ı������ŷ�����������:
ÿ���˱�����װ����Ʒ�������ǡ���ڰ�������.ÿ�������ÿ����Ʒ
���ֻ��һ��,��������ͬ�İ��п��Դ�����ͬ����Ʒ.����������,����
�������Ʒ�嵥������ȫ��ͬ.����������Ҫ���ǰ����,���а��������
��Ʒ���ܼ�ֵ����Ƕ����أ�
����:https://www.luogu.com.cn/problem/P1858
˼·:ʵ�ʾ�����k��������ǡ��װ�����������ֵ��,����ǰk�Ž�֮��,
k�����ֵ��������ͬ,����������ǡ��װ��.
*/
int n,v,k,w[N],val[N],dp[M][55],A[55],B[55];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d%d",&k,&v,&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&val[i]);
    /*
    ��Ϊ��ǡ��װ��,����ֻ��ʼ�����Ž�(1)Ϊ0
    ��Ϊ������������н�dp[0][1..k]����ʼ��Ϊ0,
    ���մ�dp[v][1..k]��ŵĸ������Ž�ȫ�����Ž�
    �����,���dpʱ�ж�dp[j][c]!=dp[j][c-1] c++,��
    �Ž���Ͳ��ܺ�����ȵ�ֵ,������������,��������,
    ֻ��Ҫ���Ž����ʵ��ѡ�����Ʒ����ȫ��ͬ,ȡ���
    ���Ž��ֵ����.
    ��ֻ��ʼ��dp[0][1]=0,���dp[v][1..k]�д�ŵĴ��Ž�,
    ʵ�����ڸ���j=v�µĴ��Ž�(ǡ��װ�������).
    */
    dp[0][1]=0;
    int t;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--){
            //�Ż�1:������Žⶼ����ǡ��װ��������Ž��������ǡ��װ��
            if(dp[j-w[i]][1]<0) continue;
            for(t=1;t<=k;t++){
                A[t]=dp[j-w[i]][t]+val[i];
                B[t]=dp[j][t];
            }
            A[t]=B[t]=-1;
            int a,b,c;
            a=b=c=1;
            while(c<=k && (A[a]!=-1 || B[b]!=-1)){
                if(A[a]>B[b])
                    dp[j][c]=A[a++];
                else
                    dp[j][c]=B[b++];
                c++;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=k;i++)//�ۼӸ��� ����������ǡ��װ�������Ž�,��dp[v][1..k]�µĸ������Ž�
        ans+=dp[v][i];
    printf("%d",ans);
    return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+100;
int d[55][maxn],tmp[55];
int main()
{
    int k,V,n;
    cin>>k>>V>>n;
    memset(d,-0x3f,sizeof(d));
    d[1][0]=0;
    for(int i=1;i<=n;i++)
    {
        int v,w;
        cin>>v>>w;
        for(int j=V;j>=v;j--)
        {
            int t1=1,t2=1,t3=k,cnt=0;
            while(t3--)
            {
                if(d[t1][j]>d[t2][j-v]+w)
                    tmp[++cnt]=d[t1++][j];
                else tmp[++cnt]=d[t2++][j-v]+w;
            }
            for(int l=1;l<=k;l++)d[l][j]=tmp[l];
        }
    }
    int ans=0;
    for(int i=1;i<=k;i++)ans+=d[i][V];
    printf("%d\n",ans);
    return 0;
}
*/

/*
//���Բ���:https://blog.csdn.net/u012350533/article/details/12361147
//��һ�ֲ���ʼ��dp[0][1]=0,����ȫ����ʼ��dpΪ0,����ʣ����������j=min(v,cur+g[i].a),
//û��̫��,��Ҫ����
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=5000+5;

int a[maxn],b[maxn];
int dp[maxn][50];

int n,k,v;


struct Goods
{
     int a, b;
     bool operator < (const Goods& r) const
     {
        return a < r.a;
     }
} g[maxn];


inline void debug()
{
     printf("where is wrong?\n");
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

inline void solve()
{
     int x,y,z,i,j,t;
     memset(dp,0,sizeof(dp));
     a[k+1]=b[k+1]=-1;
     int cur=0;
     for(i=0;i<n;i++)//n����Ʒ��
     {
         for(j=min(v,cur+g[i].a);j>=g[i].a;j--)//why? j=min(v,cur+g[i].a)
         {
             for(t=1;t<=k;t++)
             {
                 a[t]=dp[j-g[i].a][t]||j==g[i].a&&t==1?dp[j-g[i].a][t]+g[i].b:0;
                 b[t]=dp[j][t];
             }
             x=y=z=1;
             while(z<=k&&(x<=k||y<=k))
             {
                 if(a[x]>b[y])
                 {
                     dp[j][z]=a[x];
                         x++;
                 }
                 else
                 {
                     dp[j][z]=b[y];
                     y++;
                 }
                // cout << dp[j][z] << endl;//����ȥ�أ�
                // if(dp[j][z]!=dp[j][z-1])
                z++;//��ʱdp[v][k]�����k�Ž⣻
            }
         }
         cur=min(v,cur+g[i].a);//why? cur=min(v,cur+g[i].a)
     }
     int res=0;
     for(int kk=1;kk<=k;kk++)
     {
         res+=dp[v][kk];
     }
     printf("%d\n",res);
}

int main()
{
     while(scanf("%d%d%d",&k,&v,&n)!=EOF)
     {
         for(int i=0;i<n;i++)
         scanf("%d%d",&g[i].a,&g[i].b);
         sort(g, g+n);//ΪʲôҪ����
         solve();
     }
     return 0;
}
*/
