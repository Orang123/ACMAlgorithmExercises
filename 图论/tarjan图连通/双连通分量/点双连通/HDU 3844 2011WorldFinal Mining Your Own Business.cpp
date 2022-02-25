#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;
//2011WorldFinal ͬ���P3225[HNOI2012]�󳡴
//ac vector stack��� ��¼pcb���� 390ms
/*
��ظ���:
˫��ͨ����(Biconnected Connected component-BBC)
��˫��ͨͼ:��һ������ͼ�е�ȥ������һ���ڵ�,������ı��ͼ����ͨ��,
�������ڸ��,�������˫��ͨͼ(Point Biconnected Graph-PBG).
��ͼ����������ͬ��֮�䶼�����������㲻�ظ���·��.��Ҫ����ǰ�߶���PBG.
��˫��ͨ����:һ������ͼ�е�ÿһ�������˫��ͨ��ͼ����������ͼ�ĵ�˫��ͨ����(Point Biconnected Component-PBC).

ע��:
1.����PBC���󷨿�����tarjan�����Ĺ�����,������dfn[u]<=low[v]ʱ,�ͼ�¼һ��PBC,�����uΪ���,������Ҫ
���е���,���u���Ǹ��ڵ�,������ӷ�֧��С��2,��ôuʵ�ʲ��Ǹ��,������֮ǰ����¼��PBC��Ȼ�ǶԵ�.
2.��Ȼ��˫��ͨ����(pbc)�в����ڸ��,���Ƕ���ԭͼ����,�������ڵ����������,ĳ����һ����ԭͼ�еĸ��,
����ԭͼ��ɾ��������,�������ܶ�pbc.
3.pbc��ԭͼ�еĸ����ܲ�ֹһ��.�ܶ��.
4.һ�������ͬʱλ�ڶ��pbc��,һ��pbc��������������,һ����û����ͨ�ĸ���.
5.���͵�˫��ͨ�������رߵĴ����������һ����,��Ϊɾ��һ�����,��������������б߶���ɾ��.
6.�����ر߲���Ӱ���˫��ͨ������ж�.
7.n���������ͼ,�����n-1��pbc.
8.��˫�ͱ�˫�������Ļ����������.(���忴HDU 3394 ͼ�ⲿ��)
��˫ͨ���ļ����ಢ���ͼ����ཻ��Ļ�;
��˫��ͨʱ��⼫���ཻ��Ļ�;
���ڱ�˫ͨ���ļ����ಢ���Ļ�,��ʹebc�б������ڵ���,�������б�
Ҳ��ֻ��һ������,����˫ͨ���ļ����ཻ��Ļ�,���pbc������������ڵ���
��ôpbc�����б߶�������2������.
*/

/*
������ժ������
����:��һ�����µ�ϡ�н�������n�������һЩ���ӵ����,����ÿ����������������ӵ�.
�����������ӵ�֮�������һ�����.Ϊ�˽��Ϳ󹤵�Σ��,�����������һЩ���ӵ㴦��װ
̫ƽ������Ӧ������װ��,ʹ�ò����ĸ����ӵ㵹��,���ڴ����ӵ�����п󹤶��ܵ���̫ƽ��
����(�ٶ����˵��������ӵ㲻��ͨ����,����������������ӵ��������).Ϊ�˽�Լ�ɱ���
��Ӧ���ھ����ٵ����ӵ㰲װ̫ƽ��������Ҫ���㵱̫ƽ������Ŀ��Сʱ�İ�װ��������.

����:��һ������ͼ(���ܲ���ͨ)��,��һЩ��Ϳ�Ϻ�ɫ,ʹ��ɾ��ͼ���κ�һ����ʱ,ÿ����ͨ����������һ���ڵ�.
��������Ϳ�����ڵ�,������Ϳ���ٵ�������м��ַ���.

����:http://acm.hdu.edu.cn/showproblem.php?pid=3844

˼·:���ҪͿ���ٵĺڵ�,����Ȼ����Ҫ,ɾ��ĳ�����,ԭͼ����������ͨ������,
����ÿ�����ѵĲ��ֶ�������Ҫһ���ڵ�,��ô���������и��,��ô����ת��Ϊ�����
��˫��ͨ����(pbc),����������Ҫ���ö��ٺڵ�,ʵ�ʾ����ʼ������,��Ȼ�����ڸ��
���úڵ�,����һ��ɾ�����,�����е�Ĺ��˶���������,��ôɾ���ĵ���Ҫ���Ǽ������,
��Ϊ���ɾ���Ĳ��Ǹ��,��ô����ͼֻ������һ����Ϊ�ڵ㼴������,�������ɾ���ĵ��Ǹ��,
��ôԭͼ�Ϳ��ܷ�Ϊ�ü�����ͨ��,��ôÿ����ͨ�Ͷ�����Ҫ����һ���ڵ�,��Ȼ������Ҫ���Ǽ������,
ɾ���ĵ���ÿ�����Ŀ�������,�������������Ҫ���ü����ڵ���ܱ�֤���й��˶�������,���ڴ�
��������ⷽ����.
����ֻ�����pbc�еĵ���ԭͼ������Ǹ��,�Ҹ�����ĿΪ1,��ô˵�����ɾ���ø��,
��pbc�϶�����ԭͼ����ͨ,��ô���pbc�б������һ���ڵ����������ô�ɷŵķ��������ݳ˷�ԭ��
����ans*=pbc.size()-1;�����pbc�еĵ���ԭͼ�и�����Ŀ���ڵ���2,˵��ɾ�����pbc��
ĳһ�����,�Ǹ�pbc������ԭͼ������pbc��ͨ,��ô��pbc�Ϳ��Բ����úڵ�(������),
��Ϊÿ����Ĺ��˿����ӵ����pbc����������������.

�������ԭͼ�������PBG(��˫��ͨͼ),�������ڸ������,��ô���˿�����Ҫ��������2���ڵ�,
��Ϊ��һɾ���ĵ�պ��Ǻڵ�,��ô����Ҫ�ٱ���һ��,��������C[n][2]=n*(n-1)/2.���������Ҫ����.
*/

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt,block[N];
ll n;
stack<pair<int,int> > s;//pair<u,v> ��¼�߼����˵�
vector<int> pbc[N];//��¼ÿ����˫��ͨ����pbc�����е�ı��

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            /*
            ����Ҫ��ջ��ѹ������Ϊ,���ѹ��,�޷�ѹ��u��,
            do while��ջʱ,�޷���������,����u�㻹����Ҫ��ջ���,
            ��Ҳ��ѹ��������ڵ�����,����Ҫ��ȡ��dfs֮ǰ��ջ��ѹ���,
            ������Ϊһ���������λ���λ�ڶ��pbc��,���Աߵ������˵�,
            �ڼ�¼pbcʱҪ����.
            */
            s.push(make_pair(u,v));
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                //��¼u��Ϊ���,������ڸ��ڵ���ܱ����Ǹ��,����Ҫ��¼��pbc,
                //��for������������Ӹ����ٽ�����Ϊ���Ǹ��.
                vis[u]=1;
                pbc_cnt++;//pbc����+1,��Ӧ���
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    //����u-v,u��v����Ҫ����,��Ϊu v���п����ڿ���ջ���ı߼����Ѿ���¼��pbc
                    //��Ŀ����1��(u)3-2 (u)3-5�����п���ͬʱ��ջ��,Ȼ��6-3(v),����3ͬʱ��Ϊu����2��,��ΪvҲ����һ��,���Ѿ���¼��
                    if(block[tmp.first]!=pbc_cnt){//u���Ƿ��Ѿ���¼����Ϊpbc_cnt��pbc��
                        pbc[pbc_cnt].push_back(tmp.first);
                        block[tmp.first]=pbc_cnt;//��¼u��������pbc�ı��
                    }
                    if(block[tmp.second]!=pbc_cnt){
                        pbc[pbc_cnt].push_back(tmp.second);
                        block[tmp.second]=pbc_cnt;
                    }
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)//����uΪ���ڵ��������С��2,��ֻ��¼��pbc,u�㱾��ȴ���Ǹ��
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(block,0,sizeof(block));//����һ��Ҫ��ʼ��Ϊ0,��Ϊblock�ڼ�¼pbc�е��ʱ��Ҫ����
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        //n���������ͼ�����n-1��pbc,���Գ�ʼ���Ͻ�<=n-1,������m��ʼ��,�������m���Ͻ�Զ����n,������Խ��runtime error
        //��Ϊpbc�����ǰ�N����
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){//��������,ԭͼ���ǵ�˫��ͨ��,��ֻ��ѡ2������Ϊ�ڵ�,һ������
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);//n<=50000 n*n<=25*10^8 int���
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(int &e : pbc[i]){
                if(vis[e])
                    cut_num++;//��¼��pbc�и����Ŀ
            }
            if(cut_num == 1){//�����ĿΪ1ʱ,��pbc�оͱ�������һ���ڵ�,������Ϊpbc�е������һ
                ans1++;
                ans2*=pbc[i].size()-1;//�˷�ԭ��
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
/*
input
9
1 2
2 3
3 4
4 5
5 6
6 7
1 3
3 5
5 7
output
2 4

input
11
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
1 3
3 5
7 9
output
2 4

input
9
1 3
4 1
3 5
1 2
2 6
1 5
6 3
1 6
3 2
output
2 4

input
6
1 2
1 3
2 4
2 5
3 6
3 7
output
4 1
*/

/*
//ac 390ms stack����ջ���pbc ����������
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt;
ll n;
stack<int> s;
vector<int> pbc[N];//��¼ÿ����˫��ͨ����pbc�����е�ı��

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            s.push(v);
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                vis[u]=1;
                pbc_cnt++;
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].push_back(tmp);
                }while(tmp!=v);
                pbc[pbc_cnt].push_back(u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)//����uΪ���ڵ��������С��2,��ֻ��¼��pbc,u�㱾��ȴ���Ǹ��
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        //n���������n-1��pbc
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){//��������,ԭͼ���ǵ�˫��ͨ��,��ֻ��ѡ2������Ϊ�ڵ�,һ������
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);//n<=50000 n*n<=25*10^8 int���
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(int &e : pbc[i]){
                if(vis[e])
                    cut_num++;//��¼��pbc�и����Ŀ
            }
            if(cut_num == 1){//�����ĿΪ1ʱ,��pbc�оͱ�������һ���ڵ�,������Ϊpbc�е������һ
                ans1++;
                ans2*=pbc[i].size()-1;//�˷�ԭ��
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
*/

/*
//ac set ��¼pcb���� 514ms
#include<cstdio>
#include<set>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
typedef long long ll;

int m,dfn[N],low[N],num,cnt,head[N],rt,vis[N],pbc_cnt;
ll n;
stack<pair<int,int> > s;
set<int> pbc[N];
set<int>:: iterator it;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v,son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            s.push(make_pair(u,v));
            dfs(v,u);
            if(u == rt) son++;
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                vis[u]=1;
                pbc_cnt++;
                pair<int,int> tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    pbc[pbc_cnt].insert(tmp.first);//set��������ظ�Ԫ��
                    pbc[pbc_cnt].insert(tmp.second);
                }while(tmp.first!=u);
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(u == rt && son<2)
        vis[u]=0;
}

int main(){
    int u,v,cas=0;
    while(scanf("%d",&m) && m){
        cas++;
        n=pbc_cnt=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
            n=n>max(u,v)?n:max(u,v);
        }
        for(int i=1;i<n;i++) pbc[i].clear();
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                rt=i;
                dfs(i,-1);
            }
        }
        if(pbc_cnt == 1){
            //int���2147483647,N*N<=2500000000 n�����int�����
            printf("Case %d: %d %lld\n",cas,2,n*(n-1)/2);
            continue;
        }
        ll ans1=0,ans2=1;
        for(int i=1;i<=pbc_cnt;i++){
            int cut_num=0;
            for(it=pbc[i].begin();it!=pbc[i].end();it++){
                if(vis[*it])
                    cut_num++;
            }
            if(cut_num == 1){
                ans1++;
                ans2*=pbc[i].size()-1;
            }
        }
        printf("Case %d: %lld %lld\n",cas,ans1,ans2);
    }
    return 0;
}
*/

/*
//��ȵ���һ��dfs�������� ����˼·��,�������������"����"��
//���ȿ���������Tarjan�� ������ô��
//���ȼ������ǰ����еĵ�˫������ ��ô����һ�����Եõ�һ���� Ȼ�����Ǿͻᷢ��
//1.Ҷ�ӽڵ�(ֻ����һ�����ĵ�˫)���뽨 ��ΪҶ�ӽڵ�������� һ����㱻����������
//2.��Ҷ�ڵ�(�����������������ϵĸ��ĵ�˫)���ý� ��Ϊ��ʹһ����㱻����Ҳ����������һ������ߵ�һ��Ҷ�ڵ�
//3.����һ���������������ͨ�鶼�ǵ�˫(���������ĵ�˫) �����������۵�˫�Ĵ�С
//���ֻ��һ���� ��ô�������뽨 ����û�п�����ĵ�������ûд(��ʵ������д�� Ȼ�󻹹���)
//������������������ϵĵ� ��ôҪ������ һ�������˻���������һ��
//���������ǳ˷�ԭ��������� ע��Ҷ�ڵ�������ڲ��ܽ��ڸ����
//������Tarjan������dfsһ��ÿ����ͨ��ͺ��ˡ�

#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int head[505],dfn[505],low[505],vis[505],stack[505];
bool cut[505],in_stack[505];
int n,m,cnt,num,tot,deg,ans1,T,cases,root,top;
ll ans2;
struct node
{
    int from;
    int to;
    int next;
}e[1010];
inline void first()
{
    memset(head,0,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(cut,0,sizeof(cut));
    memset(vis,0,sizeof(vis));
    top=cnt=tot=n=ans1=T=0; ans2=1;
}
inline void insert(int from,int to)
{
    e[++num].from=from;
    e[num].to=to;
    e[num].next=head[from];
    head[from]=num;
}
inline int read()
{
    int x=0,f=1; char c=getchar();
    while (c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while (c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void Tarjan(int now,int father)//����
{
    dfn[now]=low[now]=++tot;
    for(int i=head[now];i;i=e[i].next)
        {
            int v=e[i].to;
            if(!dfn[v])
            {
                Tarjan(v,now);
                low[now]=min(low[now],low[v]);
                if(low[v]>=dfn[now])
                {
                    if(now==root) deg++;
                    else cut[now]=true;
                }
            }
            else if(v!=father) low[now]=min(low[now],dfn[v]);//��Ҫ���󻷻��� ����ԭ��ȥ������
        }
}
void dfs(int x)//����ÿ����ͨ��
{
    vis[x]=T;//���
    if(cut[x]) return;
    cnt++;//����
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(cut[v]&&vis[v]!=T) num++,vis[v]=T;//ͳ�Ƹ����Ŀ��
        //����Ǹ���ұ�ǲ�������ĵ���ͨ����ͬ���޸ı�ǡ�
        if(!vis[v])dfs(v);
    }
}
int main()
{
    m=read();
    while (m)
    {
        first();
        for (int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            n=max(n,max(u,v));//����ط�Ҫ����һ��
            insert(u,v); insert(v,u);
        }
        for (int i=1;i<=n;i++)
        {
            if (!dfn[i]) Tarjan(root=i,0);
            if (deg>=2) cut[root]=1;//���ڵ�ĸ��
            deg=0;//��Ҫ�����Ƕ�������
        }
        for (int i=1;i<=n;i++)
            if (!vis[i]&&!cut[i])//���Ǹ��
            {
                T++; cnt=num=0;//TΪ��ͨ��ı��
                dfs(i);
                if (!num) ans1+=2,ans2*=cnt*(cnt-1)/2;//������ �����ǳ��Զ� ��Ϊ���������ĳ���û�в���
                if (num==1) ans1++,ans2*=cnt;//��һ��
            }
        printf("Case %d: %d %lld\n",++cases,ans1,ans2);
        m=read();
    }
    return 0;
}
*/
