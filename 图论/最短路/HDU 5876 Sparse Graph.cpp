#include<cstdio>
#include<cstring>
#include<queue>
#include<set>
#include<algorithm>
#define N 200100
#define M 20100
#define INF 0x3f3f3f3f
using namespace std;

/*
前置图论知识:
完全图:完全图是一个简单的无向图,
其中每对不同的顶点之间都恰连有一条边相连.
补图:一个图G的补图或者反面是一个图有着跟G相同的点,
而且这些点之间有边相连当且仅当在G里面他们没有边相连.
图G和其补图相并得到的就是G的完全图.
题意:求解一个图的补图中s点到其余各点的最短距离,每条边的长度为单位距离.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5876
思路:因为边长是1,又是求解最短路,所以可以用bfs,那么对于补图而言遍历过的边肯定不会再
遍历,因为第一次遍历时的就是到该点的最短路,可以考虑对于原图的某点的连边相连的点,将所有点
初试放置在一个集合里,每次原图有连边的点在该集合去除,将剩余点入队,然后本次去除的点就是剩余还没有遍历
的点,将其放入原集合中,因为涉及到在集合中查找元素,所以用两个set.
*/

int n,m,cnt,head[N],dis[N];
set<int> s1,s2;
set<int>::iterator it;

struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(int s){
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    for(int i=1;i<=n;i++)//初试将除s外的点都放入s1中
        if(i!=s) s1.insert(i);
}
//O(nlogn)
void bfs(int s){
    init(s);
    queue<int> Q;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            判断这个点是否在s1中,若在将其去除,剩下的点就是补图中的连边对应的节点,
            同时这些被除去的点放入s2中代表还未遍历的点
            s1中没有的点就是已经遍历过得出最短距离的点,所以不再遍历.
            */
            if(!s1.count(v)) continue;//计算s1中v点的个数 set是红黑树结构,查找O(logN)
            s1.erase(v);//s1中删除v点
            s2.insert(v);//s2中插入v点
        }
        //将补图中与u点相连的点计算最短距离,并入队
        for(it=s1.begin();it!=s1.end();it++){
            dis[*it]=dis[u]+1;
            Q.push(*it);
        }
        /*
        //剩余的点还未遍历,下次遍历时 同样去除原图中的连边,
        直到某个点在原图中没有连边,s1中的点将全部入队,
        */
        s1=s2;
        s2.clear();
    }
}

int main(){
    int T,u,v,s;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        s1.clear(),s2.clear();
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        scanf("%d",&s);
        bfs(s);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(i == s) continue;
            if(!flag){
                printf("%d",dis[i]);
                flag=1;
            }
            else
                printf(" %d",dis[i]);
        }
        printf("\n");
    }
    return 0;
}
