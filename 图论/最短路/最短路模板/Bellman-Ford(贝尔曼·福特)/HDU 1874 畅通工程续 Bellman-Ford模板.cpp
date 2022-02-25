#include<cstdio>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f

/*
����:n������,m���� ���s->t����̾���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1874
˼·:���·����.
*/

struct node{
    int from,to,w;
}edge[N];
int n,m,cnt,dis[N];

/*
Bellman-Ford(������-����)�㷨 һ�ֻ����ɳ�(relax)���������·�㷨��
�ɳڿ����Ϊ��һ��ֱ����ĳ��������,��ʹ����2����,2���ߵ�Ȩֵ֮��ҪԶС�ڱ�����ֱ��
֧�ָ�Ȩ.���ҵ�ĳ�������������н������·�����߱���ĳЩ���·������.
*/

void addEdge(int from,int to,int w){
    edge[cnt].from=from;
    edge[cnt].to=to;
    edge[cnt].w=w;
    cnt++;
}
void init(int s){
    for(int i=0;i<n;i++)
        dis[i]=(i==s?0:INF);
}
//�ʱ�临�Ӷ�O(VE)
bool Bellman_Ford(int s){
    init(s);
    int u,v,ok;
    /*
    ����һ���ɳڲ�����ʹ���·�ı�������+1,�����·�ı������Ϊn-1(��ͨ�޻�·��һ����ֱ��������,����Ϊ����-1).
    �������ִ��n-1���ɳڲ����������ѭ��n-1��.
    �ڸ����ɳ�������·ʱ,��ÿһ�ε�ѭ���н϶̵����·Ҳ�ڱ��ɳڸ���
    */
    for(int i=1;i<n;i++){
        ok=0;
        /*
        �����ܶ�ؿ���ÿһ�����Ƿ�����ɳ�,�����ʵ�ʹ����߼���˳���й�,
        Խ�õ����п�����ǰ��Խ��������ÿ��������·,��ÿ��ѭ���ɳڵı�Խ��,
        ����cnt���иպ�����ǰ���ɳڵĵ�dis���º�,cnt����ıߵ�dis[u]�պþ���֮ǰ����
        �õ�dis[v]�����������Ϊ��������,����������ÿ��ֻ�����ɳ�һ����,�����߸պ�
        �����ı�������ǰ�Ƹ���,�պ�ѭ����n-1��
        */
        for(int j=0;j<cnt;j++){
            u=edge[j].from;
            v=edge[j].to;
            /*
            BF�㷨�ܶ��ɳڲ���dis[u]ʵ�ʻ�û���ɳ�,��������INF,��ʱ����ɳ�ʱû�������,��Ҳ��BF�㷨��ȱ��,spfa�����ڴ˵��ϸĽ�
            */
            if(dis[v]>dis[u]+edge[j].w){//dis[v]���ڸ��̵�·��,��u�н��,dis[u]+u->v
                dis[v]=dis[u]+edge[j].w;
                ok=1;//�б߿��ɳڵı��
            }
        }
        if(!ok)//���˴�ѭ��,û��һ���߿����ɳڴ���Դ�㵽���е�����·�Ѿ���� ����ֻ��������·����,ֻ����Ȩ,û�и�Ȩ,�����ڸ�����˵��
            return true;//�˳�����
    }
    //����պý��б���������n-1���ɳڸ���,��ʱ��֤�Ƿ���ڸ���
    for(int j=0;j<cnt;j++){
        u=edge[j].from;
        v=edge[j].to;
        if(dis[v]>dis[u]+edge[j].w)//���Ծɻ����ڱ߿��ɳڸ���,˵��ĳ����һ���ظ��Ե��ɳ�,˵�����ڸ���,Խ�ɳ�ԽС,����ѭ��,ĳ���㲻һ�����ɳ�n��,����ĳ����һ���Ǳ��ظ��ɳ���>=2��
            return false;
    }
    return true;
}

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dis,0,sizeof(dis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        if(Bellman_Ford(s)){
            if(dis[t]!=INF)
                printf("%d\n",dis[t]);
            else
                printf("-1\n");
        }
        else
            printf("ԭͼ���и���,���������·\n");
    }
    return 0;
}
