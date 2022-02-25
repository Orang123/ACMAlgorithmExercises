#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define INF 1e18
using namespace std;
typedef long long ll;
//124ms prim ������ǰ���ǻ�MLE,���������ڽӾ���mp
/*
���:n������ÿ�����ж���һ���˿�,��ʼ��Ҫ��n-1����·����������������ʹ���ܳ�����С.
�츣������ħ������޽�һ����·,���ڶ���A:ħ������޽���·���ӵ�2�����е��˿�,B:��
ħ���޽��ĵ�·�����ܺ�,������ʼ��ϣ��A/B�����ֵ,�����ֵ�Ƕ���.

��n�����У���ʼ��Ҫ����n-1��·��������������Ҫ�����һ������������Ե�������������㡣��ʼ��ϣ��������n-1��·����֮����̡�
Ȼ���츣ͻȻ��ð������˵������ħ�������Բ��������������ͱ����������һ��·������
��ʼ��ϣ���츣�ܰ�Ҫ�޵�n-1��·���������������������츣ϣ���ܰ�Ҫ������������������������������ÿ��·����Ҫ��������
��ָ����·���ӵ��������е�����֮�͡�
���գ���ʼ�ʸ�����һ����ʽ��A/B��A��ָҪ�츣��ħ�����������·���������� B��ָ�����츣�����������֮�������n-2��·������֮�ͣ�
ѡʹ��A/Bֵ����������
˼·:A/B���,��Ȼ��ĸӦ������С,�Ǿ������mst,���ǻ���һ����ѵĵ�·,��Ȼ������ȫͼ
ö��ÿ����������n*(n-1)/2 n<=1000��mst��ȻTLE,��ô���Կ���������mstȨֵ���Լ�mst,
��������֮��ı�Ȩ���ֵ,����������ԭ��mst�Ļ�����ֱ�ӵó�����ÿ�����ħ����·��A/Bֵ.
����ħ����·��mst��,B=sum-mp[i][j],��ħ����·ֻ��Ҫ��ȥħ����·����ı�Ȩ����,
����ħ����·����mst��,B=sum-maxLen[i][j],ħ����·������Ҫ����,���������ԭ��mst�Ļ�����,
��i��j��·���Ϲ���һ����,��ô��Ҫ��ԭ��i��j·���ϼ�ȥһ����,��ΪҪ��A/B���,��ôBԽСA/BԽ��,
��ôѡ���ȥmaxLen[i][j] i��j·���ϵ�����,��Ҳ��ΪʲôҪ�����������֮��ı�Ȩ���ֵ��ԭ��.
*/

int n,vis[N],used[N][N],pre[N];
double dis[N],val[N],maxLen[N][N],sum,mp[N][N];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(used,0,sizeof(used));
    pre[s]=s;//��һ����s����ʱ,pre[s]��δ֪��,����ʱ��û�б߼���
    for(int i=1;i<=n;i++){
        maxLen[i][i]=0;//����ʱ maxLen[pre[u]][pre[u]]���õ�,���Ҫ��ʼ��
        dis[i]=i==s?0:INF;
    }
    sum=0;
}

void prim(int s){
    init(s);
    priority_queue<pair<double,int> >Q;
    Q.push(make_pair(0,s));
    int u,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        used[pre[u]][u]=used[u][pre[u]]=1;
        for(int v=1;v<=n;v++){
            //dp����Ѽ�����ͨ���ĵ㵽�¼�����ͨ���ĵ�u��������,�����Ѽ�����ͨ���ĵ㵽pre[u]��maxLen������һ��pre[u]����ʱ�������
            if(vis[v] && v!=u)//v!=u ����max[u][u]����Ϊ0�ᱻ����,��v�����ʱ,���maxLen[pre[v]][v]ʱ maxLen[u][u]��Ϊ0�ᵼ��maxLen[pre[v]][v]���ܲ�Ϊdis[v]
                //��Ϊ����ȫͼ �ڽӾ���,����maxLen���Ժ�Q.push����һ��ѭ����,���������ȫͼ,
                //���ܲ��ܱ��������е��Ѽ���mst�ĵ�,������ʽǰ����,maxLenһ��Ҫ��������һ��for����Ѽ���mst�ĵ����
                maxLen[v][u]=maxLen[u][v]=max(maxLen[v][pre[u]],dis[u]);
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
        if(num == n) return;//���һ������ӽ���ǰ Ҫ��maxLen[v][u]��ֵ������һ��
    }
}

int main(){
    int T;
    double w,ans;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%lf",&point[i].x,&point[i].y,&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                mp[i][j]=mp[j][i]=w;
            }
        }
        prim(1);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(used[i][j])//i->j��mst��
                    ans=max(ans,(val[i]+val[j])/(sum-mp[i][j]));
                else//i->j����mst��
                    ans=max(ans,(val[i]+val[j])/(sum-maxLen[i][j]));
            }
        }
        printf("%.2f\n",ans);
    }
    return 0;
}
