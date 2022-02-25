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
ǰ��ͼ��֪ʶ:
��ȫͼ:��ȫͼ��һ���򵥵�����ͼ,
����ÿ�Բ�ͬ�Ķ���֮�䶼ǡ����һ��������.
��ͼ:һ��ͼG�Ĳ�ͼ���߷�����һ��ͼ���Ÿ�G��ͬ�ĵ�,
������Щ��֮���б��������ҽ�����G��������û�б�����.
ͼG���䲹ͼ�ಢ�õ��ľ���G����ȫͼ.
����:���һ��ͼ�Ĳ�ͼ��s�㵽����������̾���,ÿ���ߵĳ���Ϊ��λ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5876
˼·:��Ϊ�߳���1,����������·,���Կ�����bfs,��ô���ڲ�ͼ���Ա������ı߿϶�������
����,��Ϊ��һ�α���ʱ�ľ��ǵ��õ�����·,���Կ��Ƕ���ԭͼ��ĳ������������ĵ�,�����е�
���Է�����һ��������,ÿ��ԭͼ�����ߵĵ��ڸü���ȥ��,��ʣ������,Ȼ�󱾴�ȥ���ĵ����ʣ�໹û�б���
�ĵ�,�������ԭ������,��Ϊ�漰���ڼ����в���Ԫ��,����������set.
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
    for(int i=1;i<=n;i++)//���Խ���s��ĵ㶼����s1��
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
            �ж�������Ƿ���s1��,���ڽ���ȥ��,ʣ�µĵ���ǲ�ͼ�е����߶�Ӧ�Ľڵ�,
            ͬʱ��Щ����ȥ�ĵ����s2�д���δ�����ĵ�
            s1��û�еĵ�����Ѿ��������ó���̾���ĵ�,���Բ��ٱ���.
            */
            if(!s1.count(v)) continue;//����s1��v��ĸ��� set�Ǻ�����ṹ,����O(logN)
            s1.erase(v);//s1��ɾ��v��
            s2.insert(v);//s2�в���v��
        }
        //����ͼ����u�������ĵ������̾���,�����
        for(it=s1.begin();it!=s1.end();it++){
            dis[*it]=dis[u]+1;
            Q.push(*it);
        }
        /*
        //ʣ��ĵ㻹δ����,�´α���ʱ ͬ��ȥ��ԭͼ�е�����,
        ֱ��ĳ������ԭͼ��û������,s1�еĵ㽫ȫ�����,
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
