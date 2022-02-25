#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//The 36th ACM/ICPC Asia Regional Dalian Site
//ac 46ms tarjan���scc����+����dp
//�ο�����:https://blog.csdn.net/Weiguang_123/article/details/7918311
//һ��ԭͼ������ʽǰ���Ǵ洢(��ߺܶ�),Ϊ���⽨����head,edge.cnt,������ͼ������vector,��Ϊ�����߾ͺ���,������������
/*
����:n����m���ߴ�Ȩ������ͼ,�ݻ�һ���ߵĻ���Ϊ��Ȩ,
����Ҫ����һ������,�ʴݻ�һ����ʹ��ͼ����ͨ������Ҫ
���ٻ���.
ע��:��������Ӧ�������رߵ�,���Ӱ��ebc����ȡ,Ҫ�����ر��ܹ��ɵ�ebc.
ԭͼӦ���Ǳ�֤������ͨͼ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4005
˼·:��Ȼ����ݻ��Ų���ʹ�䲻��ͨ,���Ƕ����¼ӵ����߲�����ȷ��,
����һ���߻�ɻ�ʹ�ñ����˵���·���ϵ��Ų�������,ֻ�ܿ��Ǵݻٻ�֮��
����,�Ǿʹ�������ȥ����,���ӵı߹��ɵĻ��ھ����ܶ�ذ����˱�Ȩ��
С����,��ôʣ����ű�Ȩ��Ȼ�ϴ�,����ֻҪȡʣ�����б�Ȩ��С���Ŵݻپͺ�,
��ô����tarjan���ebc���㹹��������(ÿ���߶���ԭͼ�е���),���ǿ���̰��ѡ��
����Ȩ��С���Ű�����ȥ,�������С�ŵ����˵������������������֧�еı�Ȩ
������ѡ����С����Ϊ�¼ӱ߹��ɻ��ڵı�,ʹ�䲻������,����ʣ�µ��ű�Ȩ��Ȼ
���ǽϴ��(��������˼������),ͬʱ����������֧�еĴ�С��Ȩ,����Ҫ��¼��
����ÿ��������֧�д�С��Ȩ����Сֵ,������̿���ͨ������dp(������С�ŵ�
���˵�ֱ���Ϊ���ڵ�dp��������)ʵ��,Ϊʲôֻ��Ҫ��¼ÿ��������֧�д�С��Ȩ��
��Сֵ������,��Ϊ���������Ѿ�ѡ����С���Ǵ���С�ſ�ʼ���컷��,��ô���ӵı�
������ô��,����������ͬʱ��������֧�е���С�ߺʹ�С��ͬʱ����������,�����
��������С��,��ô��Ȼʣ�´�С��,��ô����Ĵ�С�ߵ���Сֵ���Ǵ�,����������˴�С��,
��ô��Ҫ�Ƚϻ����С����Сֵ�͵�ǰ��֧��С��,ѡ���С��ɾ������ʹ�䲻��ͨ,�ﵽ�ݻ�Ŀ��.

ע��:ʵ�����ɵĻ��п��ܲ�����ǡ�ý����е���С�߶��Ž�ȥ,Ҳ����˵��С�ߵ���Сֵ��������
�ǱȻ�����С���Ҫ���,���ǵ�ǰ����ȷ���ӱ�ʱ����,���ڵı�Ҳ��ȷ��,���Գ��˻����С�ߵ�
��Сֵ��ȷ������,�����ߵĴ�������ǲ�ȷ����,����֧ȡ���������¼ӱ����γ�����ȫ�Ǹ���
������֧�е���С��,��Ȼ����������������в�������,������ֻȡ���ٵĻ���,���Ǵ�Сֵ����Сֵ,
����������Ǽ��������,����ݻٷǼ����������С�ĸ��.
*/

int n,m,dfn[N],low[N],clock,cnt,ebc_cnt,head[N],block[N],de[N],ans;
stack<int> s;
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if((i^1) == fa) continue;//�ر߲�Ӱ��,���Է��ظ��׽ڵ�.
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;
        }while(v!=u);
    }
}
//Ҳ������dp[u][0] dp[u][1]�ֱ���� ��С����С��Ȩ
int dfs(int u,int fa){
    //minw1��¼u�ڵ��֧����С��Ȩ,minw2��¼u�ڵ��֧�д�С��Ȩ ����u-v�ı�Ȩ
    //sonw��¼v��������С��Ȩ ������u-v�ı�Ȩ
    int minw1=INF,minw2=INF,sonw;
    for(pair<int,int> &v : G[u]){
        if(v.first == fa) continue;
        sonw=dfs(v.first,u);
        sonw=min(sonw,v.second);//�ȽϺ�u-v�ı�Ȩ�ĸ���С
        //���v��������С��Ȩ�ȵ�ǰu������֧�м�¼������С��Ȩ��С
        //���´�С��ȨΪ֮ǰ����С��,�ڸ�����С��Ϊsonw
        if(sonw<minw1){
            minw2=minw1;
            minw1=sonw;
        }
        else if(sonw<minw2) minw2=sonw;//�������sonw����С�ߴ�,�ȴ�С��С,�͸��´�С��
    }
    ans=min(ans,minw2);//��¼�����С�ߵ���Сֵ ��Ϊ�߻���������Ҫ�Ĵ���
    return minw1;//����������֧����С��Ȩ
}

int main(){
    int u,v,w,s,t;
    while(scanf("%d%d",&n,&m)!=EOF){
        ebc_cnt=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(de,0,sizeof(de));
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        tarjan(1,-1);
        if(ebc_cnt == 1){//����������EBG(��˫��ͨͼ),�򲻴�����
            printf("-1\n");
            continue;
        }
        w=INF;
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                de[block[u]]++;
                de[block[v]]++;
                G[block[u]].push_back(make_pair(block[v],edge[i].w));//����������
                G[block[v]].push_back(make_pair(block[u],edge[i].w));
                if(w>edge[i].w){//��¼��С��Ȩ���ŵ����˵� s��t
                    w=edge[i].w;
                    s=block[u],t=block[v];
                }
            }
        }
        int res=0;
        for(int i=1;i<=ebc_cnt;i++)
            if(de[i] == 1) res++;//���ڶ�Ϊ1��Ҷ�ӽڵ�+1
        //�����������Ϊ1�ĵ�ֻ��2����,Ҳ����һ��ֱ��,��ô�����һ����λ��ӵı߾���ֱ�ӳ�ΪEBG,֮��Ͳ���������.
        if(res == 2) printf("-1\n");
        else{//���������һ�����н��,��Ϊ��Ϊ1�ĵ�����Ϊ3,Ҳ����һ������2����֧�Ľڵ�,��ô��һ�����ڴ�С��
            //��Щ�������������ж�ansΪINF,ԭͼ����ͨ,�������ر����������.
            ans=INF;
            dfs(s,t);//��s��dp����
            dfs(t,s);//��t��dp����
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
//�ݸ�ֽ�ϵ�����
input
8 7
1 2 4
2 3 1
3 4 2
4 5 3
3 7 5
3 6 6
4 8 4

output
4
*/
