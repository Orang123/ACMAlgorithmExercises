#include<cstdio>
#include<cstring>
#define N 250
using namespace std;
//2008 Asia Harbin Regional Contest
//ac 31ms dfs����Ⱦɫ����2������
/*
����:n��ѧ����m���໥��ʶ�Ĺ�ϵ,����Ҫ�����е�ѧ���ֳ�����,
ʹ��ͬ���ڵ�ѧ���໥֮�䲻��ʶ,�����������������,�ͽ��໥��ʶ��һ��ѧ��
���ŵ�˫�˼�,����������ܰ��ż���ѧ����˫�˼�.
����:�ж�m�Թ�ϵ���ɵ�ͼ�Ƿ񿴻���Ϊ����ͼ,�������"No",�����������ƥ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2444
˼·:�ж��Ƿ��Ƕ���ͼ,�����ж�ԭͼ�Ƿ���ڳ���Ϊ�����Ļ�·,���������Ƕ���ͼ,
�������ڳ���Ϊ�����Ļ�·,��Ϊ����ͼ,ֱ��������������ƥ��.�жϻ�·���ȵ���ż��
������dfs/bfs���н���Ⱦɫ,���ڰ׺ڰ�...�׺� 010101...10����,���ĳ�����ѱ�������
�ҵ�һ����·,�жϵ�ǰ����������ĵ��Ⱦɫ�Ƿ���ͬ,����ͬ��û�·����һ��Ϊ����,��
����ͬ���·����Ϊż��.֮������������ͼ������ƥ��,���Ҫ��2,��Ϊ��û�н��㻮�ֿ�,
�Ǵ����е㿼��ƥ���.��ʵ���Ը���Ⱦɫ��Ľ��,ȾɫΪ0��Ϊ�󼯺�,1��Ϊ�Ҽ���,ֻ����
�󼯺��е���������ȥ���,����ֱ������������,�ܵĸ��Ӷ�Ҳ�ή��.

why���ڳ���Ϊ�����Ļ�·�Ͳ��Ƕ���ͼ?
������ڳ���Ϊ�����Ļ�·,eg:1-2-3-1,�����1��2�ֱ�ŵ�����2��������,
��ô3��1��2��������,3���ܷ����κ�һ��������,�޷�����3�ŵ��ĸ�������,
��Ҫԭ����3ͬʱ�������󼯺Ϻ��Ҽ����еĵ�,�������޷����ֵ�����2��������.
���1��3�ŵ����Ҽ���,��ô2Ҳͬ���޷�����;ͬ��2��3�ŵ����Ҽ���,��ô1�޷�����.
���Ƕ��ڳ���Ϊż���Ļ�·,eg:1-2-3-4-1,1��2��3��4���Էֱ���������ҡ����Ҽ�����,
������е�ԭ����ÿ�������ӵ��������Ҫô�����󼯺�Ҫô�����Ҽ���,�������Ϳ��Ի��ֵ��Ҽ��ϻ��󼯺�.
��Ϊ����Ϊż���Ļ�·,β����ӵĵ�(ʵ���ײ�)��β����ǰ����ɫ�պ�����ͬ��,������Ϊ����,ǰ����ɫ��β����ӵ�
��ɫ�ǲ�ͬ��,��͵��¸õ��޷����������Ҽ���.

����ͼת��Ϊ����ͼ��Ҫ���ֵ��������Ͽ�ͨ������Ⱦɫ������,���������滷,����ɫΪ0(��ɫ)�ĵ����Ϊһ������,
��ɫΪ1(��ɫ)�ĵ����Ϊ��һ������.
*/
int n,m,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];//��ı������ܴﵽ��ȫͼ��Ϊ������ͼ����*2 N*(N-1)/2*2=N*(N-1)

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}
//vis[u]==0,����u����ɫΪ��ɫ;vis[u]==1,����u����ɫΪ��ɫ
//vis[u]==-1,����u�㻹δȾɫ,��δ����.
int dfs(int u,int fa,int color){
    vis[u]=color;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//ǰ���ڵ����ɫ�͵�ǰ�ڵ�϶��ǲ�ͬ��
        if(vis[v]!=-1){//���v�ڵ��Ѿ���Ⱦɫ,�������˻�·,�жϵ�ǰ�ڵ�u��v����ɫ�Ƿ���ͬ
            if(vis[u] == vis[v]) return 1;//��ɫ��ͬ,��·����Ϊ����,�޷����ֳɶ���ͼ.
            continue;//������ɫ��ͬ��·����Ϊż��,����������(������ѭ��)
        }
        if(dfs(v,u,color^1)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,-1,sizeof(vis));//��ʼ��δȾɫ���-1
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i] == -1){
                if(dfs(i,-1,0)){//�������·,���Ƕ���ͼ���"No"
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){//ö�����е�(2�������е����е�)ȥƥ��� ���Ҫ��2
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}

/*
//ac 15ms ���ݽ���Ⱦɫ����ԭͼ��Ϊ��ɫΪ0(��ɫ)��1(��ɫ)����������,
//�����������ƥ��ֻ��������һ�����ϵĵ�,����ʱ�临�Ӷ�.
#include<cstdio>
#include<cstring>
#define N 250
using namespace std;

int n,m,cnt,head[N],color[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa,int col){
    color[u]=col;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(color[v]!=-1){
            if(color[u] == color[v]) return 1;
            continue;
        }
        if(dfs(v,u,col^1)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(color,-1,sizeof(color));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(color[i] == -1){
                if(dfs(i,-1,0)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            //����ֻ������ɫΪ0����ɫ�ļ����еĵ�,��������2,ֱ�����,Ҳ����ֻ������ɫΪ1(��ɫ)�����еĵ�
            if(color[i]) continue;
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 31ms bfs����Ⱦɫ����2������
#include<cstdio>
#include<cstring>
#include<queue>
#define N 250
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int bfs(int s,int color){
    queue<int> Q;
    vis[s]=color;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(vis[v]!=-1){
                if(vis[v] == vis[u]) return 1;
                continue;
            }
            vis[v]=vis[u]^1;
            Q.push(v);
        }
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i] == -1){
                if(bfs(i,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/

/*
//ac 31ms (len[u]-len[v]+1) & 1 �ж�dfs��¼·����ÿ����ĳ���,����+1����������·�ĳ���
//���ﲻ������ȱ���һ����֧,�ٱ�����һ����֧������һ����֧��·,
//����ʱ���¼����������Ⱥ�,��֧���ڵĳ�����������,��Ϊ�����������������߾ͻ�һ·������ȥ,
//ֱ�����ֱ������ĵ㹹�ɻ�,u���v��(�ѷ��ʵĵ�)��Զ��һ����֧��,len[u]-len[v]+1���ǻ�·�ĳ���.
#include<cstdio>
#include<cstring>
#define N 250
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans,len[N];
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(vis[v]){
            //v������u�����,len[u]-len[v] ����v��ǰ��û�õĲ��ֵĳ���,+1��ָu��v�������ɻ�����һ����
            //��Ϊ��������� �ᱣ֤u��v��ͬһ������
            if((len[v]-len[u]+1) & 1) return 1;
            continue;
        }
        len[v]=len[u]+1;
        if(dfs(v,u)) return 1;
    }
    return 0;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || hungary(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(len,0,sizeof(len));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                if(dfs(i,-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag){
            printf("No\n");
            continue;
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/
