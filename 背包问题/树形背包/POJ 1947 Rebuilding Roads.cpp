/*
����:һ����n���ڵ����,����ȥ���������߿��Թ������ڵ���p������.
n<=150
����:http://poj.org/problem?id=1947
˼·:���Ϸ��鱳��.��������Ϊǡ�ú��еĽڵ����.
dp[u][j]=k������uΪ���ڵ����������j���ڵ�ʱ������Ҫɾ��k����.
ÿ������Ϊһ��,ÿ���е���ƷΪ��ǰ�����������ٽڵ�����Ҫɾ���ı���.
��ʼ״̬��dp[u][1]=u�ڵ�����ֱ���ڽӶ��Ӹ��� ��uΪ���ڵ������,ֻ�����˸��ڵ�u�Լ�,
��Ҫɾ������ֱ���ڽӵĶ�������.��Ҫע��������ս����Ҫ����ÿ���ڵ�Ϊ���ڵ����������
p���ڵ�ʱɾ���ı���,���ڸ��ڵ㲻��dpʱ�Ľڵ�,�����Ҫ��ɾ����ǰ���ڵ��뱾��ĸ��ڵ��
����.��:dp[i][p]+1(i!=rt),dp[i][p](i==rt).
��Ȼû��ֱ��˵�����ӽڵ��໥����,ʵ��dp[u][j] һ�����ٻᱣ��u�ڵ㱾��Ļ����ϲ��ܱ���v�ڵ�.
*/
//ac 32ms
//���Ӷ� O(n*v^2) =150^3=3.375*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 160
#define INF 0x3f3f3f3f
using namespace std;

//dp[u][j]=k������uΪ���ڵ����������j���ڵ�ʱ������Ҫɾ��k����.
int cnt,head[N],vis[N],n,p,dp[N][N];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    int sum=1,m;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //sum����uΪ���ڵ���������е����нڵ����(����u����)
        sum+=dfs(v);
        //���������Ƕ�̬�仯��,�������ڵ����������Ҫ����pʱ,����Ϊsum,����ʱ,������p,��Ϊ����p��״̬�������.
        m=sum<p?sum:p;
        for(int j=m;j>=2;j--){//��������������2,����Ϊ1�ǳ�ʼ״̬ ������ת��
            for(int k=1;k<=j-1;k++)//����������ҪС��j,��Ϊ��������⸸�ڵ�uΪ������������j���ڵ��״̬,u�ڵ����ѡ�ϲ���ѡ�ӽڵ�.
                //��1 ��֮ǰ��ʼ״ֻ̬����uһ���ڵ��dp[u][1]����ȥv�ڵ���u������Ҫ�ټӻ���,ʵ�ʼ�ȥ�ߵĸ���-1
                //v�ڵ���������k���ڵ�,��ǰu�ڵ㱣��j-k���ڵ�
                //���ת�� ���ں���k���ڵ��v������˵,
                //���v�����к��з�֧����,ÿ����֧�ڵ����϶�,��ʵ����Ҫɾ���ı����ͽ���
                //���v�����к��з�֧�϶�,ÿ����֧�ڵ�������,��ʵ����Ҫɾ���ı����ͽ϶�
                //״̬ת�Ʒ��̾��ߵľ��Ƿ�֧���� ��֧�ڵ����϶��������Ϊ���Ž�
                dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]-1);
        }
    }
    return sum;
}

int main(){
    int u,v,rt;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&p);
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)
        dp[i][1]=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        dp[u][1]++;//��ʼ״̬uֻ����u�ڵ㱾�� Ҫɾ�߸���Ϊֱ���ڽӵ����ж��ӽڵ�ĸ���.
        vis[v]=1;
    }
    //�Ҹ��ڵ� ���Ϊ0
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            rt=i;
            break;
        }
    }
    dfs(rt);
    int ans=INF;
    for(int i=1;i<=n;i++){
        if(i!=rt)//����dpʱ�ĸ��ڵ�,�򻹵�ɾȥ��ǰi���븸�ڵ�����߲��ܽ�����p���ڵ�������������
            ans=min(ans,dp[i][p]+1);
        else
            ans=min(ans,dp[i][p]);
    }
    printf("%d",ans);
    return 0;
}

/*
���ִ�����dp����������,ֻ����O(n*v^2)�����Ϸ��鱳������.
��ǳ̸���౳�����⡷��O(nv)�ĺ������01����,�����ϸ��ÿ���ڵ㵱��
һ����Ʒ,��������ͼ�ֵ�ĸ����,���Ҹ��ӽڵ��������ϸ��������ϵ����,
���������͵���Ŀ,ÿ���ڵ㲢���ܵ�������һ����Ʒ,�����߱���Ʒ����ͼ�ֵ��
����,ֻ��˵�Ǳ����������dp��.
*/

/*
//��һ��ת��,ժ�Բ���:https://www.cnblogs.com/20143605--pcx/p/5348610.html
//��Ŀ����������״̬dp(root,k)��ʾ����rootΪ���ڵ�������У�ɾ��һЩ�߱��ǡ��
//k���ڵ��������Ҫɾȥ�����ٱ��������ڸ��ڵ�root��ĳ������son��Ҫô��son������
//�е��ӽڵ�ȫ��ɾ������dp(root,k)=dp(root,k)+1��ֻ��ɾ��root��son֮��ıߣ�Ҫô
//��son��������ѡ��һЩ��ɾ�����������j���ڵ��������״̬ת�Ʒ���Ϊdp(root,k)=max(dp(root,k),dp(son,j)+dp(root,k-j))��

//dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]);,�����Ϊʲôÿ��jҪ��dp[u][j]++,
//ò��������� �տ�ʼ����״̬ ������ֱ��������ȷ�Ľ��,��dp[u][j]����������,����ʹ�ô����״̬�����ȷ
//ac 16ms
# include<iostream>
# include<cstdio>
# include<cstring>
# include<vector>
# include<algorithm>
using namespace std;

const int N=155;
const int INF=1000000000;

int n,m;
bool flag[N];
int dp[N][N];
vector<int>e[N];

void init()
{
    int a,b;
    for(int i=1;i<=n;++i){
        e[i].clear();
        for(int j=0;j<=m;++j)
            dp[i][j]=INF;
    }
    memset(flag,false,sizeof(flag));
    for(int i=1;i<n;++i){
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        flag[b]=true;
    }
}

void dfs(int u)
{
    dp[u][1]=0;
    for(int i=0;i<e[u].size();++i){
        int v=e[u][i];
        dfs(v);
        for(int j=m;j>=1;--j){
            dp[u][j]+=1;
            for(int k=1;k<j;++k){    ///k��1ѭ����j-1��һ�����ܴ�0ѭ����j
                dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]);
            }
        }
    }
}

void solve()
{
    int ans=INF;
    for(int i=1;i<=n;++i){
        if(flag[i]) continue;
        dfs(i);
        ans=dp[i][m];
        break;
    }
    for(int i=1;i<=n;++i)
        ans=min(ans,dp[i][m]+1);
    printf("%d\n",ans);
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        solve();
    }
    return 0;
}
*/

/*
//��һ��״̬��ʾ��ʽ ժ�Բ���:https://www.cnblogs.com/cglongge/p/10308685.html
//�����ܿ���,���������� Ҫ������,��ΪҪ�õ�m��,ʵ�ʾ�ɾ����n-m�������еĽڵ���Ҫ�����ٱ���.
//dp[i][j]��ʾ��i�ڵ�������������i��ɵ�������ȥ��j���ڵ���Ҫ���ٵ����ٵı���

//ac 16ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct{//��ʽǰ����
    int v,next;
}edge[320];
int head[160];
int dp[160][160];//dp[i][j]��ʾ��i�ڵ�������������i��ɵ�������ȥ��j���ڵ���Ҫ���ٵ����ٵı���
int sum[160];//sum[i]��ʾ��i�ڵ��������һ���ж��ٸ��ڵ㣨������i��
int cnt;
void add(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

//i�ڵ��������������i��
//��i�ڵ�Ϊ���������������������i��

int n,m;
void dfs(int k){
    sum[k]=0;//��ʼ��
    for(int i=1;i<=n;i++)//��ʼ��
    dp[k][i]=1e9;
    dp[k][0]=0;//�������ĸ��㣬ȥ��0���ڵ�Ļ���һ����0
    for(int i=head[k];i!=-1;i=edge[i].next){
            dfs(edge[i].v);//�����ӽڵ�����
            sum[k]+=sum[edge[i].v]+1;//����k�ڵ���������ж��ٸ��ڵ�
            dp[edge[i].v][sum[edge[i].v]+1]=1;//ȥ����ǰ�ӽڵ�Ϊ������������еĽڵ�Ļ���һ����1��ֻ��Ͽ�k�뵱ǰ�ӽڵ�����ӣ�
            //printf("%d %d %d\n",edge[i].v,sum[edge[i].v]+1,dp[edge[i].v][sum[edge[i].v]+1])    ;
            for(int j=n;j>0;j--){ //ΪʲôҪj>0,��Ϊj=0�Ļ���һ����0��û��Ҫ����
                for(int l=1;l<=j;l++)
                dp[k][j]=min(dp[k][j],dp[k][j-l]+dp[edge[i].v][l]);
                //Ϊʲôl��1��ʼ����Ϊ��0��ʼû��Ҫ��min(dp[k][j],dp[k][j]+dp[edge[i].v][0]);������
                //���һ����ԭ����dp[k][j],��Ϊ dp[edge[i].v][0]=0��Ϊʲôl���Ե���j����Ϊ�ҿ��Ե�ǰ��j��ȫ��
                //�ӵ�ǰ�ӽڵ���ɵ�����ȥ��
            }
    }
}
bool vt[160];//�������
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        int u,v;
        cnt=0;
        fill(head,head+152,false);//��ʼ��
        fill(head,head+152,-1);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            add(u,v);
            vt[v]=true;
        }
        int root=0;
        for(int i=1;i<=n&&!root;i++){//�Ҹ��ڵ�
            if(!vt[i])
            root=i;
        }
        dfs(root);
        int ans=dp[root][n-m];//��Ҫ�õ��ڵ���Ϊm����������Ҫȥ��n-m����
        for(int i=1;i<=n;i++)
        if(sum[i]+1>=m)//i�ڵ� �����б�������Ҫ��m���ڵ����
        ans=min(ans,dp[i][sum[i]+1-m]+1);//ȡ�Ե�i���ڵ�Ϊ���ڵ���ɵ�����������i��ʱ����Ҫ��ȥ���븸�ڵ�����ӣ�
        //Ȼ���ٵ��������ȥsum[i]+1-m���ڵ㣨��Ϊ��iΪ����ɵ�����������ֻ��sum[i]+1���ڵ㣩
        printf("%d\n",ans);
    }

    return 0;
}
*/

