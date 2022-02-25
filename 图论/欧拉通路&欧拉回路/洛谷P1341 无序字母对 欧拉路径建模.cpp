#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 10000
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,next,use;
}edge1[N];
struct side{
    int a,b;
    bool operator <(const side &x)const{
        if(a == x.a) return b<x.b;
        else return a<x.a;
    }
}edge2[N];
int n,cnt;
int head[N],de[N];
stack<int> s;
void addEdge(int from,int to){
    edge1[cnt].to=to;
    edge1[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){
    int v;
    for(int i=head[u];i!=-1;i=edge1[i].next){
        if(!edge1[i].use){
            v=edge1[i].to;
            edge1[i].use=edge1[i^1].use=1;//将这条边标记为已遍历
            //head[u]=edge1[i].next;//这里可以缩短时间复杂度,后面再访问到u点时因为前面的边已访问,这里可以直接忽略
            dfs(v);
        }
    }
    s.push(u);
}

int main(){
    char u,v;
    int S=INF;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("\n");//洛谷无法 用getchar会出错 建议用scanf("\n")或scanf("%s")数组输入s[0] s[1]保险一点
        scanf("%c%c",&u,&v);
        if(u>v) swap(u,v);//这里好像必须交换u得是字典序较小的,字典序较小,S取的起点是字典序最小的
        edge2[i].a=u;
        edge2[i].b=v;
        de[u]++;
        de[v]++;
        S=min(S,(int)u);
    }
    int ans=0;
    for(int i='z';i>='A';i--){//按照字典序降序比较
        if(de[i]&1){//计算奇点的个数
            ans++;
            S=i;//记录较小的奇点编号
        }
    }
    if(ans>2){
        printf("No Solution");
        return 0;
    }
    sort(edge2,edge2+n);//将边先按字典序排序
    for(int i=n-1;i>=0;i--){//因为前向星 后插入的边先遍历的特点,我们逆序插入,将字典序较小的边后插入
        addEdge(edge2[i].a,edge2[i].b);
        addEdge(edge2[i].b,edge2[i].a);
    }
    dfs(S);
    int t;
    while(!s.empty()){
        t=s.top();
        s.pop();
        printf("%c",t);
    }
    return 0;
}
/*
#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 10000
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,next,use;
}edge1[N];
struct side{
    int a,b;
    bool operator <(const side &x)const{
        if(a == x.a) return b<x.b;
        else return a<x.a;
    }
}edge2[N];
int n,cnt;
int head[N],de[N];
stack<int> s;
void addEdge(int from,int to){
    edge1[cnt].to=to;
    edge1[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){
    int v;
    for(int i=head[u];i!=-1;i=edge1[i].next){
        if(!edge1[i].use){
            v=edge1[i].to;
            edge1[i].use=edge1[i^1].use=1;
            //head[u]=edge1[i].next;
            dfs(v);
        }
    }
    s.push(u);
}

int main(){
    char u,v;
    int S=INF;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("\n");
        scanf("%c%c",&u,&v);
        edge2[i].a=u;
        edge2[i].b=v;
        de[u]++;
        de[v]++;
    }
    int ans=0;
    for(int i='z';i>='A';i--){
        if(de[i]&1){
            ans++;
            S=i;
        }
    }
    if(ans>2){
        printf("No Solution");
        return 0;
    }
    else if(ans == 0){
        for(int i='z';i>='A';i--){
            if(de[i]){
                S=i;
            }
        }
    }
    sort(edge2,edge2+n);
    for(int i=n-1;i>=0;i--){
        addEdge(edge2[i].a,edge2[i].b);
        addEdge(edge2[i].b,edge2[i].a);
    }
    dfs(S);
    int t;
    while(!s.empty()){
        t=s.top();
        s.pop();
        printf("%c",t);
    }
    return 0;
}
*/
