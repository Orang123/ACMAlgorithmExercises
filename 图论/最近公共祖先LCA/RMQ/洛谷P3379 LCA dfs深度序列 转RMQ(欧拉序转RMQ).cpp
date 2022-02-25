#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<cstring>
#define N 500100
using namespace std;
/*
dfs�������е��ܽ����Ϊ2n-1 ������Ը���ÿ��Ҷ�ӽڵ��dfs��������ֻ�����һ��,
�����ڵ����ʱ������ʵ���һ�����п��Էָ�Ҷ�ӽڵ㣬����Ҷ�ӽڵ������2�Σ�
���������Ƚ��Ҳ��������������,�����������ƵĽ�����ǳ������ڵ�������㶼������2��.����dfs�������е��ܽ�����Ϊ2n-1(nΪ���Ľ������)
dfn[u]������������е�һ�η��ʵ�u���ı������,numΪ�������еĴ�����
*/
int head[N],lg[N<<1],dep[N],dfn[N],st[N<<1][20],cnt,num;//st[j][i]����dfs�������Ϊj��ʼ���ڵ�2^i�η�������������С�Ľ����
struct Node{
    int to,next;
}edge[N<<1];

//LCA תRMQ ʱ�俨�úܽ� ��Ҫ�����Ż�����
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}
//O(n)
void dfs(int u,int fa){
    dfn[u]=++num;
    st[num][0]=u;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa){
            dfs(v,u);
            /*
            ����ʱ���ڵ���Ҫ���¼����������,ֻ��������ͳ��lca(x,y)ʱ dfs���ʵı�����������[dfn[x],dfn[y]] ��
            �Ż����x��y������������Ƚ��,lca(x,y)��ʵ��������[dfn[x],dfn[y]]�������С�Ľ��.
            (����ԭ��Ӧ������������С�Ľ������Ǹ���x������ת��y���Ĺյ�,��LCA)
            */
            st[++num][0]=u;
        }
    }
}

//Ԥ���� ��LCA����ת��Ϊ ����������е�st�� RMQ���� O((2n-1)*log(2n-1))
void RMQ(int n){
    lg[0]=-1;
    for(int i=1;i<=num;i++)//������Ԥ����dfs�����������н������lg ע����num
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=lg[num];i++){//O(log(2n))
        for(int j=1;j+(1<<i)-1<=num;j++){//O(2n)
            int a=st[j][i-1];
            int b=st[j+(1<<i-1)][i-1];
            /*
            ����Ƚ���jΪ��ʼ�����ڵ�2^(i-1)�η��������С��� ����j+(1<<i-1)Ϊ��ʼ�����ڵ�2^(i-1)�η��������С���ȡ����֮�����Сֵ��
            ���¼�����jΪ��ʼ�����ڵ�2^i�η���������С��Ƚ���� ��¼��С��Ƚ���Ÿ�ֵ��st[j][i]
            */
            if(dep[a]<dep[b]) st[j][i]=a;
            else st[j][i]=b;
        }
    }
}

//st���ѯ O(1) LCAתRMQԼ�� ���������㷨,ÿһ��ѯ�� ��Ӧһ��O(1)�Ļش�
int lca(int x,int y){
    x=dfn[x],y=dfn[y];//��¼x��y����һ�η��ʵı������
    if(x>y) swap(x,y);//x���Ϊ��С����߽�
    int k=lg[y-x+1];//������dfn[x]Ϊ��˵�dfn[y]Ϊ�Ҷ˵��dfs������������ĳ���
    int a=st[x][k],b=st[y-(1<<k)+1][k];
    //����st�����������Ϊ��2^k�η�Ϊ����һ��һ��������,�Ƚϵó�[dfn[x],dfn[y]]�����������С�Ľ���� ��Ϊԭ��x��y���������������lca(x,y)
    if(dep[a]<dep[b]) return a;
    else return b;
}

int main(){
    int n,m,s,x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        x=read(),y=read();
        addEdge(x,y);//����������
    }
    dep[0]=-1;//�Ӹ��ڵ㿪ʼ,��ȴ��㿪ʼ.
    dfs(s,0);//���ڵ�ĸ��ڵ���Ϊ����
    RMQ(n);
    while(m--){
        x=read(),y=read();
        printf("%d\n",lca(x,y));
    }
    return 0;
}
