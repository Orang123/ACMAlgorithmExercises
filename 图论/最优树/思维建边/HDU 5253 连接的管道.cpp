#include<cstdio>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
//kruskal ac 421ms
/*
����:http://acm.hdu.edu.cn/showproblem.php?pid=5253
n*m����״ũ������Ϊũ��߶�,ÿ��ũ��ֻ�ܸ������������Ŀ����ڵ�ũ������ͨ,
����ũ��֮�����Ҫ�Ĺܵ�����Ϊ2ũ��߶Ȳ�,��ʹ������ũ����ͨ�����ٹܵ�����ʱ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5253
˼·:��Ϊÿ��ũ��ֻ�ܸ������������Ŀ����ڵ�ũ������ͨ,����n*m��ũ����Ҫ�Ĺܵ�����
�Ͻ�Ϊn*m*2,����n*m����,ע�⽨�ߴ������Ҵ�������ÿ�ν��ҡ���2�����������,�����ظ�����,
֮��ֱ��kruskalȥ��С������.
*/

int n,m,k,len,fa[N*N],mp[N][N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M<<1];

void init(){
    int k=n*m;
    for(int i=1;i<=k;i++)
        fa[i]=i;
    sort(edge+1,edge+1+len);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=len;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == k-1) break;
        }
    }
    return sum;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        len=0;
        scanf("%d%d",&n,&m);
        k=n*m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(j!=m)//�ұߵ����ߵ����ұ߽�Ͳ��ý�
                    edge[++len]=Edge((i-1)*m+j,(i-1)*m+j+1,abs(mp[i][j]-mp[i][j+1]));
                if(i!=n)//�±ߵ����ߵ����±߽�Ͳ��ý�
                    edge[++len]=Edge((i-1)*m+j,i*m+j,abs(mp[i][j]-mp[i+1][j]));
            }
        }
        printf("Case #%d:\n",cas);
        printf("%d\n",kruskal());
    }
    return 0;
}
