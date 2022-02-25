#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF -0x3f3f3f3f
using namespace std;
//�ֲ�ͼ���·
//����ڶ��ַ����Ƿ��򽨱�
/*
����:n������,m����·,һ����Ʒ��ÿ�����еļ۸񶼲�ͬ,
���ڴ�1����,ѡ����ĳ����������,ĳ����������,ʹ�ò��
���,��׬ȡ�������,�����ܻص�n��,�������,����֮��
��·����û�л���.
����:https://www.luogu.com.cn/problem/P1073
˼·:����������̿��Է�Ϊ�����׶�
1.��1����ѡ����ĳ���������� ��0��
2.֮����ѡ����ĳ����������  ��1��
3.������Ҫ�ص�n��           ��2��
�����Կ��Թ���һ��3��ķֲ�ͼ�·.
���е�0�㵽��1�������ߴ�����ĳ������,��ȨΪ��.
��1�㵽��2�������ߴ�����ĳ������,��ȨΪ��.�����Ȩ��Ϊ0.
����ͨ�������ֲ�ͼ�Ϳɽ���Ȩת��Ϊ��Ȩ����ת��Ϊһ�����·ģ��ȥ���.
*/

int n,m,cnt,head[N*3],vis[N*3],dis[N*3];
//����ͼ ������ȫ��˫����� (M*3)<<1+������������2*N
struct Node{
    int to,next,w;
}edge[((M*3)<<1)+N*2];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,-0x3f,sizeof(dis));
    dis[s]=0;
}
//ע��Dijkstra��Ϊ̰��˼ά,��������������
void spfa(int s){
    queue<int> Q;
    init(s);
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]<dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,z;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&z);
        addEdge(i,i+n,-z);//��0�㵽��1������,������i������
        addEdge(i+n,i+2*n,z);//��1�㵽��2������,������i������
    }
    while(m--){
        scanf("%d%d%d",&u,&v,&z);
        addEdge(u,v,0);//����ͼ��ĵ�·��Ȩ��Ϊ0
        addEdge(u+n,v+n,0);
        addEdge(u+2*n,v+2*n,0);
        if(z == 2){//z==2 ����˫���
            addEdge(v,u,0);
            addEdge(v+n,u+n,0);
            addEdge(v+2*n,u+2*n,0);
        }
    }
    spfa(1);//�����1��3*n�ڵ���· 3*n�ڵ�����ڵ�2��������ɺ�ص�n�ڵ�
    if(dis[3*n]!=INF) printf("%d",dis[3*n]);
    else printf("0");
    return 0;
}

/*
//��������� �ֱ��1��n��ʼ��2��spfa,��¼·����С��Ȩ������Ȩ
//ȡdis2[i]-dis1[i]���ֵ
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt1,cnt2,head1[N],head2[N],vis[N],dis1[N],dis2[N],val[N];

struct Node{
    int to,next;
}edge1[M<<1],edge2[M<<1];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node){to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node){to,head2[from]};
    head2[from]=cnt2++;
}
//����1��v��·���ϵ���С��Ȩ ʵ�ʾ�������ĵ��ܵ��ﵱǰv�� ����˫��߶����п��ܻ��ظ�����,
//�ٴλص�ǰ���ڵ� ������Сֵ ����������4�ڵ� ʵ�ʱ�����1->4->5->4,4�㱻����������
void spfa1(int s){
    memset(vis,0,sizeof(vis));
    memset(dis1,0x3f,sizeof(dis1));
    dis1[s]=val[s];
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head1[u];i!=-1;i=edge1[i].next){
            v=edge1[i].to;
            if(dis1[v]>min(dis1[u],val[v])){
                dis1[v]=min(dis1[u],val[v]);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}
//����n��v��·���ϵ�����Ȩ ʵ�ʾ���v���ܵ��������ĵ�(���ֵ)
//ʵ�ʶ������� 5����ظ��������� ��5->4->5
void spfa2(int s){
    memset(vis,0,sizeof(vis));
    memset(dis2,-0x3f,sizeof(dis2));
    dis2[s]=val[s];
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head2[u];i!=-1;i=edge2[i].next){
            v=edge2[i].to;
            if(dis2[v]<max(dis2[u],val[v])){
                dis2[v]=max(dis2[u],val[v]);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,z,ans=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    while(m--){
        scanf("%d%d%d",&u,&v,&z);
        addEdge1(u,v);
        //��������� ����n�ܵ�i,��ô��������߶��Ծ�һ���ܴ�i��n,����������ۻ����ϲ��ܱ�֤�ܵ���n��
        addEdge2(v,u);
        if(z == 2){
            addEdge1(v,u);
            addEdge2(u,v);
        }
    }
    spfa1(1);
    spfa2(n);
    for(int i=1;i<=n;i++)
        ans=max(ans,dis2[i]-dis1[i]);
    printf("%d",ans);
    return 0;
}
*/

/*
//ac ��ͼdfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define N 51000
#define M 500100
using namespace std;

int n,m,head[N],cnt,ans,val[N],pric[N],mi[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//minv Ҫ��Ϊ��ʱ��������,����ȫ�ֱ���,��¼��ĳ����Сֵ,
//����һ�λ��ݵ���һ��·��ʱ,ԭ�������Сֵ���µ�·�����ܲ�������ͨ��.
//��������dp�������ǱȽϱ�����,�о�ʵ��Ч�ʲ�����,���ݼ�ǿһЩ�ͻ�TLE

void dfs(int u,int fa,int minv){
    int flag=1,tmp;
    minv=min(minv,val[u]);
    //mi�����¼�����ܹ����ʵ��õ������·���еļ�ֵ����Сֵ,
    //�����Ǽ�֦ �����ظ�����,��֮ǰ��·������˫���,
    //��������С��ֵ�ܷ��ʵ���ȱ�������һ��·��ʱ,������������·����������һ��·����ȱ�����,
    //����·���ĸ�����mi��¼�������Сֵ,�����ʼ��һ�η�������ֲ�������ȥ��������һ��·��ʱ�Ͳ����ظ�����,
    //��Ϊmi[i]�����Ѿ���¼��֮ǰ����Сֵ,��Ȼ��ʱ��minx�������ȿ�ʼ�Ľϴ�ֵ,��˲�����mi[u]>minv.
    if(mi[u]>minv){//����·���õ���ʹ�����Сֵ�Ƿ�ȵ�ǰ��������������Сֵ��,���������
        mi[u]=minv;
        flag=0;
    }
    tmp=max(pric[fa],val[u]-minv);//��¼�����
    if(tmp>pric[u]){//�ж��Ƿ��֮ǰ�Ĳ�۸���
        pric[u]=tmp;
        flag=0;
    }
    if(flag) return;//���������������һ�� �ɼ�������,�������.
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,u,minv);
    }
}

int main(){
    int u,v,z;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) mi[i]=INF;
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&z);
        addEdge(u,v);
        if(z == 2) addEdge(v,u);
    }
    dfs(1,0,INF);//����ô�1��ʼ,��Ϊ�ӱ�ĵ㿪ʼ ���ܻᵼ��,������޷�������ǰ�����������:�ȱ�����ֵС���ٱ�����ֵ������.
    printf("%d\n",pric[n]);
    return 0;
}
*/

/*
//���м��仯����������,������̫�����
//Ҳ��tarjan���� ������̫�����,Ҳ�е�û��Ҫǿ����tarjanȥ��
*/
