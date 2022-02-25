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
            edge1[i].use=edge1[i^1].use=1;//�������߱��Ϊ�ѱ���
            //head[u]=edge1[i].next;//�����������ʱ�临�Ӷ�,�����ٷ��ʵ�u��ʱ��Ϊǰ��ı��ѷ���,�������ֱ�Ӻ���
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
        scanf("\n");//����޷� ��getchar����� ������scanf("\n")��scanf("%s")��������s[0] s[1]����һ��
        scanf("%c%c",&u,&v);
        if(u>v) swap(u,v);//���������뽻��u�����ֵ����С��,�ֵ����С,Sȡ��������ֵ�����С��
        edge2[i].a=u;
        edge2[i].b=v;
        de[u]++;
        de[v]++;
        S=min(S,(int)u);
    }
    int ans=0;
    for(int i='z';i>='A';i--){//�����ֵ�����Ƚ�
        if(de[i]&1){//�������ĸ���
            ans++;
            S=i;//��¼��С�������
        }
    }
    if(ans>2){
        printf("No Solution");
        return 0;
    }
    sort(edge2,edge2+n);//�����Ȱ��ֵ�������
    for(int i=n-1;i>=0;i--){//��Ϊǰ���� �����ı��ȱ������ص�,�����������,���ֵ����С�ıߺ����
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
