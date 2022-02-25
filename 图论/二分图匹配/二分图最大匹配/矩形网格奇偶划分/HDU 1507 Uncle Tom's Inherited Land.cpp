#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;
//ac 46ms ����������֮����ż���ֶ���ͼ
/*
����:һ��n*m������,�����غͳ���2�������,������k������,
����Ҫ��������,һ��ֻ����������2��1*2��2*1���ɵľ�������,
�����������������������,�����ÿһ���������ص�����.
ע��:���������صĸ������ᳬ��50.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1507
˼·:������1*2�ľ�������������ʱ�������ص�,�����й�����,
���նԽ�����ż����ָ�n*m�����е�����Ϊ��������,�������ͼ,
�������㷨������ƥ��.���԰�����ż�Խ����ص�����Ԥ�ȴ�����,
ֱ�ӿ������漯�Ϻ�ż�����е�������1*2��2*1�㽨��.��������
���������.
*/

int n,m,k,odd,even,ans,mp[N][N],vis[N],match[N];
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int judge(int i,int j){
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y+1) return 1;
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y-1) return 1;
    if(node2[i].x == node1[j].x+1 && node2[i].y == node1[j].y) return 1;
    if(node2[i].x == node1[j].x-1 && node2[i].y == node1[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(mp,0,sizeof(mp));
    memset(match,0,sizeof(match));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);//n*m������k������
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=1;//��ǳ���
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mp[i][j]){
                    if((i+j)%2) node1[++odd]=Node(i,j);//��������
                    else node2[++even]=Node(i,j);//ż������
                }
            }
        }
        for(int i=1;i<=even;i++){//�������Ϻ�ż��������������1*2��2*1����
            for(int j=1;j<=odd;j++){
                if(judge(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=even;i++){//����ÿ��ż��������
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;//match�м�¼������������Ե�ż��ı��
        }
        printf("%d\n",ans);
        for(int i=1;i<=odd;i++){//�������� match���ҵ���Ӧ��Ե�ż��,�����ƥ��ʱż��->���
            if(!match[i]) continue;
            printf("(%d,%d)--(%d,%d)\n",node2[match[i]].x,node2[match[i]].y,node1[i].x,node1[i].y);
        }
    }
    return 0;
}

/*
//ac 46ms ʱ����Ż����������㷨����Ƶ����ʼ��vis����
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,k,odd,even,ans,mp[N][N],vis[N],match[N];
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

int dfs(int u,int clock){
    for(int &v : G[u]){
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(!match[v] || dfs(match[v],clock)){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

int judge(int i,int j){
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y+1) return 1;
    if(node2[i].x == node1[j].x && node2[i].y == node1[j].y-1) return 1;
    if(node2[i].x == node1[j].x+1 && node2[i].y == node1[j].y) return 1;
    if(node2[i].x == node1[j].x-1 && node2[i].y == node1[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(mp,0,sizeof(mp));
    memset(match,0,sizeof(match));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!mp[i][j]){
                    if((i+j)%2) node1[++odd]=Node(i,j);
                    else node2[++even]=Node(i,j);
                }
            }
        }
        for(int i=1;i<=even;i++){
            for(int j=1;j<=odd;j++){
                if(judge(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=even;i++){
            if(dfs(i,i)) ans++;
        }
        printf("%d\n",ans);
        for(int i=1;i<=odd;i++){
            if(!match[i]) continue;
            printf("(%d,%d)--(%d,%d)\n",node2[match[i]].x,node2[match[i]].y,node1[i].x,node1[i].y);
        }
    }
    return 0;
}
*/

/*
//ac 31ms
//��һ�ּ�¼���� ��ȡ��İ취 (i-1)*m+j-1
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,k,ans,mp[N][N],vis[N],match[N],seq[N],cnt;
vector<int> G[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(mp,-1,sizeof(mp));
    memset(match,0,sizeof(match));
    for(int i=1;i<=50;i++) G[i].clear();
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        scanf("%d",&k);//n*m������k������
        while(k--){
            scanf("%d%d",&x,&y);
            mp[x][y]=0;//��ǳ���Ϊ0
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j] == -1){//����Ϊ-1
                    //��¼mp[i][j]��ʾ�ĵ�ı��Ϊcnt
                    //���Ϊcnt�ĵ��Ӧ��x����i,y����Ϊj,x=seq[cnt]/m+1,y=seq[cnt]%m+1
                    //seq[cnt]���Ϊcnt�ĵ��Ӧ������ӳ��ֵΪ(i-1)*m+j-1 �������ƥ���Ե�����
                    seq[++cnt]=(i-1)*m+j-1;
                    mp[i][j]=cnt;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!((i+j)%2)) continue;//ֻ������֮��Ϊ�����ĵ㷢���ĵ���� �����ĸ�����
                if(j<m && mp[i][j+1])
                    G[mp[i][j]].push_back(mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    G[mp[i][j]].push_back(mp[i+1][j]);
                if(j>1 && mp[i][j-1])
                    G[mp[i][j]].push_back(mp[i][j-1]);
                if(i>1 && mp[i-1][j])
                    G[mp[i][j]].push_back(mp[i-1][j]);
            }
        }
        for(int i=1;i<=cnt;i++){
            //if((seq[i]/m+seq[i]%m)%2 == 0) continue;//ż����ʵ����û�н��ߵ�
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;//ż���㲢û�н����� ����ö��ʱ��ֱ���˳�
        }
        printf("%d\n",ans);
        int x1,y1,x2,y2;
        for(int i=1;i<=cnt;i++){
            if(!match[i]) continue;//cnt����ֻ������֮��Ϊż���ĵ�match����ֵ i����Ե���Ϊmatch[i]
            //��Ϊseq[cnt]=(i-1)*m+j-1
            x1=seq[match[i]]/m+1;
            y1=seq[match[i]]%m+1;
            x2=seq[i]/m+1;
            y2=seq[i]%m+1;
            printf("(%d,%d)--(%d,%d)\n",x1,y1,x2,y2);
        }
    }
    return 0;
}
*/
