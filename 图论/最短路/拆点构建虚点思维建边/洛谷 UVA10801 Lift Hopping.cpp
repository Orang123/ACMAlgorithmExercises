#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 650
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
//�ֲ�ͼ���· ��ͬ���������Ŀ�ǶԵ�״̬�Ĳ��
//�����Ŀ�ֲ�ͼ���ǵ������ڵ�¥��,ͬ��֮������ߴ����˵���,
//�����֮����������¥����ƶ�,������ֲ�ͼ�ƶ�����ÿ����ĺ������,����������ߴ�����
//��Ϊһ��¥��n������,ÿһ�����n��״̬,�ֱ��ʾ��ͬ�ĵ��������¥
/*
����:0~99��¥��,һ���˳�ʼ��0��(������ʱ��),n������(n<=5),
����i�������������ʱ��Ϊt[i],�˿���ͬһ��ͣ�µĵ��ݻ���,�ķ�ʱ��60s,
�������˴�0�㵽��k��,������Ҫ���Ѷ���ʱ��.
����:https://www.luogu.com.cn/problem/UVA10801
˼·:���԰�ÿһ������һ����,����ÿһ�㶼��n������,
���Խ�ÿ����n��״̬��ʾ,����ͬ����������״̬,
��Ϊ¥�������99��,���Ե���i��j��ĵ�״̬���Ա�ʾΪ
i*100+j,���ڵ���֮��Ļ���,��Ϊ�����͵�������С,
���Կ��Ա���ö��ÿһ��������������״̬����.
*/

int n,k,cnt,head[N],vis[N],dis[N],t[N],floor[N];

struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void spfa(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&t[i]);//t[i] ÿ�������������������ĵ�λʱ��
        for(int i=1;i<=n;i++){
            int num=0;//��ʾ������ͣ�ڼ���¥��
            addEdge(0,100*i,0);//����һ������Դ�㵽0���ÿ������,ʵ�ʾ��ǿ��ǳ�ʼ0�㳢��ÿ��������Ϊ��ʼ��
            while(scanf("%d",&floor[++num]))//floor��¼����ÿ��������¥����ͣ������
                if(getchar()=='\n') break;//��Ϊû��˵������ͣ�ڼ���¥��,�����Իس�������.
            for(int j=1;j<num;j++){
                //��Ϊ���������»�ͨ,���Թ�������i������������¥��(j,j+1)��˫���
                //�ķ�ʱ��Ϊ(floor[j+1]-floor[j])*t[i]
                addEdge(100*i+floor[j],100*i+floor[j+1],(floor[j+1]-floor[j])*t[i]);
                addEdge(100*i+floor[j+1],100*i+floor[j],(floor[j+1]-floor[j])*t[i]);
            }
        }
        /*
        ö��ÿ��¥�����Ի��˵ĵ��ݹ���˫���,
        ʵ�����ĵ��ݿ����޷���ͨ,��Ϊ������ͣ���в�һ����ͣ�����
        */
        for(int i=0;i<=99;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    if(j!=k)
                        addEdge(100*j+i,100*k+i,60);//��Ϊ��O(n^2)ö��,����ֻҪö�ٵ���߾ͺ�
                }
            }
        }
        spfa(0);//��Ϊ������ ����Դ������ֻ��һ�����·
        int ans=INF;
        for(int i=1;i<=n;i++)//�������k���ĸ����ݵ���ʱ����ʱ��С,���ԱȽϼ�¼��Сֵ
            ans=min(ans,dis[i*100+k]);//ʵ����Ҳ���Խ�����k�㽨һ���������t,ȨΪ0,��ȡdis[t]����
        if(ans!=INF) printf("%d\n",ans);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
