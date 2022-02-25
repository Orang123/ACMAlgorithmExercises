/*
����:ժ������
����һ������N��0<N<=100000�����ڵ�������ڵ��Ŵ�0��N-1����
Ȼ�����һ������D(0<D<N),�������0�Žڵ�ľ������D�Ľڵ������
�������ڽڵ�ľ���Ϊ1��
����:https://acm.hdu.edu.cn/showproblem.php?pid=4707
˼·:����+dfs
*/
//ac 405ms ������d���뷶Χ�ڵĵ�ĸ���,n-sum���Ǵ���d�ĵ�ĸ���.
#include<cstdio>
#include<cstring>
#define maxn 100002
struct node{
    int to;//to�Ǵ���a���������������ӵĽ��,nextָ����һ��a������ӵĽ����±�
    int next;
}edge[maxn<<1];//��n����� ��ͨ�޻�· ��(n-1)���߶�������������,������Ϊ��������,��˫���,���Ա�����2(n-1),���maxn<<1 Ҫ��2
int head[maxn],n,d,index,sum;//head[i] ���Ϊi�ĵ������ӵ��Ӧ�������±�,index��ʾ���鵱ǰָ��

void add_edge(int from,int to){
    edge[index].to=to;
    edge[index].next=head[from];
    head[from]=index;
    index++;
}
void dfs(int u,int fa,int d0){
    if(d0 == d)
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa)
            continue;
        sum++;
        dfs(v,u,d0+1);
    }
}
int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&d);
        index=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);//Ϊ����dfs()���ĸ�����Ϊ��㿪ʼ,�����һ���Ž���˫��ߵ�,Ҳ����ͨͼ�ĸ���
            add_edge(b,a);
        }
        sum=1;//0�ŵ㱾���� �����
        dfs(0,-1,0);
        printf("%d\n",n-sum);
    }
    return 0;
}

/*
//ac 421ms ֱ���жϾ������d�ĵ�ĸ���
#include<cstdio>
#include<cstring>
#define maxn 100002
struct node{
    int to;//to�Ǵ���a���������������ӵĽ��,nextָ����һ��a������ӵĽ����±�
    int next;
}edge[maxn<<1];//��n����� ��ͨ�޻�· ��(n-1)���߶�������������,������Ϊ��������,��˫���,���Ա�����2(n-1),���maxn<<1 Ҫ��2
int head[maxn],n,d,index,sum;//head[i] ���Ϊi�ĵ������ӵ��Ӧ�������±�,index��ʾ���鵱ǰָ��

void add_edge(int from,int to){
    edge[index].to=to;
    edge[index].next=head[from];
    head[from]=index;
    index++;
}
void dfs(int u,int fa,int d0){
    if(d0>d)
        sum++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa)
            continue;
        dfs(edge[i].to,u,d0+1);
    }
}
int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&d);
        n--;
        index=0;
        while(n--){
            scanf("%d%d",&a,&b);
            add_edge(a,b);//Ϊ����dfs()���ĸ�����Ϊ��㿪ʼ,�����һ���Ž���˫��ߵ�,Ҳ����ͨͼ�ĸ���
            add_edge(b,a);
        }
        sum=0;
        dfs(0,-1,0);
        printf("%d\n",sum);
    }
    return 0;
}
*/
