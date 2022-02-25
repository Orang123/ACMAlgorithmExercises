#include<cstdio>
#include<cstring>
#define N 100100
using namespace std;
//ac 218ms ��ʽǰ���ǽ�ͼ
//2010 Asia Tianjin Regional Contest
/*
����:n��ѧ��,ÿ���˶�˵�Լ��������ڵ���������,
����ѧ�������п����Ǵ�����������ķ�Χ��,����ʦ��֪��
˭˵�˻�,������ʦ��֪������ж���ѧ��˵����ʵ��,���
˵ʵ��ѧ���ı��,����ж��������,�������ֵ����һ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3729
˼·:���Խ�ѧ������������ķ�Χ��Ϊ�����ֿ��ļ���,��һ��ѧ��ֻ��
��Ӧһ������,��ÿ��ѧ���������Ķ�Ӧ��ϵ�ǲ����ص���,��û�й�����,
ʵ�ʾ������ѧ����������Ӧ��ϵ�����ƥ��,ÿ��ѧ����Ҫ�Ͷ�Ӧ�����
������ѧ���������������,����Ҫ��������ֵ���ѧ�����,����̰��
�������������ʱ�����n���ο���n-1...1,��Ϊ���ƥ��ķ������ܲ�Ψһ,
�������ƥ���ֵһ����Ψһ��.
*/
int n,cnt,head[N],vis[N],match[N],ans,flag[N];
struct Edge{
    int to,next;
}edge[N*60];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    memset(flag,0,sizeof(flag));
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            for(int j=a;j<=b;j++)
                addEdge(i,j);
        }
        for(int i=n;i>=1;i--){
            memset(vis,0,sizeof(vis));
            if(dfs(i)){
                ans++;
                flag[i]=1;
            }
        }
        printf("%d\n",ans);
        int k=0;
        for(int i=1;i<=n;i++){
            if(!flag[i]) continue;
            if(!k){
                k=1;
                printf("%d",i);
            }
            else
                printf(" %d",i);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 187ms ����ͼ,ֱ�Ӵ�����sec��st~ed dfs����
#include<cstdio>
#include<cstring>
#define N 100100
using namespace std;

int n,vis[N],match[N],ans,flag[N];
struct Section{
    int st,ed;
}sec[110];

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    memset(flag,0,sizeof(flag));
}

int dfs(int u){
    for(int v=sec[u].st;v<=sec[u].ed;v++){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&sec[i].st,&sec[i].ed);
        for(int i=n;i>=1;i--){
            memset(vis,0,sizeof(vis));
            if(dfs(i)){
                ans++;
                flag[i]=1;
            }
        }
        printf("%d\n",ans);
        int k=0;
        for(int i=1;i<=n;i++){
            if(!flag[i]) continue;
            if(!k){
                k=1;
                printf("%d",i);
            }
            else
                printf(" %d",i);
        }
        printf("\n");
    }
    return 0;
}
*/
