#include<cstdio>
#include<cstring>
#define N 500
using namespace std;
//ac 0ms edge[i].flag��Ǳ����
/*
����:n�Żõ�Ƭ�ѷ���һ��,��n��������n�Żõ�Ƭ��,ÿ�Żõ�Ƭ
��x��y�������С�����Χ,���ڿ��ǽ�ÿ������ֻ��һ�Żõ�Ƭ��
��Ӧ,����һ�Żõ�Ƭֻ�ܶ�Ӧһ������,����Ҫ������Ļõ�Ƭ�����ֵĶ�Ӧ��ϵ,
���Ƿ���������Ӧ��ϵΪ�����,���������õ�Ƭ����Ӧ�������,
����ϵ�������,��������Ӧ��ϵҲ�Ǳ����.
����:http://poj.org/problem?id=1486
˼·:n�Żõ�Ƭ����һ������,n����������һ������,�պù��ɶ���ͼ������
����,��Ϊ����ֻ�ܶ�Ӧһ���õ�Ƭ,�õ�ƬҲֻ�ܶ�Ӧһ������,��������Ķ�Ӧ��ϵ�����й�����,
ʵ�ʾ���������ͼ�����ƥ��.���������ƥ��,Ȼ��ö��ɾ��ÿ��ƥ���,
����ȡ���ƥ��,������ƥ����������,��˵�������������ƥ����б���ı�,����
������ƥ��������,��˵��ö��ɾ��������ƥ��߲��Ǳ����.
*/
int cas,n,head[N],cnt,vis[N],link[N],match[N],ans;
struct Point{
    int minx,maxx,miny,maxy;
}point[N];
struct Edge{
    int from,to,next,flag;
}edge[N*N];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!edge[i].flag) continue;//����ƥ����ѱ�ɾ��
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(){
    int num=0;
    memset(link,0,sizeof(link));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) num++;
    }
    return num;
}

void init(){
    cnt=0;
    cas++;
    memset(head,-1,sizeof(head));
}

int main(){
    int x,y;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)//����n�Żõ�Ƭ��x��y���귶Χ
            scanf("%d%d%d%d",&point[i].minx,&point[i].maxx,&point[i].miny,&point[i].maxy);
        for(int i=1;i<=n;i++){//����n�����ֵ�x��y����
            scanf("%d%d",&x,&y);
            for(int j=1;j<=n;j++){//�����i�����ֵ������ڻõ�Ƭj�����귶Χ��,��j->i�������
                if(x>=point[j].minx && x<=point[j].maxx && y>=point[j].miny && y<=point[j].maxy)
                    addEdge(j,i,1);//��Ĭ�ϱ���Ǵ��ڵ� flag=1
            }
        }
        ans=hungary();
        for(int i=1;i<=n;i++)
            match[link[i]]=i;//�õ�Ƭlink[i]ƥ�������Ϊi
        int flag=0;
        for(int i=0;i<cnt;i++){
            x=edge[i].from,y=edge[i].to;
            if(match[x] != y) continue;//ö��ɾ���ı������Ѿ�ƥ���
            edge[i].flag=0;
            if(hungary() == ans)
                match[x]=0;//ƥ�������� �ñ߲��Ǳ����
            else
                flag=1;
            edge[i].flag=1;//ƥ���i�ָ�
        }
        printf("Heap %d\n",cas);
        if(!flag)//û��һ������� ���"none"
            printf("none\n");
        else{
            int k=0;
            for(int i=1;i<=n;i++){
                if(!match[i]) continue;
                if(!k){
                    k=1;
                    printf("(%c,%d)",'A'+i-1,match[i]);//�������ߵĻõ�ƬA��B...��Ӧ������match[i]
                }
                else
                    printf(" (%c,%d)",'A'+i-1,match[i]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 0ms mp��ͼ mp[i][match[i]]����Ƿ�Ϊ�����
#include<cstdio>
#include<cstring>
#define N 500
using namespace std;

int cas,n,vis[N],mp[N][N],link[N],match[N],ans;
struct Point{
    int minx,maxx,miny,maxy;
}point[N];

int dfs(int u){
    for(int v=1;v<=n;v++){
        if(!mp[u][v]) continue;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int hungary(){
    int num=0;
    memset(link,0,sizeof(link));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) num++;
    }
    return num;
}

void init(){
    cas++;
    memset(mp,0,sizeof(mp));
}

int main(){
    int x,y;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d",&point[i].minx,&point[i].maxx,&point[i].miny,&point[i].maxy);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&y);
            for(int j=1;j<=n;j++){
                if(x>=point[j].minx && x<=point[j].maxx && y>=point[j].miny && y<=point[j].maxy)
                    mp[j][i]=1;
            }
        }
        ans=hungary();
        for(int i=1;i<=n;i++)
            match[link[i]]=i;
        printf("Heap %d\n",cas);
        int flag=0;
        for(int i=1;i<=n;i++){
            mp[i][match[i]]=0;
            if(hungary() != ans){
                if(!flag)
                    printf("(%c,%d)",'A'+i-1,match[i]);
                else
                    printf(" (%c,%d)",'A'+i-1,match[i]);
                flag=1;
            }
            mp[i][match[i]]=1;
        }
        if(!flag) printf("none");
        printf("\n\n");
    }
    return 0;
}

*/
