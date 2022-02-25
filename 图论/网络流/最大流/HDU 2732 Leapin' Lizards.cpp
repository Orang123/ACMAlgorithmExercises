#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define N 1000
#define M 1600000
#define INF 0x3f3f3f3f
using namespace std;
//ac 0ms dinic
/*
����:����һ������,�����ϵ�һЩλ��('L')����һֻ����,��������������Ծ������d,
���һֻ���������������Ե,��ô���Ͱ�ȫ��.��ÿ��������һ�������������x,
�������xֻ����������������,����������Ҳ���������������.���������ж�
��ֻ��������������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2732
˼·:��Ϊÿ��λ���������������,����ֱ�ӱ�����Ҫö�����п�������λ�õĿ�����,
��¼���������������������,�Ⲣ����һ������ʽʱ��.���ڿ��Խ�ÿ������ĵ�(i-1)*m+j,
����Ϊ(i-1)*m+j��(i-1)*m+j+n*m������������ͳ���,����Դ��0,���n*m*2+1,ÿ��'L'(������)
�ĵ㽨0->(i-1)*m+j,����Ϊ1(ÿ���������ֻ����һ������),����õ��������������ǰ����,
��㵽���㽨����Ϊs1[i][j]-'0'�ı�,��:(i-1)*m+j->(i-1)*m+j+n*m,ÿ��������������Ծ����
d֮����������,�����ͻ������ΪINF������,��:(i-1)*m+j+n*m->n*m*2+1,��������������d����
֮������������������,֮�����������������ж���ֻ��������������,��𰸾�Ϊԭ������������-�����.

ע��:����ʱ��ÿ�����������ֻ��1ֻ����������,��ô��������Ľⷨ�᲻�������Ҫ���ͻ��?
�����,������kֻ�����ܳ�ȥ,��ôһ������һ����������Ҫ��Ľ�,ʹ����kֻ���水˳���ȥ,
������ʱ��ÿ�����������ֻ��1ֻ����.(������ĳ��ʱ��,����j���ȥ,������������h��,
��������h���Ѿ���������,��ô������Υ���������Ҫ��. ��ʵ���ǿ�����ô��,����Ϊʲô����
����h�ϵ������Ȱ�������j��ǰ������·�߳�ȥ,Ȼ����������j������h��ȥ���֮ǰ������,
��ô�����Ȳ�Υ������,Ҳ�õ��˽�)
*/
int cas,n,m,d,cnt,head[N],st,ed,dis[N],sum,ans;
char s1[30][30],s2[30][30];
struct Edge{
    int to,next,cf;
}edge[M<<1];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed) return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow) break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(){
    while(bfs(st))
        ans+=dfs(st,INF);
    return ans;
}

void init(){
    cas++;
    ans=sum=st=cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&d);
        for(int i=1;i<=n;i++){
            scanf("%s",s1[i]+1);
            if(i == 1){
                m=strlen(s1[1]+1);//m=�����ж�����
                ed=n*m*2+1;//�����
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%s",s2[i]+1);
            for(int j=1;j<=m;j++){
                if(s2[i][j] == 'L'){//����õ�����������
                    sum++;//��¼����
                    addEdge(0,(i-1)*m+j,1);//��Դ�㽨����Ϊ1�ı�
                }
                if(s1[i][j] == '0') continue;//��������������������Ϊ0,�򲻽������ͳ����Լ��ͻ�������
                addEdge((i-1)*m+j,(i-1)*m+j+n*m,s1[i][j]-'0');
                if(i+d>n || i-d<1 || j+d>m || j-d<1)//����ǰ������d��������������,�������㵽��������
                    addEdge((i-1)*m+j+n*m,ed,INF);
                else{//����ö�ٸõ�d�������������ĵ�,������ǰ����㵽�������������,����ΪINF
                    for(int x=1;x<=n;x++){
                        for(int y=1;y<=m;y++){
                            if(s1[x][y] == '0') continue;
                            if(x == i && y == j) continue;
                            if(abs(x-i)+abs(y-j)<=d)//�����پ���С��d�򽨱�
                                addEdge((i-1)*m+j+n*m,(x-1)*m+y,INF);
                        }
                    }
                }
            }
        }
        max_flow();
        if(sum-ans == 0)
            printf("Case #%d: no lizard was left behind.\n",cas);
        else if(sum-ans == 1)
            printf("Case #%d: 1 lizard was left behind.\n",cas);
        else
            printf("Case #%d: %d lizards were left behind.\n",cas,sum-ans);
    }
    return 0;
}
