#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
typedef long long ll;
//ac 78ms
/*
����:�������Ӷ��ٱ���ʹ��ԭͼ�Ծɲ���ǿ��ͨͼ,
��ǿ��ͨͼ�������������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4635
˼·:https://blog.csdn.net/qq_34374664/article/details/78055357 �ο�����
���治�ÿ���,���Դӷ��濼��,�Ƚ�ԭͼtarjan���SCC,
��¼����SCC�е�ĸ���������,���������ĳ������,
����һ������Ϊ0�����Ϊ0��SCC �����x,����������(SCC)����һ������(�����y),
������ͼ��Ϊ2����,���ڽ��������ֶ�������ȫͼ,������ֱ�Ϊx*(x-1),
y*(y-1),������2����֮�仹û������,ʵ��������������ı�����һ�������е�
ÿһ���㶼����һ�����������е������ɵĵ����,�������ܱ�֤2���ֲ��ṹ��һ��
SCC,��ô��� ���߸��ݳ˷�ԭ��Ϊx*y,�����������ķ�ǿ��ͨͼ�ܱ���Ϊ
x*(x-1)+y*(y-1)+x*y��ȥ��������еı���m,������ܼӵı���Ϊx*(x-1)+y*(y-1)+x*y-m
��Ȼ������Ҫ����ÿ���������Ϊ0��SCC��Ϊ����������ܼӵı���,�˷�ԭ������ֵ��Ϊ��
�˷����ӵĴ�С����,ֻҪ��¼���ֵ����.

��Ȼ���Դӷ��濼��,ֱ�ӽ�����ͼ������ȫͼ,��ôֻҪ����ֳ�2����,
ȥ��2���ּ��������������ͱ�����ڵı���m,Ҳ���������ӵı�����:n*(n-1)-x*y-m
���������ǿ��ͨͼ��SCC�ĸ���Խ��������ӵı���Խ��,����ǿ��ͨͼSCC��������Ϊ2,
Ҳ����Ϊ2��SCC��ʱ��,������ӵı���������.

Ϊʲô���ǳ������Ϊ0�ĵ�SCC,�о����ѡ����Ǳȵĳ���Ȳ�Ϊ0��SCC,���ֻ��ƫС,����ƫ��,
�е��ɻ�.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],inde[N],outde[N],amout[N];
stack<int> s;
struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            amout[id]++;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int T,u,v,cas=0;
    ll ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        ans=cnt=num=id=0;
        memset(dfn,0,sizeof dfn);
        memset(head,-1,sizeof head);
        memset(amout,0,sizeof amout);
        memset(inde,0,sizeof inde);
        memset(outde,0,sizeof outde);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id == 1){//ֻ��һ��SCC,�������SCG(ǿ��ͨͼ)
            printf("Case %d: -1\n",cas);
            continue;
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u] != block[v]){
                inde[block[v]]++;
                outde[block[u]]++;
            }
        }
        ll x,y;
        for(int i=1;i<=id;i++){
            if(!inde[i] || !outde[i]){
                x=amout[i],y=n-x;
                ans=max(ans,x*(x-1)+y*(y-1)+x*y-m);
                //��x*y��С��ʱ��ֵ���,��x��y�������ʱ����ǳ˻���С��,
                //����Ҳ����ֱ����SCC�е�����С��,ֻ����һ�ξͿɴ�������ӱ���
                //ans=max(ans,n*(n-1)-x*y-m);
            }
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
