#include<cstdio>
#include<cstring>
#define N 40
using namespace std;
//ac 16ms ����������ż���ֶ���ͼ+ƥ����*2�Ƿ���ڷǿն���(n*m-k)
/*
����:n*m�ľ�������,һЩ����ʱ�ն�,����Ҫ��1*2��2*1��С����
���Ƿǿն�������,���Ƿ��ܽ��ǿն��ĸ���ȫ������,�������"YES",
�������"NO".
����:http://poj.org/problem?id=2446
˼·:��ż���־�������Ķ���ͼ����������ƥ��,������ȫ�����Ƿǿն�
�ĸ���ʱ,���еķǿն��ĵ㶼Ҫ������ƥ���еı߼�,������ƥ��*2==���зǿն��ĸ���,
�����"YES",����"NO".
����ͨ���ж��Ƿ�����ƥ�����ж���ƥ��߼��Ƿ��ܸ������зǿն���.
*/

int n,m,k,cnt,mp[N][N],odd,even,head[N*N],vis[N*N],match[N*N],ans;
struct Edge{
    int to,next;
}edge[N*N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
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
    odd=even=ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(mp,-1,sizeof(mp));
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    //int num=0;
    init();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&u,&v);
        mp[v][u]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j]) continue;
            //num++;
            if((i+j)%2) mp[i][j]=++odd;
            else mp[i][j]=++even;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j] || (i+j)%2 == 0) continue;
            if(i<n && mp[i+1][j])
                addEdge(mp[i][j],mp[i+1][j]);
            if(j<m && mp[i][j+1])
                addEdge(mp[i][j],mp[i][j+1]);
            if(i>1 && mp[i-1][j])
                addEdge(mp[i][j],mp[i-1][j]);
            if(j>1 && mp[i][j-1])
                addEdge(mp[i][j],mp[i][j-1]);
        }
    }
    for(int i=1;i<=odd;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    //if(ans*2 == num) printf("YES");//Ҳ����Ԥ��ͳ�Ƴ��ǿն���ĸ���num
    if(ans*2 == n*m-k) printf("YES");//һ��ƥ��ߺ�2���ǿն��� Ҫ��2,�ܹ�n*m����,k���ն�,�ǿն�n*m-k
    else printf("NO");
    return 0;
}

/*
//ac 16ms ��ż���ʻ���+�ж��Ƿ�����ƥ��
//��Ҫ���ж���ż�����ϵ����Ƿ����,����Ȳ���������ƥ��,
//����ٽ�һ���������ж�ÿ�����Ƿ�����Ե�,��������������ƥ��.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,k,cnt,mp[N][N],odd,even,head[N*N],vis[N*N],match[N*N],ans;
struct Edge{
    int to,next;
}edge[N*N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
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
    odd=even=ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(mp,-1,sizeof(mp));
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v;
    init();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&u,&v);//�����ʾ���ǵ�v�е�u�� һ���ӵ�
        mp[v][u]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j]) continue;
            if((i+j)%2) mp[i][j]=++odd;
            else mp[i][j]=++even;
        }
    }
    //�������ͼ�����ϵ��������,�򲻴�������ƥ��,��Ϊ�ϴ󼯺��еĵ��Ȼ����ʣ��δ��Եĵ�.
    if(even != odd){
        printf("NO");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!mp[i][j] || (i+j)%2 == 0) continue;
            if(i<n && mp[i+1][j])
                addEdge(mp[i][j],mp[i+1][j]);
            if(j<m && mp[i][j+1])
                addEdge(mp[i][j],mp[i][j+1]);
            if(i>1 && mp[i-1][j])
                addEdge(mp[i][j],mp[i-1][j]);
            if(j>1 && mp[i][j-1])
                addEdge(mp[i][j],mp[i][j-1]);
        }
    }
    int flag=0;
    for(int i=1;i<=even;i++){
        memset(vis,0,sizeof(vis));
        if(!dfs(i)){
            flag=1;
            break;
        }
    }
    if(!flag) printf("YES");//���even����ÿ���㶼����Ե� ��������ƥ��.(��ʱeven == odd)
    else printf("NO");//even���ϴ���δ��Եĵ�,��ƥ��߼��޷��������зǿն�����,��Ȼ���зǿն�����ʣ��.
    return 0;
}
*/
