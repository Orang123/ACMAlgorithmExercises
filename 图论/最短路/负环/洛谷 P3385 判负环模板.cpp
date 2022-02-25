#include<cstdio>
#include<cstring>
#include<queue>
#define N 3500//100��
#define INF 0x3f3f3f3f
using namespace std;
//spfa bfs�и���
/*
����:https://www.luogu.com.cn/problem/P3385
����:https://www.luogu.com.cn/problem/P3385
˼·:spfa�и���
*/

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[1]=0;
    for(int i=2;i<=n;i++)
        dis[i]=INF;//�����ʼ��Ϊ����С,��ΪҪ���·,����Դ���ɳں�Ϳɸ���
}

bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);
    vis[u]=1;
    num[u]++;
    while(!Q.empty()){
        u=Q.front();
        vis[u]=0;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){//�ɳ��ж� �·
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                 /*
                �ж��Ƿ���ڸ���,������ÿ�������ֻ�ɱ����Լ���n-1���㹹�ɵ�·���ɳ�,
                ����n��·����ʼ��������ɳ�ʱ���·��һ�������˸���,��Ϊ��һ����֮ǰ��n-1��·���е�����һ���ظ���,
                �����ٶ��ɳھ�����Ϊ����Ȩֵ��Ϊ�����ŵ������ɳ�ֵԽ��ԽС
                */
                if(num[v] >= n) return false;//���� ע����>= �Ż����� ���ϵİ���������>n �е㲻��,>=nҲ��ac��
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
       int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(num,0,sizeof(num));
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//�������ﹹ�����·ģ�� ��ȡ���ֵ
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        if(SPFA(1)) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}

/*
//dfs�и���
//���������е㿴����,�����һ��������·�����ڸ���������ܽ���,����������ȱ��� ���һֱû�б��������ڸ�����·��,Ч��Ҳ�Ƚϵ�,
//��bfs��α����ǰ��ձ���������,����ƽ������ÿ��·����������� ����,���Ե����ָ���ʱ,����֮ǰ������̫��������·��ȥ����
//������� spfa�����и������׼������
#include<cstdio>
#include<cstring>
#define N 3500//��ȵ����� ��ǿ,һ��������ʱ��,91��
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[1]=0;
    for(int i=2;i<=n;i++)
        dis[i]=INF;
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//�ɳ��ж� ���·
            dis[v]=dis[u]+edge[i].w;
            //����ڶ��η��ʵ��õ�(˵�������˻�),��Ϊ��dfs�����������ԭ�ȵ�����·��һ·���ʵ���,
            //�˹���Ȩֵ�����������ǲ����ۼӱ��Ĺ���,���ڶ��η����ٶȱ�ø�С��
            //ֻ��˵�������ɵĻ�Ȩֵ��Ϊ��������˲����ڵڶ��η���ʱ�õ��ɳ�,˵���ڷ��ʵĹ����й����˸���,֮��ͻ�������ȫ����ջ
            //�������spfa�и�����ȻЧ�ʸ�,���ڶ��η��ʵ���ʱ��Ϳ����ж�����,��spfa��Ҫ��������n�β�����ʽ�ж�
            if(vis[v]) return false;
            if(!dfs(v)) return false;//û�и����ͳ�����һ�����Ƿ񹹳ɸ���
        }
    }
    vis[u]=0;
    return true;//û�и����������˳�
}
int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        cnt=0;
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//���ﹹ�����·ģ�� ��ȡ���ֵ
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        if(dfs(1)) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
*/

/*
//���memset(dis,0,sizeof(dis))���߸�Ȩ�ߵ����� ���Ǵ���һ��żȻ��,��Щ����,��׼�������ǽ���spfa�и���
//���һ�����Ե㳬ʱ,һ�����Ե�wa 82��,�������ٲ���,
//���Ҵ�����ȻҪ���1����,������������Ļ���Ϊ�ǴӸ�Ȩ�߿�ʼ����,�����Ҫÿ���㶼��Ϊ��㳢��dfs���ܱ�֤�����ȷ
#include<cstdio>
#include<cstring>
#define N 3500
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//�ɳ��ж� ���·
            dis[v]=dis[u]+edge[i].w;
            if(vis[v]) return false;
            if(!dfs(v)) return false;//û�и����ͳ�����һ�����Ƿ񹹳ɸ���
        }
    }
    vis[u]=0;
    return true;//û�и����������˳�
}
int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//���ﹹ�����·ģ�� ��ȡ���ֵ
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
        	init();
        	if(!dfs(i)){
        		flag=1;
        		break;
			}
		}
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
*/
