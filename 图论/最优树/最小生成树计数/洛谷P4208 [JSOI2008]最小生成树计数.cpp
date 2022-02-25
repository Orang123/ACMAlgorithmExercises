#include<cstdio>
#include<algorithm>
#define N 120
#define M 1100
#define Mod 31011
using namespace std;
//dfs����+���鼯 ac 29ms
/*
����:n����,m���ߵ�����ͼ,�����С�������ĸ���.
���������С��������������һ���߲�ͬ,����������С���������ǲ�ͬ��.
����:https://www.luogu.com.cn/problem/P4208
����:"һ��ͼ��������С��������Ȩֵ��ȵıߵĸ���һ����ͬ".
֤��:3+7=4+6=10��������3��7��4��6�����ֱ���Ϸ���,������mstʱ,��̰��ѡ3+4=7,����ѡ�ϴ�ı�Ȩ3+7��4+6����.
˼·:����δ����mst�ı�u-v,��������,�ж�����u-v���·�����ж������ߺ�δ����
�ı�Ȩֵ���,��ô������mst��һ�ο��ܵ���״���ж�����.����ó˷�ԭ���۳˳����ж�
�Ĵ𰸼���.����������������Ȱ���ͬ��Ȩ������һ������������,Ȼ�����mst�������ͬ
��Ȩ��������Ҫ�Ӷ��ٱ�,֮������dfs���Ѷ�ÿһ����ȱ�Ȩ������,����ѡ����mst�������
������ȱ�Ȩ����Ŀcnt,����ö�ٳ����ܵ�cnt����ȱ�Ȩ,sum����,֮��˷�ԭ���ٺ�ans�۳�,
����ͳ����һ����ȱ�Ȩ������.
�������fighter:
Ϊʲô���ܶ�dfs��ʹ�õĲ��鼯����·��ѹ��������Ϊ����Ϊ��dfs���������������Ҫ��ԭ��
�Ա�֤��������ȷ�ԣ������ֻ�ԭҪ��֤���鼯�Ľṹ�����ر���ԭ���������·��ѹ����
��ô��ǰ�ĸ��ڵ㣬��dfs������Ѿ����Ǹ��ڵ㣬ԭ�������ӽڵ㾭��·��ѹ����
��ָ���˵�ǰ�����𡱸��ߵĸ��ڵ㣬��ʱ�����Ҫ��ԭ���鼯�Ľṹ�ͻ�ʮ�����ѡ�
��Ϊ��ֻ����ʱ��"����"���ߵĸ��ڵ㻹ԭ,��֮ǰ���ӽڵ���Ϊ·��ѹ��,���Ծ�ָ�����Ѿ���
��ԭ�ĵ�"����"���ߵĸ��ڵ�,�����������б����ӽڵ��"����"���ߵĸ��ڵ����ӽڵ㻹û����
��ԭ֮ǰ������,�����Ϊ���Ƚڵ�һ��,���޷�����,���Ӱ���ӱߵĽ��,���¼������.

*/

int fa[N],sum;

struct Node{
    int u,v,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[M];

struct section{
    int l,r,num;//l��ʾ Ȩֵ��ȵıߵ��±����˵�,r��ʾ�Ҷ˵�,num��ʾ��mst������Ȩֵ��ȵıߵ�����
}sec[M];

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:find(fa[x]);
}

/*
dfs���ı���˼��:��ʵ���ǿ���ԭ�� mst�� ĳ��·�� δ����ı� �Ƿ��к͵�ǰ·���еı�Ȩ��ͬ,
����� �����˻���Ȼ��˳��ɾ��ԭ�������ߡ���������һ���µ�mst.
*/
//��dfsӦ�õ�����L��������ͨͼ�� ���е���С��������Ȩֵ��ȵı���������ͬ��

void dfs(int x,int now,int cnt){
    int a,b;
    if(now == sec[x].r+1){//��Ȩֵ��ȵı� ö�ٵ��� �Ҷ˵㼴 ����
        if(cnt == sec[x].num)//�ж�Ȩֵ��ȵı��Ƿ�ͳ�ʼ��ʱ��mst��ͬ,����ͬ���ʱѡ���Ȩֵ��ͬ�ı߾͹����� �µ�mst
            sum++;
        return;
    }
    a=find(edge[now].u);
    b=find(edge[now].v);
    if(a!=b){//����ǰ�� �ܼ���mst
        fa[a]=b;
        dfs(x,now+1,cnt+1);//��һ���ߵ��±�now+1,���ɵ���ͬȨֵ�ı���Ŀcnt+1
        /*
        ����ʱ,���ǲ�����������,���Լ�������Ȩֵ��ȵı� ,���յ���Ŀ�Ƿ��ܴﵽ��ʼʱ��mstȨֵ��ȵıߵ���Ŀ
        ͬʱҪ��֮ǰ��ͨ������2�����Ϸֿ��ָ���δ����������ʱ��ͼ�Ľṹ.
        ע��find��������Բ�����·��ѹ��,����·��ѹ���ᵼ��,
        ��Ϊ�� ����find �ټӱ�ʱ,���a�Ķ��� �����ܻ��Ϊ�µ�b�Ķ���
        ��ʱ����fa[a]=a,fa[b]=bҲֻ���� �ı䵱�����ڵ�� ָ��,���ӽ��ָ�� ����Ϊ�����������b���·��ѹ����ָ��b,
        ���Ӱ�����ӱ�ʱ��ͨ��ϵ���ж�,����û����ȫ�ָ���֮ǰ����ͨ״̬.
        eg:���Ǳ߼�1-2,1-3,1-4,1-5,1-6,3-5������Ĳ��鼯����ѹ������fa[1]=2,fa[2]=3,fa[3]=4,fa[4]=5,fa[5]=6,3-5�ı���Ϊ���ɻ�·���ܼӽ���,
        �������·��ѹ���󲢲鼯�Ĺ���fa[1]=fa[2]=fa[3]==fa[4]=5,fa[5]=6,�����ʱ���ݲ�ѡ��1-5,1-6����������,��ô���鼯��ԭֻ��
        ��ԭfa[4]=4,fa[5]=5,fa[6]=6,����fa[1]=fa[2]=fa[3]=5,��Ȼ��ָ��5,����3-5������,��Ϊfa[3]=fa[5]=5,���²��ܼ���3-5������,
        �������߲�û�й��ɻ�,ֻ����Ϊ·��ѹ��,�����ӽڵ�ָ����߼���ĸ��ڵ�,���»�ԭʱ,��û�л��ݵ��ӽڵ�ʱ,��fa��ָ��û��
        ��ԭ,������ӽڵ��֮ǰ�Ͽ��ļ���ߵĸ��ڵ�����������޷�����.
        1->2->3·��ѹ����ͱ��1->3��2->3,����1��2�Ķ��ӣ�����1���3�Ķ�����,���ڻָ�ʱҲֻ��ʹ��fa[2]=2,��fa[1]�Ѿ�����3��,
        ������û�лָ���ԭ��δ����������ʱ����ͨ״̬
        */
        fa[a]=a,fa[b]=b;
    }
    dfs(x,now+1,cnt);//���ǲ�����������,���Լ�������Ȩֵ��ȵı�
}

int main(){
    int n,m,a,b,c,cnt=0,cnt0=0,ans=1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge+1,edge+1+m);
    init(n);
    for(int i=1;i<=m;i++){
        /*�������ж�i ��i+1 ���±��0��ʼ ����ͻ�wa��֪Ϊ��*/
        if(edge[i].w!=edge[i-1].w){//������ڱ� ��Ȩֵ�����,��˵�� ��ʱ��i��Ӧ�ı�Ȩ���µĽϴ�ı�Ȩ
            sec[cnt].r=i-1;//��¼֮ǰ��ȱ�Ȩ���Ҷ˵���±�
            sec[++cnt].l=i;//��¼�µ���ȱ�Ȩ����˵�Ϊ��ʱ�ı�i�±�
        }
        a=find(edge[i].u);
        b=find(edge[i].v);
        if(a!=b){//����mst���ϼӱ�
            fa[a]=b;
            sec[cnt].num++;//��mst�����ֱ�Ȩ�ĸ���+1
            cnt0++;
            //if(cnt0 == n-1) break;���ﲻ����ǰ����,��Ϊ�п�����ǰ�˳�ѭ�� ����Ȩֵ��ȵı߾�û�б���¼��ȥ
        }
    }
    sec[cnt].r=m;//ѭ������ʱ,���һ�ֱ�Ȩ���Ҷ˵�Ϊ�±�m
    if(cnt0 != n-1){//��������mst,�����0
        printf("0\n");
        return 0;
    }
    init(n);
    for(int i=1;i<=cnt;i++){//ö��ÿһ�� Ȩֵ��ȵı�
        sum=0;//��ʼ�����Ȩֵ��ȵıߵ����ܹ���mst�Ĳ�ͬ�������
        dfs(i,sec[i].l,0);
        ans=(ans*sum)%Mod;
        for(int j=sec[i].l;j<=sec[i].r;j++){
            a=find(edge[j].u);
            b=find(edge[j].v);
            if(a!=b)
                fa[a]=b;
        }
    }
    printf("%d\n",ans);
    return 0;
}
/*
//�����������(����������) ��˹��Ԫ���� ac 27ms
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N=101,M=1001,MOD=31011;

//ԭͼ����Ȩ��ɢ��������ȱ�Ȩ�洢
struct e
{
    int x,y,v;
} tp[M],mst[M];
vector<e> edge[M];
int cmp(e a,e b)
{
    return a.v<b.v;
}

bool is[M];

//���鼯
int bcj[N],bel[N];
void init(int a)
{
	for(int i=1;i<=a;i++) bcj[i]=i;
}
int rt(int a)
{
    if(bcj[a]==a) return a;
    return bcj[a]=rt(bcj[a]);
}
bool uni(int a,int b)
{
    int p=rt(a),q=rt(b);
    if(p==q) return true;
    bcj[p]=q;
    return false;
}

//�������� �������ڽӡ���������
int n,deg[N][N],g[N][N],mat[N][N];

int treecnt()//������������շת�����˹��Ԫ
{
    int i,j,k,ans=1;
    for(i=1;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            while(mat[j][i])
            {
                int div=mat[i][i]/mat[j][i];
                for(k=i;k<n;k++) mat[i][k]=(mat[i][k]-1ll*mat[j][k]*div%MOD+MOD)%MOD;
                swap(mat[i],mat[j]);
                ans*=-1;
            }
            if(mat[i][i]==0) return 0;
        }
        ans=1ll*ans*mat[i][i]%MOD;
    }
    return (ans+MOD)%MOD;
}

int main()
{
    int a,b,i,j,k,tl=0,tmp=0,cnt=0;
    scanf("%d%d",&a,&b);
    init(a);
    for(i=0;i<b;i++) scanf("%d%d%d",&tp[i].x,&tp[i].y,&tp[i].v);
    sort(tp,tp+b,cmp);

    //kruskal
    for(i=0;i<b;i++)
    {
        if(tp[i].v!=tmp) tl++,tmp=tp[i].v;
        edge[tl].push_back(tp[i]);
        if(uni(tp[i].x,tp[i].y)) continue;
        is[tl]=1,mst[cnt]=tp[i],mst[cnt++].v=tl;
    }
    if(cnt!=a-1)
    {
        printf("0");
        return 0;
    }

    //ͳ�ƴ�
    int ans=1;
    for(i=1;i<=tl;i++)
    {
        //�����С��������û���õ��˱�Ȩ
        if(!is[i]) continue;

		init(a);
        int siz=edge[i].size();
		n=0;

		//���������ϵı�ȫ�����ϲ�����
		for(j=0;j<cnt;j++)
		{
			if(mst[j].v==i) continue;
			uni(mst[j].x,mst[j].y);
		}
		for(j=1;j<=a;j++)
		{
			if(bcj[j]==j) bel[j]=++n;
		}
		for(j=1;j<=a;j++) bel[j]=bel[rt(j)];

        //��ԭͼ�д˱�Ȩ�ı�ȫ������
        for(j=0;j<siz;j++)
        {
            int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
            deg[bx][bx]++,deg[by][by]++;
            g[bx][by]++,g[by][bx]++;
        }

        for(j=1;j<=n;j++)
            for(k=1;k<=n;k++)
                mat[j][k]=deg[j][k]-g[j][k];
        ans=ans*treecnt()%MOD;

        //ɾ�����ϵı�
        for(j=0;j<siz;j++)
        {
            int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
            deg[bx][bx]--,deg[by][by]--;
            g[bx][by]--,g[by][bx]--;
        }
    }
    printf("%d",ans);
    return 0;
}
*/

/*
�����¼��ͬȨֵ�ı��������ж�i ��i+1 ���±��0��ʼ ����ͻ�wa��֪Ϊ��
#include<cstdio>
#include<algorithm>
#define N 120
#define M 1100
#define Mod 31011
using namespace std;
int fa[N],sum;

struct Node{
    int u,v,w;
    bool operator < (const Node &x)const{
        return w<x.w;
    }
}edge[M];

struct section{
    int l,r,num;
}sec[M];

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:find(fa[x]);
}

void dfs(int x,int now,int cnt){
    int a,b;
    if(now == sec[x].r+1){
        if(cnt == sec[x].num)
            sum++;
        return;
    }
    a=find(edge[now].u);
    b=find(edge[now].v);
    if(a!=b){
        fa[a]=b;
        dfs(x,now+1,cnt+1);
        fa[a]=a,fa[b]=b;
    }
    dfs(x,now+1,cnt);
}

int main(){
    int n,m,a,b,cnt=0,cnt0=0,ans=1;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge,edge+m);
    init(n);
    for(int i=0;i<m-1;i++){
        if(edge[i].w!=edge[i+1].w){
            sec[cnt].r=i;
            sec[++cnt].l=i+1;
        }
        a=find(edge[i].u);
        b=find(edge[i].v);
        if(a!=b){
            fa[a]=b;
            sec[cnt].num++;
            cnt0++;
            //if(cnt0 == n-1) break;
        }
    }
    sec[cnt].r=m-1;
    if(cnt0 != n-1){
        printf("0\n");
        return 0;
    }
    init(n);
    for(int i=0;i<=cnt;i++){
        sum=0;
        dfs(i,sec[i].l,0);
        ans=(ans*sum)%Mod;
        for(int j=sec[i].l;j<=sec[i].r;j++){
            a=find(edge[j].u);
            b=find(edge[j].v);
            if(a!=b)
                fa[a]=b;
        }
    }
    printf("%d\n",ans);
    return 0;
}

*/
