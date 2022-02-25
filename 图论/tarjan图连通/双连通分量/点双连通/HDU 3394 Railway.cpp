#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 218ms ���pbc,��ջ��ѹ��,����ѹ�ߵ����� �ϸ�Ч
//�ر߲�����Ӱ�����Ľ��
//�µĶ���:"pbc������������ڵ�����ʱ��,�����pbc����ÿ���߼�������2����2�����ϵĻ�����"
/*
����:n����,m���ߵ�����ͼ(��һ����ͨ,���ر�),���һ����ͬʱ��2�����������ϵĻ�
����,���������Ϊ"��ͻ��",���һ���߲����κ�һ������,�����Ϊ"������",
����Ҫ���"������"��"��ͻ��".
����:http://acm.hdu.edu.cn/showproblem.php?pid=3394
˼·:����"������",�����κ�һ������,�Ǿ�������ͼ�����е���.
����"��ͻ��",�۲�ɷ���,"����һ������,����������ڵ�����ʱ��,
���������ÿ���߼�������2����2�����ϵĻ�����".��ô����ֻҪ���
����ͼ�����п��ܵĻ�����,��ô���õ�˫��ͨ�������Ǳ�˫��ͨ����
�����л���,���ڱ�˫��ͨ������ebc����������"1-2,2-3,1-3,3-4,4-5,3-5",
����ebc�еı���Ϊ6,����Ϊ5,��Ȼ����>����,�����������ebc��û��
һ������ͬʱ��2����2�����ϵĻ�����,ÿ����ֻ��һ������.ע�⻷��
ָ���������ÿ����ֻ����1�ξ��ܻص����Žл�,������3�������Ȼ
��Ϊ2�����Ľ���,Ҫ�ұ�Ļ����뾭���õ�,����ʱ�������3��Ȼ�þ���2��,
��Ȼ���ǻ�.���Ա�˫ͨ���ļ����ಢ���ͼ����ཻ��Ļ�.��ô���ǵ�˫��ͨ,
��˫��ͨʱ��⼫���ཻ��Ļ�,��Ϊ������,�������ұ�Ļ�ʱ,���Ժ��м�㽻��,
ʹ�ó��������,�����ǡ��ֻ����һ��.��������pbc,ͳ��pbc�ıߵĸ���,�ж�
�Ƿ�������ڵ���,���������ͻ�߼��ϵ�ǰpbc�ڱ���.
*/

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],vis[N],ans1,ans2;//ans1 �����߸��� ans2��ͻ�߸���
stack<int> s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//����pbc�ڵ����г�ͻ��
void cal(){
    memset(vis,0,sizeof(vis));
    for(int &v : pbc)
        vis[v]=1;//����ǰpbc�ڵĵ����ϱ��
    int res=0;
    for(int &u : pbc){
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])//ֻ��¼����ǰpbc�ڵĵ�
                res++;
        }
    }
    res/=2;//��Ϊ�������,�����һ�η����,ʵ�ʱ���Ҫ��2
    if(res>pbc.size())//�������pbc�ڱ������ڵ���
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//���׽ڵ����迼��
        if(!dfn[v]){
            /*
            //��ջ��÷�������,������ڿ�ͷfor��,�ᵼ��ÿ����ͨ��ĸ��ڵ㶼�޷���ջ,
            ��Ϊջ�ĺ���ȳ�����,��Ȼ���Ҳ����Ӱ��,��sÿ�ζ���ʣ��,ÿ��������ʼǰ
            ����Ҫ���һ��,���鷳,���Է���for��dfs֮ǰÿ����ͨ��ĸ��ڵ�ʵ����û��
            ��ջ��,��ÿ����ջ����v,��ǰ��uʵ������һ��dfsʱ�Ѿ���Ϊv��ջ��,����Ҳ
            ��Ӱ�����ʱǰ��pbc����ȡ.
            */
            s.push(v);
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//����������
                ans1++;
            if(dfn[u]<=low[v]){//�õ�pbc �����ͻ��
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc.push_back(tmp);
                }while(tmp!=v);
                //���u�Ǹ����ôu�����ٻ�Ҫ��ǰ���游�ڵ㹹����һ��pbc,
                //���ﲻ��ջѹ��u�ڵ�,��Ϊ���ܶ��pbc��Ҫ�õ�,do-while�������ֶ��ڵ�ǰpbc����u�㼴��
                pbc.push_back(u);
                cal();
                pbc.clear();//ÿ�ν�pbc���
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){//ԭͼ���ܲ���ͨ
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);//ԭͼ��ʹ��PBG,Ҳ��������ֱ�Ӱ����洦����.
    }
    return 0;
}

/*
//ac 202ms �߼�����ջ��,��¼pbcʱ����,��¼pbc��ʱֱ����tarjan�����
//�������ֻ��Ϊ�����pbc�еĵ�,��û�б�Ҫ��stack���¼�ߵ�(���Ƿ����),���Բ��ýϼ򵥵���ջ���¼��İ취
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;//���׽ڵ����迼��
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                int num=0;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    num++;//ÿ���߶��ǵ�ǰpbc�еı�
                    if(block[tmp.first]!=pbc_cnt){
                        pbc.push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc.push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
                if(num>pbc.size()) ans2+=num;//��pbc�������ڵ���ʱ,���б߶��ǳ�ͻ��
                pbc.clear();
            }
        }
        //pbc�еı� ����ֻ��¼�����Ҳ���ǻر�,��u����v��֮����ʵ�,���б߶���¼���ж�,
        //��ô�����ǰ��߻ᵼ����һ��pbc�ڼ�¼��ʱ�򽫵�ǰpbc�еĵ�Ҳ��¼��ȥ,��ô����ͻ����
        else if(dfn[u]>dfn[v]){
            s.push(make_pair(u,v));//ֻ��¼�����,������ж�dfn[u]>dfn[v],�������Ƚڵ�ʱ��֮���Ӧ��ǰ����ֻ�����¼һ��
            low[u]=min(low[u],dfn[v]);//u��ʱ�����v����,���ܻص���ĳһʱ�̵ĵ��ʱ�����һ����v���ʱ�����
        }
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/

/*
//ac 218ms ���pbc vector����
//�ر߲�����Ӱ�����Ľ��
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,block[N],vis[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
vector<int> pbc;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void cal(){
    memset(vis,0,sizeof(vis));
    for(int &v : pbc)
        vis[v]=1;
    int res=0;
    for(int &u : pbc){
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])
                res++;
        }
    }
    res/=2;
    if(res>pbc.size())
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    if(block[tmp.first]!=pbc_cnt){
                        pbc.push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc.push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
                cal();
                pbc.clear();
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/

/*
//ac 249ms ���pbc set����
//�ر߲�����Ӱ�����Ľ��
#include<cstdio>
#include<cstring>
#include<stack>
#include<set>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,head[N],cnt;
int dfn[N],low[N],clock,vis[N],pbc_cnt,ans1,ans2;
stack<pair<int,int> > s;
set<int> pbc;
set<int>:: iterator it;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void cal(){
    memset(vis,0,sizeof(vis));
    //set ������ for(int &v : pbc)���� c++11д��
    for(it=pbc.begin();it!=pbc.end();it++)
        vis[*it]=1;
    int res=0;
    for(it=pbc.begin();it!=pbc.end();it++){
        for(int i=head[*it];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(vis[v])
                res++;
        }
    }
    res/=2;
    if(res>pbc.size())
        ans2+=res;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans1++;
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc.insert(tmp.first);
                    pbc.insert(tmp.second);
                }while(tmp.first!=u);
                cal();
                pbc.clear();
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    ans1=ans2=pbc_cnt=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/
