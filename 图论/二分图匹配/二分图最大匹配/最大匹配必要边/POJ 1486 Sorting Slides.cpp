#include<cstdio>
#include<cstring>
#define N 500
using namespace std;
//ac 0ms edge[i].flag标记必须边
/*
题意:n张幻灯片堆放在一起,有n个数字在n张幻灯片内,每张幻灯片
有x、y坐标的最小、最大范围,现在考虑将每个数字只和一张幻灯片相
对应,并且一张幻灯片只能对应一个数字,现在要求解最多的幻灯片和数字的对应关系,
看是否有哪条对应关系为必须的,即如果这个幻灯片不对应这个数字,
最大关系数会减少,则这条对应关系也是必须的.
链接:http://poj.org/problem?id=1486
思路:n张幻灯片属于一个集合,n个数字属于一个集合,刚好构成二分图的两个
集合,因为数字只能对应一个幻灯片,幻灯片也只能对应一个数字,因此这样的对应关系不能有公共点,
实际就是求解二分图的最大匹配.先求解出最大匹配,然后枚举删除每条匹配边,
再求取最大匹配,如果最大匹配数量减少,则说明这条边是最大匹配边中必须的边,否则
如果最大匹配数不变,则说明枚举删除的这条匹配边不是必须的.
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
        if(!edge[i].flag) continue;//这条匹配边已被删除
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
        for(int i=1;i<=n;i++)//输入n张幻灯片的x、y坐标范围
            scanf("%d%d%d%d",&point[i].minx,&point[i].maxx,&point[i].miny,&point[i].maxy);
        for(int i=1;i<=n;i++){//输入n个数字的x、y坐标
            scanf("%d%d",&x,&y);
            for(int j=1;j<=n;j++){//如果第i个数字的坐标在幻灯片j的坐标范围内,则建j->i的有向边
                if(x>=point[j].minx && x<=point[j].maxx && y>=point[j].miny && y<=point[j].maxy)
                    addEdge(j,i,1);//边默认标记是存在的 flag=1
            }
        }
        ans=hungary();
        for(int i=1;i<=n;i++)
            match[link[i]]=i;//幻灯片link[i]匹配的数字为i
        int flag=0;
        for(int i=0;i<cnt;i++){
            x=edge[i].from,y=edge[i].to;
            if(match[x] != y) continue;//枚举删除的必须是已经匹配边
            edge[i].flag=0;
            if(hungary() == ans)
                match[x]=0;//匹配数不变 该边不是必须边
            else
                flag=1;
            edge[i].flag=1;//匹配边i恢复
        }
        printf("Heap %d\n",cas);
        if(!flag)//没有一个必须边 输出"none"
            printf("none\n");
        else{
            int k=0;
            for(int i=1;i<=n;i++){
                if(!match[i]) continue;
                if(!k){
                    k=1;
                    printf("(%c,%d)",'A'+i-1,match[i]);//输出必须边的幻灯片A、B...对应的数字match[i]
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
//ac 0ms mp存图 mp[i][match[i]]标记是否为必须边
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
