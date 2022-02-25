#include<cstdio>
#include<algorithm>
#define N 550
#define M 25500
#define INF 0x3f3f3f3f
using namespace std;
//ac 686ms  ���ݸĹ� ֮ǰ��ͨ�Ĳ��鼯�ϲ���TLE,��Ҫ�����������ʽ�ϲ�
//����wa�˺ܶ�� ����Ϊ����ͨ������ж�û����cnt!=n-1��ѭ�����ж�,
//����ѭ����flag���,ʵ��������ͨ�������Ѿ�������n�����ʱ�ӱ�����δkurskal֮ǰ�Ѿ��ﵽn-1
/*
����:n������,m����·��Ҫ�޽�,�Ѿ���t������Ⱥ�໥��ͨ,����
��t������Ⱥ֮�䲻��Ҫ���޽���·,��ʹ�����г����໥��ͨ�޽�
��·����ͷ����Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3371
˼·:������Ⱥ�г���fa[N]���鶼���ӽ�����,����һ��kruskal��������ʽ�ϲ�����.
*/

int n,m,k,fa[N],seq[N],cnt;

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    int x,y,sum=0;
    //������ڲ��ܹ����������������flag���,��Ϊ�п������е���ͨ���Ѿ���n������������,
    //��������������ѭ��,����cnt=n-1,��ʱ������Ϊ����ͨ.
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    if(cnt != n-1) sum=-1;
    return sum;
}

int main(){
    int T,num,x,y;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        init();
        while(k--){
            scanf("%d",&num);
            for(int i=0;i<num;i++){
                scanf("%d",&x);
                seq[i]=x;
                x=find(seq[i]);
                y=find(seq[0]);
                if(x!=y){
                    fa[x]=y;
                    cnt++;
                }
            }
        }
        //for(int i=1;i<=n;i++) ����������ͨ�����˶��ٱ� Ҳ������������
            //if(fa[i]!=i) cnt++;
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
https://www.cnblogs.com/liyinggang/p/5471493.html ����ʽ�ϲ�
����ʽ�ϲ�������ʽ�ϲ���Ϊ�˽���ϲ����������˻��������������dep[i]��ʾ��Ϊi�����������ȣ�
�ϲ�ra��rbʱ������������С���������ȴ�Ľ��к� ���������������������һ���������ѡ��һ����Ϊ����
���ҽ�����������dep����1���������ĺô�����n�β������κ�һ�ü������������ȶ����ᳬ��log(n)��
����ʹ�ò��ҵĸ��ӶȽ�ΪO( log(n) ����
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 505;
const int M = 25000;
struct Edge
{
    int s,e,len;
} edge[M];
int father[N],n,m,k;
int dep[N];
int _find(int x)
{
    if(x==father[x])return x;
    return _find(father[x]);
}
int cmp(Edge a,Edge b)
{
    return a.len<b.len;
}
int kruskal(int m)
{
    sort(edge+1,edge+m+1,cmp);
    int cost = 0;
    for(int i=1; i<=m; i++)
    {
        int x  = _find(edge[i].s);
        int y  = _find(edge[i].e);
        if(x!=y)
        {
            if(dep[x]==dep[y])
            {
                father[x] = y;
                dep[y]++;
            }
            else if(dep[x]<dep[y])
            {
                father[x] = y;
            }
            else
            {
                father[y]=x;
            }
            cost += edge[i].len;
        }
    }
    return cost;
}
int main()
{
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1; i<=n; i++)
        {
            father[i] = i;
            dep[i] =0;
        }
        for(int i=1; i<=m; i++)
        {
            scanf("%d%d%d",&edge[i].s,&edge[i].e,&edge[i].len);
        }
        while(k--)
        {
            int t,a;
            scanf("%d%d",&t,&a);
            t--;
            while(t--)
            {
                int b;
                scanf("%d",&b);
                int x = _find(a);
                int y = _find(b);
                if(x!=y)
                {
                    if(dep[x]==dep[y])
                    {
                        father[x] = y;
                        dep[y]++;
                    }
                    else if(dep[x]<dep[y])
                    {
                        father[x] = y;
                    }
                    else
                    {
                        father[y]=x;
                    }
                }
            }
        }
        int ans = 0;
        int cost = kruskal(m);
        for(int i=1; i<=n; i++)
        {
            if(father[i]==i) ans++;
        }
        if(ans==1)printf("%d\n",cost);
        else printf("-1\n");
    }
}
*/
