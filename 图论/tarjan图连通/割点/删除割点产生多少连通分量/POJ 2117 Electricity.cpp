#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 532ms
/*
����:һ�����糧����,Ϊ�˶����������,���Ǽ�����ܷ�������¼�
�Ƿ��糧��һ�����ӵ㷢������,����ܵ���������ѳɼ�������.����
Ӧ��ȷ����ɾ������һ�����ӵ�(������ɾ�������ӵ㱾��)���������
���������δ���Ӳ��ֵ�����.
����:
��������ͼ,��ɾ��һ���������ܲ�����������ͨ�����Ƕ���.
����:http://poj.org/problem?id=2117
˼·:����ͳ��ɾ��ÿ�������������������ͨ����,����ÿ������Ϊ���׵ķ�֧,
���ɾ���������ʹ�������֧��������ͨ,��������ͨ������1.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;
int ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) EΪ��
    dfn[u]=low[u]=++num;
    int v,son=0,conn=0;//conn����ͳ�Ƶ���u�ڵ�֮����������������ͨ����,���Ӧ�û���Ҫ����u��֮ǰû�������ͨ��������Ϊ1.
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            son++;
            low[u]=min(low[u],low[v]);
            if(u != root && dfn[u]<=low[v])
                conn++;//ͬһ����ÿ��һ����֧��Ϊһ�θ��,��ɾ�������,����������һ����ͨ����
            //���ﲻ�ܷ���for����,��Ϊɾ�����ڵ�����ڵ����������з�֧�����Ϊһ����ͨ����,���Զ���ÿ����֧��Ҫconn++
            //���ֻ���жϸõ��Ƿ��Ǹ��,�ǿ��Է���forѭ�������
            //����son==1,ֻ��һ����֧�ǲ���¼��,���ǵ�son>=2ʱ,����¼����ͨ����ʵ���ټ�¼��һ��,����������н������+1
            else if(u == root && son>=2)
                conn++;//ͬ��
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    ans=max(ans,conn);//��ȡ��������Ϊ����������ӵ������ͨ��
}

int main(){
    int n,m,a,b;
    while(scanf("%d%d",&n,&m) && n||m){
        if(m==0){//��0����,����n����ͨ����,����һ����,��ͨ����Ϊ(n-1)��
            printf("%d\n",n-1);
            continue;
        }
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        ans=num=cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                res++;
                root=i;
                dfs(i,-1);
            }
        }
        //���ڸ���Ǹ��ڵ�����,ansʵ���ټ�¼��һ����֧,
        //��Ϊֻ��son>=2ʱ�ſ�ʼ����,��ֻ��һ����֧ʱ���Ǹ��,����resǡ�ò���һ������ķ�֧
        printf("%d\n",res+ans);//res��ԭͼ�е���ͨ������,ansΪɾ��һ�����������ӵ���ͨ������
    }
    return 0;
}

/*
//��һ�����ɾ������ʣ����ͨ������д��
//ac 516ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int root;
int ans;

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){//O(E) EΪ��
    dfn[u]=low[u]=++num;
    int conn=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                conn++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) conn--;
    ans=max(ans,conn);//��ȡ��������Ϊ����������ӵ������ͨ��
}

int main(){
    int n,m,a,b;
    while(scanf("%d%d",&n,&m) && n||m){
        if(m==0){//��0����,����n����ͨ����,����һ����,��ͨ����Ϊ(n-1)��
            printf("%d\n",n-1);
            continue;
        }
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        ans=num=cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                res++;
                root=i;
                dfs(i,-1);
            }
        }
        //���ڸ���Ǹ��ڵ�����,ansʵ���ټ�¼��һ����֧,
        //��Ϊֻ��son>=2ʱ�ſ�ʼ����,��ֻ��һ����֧ʱ���Ǹ��,����resǡ�ò���һ������ķ�֧
        printf("%d\n",res+ans);//res��ԭͼ�е���ͨ������,ansΪɾ��һ�����������ӵ���ͨ������
    }
    return 0;
}
*/
