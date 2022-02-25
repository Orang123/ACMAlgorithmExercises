#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//ac 44ms ʵ�ʻ��ǰ������������ÿ������ѡȡһ����Ʒ�ķ��鱳��
//ÿ����ƷΪ ����+������ܸ������
//���Ӷ�O(nv) 01����
/*
����:n����Ʒ,��Ϊ����,�ֱ��������͸���,ÿ����Ʒ
�ж�Ӧ�ļ۸�v,��Ҫ�̶�p,�Լ�����Ӧ���������q,��
qΪ0ʱ�������Ʒ������,�������Ʒ������q�ĸ���.��Ҫ
�򸽼��ͱ����ȹ���ø�������Ӧ������,�����޷������
����,ÿ������������0��1��2������,��Ҫ�ȷ�Ϊ1~5.����
��mԪǮ,����n����Ʒ���ܻ�õļ۸����Ҫ�̶ȳ˻�����
���ܺ��Ƕ���.
ע��:����֮�䲢û��֮���������ϵ,����ֻ��������.
����:https://www.luogu.com.cn/problem/P1064
˼·:��Ϊÿ���������Ҳֻ��2������,��˶������е���Ʒ
���Դ����е�������ʼö�ٹ���,��5�ֿ����Եķ���:
�����������2������
1.�������
2.���������
3.��������Լ���1������
4.��������Լ���2������
5.��������Լ������е�2������
�������û�и�����ֻ�����1��2,���������ֻ��1��������ֻ��
���1��2��3.
��ô��Ȼ������01����ģ���������,��Ʒ���Ϊ�۸�,��Ʒ��ֵΪ
��ֵ����Ҫ�ȵĳ˻�,��������:
��չ:���ÿ�������ж������,����ֱ���ȷŸ����ٷ�����,ֻ�ǲ���������,ǰһ״̬��
֮ǰ�����������������Ž�,�������������еĸ���.�ɲο�HDU 3449����.����ֱ�ӽ���һ��
��,ֱ����dfs���������dfs�����н���01����.

ʵ������������ǰ������������ÿ������ѡȡһ����Ʒ�ķ��鱳��
ÿ����ƷΪ ����+������ܸ������
*/
int n,m,dp[M];
//mc��������
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
}mc[N];
//ax[i]��������i��Ӧ�����и���
struct AX{
    int num;//����i����Ӧ�ĸ�������
    Goods gds[3];//һ�����������2������
}ax[N];

int main(){
    int v,p,q;
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//0 �������Ʒ������
            mc[i]=Goods(v,v*p);
        else{//����������Ʒ������q�ĸ���
            ax[q].num++;//����q�ĸ�����+1
            ax[q].gds[ax[q].num]=Goods(v,v*p);//������Ӧ�����ļ۸�ͼ�ֵ
        }
    }
    for(int i=1;i<=n;i++){//n����Ʒ
        //����ֻ��������,mc[i].w��Ϊ0�����i����ƷΪ����
        for(int j=m;mc[i].w && j>=mc[i].w;j--){
            //ʵ�ʾ����ڵ�i�������µķ������,����+1/2����������� ��4��ѡȡ���
            //���1 2 ������ѡȡ��� ֻ������
            dp[j]=max(dp[j],dp[j-mc[i].w]+mc[i].val);
            //�������и���
            if(ax[i].num){//����+����
                //���3 �����͸���1��ѡȡ���
                if(j>=mc[i].w+ax[i].gds[1].w)
                    dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[1].w]+mc[i].val+ax[i].gds[1].val);
                //���������ĸ�������2��
                if(ax[i].num == 2){
                    //���4 �����͸���2��ѡȡ���
                    if(j>=mc[i].w+ax[i].gds[2].w)
                        dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[2].w]+mc[i].val+ax[i].gds[2].val);
                    //���5 �����͸���1�Լ�����2��ѡȡ���
                    if(j>=mc[i].w+ax[i].gds[1].w+ax[i].gds[2].w)
                        dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[1].w-ax[i].gds[2].w]+mc[i].val+ax[i].gds[1].val+ax[i].gds[2].val);
                }
            }
        }
    }
    printf("%d",dp[m]);
    return 0;
}

/*
//ac 105ms ���鱳��ÿ������ȡһ����Ʒ�򻯰汾
//����������,ÿ�����ƷΪ����+(�������ܵĸ������)
//ʵ�ʿ������:
//��һ����Ʒ�ļ۸��ʵ��Ȩ�ص���������
//�ڶ�����Ʒ�ļ۸��ʵ��Ȩ�ص��ڵ�һ����Ʒ+��һ��������
//��������Ʒ�ļ۸��ʵ��Ȩ�ص��ڵ�һ����Ʒ+�ڶ���������
//���ĸ���Ʒ�ļ۸��ʵ��Ȩ�ص��ڵڶ�����Ʒ+�ڶ���������
//������һ��forѭ�����е��Ƽ��㣬ÿ�μ����¸���ʱ�ڱ�������
//�ø�����Ӧ�����͸���������������ͬʱ�����ۼӣ����ۼӺ�Ľ��push_back��ĩ�˼���
//���Ӷ�O(k*v*num[k])=60*32000=1.92*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 70
#define M 33000
using namespace std;

int n,m,dp[M];
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
};
vector<Goods> gds[N];

int main(){
    int v,p,q,len;
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//������Ϊһ��
            gds[i].push_back(Goods(v,v*p));
        else{
            len=gds[q].size();
            //����������������������Ϊ�����ڶ�������Ʒ
            for(int j=0;j<len;j++)
                gds[q].push_back(Goods(v+gds[q][j].w,v*p+gds[q][j].val));
        }
    }
    for(int i=1;i<=n;i++){
        if(!gds[i].size()) continue;//��i����Ʒ��������
        for(int j=m;j>=0;j--){
            for(Goods &k : gds[i]){
                if(j>=k.w)
                    dp[j]=max(dp[j],dp[j-k.w]+k.val);
            }
        }
    }
    printf("%d",dp[m]);
    return 0;
}
*/

/*
//ac 83ms ���鱳����ǰ������ȡһ����Ʒ�뵱ǰ��һ����ƷҲ��ѡ �Ƚ���ȡ����ֵ
//����������,ÿ�����ƷΪ����������1������2
//���ù��������Ż� 2������һ������ֻ��¼ǰi-1��״̬tp,��һ�������¼ǰi��״̬dp
//�ȿ��ǹ�������,�ٿ����������ѹ����״̬�� ��ʣ�µĸ����������01����
//���Ӷ�O(k*v*num[k])=60*32000=1.92*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 70
#define M 33000
using namespace std;

//tp[j]����ǰi-1���״̬
//dp[j]����ǰi���״̬
int n,m,dp[M],tp[M];
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
};
vector<Goods> gds[N];

int main(){
    int v,p,q;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//������Ϊһ��
            gds[i].push_back(Goods(v,v*p));
        else
            gds[q].push_back(Goods(v,v*p));
    }
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    for(int i=1;i<=n;i++){
        if(!gds[i].size()) continue;//��i����Ʒ��������
        //��ǰi-1������Ž⸳ֵ��tp
        for(int j=0;j<=m;j++)
            tp[j]=dp[j];
        //ǰi���״̬��ʼ��Ϊ-INF
        memset(dp,-0x3f,sizeof(dp));
        //�ȹ�������
        for(int j=m;j>=gds[i][0].w;j--)
            dp[j]=max(dp[j],tp[j-gds[i][0].w]+gds[i][0].val);
        //�����ǰ��ֻ������ gds[i].size()=1 �����ֱ���˳�
        //��dp�������������� �������븽�� 01����
        for(int k=1;k<gds[i].size();k++){
            for(int j=m;j>=gds[i][k].w;j--)
                dp[j]=max(dp[j],dp[j-gds[i][k].w]+gds[i][k].val);
        }
        //�Ƚ�ǰi�����Ž� ��ѡȡ��i����Ʒ(dp[j])�Ͳ�ѡȡ��i����Ʒ(ǰi-1����Ʒtp[j])״̬�Ƚ� ѡȡ����ֵ
        for(int j=0;j<=m;j++)
            dp[j]=max(dp[j],tp[j]);
    }
    printf("%d",dp[m]);
    return 0;
}
*/

/*
//ac 63ms ��ǰ���α���ͳ�Ƴ��������������ٽ��к�������01����
//���Ӷ�(nv) ��׼��01�������Ӷ�
//������������ܴ���������ϵΪ2��������ϵ(�������⡢HDU 3449��USACO Video Game Troubles)
//��������ǲ����������͸�����,����ÿ����Ʒ֮�䶼������һ��������ϵ,
//������ϵ����Ƕ��,������ϵ���߶ȿ��Դ���2.���߲����Ƶ����ִ�ͳ�����Ϸ��鱳�����͵���Ŀ.
//��a->b->c->d,Ҫ����d�ͱ����ȹ���a,b,c,Ҫ����c,�ͱ����ȹ���a��b.
//������a,������bҲ�ɲ���,����c,d�����򶼿ɲ���.
//��:��Ʒ���������ϵ���Դ���һ����������,��������ܴ����Ϊ��������
//��Ʒ������ϵ,�������������������֮�䲢û��������ϵ,������Ʒ���γɵ�
//������ϵ�Ƕ������:ɭ��.������������һ��0�ڵ������Ӹ��������γɵ�ɭ��,
//ʹ���Ϊһ�ø��ڵ�Ϊ0�ڵ��������.����dfs��¼�����Ʒ������ϵ��������
//�Ĵ���pNode,����¼ÿ���ڵ�i֮ǰ����ֵ����������ĺ�������pre[i].
//���պ��������Ĵ������01����,���ڵ�i���ڵ����ѡȡ��dp[i-1][j-pNode[i].w]+pNode[i].val
//�����ѡȡ��i���ڵ�,��ô�������еĽڵ�Ͷ�����ѡȡ,��ǰһ��ת̬�Ͳ���dp[i-1][j],����
//dp[pre[i]][j],pre[i]�ǽڵ�i����������ֵ��������ĺ�������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//dp[i][j]��ʾ��jԪ�����������õ�������������ǰi����Ʒ���ܵõ�������ֵ
int id,cnt,head[N],n,m,dp[N][M],pre[N];

struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
}node[N],pNode[N];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    int dfn=id;//��¼u�������ֵ��������ĺ�����������
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
    }
    pNode[++id]=node[u];//��¼���������Ĵ���ڵ�
    //��¼�ڵ�u������ֵ��������ĺ�����������
    //��Ϊ01����ʱ��ѡu�ڵ���ǰһ״̬,��Ϊu�ڵ㲻ѡ��ôu�������еĽڵ�Ͷ�����ѡ��
    pre[id]=dfn;
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        node[i]=Node(v,v*p);
        addEdge(q,i);//q=0ʱ,��������ڵ�0��������i
    }
    dfs(0);//0��������ڵ� �����Ÿ�������
    //֮�����ö�ά��������Ϊ dp[i][j]��ǰһ״̬��dp[pre[i]][j]����dp[i-1][j],���Բ����ù��������Ż���һά
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){//�����Ƕ�ά01���� �����������򡢽���Կ�
            if(j>=pNode[i].w)
                //����ע��pNode[i]�����������еĵ�һ���ڵ�,�����ڼ�¼״̬��ʱ��,
                //���������ĵ�һ��״̬pNode[1]�����ʵ�ʽڵ����Ϊʵ��ǰ1����Ʒװ��ʱ�����Ž�.
                //����ʵ�ʺ�������Ľڵ�˳��֮��ǰi-1��״̬��ǰi��״̬֮�����������.
                //����dp[i-1][j-pNode[i].w]+pNode[i].val������,����������������ϵa->b->c->d,
                //������������������������ȫ��װ��a��b��c��d 4����Ʒ,Ҳ�������ѡȡa��d��
                //ûѡȡ�м�b��c ����ѡȡ�ӽڵ����û��ѡȡ�ӽڵ��ȫ���游�ڵ�����.
                //��Ϊ����a������ܴ�,a����һ״̬��b�ڵ�,ö������j,j-w[a]���ʣ�µ�������b�и���
                //װ����b,���װ����b,��b��dp�׶δ�ʱ��dp[b][j-w[a]]��״̬Ӧ����b������ֵ����������һ������ڵ�,
                //������Ϊ����װ��b,��ȻҲ����װ��c��d�����ڵ�.
                //eg:������Ʒ���1��2��3,����ֱ�3��2��1 ��ֵ3��2��1 ������ϵ1->2->3,������Ϊ4ʱ,�����һ�����������Ʒ1ʱ,
                //4-3=1,1�ڵ���һ״̬2�ڵ�������Ϊ1ʱ��Ȼװ����2�ڵ㱾��,��ô2��dp�׶�������Ϊ1ʱ,��Ȼ�̳е�����һ�׶�pre[2],
                //���pre[2]�϶��ǲ��Ậ��2���ӽڵ�3�ڵ��.��˲������ѡ��1��3�ڵ�,��û��ѡ3�ĸ��ڵ�2�ڵ�����.
                dp[i][j]=max(dp[pre[i]][j],dp[i-1][j-pNode[i].w]+pNode[i].val);
            else
                dp[i][j]=dp[pre[i]][j];
        }
    }
    printf("%d",dp[n][m]);
    return 0;
}
*/

/*
//ac 73ms dfs������ģ��������,��dfs����01���� �����ú������� pNode,pre��¼�������
//���Ӷ�(nv) ��׼��01�������Ӷ�
//������������ܴ���������ϵΪ2��������ϵ(�������⡢HDU 3449��USACO Video Game Troubles)
//��������ǲ����������͸�����,����ÿ����Ʒ֮�䶼������һ��������ϵ,
//��Ϊÿ�������������+1ʱ,���ᱣ����һ����������״̬dp[v][j]=dp[u][j],��˲�����ֶ���
//a->b->c->d,ֻѡȡa��d��ѡȡ�м�b��c�Ŀ���,��Ϊ��ѡȡb��c����Ӧ����һ״̬һ������b��c���ӽڵ�d.
//������ϵ����Ƕ��,������ϵ���߶ȿ��Դ���2.���߲����Ƶ����ִ�ͳ�����Ϸ��鱳�����͵���Ŀ.
//������α���(ò�Ʋ��Ǵ�ͳ�������Ǹ������Ϸ��鱳��),dfsֻ��ģ������
//��ϵ���ĺ�������������01����,ͬ�����ڽڵ�i��ѡȡ,��ôi�������ڵ㶼����ѡȡ,
//ʵ�ʵ���һ״̬���ǽڵ�i������������ߵĴ�������ֵ��������ڵ�����Ž�.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//����i�ڵ���dfs���������õ�����Ϊk
//dp[i][j] ����dfs��������ǰk���������Ʒ��jԪǮ���������ܻ�õ�����ֵ
int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//ʵ��������ǰѸ����������丽�����ɵ�ɭ���еĶ����ͨ������ڵ�0������������һ��������
void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
		//��ʵģ��Ļ���01�����Ǹ�����,pre[v]����v������ֵ������������
		//�����һ�����ڵ�,��������û������pre[v]�������,��ͨ��dfs�Ļ���
		//������ģ��01����ǰi-1����Ʒ��״̬��ǰi����Ʒ��״̬ת��.
		//dp[u][j]����ǰi��״̬,dp[v][j]����ǰi-1��״̬,��Ϊ��dfs�������
		//�ǰ��պ������������Ϊ01����ѡȡ��Ʒ��˳��
		//�����ʼ������Ϊdfs�ĺ������,�������������������ұ��ֵ�������Ҷ�ӽڵ�
		//���ǽ�����֮ǰ�ĺ������+1����һ��״̬,����ڱ����Ҳ�����ʱҪ������������һ������
		//����Ʒ�����Ž⸳ֵ����ǰ���������Ҷ�ӽڵ�,��˾�Ҫdfs����dp[v][j]=dp[u][j]����ʵ��
		//Ҷ�ӽڵ���Ϊ�����������һ���ڵ���ǰ��״̬������������Ž�
        for(int j=0;j<=m;j++)
            dp[v][j]=dp[u][j];
        dfs(v);
        //v�������ڵ��Ѿ�������,���ڼ���u������0�ڵ�,v������,
        //����ѡȡv�ڵ㻹�ǲ�ѡȡv�ڵ�,���ѡȡv�ڵ�,��ôv���ӽڵ���v�ĸ���,
        //���ݱ���ʣ������j�Ĳ�ͬ,dp[v][j-w[v]]+val[v]���Ž���v�ĸ�������ѡ��Ҳ���ܲ�ѡ,������Ϊ���Ž�.
        //��dp[u][j]ǰһ״̬������ڵ���֮ǰ����������������͸��������������Ž�,�����ѡȡv(����),
        //��ôv�ĸ���Ҳ����ѡȡ,����v����һ״̬����dp[u][j].

        //ͬ�����u��ʵ�ʵ������ڵ�,��ʱdp[u][j]��dp[v][j]ʵ�ʶ���ʾ����ڵ���֮ǰ����������������͸��������������Ž�
        //��dp[v][j-w[v]]+val[v]������ǰһ״̬������������Ž�
        for(int j=m;j>=w[v];j--)//����m��Զ���� ��ʼ��������,û�м���,���������Ȼ��01�����ı�׼����
            //u��v��Ų���һ�����1,���ܲ�ܶ�
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0ʱ,��������ڵ�0��������i
    }
    dfs(0);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 78ms ��ֺ⡶ǳ̸���౳�����⡷�е�����
//dfs���κ������01����+��֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)//��֦
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        for(int j=0;j<=tot-w[v];j++)
            dp[v][j]=dp[u][j]+val[v];
        dfs(v,tot-w[v]);
        for(int j=tot;j>=w[v];j--)
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]);
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0ʱ,��������ڵ�0��������i
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 38ms dp[M][2]����
//ժ���������
//����ֻ��ֱ���ÿ�������Լ��������ĸ�����������dp[k][0]Ϊ����kԪǮ����������ǰ������һ�������򸽼����ɻ�õ�������棻
//dp[k][1]Ϊ����kԪǮ�������˵�ǰ��������һ�������˸������ɻ�õ�������档
//��ô��������������2�������
//��Ʒiû�С��󶨡�����
//��Ʒi�С��󶨡�����
//����Ʒiû�С��󶨡�����,����ֱ���ô�ͳ��0-1����״̬ת������ʽ(��ʱ��dp[k][0]���൱��dp[k])
//dp[k][0]=max(dp[k][0],dp[k-v[i]][0]+v[i]*w[i]);
//����Ʒi���󶨡��˸�������ô���ڸ���j״̬ת�Ʒ���ʽӦΪ
//dp[k][1]=max(dp[k-v[i]][0]+v[i]*w[i],dp[k-v[j]][1]+v[j]*w[j]);
//ע�����Ҫ�ڹ���������������²���ʹ�� dp[k-v[j]][1]+v[j]*w[j];
//����ᵼ��WA;���Ҫ��dp[k][0]��dp[k][1]�е�������汣����dp[k][0]�С������������������~.~
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define pi pair<int,int>
#define f first
#define s second

using namespace std;

int n,m;
int dp[32001][2];
vector<pi>gp[61];//vector���ڼ�¼����
int cnt,v[61],w[61],id[61];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(c==0){//��������
			v[++cnt]=a;
			w[cnt]=b;
			id[cnt]=i;
		}
		else{
			gp[c].push_back(pi(a,b));
		}
	}
	for(int i=1;i<=cnt;i++){
		if(gp[id[i]].size()==0){//û�и���
			for(int j=n;j>=v[i];j--)dp[j][0]=max(dp[j][0],dp[j-v[i]][0]+v[i]*w[i]);
		}
		else{//�и���
			for(int j=n;j>=v[i];j--)dp[j][1]=dp[j-v[i]][0]+v[i]*w[i];
			for(int k=0;k<gp[id[i]].size();k++){
				int vk=gp[id[i]][k].f;//��ǰ�����ļ۸�
				int wk=gp[id[i]][k].s;//��ǰ��������Ҫ�ȼ�
				for(int j=n;j>=v[i]+vk;j--)dp[j][1]=max(dp[j][1],dp[j-vk][1]+vk*wk);//j�ı߽������ǳ���Ҫ
			}
			for(int j=n;j>=v[i];j--)dp[j][0]=max(dp[j][1],dp[j][0]);//�������Ž�
		}
	}
	printf("%d\n",dp[n][0]);//���
	return 0;
}
*/

/*
//50��,TLE ���Ϸ��鱳�� ��ͳ���α������� ���Ӷ�O(n*v^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)//��֦
        return;
    for(int i=w[u];i<=tot;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,tot-w[u]);
        for(int j=tot;j>=w[u];j--){
            //����k���½����w[v] ����ȷ��
            for(int k=w[v];k<=j-w[u];k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//�����ܶ��װ������
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0ʱ,��������ڵ�0��������i
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 182ms ��ͳ���α���(���Ϸ��鱳��)���� ������������Ǯ������Ʒ�۸���С100��,���͸��Ӷ�.
//����putin ��С�������� ��TLE. ���Ӷ�O(n*v^2)
//ժ���������
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
#define ll long long
#define in inline
inline ll read(){
    ll x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();
    }
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();
    }return x*f;
}
const int mx=1550;
int h[mx],p,f[61][3210],w[mx],v[mx],m;
struct edge{
    int next,v;
}e[4*mx];
inline void add(int a,int b){
    p++;e[p].next=h[a];h[a]=p;e[p].v=b;
}
int n,flag;
inline void putin(){
    m=read();n=read();m/=10;
    for(int i=1,p,x;i<=n;i++){
    	w[i]=read();v[i]=read();p=read();
    	w[i]/=10;
    	if(w[i]%10>0)flag=1;//�Ż���������ֲ�������100�ľͱ�ǡ�
    	v[i]*=w[i];//�����������v��ʱ���ǳ˵ĳ���10��w�����Դ𰸳�10��
    	add(p,i);
    }
    if(flag==0){//�Ż���
    	m/=10;
    	for(int i=1;i<=n;i++)w[i]/=10;
    }

    memset(f,0xcf,sizeof(f));
}
void dfs(int u){
    for(int i=0;i<=w[u];i++)f[u][i]=0;
    for(int i=h[u];i;i=e[i].next){
    	int v=e[i].v;
    	dfs(v);
    	for(int t=m;t>=w[v];t--){//���Ż������ը
    		for(int j=t;j>=w[v];j--)
    		f[u][t]=max(f[u][t],f[u][t-j]+f[v][j]);
        }
    }
    if(u!=0){
        for(int t=m;t>=w[u];t--)f[u][t]=f[u][t-w[u]]+v[u];
    }
}
int main(){
    putin();
    dfs(0);
     printf("%d",f[0][m]*10);
    return 0;
}
*/

/*
//ac 85ms ������Ʒ
�ο�����:https://www.luogu.com.cn/blog/user24559/solution-p1064(�����������ݲ���)
https://www.luogu.com.cn/blog/rocon/solution-p1064(�����Ƿ���)
�����Ŀ���ǽ�һ��0�㣬������Ϊ0����ֵΪ0��Ȼ�����Ǿ���һ����0Ϊ�������ˡ�
ѡ��һ����Ĺ����ǣ�����ѡ���丸�ס�
������֪������������Ʒ�ĺ���O(m^2)�ģ�mΪ������ڱ��������Ϊn���������������Ȼ���������ַ�����

������Ʒ�ĺͣ�������������Ʒ�ϲ���һ��������Ʒ�����㣬����ö��������������������Ʒ�����㣺
G[j] = max{ G1[j-k] + G2[k] } (C>=j>=k>=0)
�֣�������֪��������Ʒ�Ĳ���O(m)�ģ��������������O(nm)�Ļ����Ǿ��ܽԴ�ϲ�ˡ�

������Ʒ�Ĳ��� ��Ϊ����������Ʒ֮����ڽ��������Բ���ͬʱ���߶�ȡ����ô���Ǿ���Ҫ�󷺻���Ʒ�Ĳ�����ͬһ�����������Ҫѡȡ�����м�ֵ�ϴ��һ�ߣ�Ч�� O(C)��
G[j] = max{ G1[j] , G2[j] } (C>=j>=0)
�����������ڣ����Ǹ���ν����ϵķ�����Ʒ�ĺ�ת��Ϊ����

������״̬FiΪ����iΪ�����������������Ϊ��ǰ�Ѿ������ĵ㼯���γɵ������ķ�����Ʒ������ѡȡ������i��ѡ���������ڿ���ȥ�ݹ鵽i��һ������s��
���Ƿ��֣����������i��Ӳ��һ��s��Fi�ͻ���Fs��

��������ڵ�ǰ�� Fi��ǿ�Ʒ�����Ʒ s ����Ϊ�� s Ϊ���������ĳ�ʼ״̬�Ļ�����ô�������� s Ϊ���������Ժ�Fs������ Fi�н����ķ�����Ʒ��ʵ������ Fs����Fi�� ��ͬʱ��Fs�������������Ʒs����Fs[j] (Vs>j>=0)�Ѿ��������ˣ���Fs[j] (C>=j>=Vs)��Ȼ������Ʒ s��Ϊ�˷��㣬���������Ժ��ڳ����й涨ֻ��Fs[j] (C-Vs>=j>=0)�ǺϷ��ġ�
������ֻ��Ҫ�� Fs��Fi�Ĳ����� Fi��������˶�һ�����ӵĴ����� �ˣ�������Ҫ����ʱ�临�ӶȽ�ΪO(n*C)��
��ô�����˼�밡��
#include<bits/stdc++.h>
using namespace std;
const int inf=1e7;
int head[1001],nxt[2001],point[2001],W[1001],V[1001];
int f[61][32011];
int tot,n,m,pi,qi;
void addedge(int x,int y){
    tot++;nxt[tot]=head[x];head[x]=tot;point[tot]=y;
}
void dfs(int now,int dad){
    for(int i=m;i>=0;i--) if(i>=W[now]) f[now][i]=f[dad][i-W[now]]+V[now];
    for(int tmp=head[now];tmp;tmp=nxt[tmp]){
        int v=point[tmp];
        dfs(v,now);
        for(int i=0;i<=m;i++) if(i+W[v]<=m)f[v][i]=f[v][i+W[v]]-V[v];else f[v][i]=-inf;
        for(int i=m;i>=0;i--) if(i>=W[v]) f[now][i]=max(f[now][i],f[v][i-W[v]]+V[v]);
    }
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&W[i],&pi,&qi);
        addedge(qi,i);
        V[i]=W[i]*pi;
    }
    memset(f,-51,sizeof(f));
    f[0][0]=0;
    dfs(0,0);
    int ans=0;
    for(int i=0;i<=m;i++) ans=max(ans,f[0][i]);
    cout<<ans<<endl;
}
*/

/*
//ac 56ms ��ֺ������еİ취
//���˾�������˼·������� �ҵ�����(����������)��dfs ���������ģ��01����������� �������������
#include<bits/stdc++.h>
using namespace std;

int N,m,w[200],c[200],x,dp[200][40000];//�����Сqwq
int head[200],k=1;//��ʽǰ���Ǽӱ���
struct edge
{
	int to,next;
}e[200];//���ı�

void adde(int u,int v)//��ʽǰ���Ǽӱ�
{
	e[k].to=v;
	e[k].next=head[u];
	head[u]=k++;
}

void dfs(int u,int t,int fa)
//u�ǵ�ǰ�ڵ㣬t�ǵ�ǰ������fa�Ǹ��׽ڵ�
{
	if(t<=0)return;//װ������
	for(int i=head[u];i;i=e[i].next)//������õ�������ÿһ����
	{
		int v=e[i].to;
		if(v==fa)continue;//����Ǹ��ڵ�������
		for(int k=N-w[v];k>=0;k--)
			dp[v][k]=dp[u][k]+c[v];//Ҫѡ�������ͱ���ѡ�ýڵ�
		dfs(v,t-w[v],u);//�����ݹ�
		for(int k=N;k>=w[v];k--)
			dp[u][k]=max(dp[u][k],dp[v][k-w[v]]);//ѡ��ѡ������01������
	}
}

int main()
{
	scanf("%d%d",&N,&m);
	for(register int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&w[i],&c[i],&x);
		c[i]*=w[i];//����
		adde(i,x);adde(x,i);//��˫���
	}
	dfs(0,N,-1);//0Ϊ������ڵ㣬������dp
	int ans=0;
	for(register int i=0;i<=N;i++)//����һ��Ҫд<=����Ϊ���Ըպð�Ǯ����
		ans=max(ans,dp[0][i]);//ͳ�ƴ�
	printf("%d\n",ans);//���
	return 0;//����������һ��
}
*/

