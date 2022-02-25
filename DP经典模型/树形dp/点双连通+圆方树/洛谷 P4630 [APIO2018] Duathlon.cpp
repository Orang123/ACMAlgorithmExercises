#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
//ac 876ms ��O2 tarjan���pbc����Բ����+����dp�������·����Ȩ��
/*
����:n����m��������ͼ,���ж��ٶ���Ԫ��(s,c,f)(s,c,f������ͬ)
ʹ�ô���һ����·����s����,����c����f.
����:https://www.luogu.com.cn/problem/P4630
˼·:����pbc(��˫)������2������:
1.pbc����������(s,f)֮���·����Ȼ��һ����·���ᾭ����pbc������һ��c.
2.��1���Ƴ�����Բ������������Բ��s,f֮���·���ϲ�ͬ���м�ĵ��������
s��f������pbc�����е�Ĳ����Ĵ�С,��s��f������pbc������һ�㶼����Ϊs��f·���ϵ��м��.
�������pbc��֤��pbc����������֮�����ͨ��,��s��f·����;����pbc,��ôpbc
������һ�㶼����Ϊ�м������.
��2�����ʵ�֤�����Բο�����:https://www.cnblogs.com/PinkRabbit/p/10446473.html

��ô���ڸ�Բ�������ϵ�Ȩ,����ĵ�ȨΪ��Ӧpbc�е�ĸ���,Բ��ĵ�ȨΪ-1.
�����ᷢ��Բ������������Բ��֮��·��������Ϊ·���ϵ�Ȩ��,������Ҫע��
����Բ-��-Բ����ʵ��ֻ��2��Բ���·��,��Ȩֵ�ۼӺ͸պ���0,����֮���Խ�
Բ���Ȩ����Ϊ-1,����ΪԲ�����ϵ���������һ����Բ-��-Բ-��-Բ��������,
����Ϊͬһ�����ͬʱ���׸����pbc,��ô·����2������ķ�����м�Բ��ĸ���
���ظ��ۼ�һ��,��������һ·�����м��Ķȶ���2,��ζ�ż���ʱֻ����ͬʱΪ
�������ڷ��㹱��,ֻ�н�Բ���Ȩ����Ϊ-1,���ܵ������ظ����׵ĸ���,������
s��f·�������˵��Բ��,ʵ�ʲ�������Ϊ�ظ����׶�����-1,����Ϊ����·������
ʱ,�ǰ������˵�̶�����,ͨ�������м�Բ��ĸ���������·��������,�������˵�
s��f�������������,���Ե�Ȩ����Ϊ-1�պý����ڷ���Ķ���ĵ�Ȩ����.
�����ٽ�һ��˼��,ʵ��������Ҫ����ľ���Բ������·��Բ���������2�����в�ͬ·��
�ĵ�Ȩ��(Բ��+����),��ôʵ�ʿ��Ե�������ÿ����(Բ��+����)���׸��˶������˵�Ϊ2Բ���·��,
Ҳ����ʵ�ʸõ�ĵ�Ȩ�����˶��ٴ�,�����ͨ������dp�����.����һ��ͳ�Ʊ�Ȩ������·�����״���
������dp����ĿHDU 5723 Abandoned country.

�ܵ���˵����ͨ���̶�s,f���˵�����ʵ����ѡȡ���м��c�ĸ���ת�������s-f·����Ȩ������.
*/
int n,m,head[N],cnt;
int dfn[N],low[N],clock,num,pbc_cnt;//pbc_cnt����
//siz[u]��¼����Բ������u�ڵ���������uԲ��ĸ���,ֻ��Բ����ʵ�ʴ��ڵĵ�.
//val��¼Բ������ÿ����ĵ�Ȩ Բ��Ϊ-1,����Ϊ��Ӧpbc�е����,����ĶȾ��Ƕ�Ӧpbc�е�ĸ���
ll ans,val[N<<1],siz[N<<1];
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    num++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(v);
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                int tmp;
                do{
                    //sizҲ�����÷�����Ϊu����ڵ�ĸ��׼��������,�˳�do-while��u����Ϊ����ĸ���
                    tmp=s.top();
                    s.pop();
                    val[pbc_cnt]++;
                    G[pbc_cnt].push_back(tmp);//����Բ����
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                val[pbc_cnt]+=2;//val��ʼֵΪ-1 ���Լ�u�󻹵��ټ�1
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)=O(2n+2n-1)~=O(n)
void dfs(int u,int fa){
    siz[u]=u<=n?1:0;//ֻ��¼Բ�����,ֻ��Բ����ʵ�ʴ��ڵĵ�,������ظ����㹱�׵�·������
    for(int v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
        /*
        ֮ǰͳ�Ƶ�u������Բ���뵱ǰv������Բ��ֱ���Ϊ(s,f)·�����˵�s��f,
        �˷�ԭ�� �˻������ܹ��ɵ����в�ͬ·���ĸ���,Ҳ����val[u]Ӧ�ù��׸������·�����ܴ���.
        �����uΪԲ��ʱ,v��Ȼ�Ƿ���,�����㲻����Ҷ�ӽڵ�,����siz[v]��Ȼ>=1,�������Բ-��-ԲҲ���������.
        ��2����Ϊ,s��f���Եߵ�Ҳ����(s,c,f)(f,c,s),ÿ��·������2�ֱ����ʽ.
        ��Ҳ�Ǻͼ����Ȩ�����ߵ㹹��·�����״�����ͬ�ĵط�.
        */
        ans+=2*val[u]*siz[u]*siz[v];
        siz[u]+=siz[v];//�ȳ˷�ԭ��������ۼ�siz
    }
    //����Բ�����游�ڵ��е�Բ�㻹����u�������е�Բ�㹹���µ�(s,f)·��
    //�游�ڵ���Բ��ĸ���Ϊnum-siz[u],numΪ��ǰ��ͨ���е�ʵ�ʽڵ���Ҳ���ǵ�ǰԲ������Բ���ܸ���.
    ans+=2*val[u]*siz[u]*(num-siz[u]);
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    memset(head,-1,sizeof(head));
    memset(val,-1,sizeof(val));//��ʼ��Բ������ȨΪ-1
    memset(dfn,0,sizeof(dfn));
    int n2=n<<1;
    for(int i=1;i<n2;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){//ԭͼ���ܲ���ͨ,����Բ�������ܹ���ɭ��
        if(!dfn[i]){
            num=0;
            tarjan(i,-1);
            dfs(i,-1);
        }
    }
    printf("%lld",ans);
    return 0;
}
