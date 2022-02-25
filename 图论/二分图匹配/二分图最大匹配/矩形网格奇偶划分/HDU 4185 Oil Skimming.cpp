#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;
//ac 0ms
/*
����:һ��n*n������,��'#'��'.'���,����'#'������,
'.'����ˮ,����Ҫ���͵�,����ֻ�ܰ���1*2�ľ���(2��'#'���)��,
���ο��Ժ�����,Ҳ����������,��������ˮ��'.',��������һ�κ�
��������û��'#',����û����,�����ܽ�����,�����ص�,�������
�ڶ��ٴ��͵�.
ע:һ���ȽϿӵĵط�����n*n����'#'�ĸ���ʵ����С��n��,���vis���鿪��n*n,
������������ÿ��������ʱ,����memset��ʼ��vis,������TLE,����vis�����СΪN,
����vis�������ó�N*N vis���Կ��Ǽ�¼ʱ���,����visÿ������ֻ���ʼ������,����TLE.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4185
˼·:ʵ���Ͼ��������������'#'�����,ÿ���һ��,������'#'�Ͳ�����
�ͱ��'#'�����,Ҳ������������'#'��Եı߼������й�������,��Ȼ����
������ƥ��,�������е�#����#���������������ӵ�#ǡ�ÿ��Էֳ���������,
ʣ��ĵ㰴�������ζԽ������Ӿ��ܽ������������ż���ʷֳ�2������,
��ô��Ȼ�����ת��Ϊ�������㷨������ͼ���ƥ��.
������벢û�н�����ͼ���������Ϸֳ���,��������'#'������˫���,Ȼ�����е�
���������,�����������㷨������,���Ҫ��2.
*/
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,cas,id,ans,mp[N][N],cnt,head[N],vis[N],link[N];
struct Edge{
    int to,next;
}edge[4*N];//ÿ��#���������4����

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 && y<=n && mp[x][y])
        return 1;
    return 0;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=id=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#') mp[i][j]=++id;//Ϊÿ��'#'�͵α��
                else mp[i][j]=0;//����'.'����ˮ
            }
        }
        /*
                ���ｨ�߿���ֻ����ÿ��'#'�����·�2������,Ȼ��˫���
                if(j<n && mp[i][j+1]){
                    addEdge(mp[i][j],mp[i][j+1]);
                    addEdge(mp[i][j+1],mp[i][j]);
                }
                if(i<n && mp[i+1][j]){
                    addEdge(mp[i][j],mp[i+1][j]);
                    addEdge(mp[i+1][j],mp[i][j]);
                }
        */
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!mp[i][j]) continue;//����[i][j]������'#'
                for(int k=0;k<4;k++){//����[i][j]#�ĸ������'#'����
                    int x=i+dir[k][0];
                    int y=j+dir[k][1];
                    if(judge(x,y))
                        addEdge(mp[i][j],mp[x][y]);
                }
            }
        }
        for(int i=1;i<=id;i++){
            memset(vis,0,sizeof(vis));//vis��ʼ��,����vis�����С������N*N,�����TLE
            if(dfs(i)) ans++;
        }
        //��ΪX Y���������еĵ㶼���������,���Խ��Ҫ��2,����ansһ����ż��,��Ϊ������Ǵ�2�����ϳ����ֱ�����,ֵ����һ�����Ծ���2��
        printf("Case %d: %d\n",cas,ans/2);
    }
    return 0;
}

/*
//������vis����ʱ����Ż����� ����ÿ�������ʱ����ʼ��vis����
//ÿ������Զ�����һ���µ�clockʱ���,����vis[v] == clock��ȷ��v���Ƿ��Ѿ����ʹ�
//ac 46ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;

int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,cas,id,ans,mp[N][N],cnt,head[N*N],vis[N*N],link[N*N];
struct Edge{
    int to,next;
}edge[4*N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int judge(int x,int y){
    if(x>=1 && x<=n && y>=1 && y<=n && mp[x][y])
        return 1;
    return 0;
}

int dfs(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;//����ǰ�� �Ѿ�������
        vis[v]=clock;//��Ƿ��ʹ����ʱ���Ϊclock
        if(!link[v] || dfs(link[v],clock)){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=id=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#') mp[i][j]=++id;
                else mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!mp[i][j]) continue;
                for(int k=0;k<4;k++){
                    int x=i+dir[k][0];
                    int y=j+dir[k][1];
                    if(judge(x,y))
                        addEdge(mp[i][j],mp[x][y]);
                }
            }
        }
        for(int i=1;i<=id;i++)
            //ÿ��������Եĵ�ʱ�������һ�� clock=i ʱ��������ı��
            if(dfs(i,i)) ans++;
        printf("Case %d: %d\n",cas,ans/2);
    }
    return 0;
}
*/

/*
//�������������������֮�͵���ż���ʻ��ֶ���ͼ��2������,ֻ����һ�����ϵĵ����������ƥ��,�������2
//ac 0ms
//1.
//��������������������(�ݸ�ͼ���Խ���)�ĵ�ǡ�ù��ɶ���ͼ��һ������,
//ʣ��㹹����һ������,���ֵ������Ƕ���ͼ�����������ڲ��ĵ�֮����û��
//���ߵ�,�������������жԽ���֮��ĵ�ǡ��û������,���԰��նԽ������������
//ǡ���ܹ��������ͼ��һ������.
//2.
//ʵ��������������'#'��Ķ���ͼ���ϻ��ָպ���������֮�͵���ż�Ի���
//�����(x,y) (x+y)%2==1 ��������� ��ô�ĸ�����(x+/-1,y+/-1),��ԭ����(x,y)
//һ����1��1ż,��4������������'#'����Ҫôͬʱ��1Ҫôͬʱ��1,Ҫôһ����1һ����1,
//�����������Ծ���һ������һ��ż��,����֮���Ծ�������,�������ŷ����ӱߵĶԽ���
//�����ҵ���������֮��Ϊ�����ĵ�.
//�����(x,y) (x+y)%2==0 ����֮��ż��,ԭ����2������:Ҫô��ż��Ҫô������,���Խ��߷���
//����(x+/-1,y+/-1)���� Ҫôȫ��ż��Ҫôȫ������,����֮���Ծ���ż��,�����ӶԽ����ܽ�
//��������֮��Ϊż����'#'���ҵ�.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 700
using namespace std;
//odd ��������֮��������'#'����
//even��������֮��ż����'#'����
//'#'��Ҫ����N
int n,cas,odd,even,ans,mp[N][N],cnt,head[N],vis[N],link[N];
struct Edge{
    int to,next;
}edge[4*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=odd=even=0;
    cas++;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&x);
                if(x == '#'){
                    //����֮��Ϊ������Ϊһ������,����֮��Ϊż����Ϊ��һ������ ǡ�ù��ɶ���ͼ
                    //�ֿ���¼��ı��,2�������е�ı�ſ�������ͬ��
                    if((i+j)%2) mp[i][j]=++odd;//����  (i+j) & 1Ҳ��  & ���ȼ��� ==��
                    else mp[i][j]=++even;//ż��
                }
                else
                    mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //((i+j) & 1) == 0 Ҳ��  & ���ȼ��� ==��
                if((i+j)%2 == 0 || !mp[i][j]) continue;//����ֻ��������֮��Ϊ������'#'�㹹�ɼ��Ϸ����ĵ����
                //������뿼��4������,��Ϊ����֮��Ϊ������'#'��������4������ĵ�һ���������Ϊż���ĵ�
                //������ֻ���������������,����Ҫ����4������
                if(i>1 && mp[i-1][j])
                    addEdge(mp[i][j],mp[i-1][j]);
                if(j>1 && mp[i][j-1])
                    addEdge(mp[i][j],mp[i][j-1]);
                if(j<n && mp[i][j+1])
                    addEdge(mp[i][j],mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    addEdge(mp[i][j],mp[i+1][j]);
            }
        }
        for(int i=1;i<=odd;i++){//��������֮��Ϊ������'#'��ȥ���ż��
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("Case %d: %d\n",cas,ans);//��Ϊֻ������㼯�ϵ�ż�㼯�ϵĵ����,����ֱ�����ans,���س�2
    }
    return 0;
}
*/
