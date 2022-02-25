#include<cstdio>
#include<cstring>
#include<queue>
#define N 550
#define M 1000
using namespace std;
struct node{
    int to,next;
}edge[M];
int n,m,head[N],cnt,inde[N],arr[N];
/*
��������������˼ά,�ֱ���Kahn�㷨��dfs�㷨,�������Kahn�㷨 �ǴӸ������Ϊ0�ĵ㿼�ǵ�,Ҳ��Ϊ�㷺ʹ��,dfs��ͨ�������������һ����һ���ǳ���Ϊ0�ĵ�����Ƕȿ��ǵ�,dfs����Ҫÿ���㶼����,ֻҪ��û���ʹ�
*/
void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}
//O(v+E)
bool toposort(){
    /*��������������� ͬʱ�����Ϊ0�ĵ�������ǰ������ν,�������ö��л�ջ������ǶԵ�*/
    priority_queue<int,vector<int>,greater<int> > Q;//С���� ��ĿҪ��ͬʱ�����Ϊ0ʱ ��Ž�С������ǰ��
    int index=0;
    for(int i=1;i<=n;i++)
        if(!inde[i])//��ʼ�� ���տ�ʼ���Ϊ0�ĵ� ��Ϊ������ǰ���
            Q.push(i);
    while(!Q.empty()){//O(V)
        int u=Q.top();
        arr[++index]=u;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){//�ۼ�ΪO(E)
            int v=edge[i].to;
            if(!--inde[v])//��u�������ӵıߵĶ˵����ȶ���1,���˵����Ϊ0ʱ,�������,˵������ǰ���������Ѵﵽ,������Ҳ���������,���ں���Ĵ���
                Q.push(v);
        }
    }
    /*���������DAG(�����޻�ͼ) ���յ����ѵ�Ԫ�ظ���ӦΪ���е�ĸ���,���л�,
    ���������·���ϵĵ㶼�޷�ȷ������֮���ǰ�� ��������,û��һ�������Ȼ�Ϊ0,
    ����޷������,a��b��ǰ������,bҲ��a��ǰ������,�໥ì��*/
    if(index < n)
        return false;
    return true;//DAG���е㶼�����,��������
}

int main(){
    int a,b;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(inde,0,sizeof(inde));
        memset(head,-1,sizeof(head));
        cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            inde[b]++;
        }
        if(toposort()){
            printf("%d",arr[1]);
            for(int i=2;i<=n;i++)
                printf(" %d",arr[i]);
            printf("\n");
        }
        else
            printf("ԭͼ�к��л�·�޷�����\n");
    }
    return 0;
}
/*dfs�汾 ���P2883
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
#define M 50100
using namespace std;
int n,m,head1[N],head2[N],cnt1,cnt2,ans=-1,inde[N],outde[N],num1[N],num2[N],vis[N];
struct Node1{
    int from,to,next;
}edge1[M];
struct Node2{
    int from,to,next;
}edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node1){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node2){from,to,head2[from]};
    head2[from]=cnt2++;
}

void dfs1(int u){
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        int v=edge1[i].to;
        num1[v]+=num1[u];
        if(!--inde[v])
            dfs1(v);
    }
}

void dfs2(int u){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        num2[v]+=num2[u];
        if(!--outde[v])
            dfs2(v);
    }
}
//����������ͼ���ֱ������ÿ�����·����
int main(){
    int u,v;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge1(u,v);
        addEdge2(v,u);
        inde[v]++;
        outde[u]++;
    }
    for(int i=1;i<=n;i++){
        if(!inde[i]){
            vis[i]=1;
            num1[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            dfs1(i);
    }
    num2[n]=1;
    dfs2(n);
    for(int i=0;i<m;i++)
        ans=max(ans,num1[edge1[i].from]*num2[edge1[i].to]);//��������·�� ���˵�(���򡢷���)ͨ���Ĵ��� ��˼�ʹ�� ��ȡ���ֵ
    printf("%d\n",ans);
    return 0;
}

*/

