#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
typedef long long ll;
//ac 109ms
/*
����:n��ը��,ÿ��ը��������ͱ�ը�뾶��Χ�������ɱ�,���ը��A����
ը��B�ľ���С�ڵ���ը��A��ը�뾶,������ը��A��ͬʱ����ը��B,��������.
�����ʽ�����ը���������������С����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5934
˼·:���ȱ���O(N^2)ö����ȫͼ���п��ܵı�,����ը��A��B֮��ľ���С�ڵ���A�ı�ը�뾶,
�򽨵����A->B.֮����tarjan����SCC ���������SCC�е�����ը������С����,��ô���
SCC��ֻ�����������С���ѵ�ը��,����ը���Ͷ�������,֮������ͳ�Ƹ���������.�������
Ϊ0�ĵ�,��ôֻ��Ҫ�ۼ��������Ϊ0�ĵ��SCC�е���С���Ѿ�����������ը������С����,��Ϊ
���Ϊ0�ĵ�û�б�ָ����,������ͨ����������������.
*/

int n,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],minVal[N],inde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

struct Point{
    double x,y,r;
    int c;
}point[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

double getDis(double x1,double y1,double x2,double y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
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
            block[v]=id;
            minVal[id]=min(minVal[id],point[v].c);//��¼SCC�е���С����
        }while(v!=u);
    }
}

int main(){
    int T,u,v,cas=0;
    double w;
    scanf("%d",&T);
    while(T--){
        cas++;
        id=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(inde,0,sizeof inde);
        memset(minVal,0x3f,sizeof minVal);
        memset(head,-1,sizeof head);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%lf%d",&point[i].x,&point[i].y,&point[i].r,&point[i].c);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                if(w<=point[i].r*point[i].r) addEdge(i,j);//i j��ľ���С�ڵ���i�ı�ը�뾶,��i->j
                if(w<=point[j].r*point[j].r) addEdge(j,i);
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from,v=edge[i].to;
            if(block[u]!=block[v])
                inde[block[v]]++;
        }
        ll sum=0;
        for(int i=1;i<=id;i++){
            if(!inde[i])//�ۼ����Ϊ0��SCC����С����
                sum+=minVal[i];
        }
        printf("Case #%d: %lld\n",cas,sum);
    }
    return 0;
}
