#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200100
using namespace std;

/*
����:��һ��n���ڵ����,ѡ�������ڵ�ʹ���������ɵ�·�����ಢ��ֵ���.
����:https://codeforces.ml/problemset/problem/1294/F
˼·:�����㹹�ɵ�·����һ����������ֱ��,���������ֱ���������˵�,
��������ڵ���ѡȡ����ֱ�����˵���������һ��.
*/

int cnt,n,head[N],dis1[N],dis2[N],ans,st,d;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis1[u]>=ans){//��������Ǵ��ڵ���,��Ϊ�ڶ���dfs,�п����Ҳ�����֮ǰ�����ans,����ֱ������һ���˵㻹����Ҫ��¼��
        ans=dis1[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis1[v]=dis1[u]+1;
        dfs(v,u);
    }
}

int main(){
    int u,v,a,b,c;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    ans=-1;
    dfs(1,-1);
    a=st;
    dis1[st]=0;
    dfs(st,-1);//����ֱ��
    b=st;
    d=ans;
    for(int i=1;i<=n;i++)
        dis2[i]=dis1[i];//dis2��¼����ֱ��a�˵�ľ���
    dis1[st]=0;
    dfs(st,-1);//dis1��¼����ֱ��b�˵�ľ���
    dis1[st]=0;
    ans=-1;
    for(int i=1;i<=n;i++){
        if(i == a || i == b) continue;//�п�����������һ��ֱ��,ѡȡ�������㶼�ǲ�ͬ��������,ֱ���п��ܻ�ѡȡ2����ͬ�ĵ㵫�����Ȼ������
        if(dis1[i]+dis2[i]+d>ans){
            ans=dis1[i]+dis2[i]+d;
            c=i;
        }
    }
    printf("%d\n",ans/2);//ֻ����ʵ��·���ߵĲ���Ȩ,��dis1[i]+dis2[i]+d�պ��ظ�������2��
    printf("%d %d %d\n",a,b,c);
    return 0;
}
