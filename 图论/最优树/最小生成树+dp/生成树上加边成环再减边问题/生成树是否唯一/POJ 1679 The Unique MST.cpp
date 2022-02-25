#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 105
using namespace std;
//��6������ ���һ��+kruskal+lca��û��
//������n-1��kurskal�жϷ� ac 16ms
/*
����:�ж���С�������Ƿ�Ψһ.
����:http://poj.org/problem?id=1679
˼·:��Ϊn<=100,��������һ��kurskal���mstȨֵ��,�ٳ���ɾ��ԭmst
�е�ÿһ����,��kruskal�ж��Ƿ�Ȩֵ�ͺ�֮ǰһ��,�����һ����,��mst
��Ψһ,���ȫ����һ��,��ômst��Ψһ��.ʱ�临�Ӷ�O(nmlogm)
*/

struct node{
    int x,y,price;
    bool operator < (const node &a)const{
        return price<a.price;
    }
}edge[N*N];
int vertex[N],n,m;
bool visit[N*N/2];//ע���������ж�ɾ����������,�����СӦ��N*N,�������жϵ� �����С����N,����������Խ���쳣,poj�����Ŀ��re���ᱨ,�ᱨwa

void init(){
    for(int i=1;i<=n;i++){
        vertex[i]=i;
    }
}
int find0(int x){
    if(vertex[x]!=x)
        return vertex[x]=find0(vertex[x]);
    return x;
}
bool unionSet(int x,int y){
    int x0=find0(x);
    int y0=find0(y);
    if(x0!=y0){
        vertex[x0]=y0;
        return true;
    }
    else
        return false;
}
int kruskal(){
    int sum=0,cnt=0;
    init();
    for(int i=0;i<m;i++){
        if(unionSet(edge[i].x,edge[i].y)){
            visit[i]=true;
            sum+=edge[i].price;
            cnt++;
            if(cnt == n-1) return sum;
        }
    }
    return sum;//������Ϊ �п���m=0���б�ȨΪ0�ı�,ʵ����С��Ȩ��Ϊ0,��������������-1,���Ե�������������ʱҲͳһ�����Ȩ��0
}

int subEdge(int num){
    int sum=0,cnt=0;
    init();
    for(int i=0;i<m;i++){
        if(i!=num&&unionSet(edge[i].x,edge[i].y)){//�ܿ�֮ǰ��С�����Ϊnum�ı߿����ܲ��ܹ���Ȩ��һ������С��
            sum+=edge[i].price;
            cnt++;
            if(cnt == n-1) return sum;
        }
    }
    return -1;
}

int main(){
    int t,sum,ans;
    int flag;
    scanf("%d",&t);
    while(t--){
        memset(visit,false,sizeof(visit));
        flag=0;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
            scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].price);
        sort(edge,edge+m);
        sum=kruskal();
        /*
        ������������� ǰ��߷ǳ�С������߷ǳ�����������ι��ɵĲ�Ψһ��С��,
        ��Ϊ������ǰ���С�ı�,�ǵ�һ�ε���С��һ���Ὣ��Щ�߰�����ȥ��,
        ���Ի��ǵÿ�����û�к�ԭ����С��������Ȩһ���ı߿��Ƿ��ܹ�����.
        */
        for(int i=0;i<m;i++){
            if(visit[i]){//���ų���ɾ��ԭ����С����ÿһ����,��������ܹ�����Ȩ����ͬ����С��
                ans=subEdge(i);
                if(ans==sum){
                    flag=1;
                    break;
                }
            }
        }
        if(flag)
            printf("Not Unique!\n");
        else
            printf("%d\n",sum);
    }
    return 0;
}

/*
//ac 0 ms 676K �ڶ��������
//�ӱ߳ɻ�,�ټ���,�ָ�������,��������ߵ������ӱ�,��mst��Ψһ.
//prim+dpͳ�Ƴ�������������·���ϵ�����Ȩ,�ж�û�����������ı����˵��ϵ�mst�е�����Ȩ�Ƿ�͸ñ�Ȩ���,
//������,��˵����������Ψһ.���δ����ı�û��һ��������·������Ȩ���,����������Ψһ��.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define N 105
#define M 10005
#define INF 0x3f3f3f3f
using namespace std;
bool vis[N],used[N][N];
//pre[i] ��¼i����ǰ�����,maxLen[i][j]��¼mst��·��i��j֮��ߵ����Ȩֵ,��Ҳ�Ƿ�mst�еı߻����Ȩֵ��ȵĿ������
int cnt,head[N],dis[N],pre[N],maxLen[N][N],sum,seq[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

int getCost(int u,int v){
    for(int i=head[u];i!=-1;i=edge[i].next){
        if(edge[i].to == v) return edge[i].w;
    }
    return -1;
}

void init(){
    sum=cnt=0;
    memset(vis,false,sizeof(vis));
    memset(used,false,sizeof(used));
    memset(maxLen,0,sizeof(maxLen));//maxLen[v][v]�Լ����Լ�,����һ����·��ʱҪ�õ�,Ҫ��ʼ��Ϊ0
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));//����ʱ��memset INF �����
    memset(pre,0,sizeof(pre));//Ҫ��ʼ����һ������ĵ��pre[s]=s
}
//����˼����ǿ��ǲ���mst�еı���Щ���ܵ�Ȩֵ�����mst�еı����
void prim(int n){
    priority_queue<pair<int,int> > Q;
    dis[1]=0;//��СȨ��һ��Դ���ۼ�ʱ,��û�б�.Ӧ��Ϊ0
    Q.push(make_pair(dis[1],1));
    int u,v,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        used[pre[u]][u]=used[u][pre[u]]=true;//����������������Ѿ�����mst(Minimum Spanning Tree)��
        sum+=dis[u];//�ۼ�mstȨֵ��
        //���Ѿ�����mst�еĵ�,ö��ÿһ����i,��¼��i��u·���бߵ����Ȩֵ,ע��i��u֮������кܶ��,
        //��һ����ֱ�����ӵ�,seq[i]=uʱ,·��Ϊi��i���Ի�������,�����¼,����¼��maxLen[u][u]����ֵ,��Ϊ0,
        //��ô���´μ����±�ʱ,seq[i]=pre[u],maxLen[seq[i]][u]=max(maxLen[pre[u]][pre[u]],dis[u])
        //�������ֵ�϶���dis[u],���п��ܾ�ȡ����maxLen[pre[u]][pre[u]],�ᵼ�º����Ľ�������,
        //��Ȼ��������ݽ���,�պ�ÿ�ζ��ϴ�Ķ���dis[u],����Ҳˮ����
        for(int i=1;i<=num;i++)
            //�Ƚ�seq[i]��pre[u]·���е����Ȩֵ���¼���ı�pre[u]��u��Ȩֵ,ȡ���ֵ
            //maxLen[seq[i]][pre[u]]֮ǰ�ǿ϶���¼����,����Ϊʲôȡ���ֵ,������С��
            //����ĳ��·���м���һ����ʱ���ػṹ�ɻ�·�������������һ���Ǵ��ڵ��ڸ�·����
            //Ȩֵ���ı�,��Ȼ������һ��ʼ������С��������ı���.����˵i��u��·��
            //������ȡ�Ĳ�������,���ڹ���mst�����ʱ,ʵ�����ǲ���������������С�ıߵ�,
            //��Ϊ����ѡ��Ľϴ����mst��Ȩ��һ��������С��,mstÿ����ȡ�Ķ��Ǿ��뵱ǰmst
            //���ϵ��������ĵ�,�������С�ı�Ҳ�ᱻ��ǰ�ϲ�,����������������ӽϴ�ߵĺ��档
            //���Է�mst�еı�һ���Ǵ��ڵ���mst��·�������Ȩֵ�ߵġ���������ֻ����ȷ����mst�б�
            //��ֵ���ܻ��mstĳ��·���е�������Ȩֵ��ͬ,���պ���ͬʱ������滻,����mst�㲻Ψһ.

            //��seq[i]=pre[u]ʱ,��ȻmaxLen[pre[u]][u]����Ϊ����mst�ڵı�,������Ϊ��mst��ȥ�Ƚ�Ȩֵ�Ƿ�
            //��ȿ����,�����ﻹҪ��¼��ֵ��Ϊ�����ӱ��ڼ�¼maxLen���Ƿ���õ�maxLen[seq[i]][pre[u]]��ֵȥ�Ƚ�
            maxLen[seq[i]][u]=maxLen[u][seq[i]]=max(maxLen[seq[i]][pre[u]],dis[u]);//֮����Ҳ��¼�����maxLen[u][i]��Ϊ�˵�ʱ�Ƚϵ�ʱ���п��ܻ������ж�u->i������,��ô���Խ����жϳ���Ψһ��
        num++;
        seq[num]=u;//���Ѿ�����ĵ���� seq���� ��maxLen[seq[i]][u] dp���,�ټ���u��,��Ϊ���ܸı�maxLen[u][u]��ֵ
        if(num == n) break;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && dis[v]>edge[i].w){
                dis[v]=edge[i].w;
                pre[v]=u;//��¼��ǰ�������mst�����о�����С�ĵ��ǰ���ڵ�,�������maxLen
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int t,n,m,u,v,w;
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
        }
        prim(n);
        bool flag=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int val=getCost(i,j);
                if(!used[i][j] && val!=-1 && val == maxLen[i][j]){//�ж�δ����mst�еı� �Ƿ���ܺ�ԭ��mst�е�ĳ�������,�����,����滻,mst�Ͳ�Ψһ
                    flag=true;
                    break;
                }
            }
            if(flag) break;
        }
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",sum);
    }
    return 0;
}

*/

/*
//������������� ac 0ms
//ֱ����primÿ�μ�����뼯��mst�о�����̵ĵ�vʱ,���ж��Ѿ���mst�еĵ�
//u(������v�������ӵ�ǰ���ڵ�)����û�е�vδ����mst�ı�Ȩ�͵�ǰ����ı����,
//�����,��˵��mst��Ψһ,���ȫ����û��,��˵��mst��Ψһ��.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define N 105
#define M 10005
#define INF 0x3f3f3f3f
using namespace std;
bool vis[N],used[N][N],flag;
int map0[N][N],dis[N],pre[N],sum,seq[N];

void init(){
    sum=0;
    flag=false;
    memset(map0,INF,sizeof(map0));
    memset(vis,false,sizeof(vis));
    memset(used,false,sizeof(used));
    memset(dis,INF,sizeof(dis));//����ʱ��memset INF �����
    memset(pre,0,sizeof(pre));
}

void prim(int n){
    priority_queue<pair<int,int> > Q;
    dis[1]=0;//��СȨ��һ��Դ���ۼ�ʱ,��û�б�.Ӧ��Ϊ0
    Q.push(make_pair(dis[1],1));
    int u,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        used[pre[u]][u]=used[u][pre[u]]=true;
        sum+=dis[u];
        for(int i=1;i<=num;i++){
            //ÿ����һ����,���жϵ�ǰ��mst����������ĵ����pre[u]��,�ܷ���һ������u��Ȩֵ�뵱ǰ��Ȩֵ��ͬ�ı�,����,mst��Ψһ,�������ݱ�֤ͼ����ͨ��
            if(seq[i]!=pre[u] && map0[seq[i]][u]==dis[u]){
                flag=1;
                return;//���� ��������
            }
        }
        seq[++num]=u;
        if(num == n) break;
        for(int i=1;i<=n;i++){
            if(!vis[i] && dis[i]>map0[u][i]){
                dis[i]=map0[u][i];
                pre[i]=u;
                Q.push(make_pair(-dis[i],i));
            }
        }
    }
}

int main(){
    int t,n,m,u,v,w;
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            map0[u][v]=map0[v][u]=w;
        }
        prim(n);
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",sum);
    }
    return 0;
}
*/

/*
//ac 16ms
//kruskal+����������+����n������dp(�ɸ��ڵ����ӽڵ�ת��)�������·���ϵ�����Ȩ
//��ΪҪ�������·��������Ҫ��ÿ����Ϊ���ڵ����,���µ������е�·��������Ȩ,
//֮�����ж�δ����mst�еı��Ƿ��кͼ���mst��·��(��·)�ϵ�����Ȩ���,������Ψһ,����Ψһ.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 105
#define INF 0x3f3f3f3f
using namespace std;
//G[i][j] ������¼�ӵ�i����j��·��֮�����ı�Ȩֵ ��ʵҲ��������ʽǰ�������,�����ռ临�Ӷȵ�һЩ,��Ŀ��������ȫͼ,���ڽӾ����е�û��Ҫ
struct Node{
    int x,y,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[N*N/2];

void init(){
    memset(used,0,sizeof(used));
    memset(G,0x3f,sizeof(G));//����memset�Ǹ�ֵ1�ֽ�Ҳ����8λ,����ÿһ�ֽڸ�ֵ0x3f,���G[i][j]��ֵ����0x3f3f3f3f
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}


//�Լ�д�� dp������ϸ��ڵ㵽���е������Ȩ maxLen[rt][v] n��dfs�����ÿ����i��Ϊ���ڵ��dp
//״̬ת���ǴӸ��ڵ����ӽڵ�ת��,��Ϊ·���ǲ��ϼӱ߱߳���.
//void dfs(int rt,int u,int fa){//O(n^2)
    //for(int i=head[u];i!=-1;i=edge[i].next){
        //int v=edge[i].to;
        //if(v == fa) continue;
        //maxLen[rt][v]=max(maxLen[rt][u],edge[i].w);
        //dfs(rt,v,u);
    //}
//}

//void dfs(int u,int fa){//O(n) dp���
    //seq[++num]=u;//ÿ����һ����ͽ������seq������,����dp
    //for(int i=head[u];i!=-1;i=node[i].next){
        //int v=node[i].to;
        //if(v == fa) continue;
        //for(int j=1;j<=num;j++)//���֮ǰ�������ĵ㵽��ǰ��·���ϵ�����Ȩ
            //dp[seq[j]][v]=dp[v][seq[j]]=max(dp[seq[j]][u],node[i].w);//�Ƚ�֮ǰ�㵽ǰ���͵�ǰ��Ȩ�����ֵ
        //dfs(v,u);
    //}
//}


void dfs(int u,int v, int w){
    vis[v]=1,G[u][v]=w;//��¼v���ѷ���,u��v��·�����ϵ����Ȩֵ
    for(int i=1;i<=n;i++)
        if(!vis[i] && G[v][i]!=INF) dfs(u,i,max(w,G[v][i]));//u����ʼ�� ��һֱ�����,i��ÿ��·����������һ���˵�
        //�����Ͼ�����mst���ҵ�һ�����ܷ񹹳ɻ�·,���ܹ��ɻ�· ���������ߺ�mst�б�Ȩ��ͬ��mst��Ψһ,
        //��������ΪʲôҪ��¼mst·���ϵ�����Ȩ,������Ϊ����i->j�������ɻ�·,��ôi->j��Ȩֵ����ֻ��
        //���ڵ���mst��i��j·���ϵ�����Ȩ,��Ϊ���i->j�����߱����ȨֵС,��ô����Kruskalÿ�ζ�ȡ��Ȩ
        //��С�ı�,���ڵ�mst�Ͳ�����С��������,����i->j������Ӧ������mst��
}

int main(){
    int t,u,v,ans;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=0;i<m;i++)
            scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].w);
        sort(edge,edge+m);
        ans=0;
        for(int i=0;i<m;i++){
            u=find(edge[i].x);
            v=find(edge[i].y);
            if(u!=v){
                fa[v]=u;
                ans+=edge[i].w;
                G[edge[i].x][edge[i].y]=G[edge[i].y][edge[i].x]=edge[i].w;//��G �ڽӾ������ʼ��ĳ������mst�е����˵��Ȩֵ
                used[i]=1;//��¼����mst�еı�
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            dfs(i,i,0);//��¼��ÿ���������mst�е�·���ıߵ����Ȩֵ
        }
        int flag=0;
        for(int i=0;i<m;i++)
            //����mst�еı�ʹ��mst����x��y·���ϵĻ�·���ұ�Ȩ����
            //edge[i].x��edge[i].y ·���ϵ�����Ȩ,��mst��Ψһ
            if(!used[i] && edge[i].w == G[edge[i].x][edge[i].y]){
                flag=1;
                break;
            }
        if(flag) printf("Not Unique!\n");
        else printf("%d\n",ans);
    }
    return 0;
}

*/

/*
//Oi-wiki����,��������ʱ��û�㶮 �ռ�(380K)��ʱ��(0ms)�������ŵ�
//���� Kruskal �㷨��ֻҪ����Ϊ��ǰȨֵ�ı߿��Էż�����ʵ�ʷ��˼�����
//���������ֵ��һ������ô��˵���⼸������֮ǰ�ı߲�����һ����
//���������������������ǰȨֵ�ıߣ�������ݲ��鼯���������ǲ��ܷŵģ���
//����С��������Ψһ��
#include <algorithm>
#include <cstdio>
using namespace std;
struct Edge {
  int x, y, z;
};
int f[100001];
Edge a[100001];
int cmp(const Edge& a, const Edge& b) { return a.z < b.z; }
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    sort(a + 1, a + m + 1, cmp);
    int num = 0, ans = 0, tail = 0, sum1 = 0, sum2 = 0;
    bool flag = 1;
    for (int i = 1; i <= m + 1; i++) {
      if (i > tail) {
        if (sum1 != sum2) {
          flag = 0;
          break;
        }
        sum1 = 0;
        for (int j = i; j <= m + 1; j++) {
          if (a[j].z != a[i].z) {
            tail = j - 1;
            break;
          }
          if (find(a[j].x) != find(a[j].y)) ++sum1;
        }
        sum2 = 0;
      }
      if (i > m) break;
      int x = find(a[i].x);
      int y = find(a[i].y);
      if (x != y && num != n - 1) {
        sum2++;
        num++;
        f[x] = f[y];
        ans += a[i].z;
      }
    }
    if (flag)
      printf("%d\n", ans);
    else
      printf("Not Unique!\n");
  }
  return 0;
}
*/

/*
��Ȼ�ж�Ψһ����������lca����ȥ�ж� ���ɻ��ı�Ȩ�Ƿ����mst·���ϵ�����Ȩ,
��������˵��mst��Ψһ,����mst��Ψһ��.
*/
