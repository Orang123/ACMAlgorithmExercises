/*
����:һ��n*m�ķ������,���������'@'����,ֻ������������4������,
'.'������,��#����ǽ,��k�����������ڸ�����,���Ҹ�������k��������
��������,���������������Ҫ�߶��ٲ����԰�k������ȡ������,�����
������k���������-1.
0<n,m<=100.0<k<=4.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4771
˼·:Ҫ���õ����б��������ٲ���,������bfs������������Ƚ��ȳ�,ÿһ��
״̬����չ,ÿ������ƽ�����ӵĲ�������1,ÿ��״̬���ߵ�·��ÿ�����ǰ�
���Ų������������ȥ�ߵ�,������ȳ��Ӵﵽȡ��k������ʱ,���õĲ����������ٵ�,
bfs��̰�İ���ÿ��������̵�·������״̬ת�Ƶ�,
ֻ���������ȡ��һ�������ϵı���,������Ҫ�����ߵ�֮ǰ�߹��ĸ���,ֻ��
�ٴ��ߵ�֮ǰ�߹��ĸ���ʱ���ϳ��б���������ͬ,����ǲ�ͬ��״̬,���Զ���
ÿ������(x,y)��״̬Ӧ���ǵ�ǰ�����������б����ļ���������,�������ܱ�
֤״̬��ǵ���Ч�� ʹ���ܹ��ظ������ߵ�֮ǰ�߹��ĸ���.����ȡ����������
������,�����ö�����λ����ʾ,����k������������k��0/1������λ��ʾ,0����
��ǰλ�ı�����ûȡ��,1����ǰλ�ı���ȡ����,��ô���б������еĿ������
��2����λ������0~(1<<k)-1��10������ֵ��ʾ,����vis������Ҫ���� vis[N][N][1<<4].
��С��0������λ����0,����һ��������ûȡ,(1<<k)-1��������λ����1,k��������ȡ����.

ע��:
1.��������k���������Ƿ����ڲ�ͬ�ĸ����ϵ�,�������������Է�����ͬһ������,
��ô��״̬ѹ��ʱҪ����ǰ�����ϵ����б�����ѹ����ȥ.
2.������dfs����+״̬ѹ��,��Ϊ����������ܱ�֤����������vis[x][y][sta]�Ĳ���
����С��,���ֱ�ӱ�ǻᵼ�º������ٲ�����״̬ȡ���ı���������vis[x][y][sta]
�Ѿ���֮ǰ�϶ಽ�� ��ǰ���,������С������״̬�Ͳ��ܵõ�������չ,���ܼ�������ȥ,
�Ӷ�������С�������Ǵ����.
*/
//ac 0ms bfs+״̬ѹ�� ��forѭ���ڲ����֮ǰ�ж�״̬�Ƿ��ѱ��.
//ʱ�临�ӶȺͿռ临�Ӷȶ���O(n*m*2^k) ÿ���ڵ������16��״̬0~2^4-1,���п�����չ��״̬�����n*m*(2^k) 100*100*16=160000=1.6*10^5
//ʵ�ʸ��Ӷȿ϶�Ҫ��O(n*m*2^k)ҪС,��ΪֻҪ״̬�ﵽ2^k-1�ͻ����.
//k�������������ڲ�ͬ�ĸ����� judge���ҵ��ĸ�����ֱ�ӷ���
//ע�����(nx,ny)���б�����״̬ ʵ��״̬�ж�vis�����ж� ֮ǰ��״̬δȡ����(nx,ny)������״̬��:!vis[nx][ny][tp.sta],
//��״̬����Ծ���Ҫ���ȡ���õ㱦����״̬��:vis[nx][ny][tp.sta|1<<val]=1,���������� ����vis[nx][ny][tp.sta]��û�б�ǵ�,Ҳ����������������ϳ�·�� ��֮ǰ״̬һ�����ظ����.
//Ҳ�����ж�vis[nx][ny][tp.sta|1<<val]����õ�ȡ���õ㱦����״̬
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

//���ҵ�ǰ����(x,y)�Ϸ��õ����ĸ�����,��i��������Ӧ�Ķ�����λ��1<<(i-1)
int judge(int x,int y){
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            return i-1;//�ҵ��ͷ���
    }
    return -1;//��ǰ����û�з��ñ���
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    vis[sx][sy][0]=1;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        Q.pop();
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int val,sta;
                val=judge(nx,ny);
                //ע�ⲻ����tp.sta + 1<<val ��Ϊ�ӷ��ᵼ��ͬһ���ӵı����ظ�ȡ,
                //����λ������Ѿ�ȡ����ǰ���ӱ���,��ô��λ��|��ת̬����tp.sta��δ�õ���״̬ �����ظ����
                if(val != -1)
                    sta=tp.sta | 1<<val;
                else//��ǰ����û�з��ñ���
                    sta=tp.sta;
                if(!vis[nx][ny][sta]){
                    vis[nx][ny][sta]=1;//��ǵ�ǰ״̬
                    Q.push(State(nx,ny,tp.step+1,sta));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){//��¼������ //��������ݳ����� �ǲ�����������,��Ȼ��ʼ״̬��sta ҲӦ���ж�һ��
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 15ms bfs+״̬ѹ�� ��forѭ���ڲ����֮ǰ�ж�״̬�Ƿ��ѱ��
//��ǿ�� һ��������ܷŶ������ ��״̬ѹ��ʱҪ����ǰ�����ϵ����б�����ѹ����ȥ.
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

int judge(int x,int y){
    int val=0;
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            val|=1<<(i-1);//Ҫ����ǰ�����ϵ����б�����Ӧ�Ķ�����λ1��ȡ��
    }
    return val;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    vis[sx][sy][0]=1;
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        Q.pop();
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int sta;
                sta=tp.sta | judge(nx,ny);
                if(!vis[nx][ny][sta]){
                    vis[nx][ny][sta]=1;
                    Q.push(State(nx,ny,tp.step+1,sta));
                }
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
//ac 0ms bfs+״̬ѹ�� ��forѭ���ⲿ����֮���ж�״̬�Ƿ��ѱ��.
//k�������������ڲ�ͬ�ĸ����� judge���ҵ��ĸ�����ֱ�ӷ���
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
using namespace std;

int n,m,k,vis[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct Goods{
    int x,y;
}gds[4];
struct State{
    int x,y,step,sta;
    State(int x=0,int y=0,int step=0,int sta=0):x(x),y(y),step(step),sta(sta){}
};

int judge(int x,int y){
    for(int i=1;i<=k;i++){
        if(x == gds[i].x && y == gds[i].y)
            return i-1;
    }
    return -1;
}

int bfs(int sx,int sy){
    queue<State> Q;
    Q.push(State(sx,sy,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(tp.sta == (1<<k)-1)
            return tp.step;
        if(vis[tp.x][tp.y][tp.sta])//ע���������pop֮��,����ǰtp��һֱ������,��ѭ��
            continue;
        vis[tp.x][tp.y][tp.sta]=1;
        for(int i=0;i<4;i++){
            int nx=tp.x+dir[i][0];
            int ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]!='#'){
                int val,sta;
                val=judge(nx,ny);
                if(val != -1)
                    sta=tp.sta | 1<<val;
                else
                    sta=tp.sta;
                Q.push(State(nx,ny,tp.step+1,sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '@'){
                    sx=i;
                    sy=j;
                }
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&gds[i].x,&gds[i].y);
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
//TLE dfs+������״̬ѹ�� ö�ٳ������ߵ�Ŀ�ĵ�ķ�����ʱ������Сֵ
//���Ӷ�O(4^(n*m*2^k))��ΪҪ�����е�ȡ��k�������Ĳ�����ö�ٳ��� �Ƚ������С����,Ҫ�����������
//dp[x][y][sta]������(x,y)ʱ��ǰ��Я���ı���״̬Ϊstaʱ��֮ǰ�ı�����������Ҫ�Ĳ��� ������֦,�����ǰ�������ܱ�֮ǰ������С �򷵻�
//dfs����+dp��¼��С������֦��ԭ��:��Ϊ����������ܱ�֤����������dp[x][y][sta]�Ĳ���
//����С��,���ֱ�ӱ��Ϊ1���ػᵼ�º������ٲ�����״̬ȡ���ı���������dp[x][y][sta]
//�Ѿ���֮ǰ�϶ಽ�� ��ǰ���,������С������״̬�Ͳ��ܵõ�������չ,���ܼ�������ȥ,
//�Ӷ�������С�������Ǵ����.�����Ҫö�ٳ������ߵ�Ŀ�ĵ�ķ�����ʱ������Сֵ

//��Ϊ���Ⲣû����ȷ�ĵ�Ŀ�ĵ�,�����޷�ʹ��һ��Ŀ�ĵصĵ������������������پ����֦

//ֱ��dp[x][y][sta]=1���ػ�� ���� ����HDU Discussģ��
//4 4
//#@##
//..#.
//#.##
//....
//4
//2 1
//2 2
//4 3
//4 4
#include<cstdio>
#include<cstring>
#include<queue>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

//dp[x][y][sta]������(x,y)ʱ��ǰ��Я���ı���״̬Ϊstaʱ��֮ǰ�ı�����������Ҫ�Ĳ��� ������֦,�����ǰ�������ܱ�֮ǰ������С �򷵻�
int n,m,k,dp[N][N][1<<4],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;
//val[i]�����i������ѡȡ������Ķ�����λ1��Ӧ��ʮ������ֵ
//mp[x][y]=val ����ǰ����(x,y)�Ϸ��õı���������,һ�����ӿ��ܷ��ö������ ����mp[x][y]���ۼ�
int val[5]={0,1,2,4,8},mp[N][N];

void dfs(int x,int y,int step,int sta){
    //�����ǰ����(x,y)���ȡ���ı���״̬��Ҫ�Ĳ������ܱ�֮ǰ�����Ĳ�����С �򷵻�
    //��Ϊ��ǰ�Ѿ����ܸ���,�����ı����϶�Ҳ�����֮ǰ�������� �����������
    if(step>=dp[x][y][sta])
        return;
    dp[x][y][sta]=step;
    if(sta == (1<<k)-1){
        ans=min(ans,step);
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny]>=0)
            //ע�ⲻ����tp.sta + 1<<val ��Ϊ�ӷ��ᵼ��ͬһ���ӵı����ظ�ȡ,
            //����λ������Ѿ�ȡ����ǰ���ӱ���,��ô��λ��|��ת̬����tp.sta��δ�õ���״̬ �����ظ����
            dfs(nx,ny,step+1,sta|mp[nx][ny]);
    }
}

int main(){
    int sx,sy,x,y;
    char c;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&c);
                if(c != '#'){
                    mp[i][j]=0;
                    if(c == '@'){
                        sx=i;
                        sy=j;
                    }
                }
                else
                    mp[i][j]=-1;
            }
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&x,&y);
            //�������ܷ�����'#'ǽ��,����Ҳ��ʹ��mp[x][y]ԭ�ȵ�-1�ۼӱ������ ����֮�������״̬��չ����.
            if(mp[x][y]>=0)
                //mp[x][y]=val ����ǰ����(x,y)�Ϸ��õı���������,һ�����ӿ��ܷ��ö������ ����mp[x][y]���ۼ�
                mp[x][y]+=val[i];
        }
        dfs(sx,sy,0,mp[sx][sy]);//�п��ܳ�ʼλ��'@'����ͷ����б���,����HDU������ �Ƚ��� ��ʼλ�ò�δ���ñ���
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}
*/

/*
//ac 31ms bfs���������'@'�ͷ��ñ����ĸ��������������̾�����ڽӾ���p[i][j]+dfsö��ȫ���� �ӳ��������ȡk��������˳������(ȫ����)
//k<=4,ȫ���и��Ӷ�4!
//��ˣ������Ƚ�����k���㹹��һ��ͼ��ͼ֮���Ȩ��Ϊ����֮������·�����룬����������ʹ��bfs��á�
//�ڹ�������ͼ֮�󣬿���ʹ��dfs����һ���������������������������k�������С·���ĳ��ȡ�
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

int n,m,sx,sy,k,res;
char graph[105][105];
bool vis[105][105];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

struct Node{
    int x,y;
}node[10];

struct node1{
    int x,y,step;
};
int p[10][10];

int bfs(int from,int to){
    memset(vis,0,sizeof(vis));
    queue<node1> q;
    node1 cur,next;
    cur.x = node[from].x;
    cur.y = node[from].y;
    cur.step = 0;
    q.push(cur);
    vis[cur.x][cur.y] = 1;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        if(cur.x==node[to].x && cur.y==node[to].y){
            return cur.step;
        }
        for(int i=0;i<4;i++){
            int xx = cur.x+dx[i];
            int yy = cur.y+dy[i];
            if(xx>=1 && xx<=n && yy>=1 && yy<=m && graph[xx][yy]!='#' && !vis[xx][yy]){
                vis[xx][yy] = 1;
                next.x = xx;
                next.y = yy;
                next.step = cur.step+1;
                q.push(next);
            }
        }
    }
    return -1;
}

//ö��ȫ���� k<=4 O(k!)=O(4!) ��˸��Ӷȿɽ���
void dfs(int f[],int pre,int cost,int cnt){
    if(cnt==k){
        if(cost<res){
            res = cost;
        }
        return ;
    }
    for(int i=1;i<=k;i++){
        if(f[i]==0){
            f[i] = 1;
            //ö�ٵ�cnt������Ҫȡ�ı����ǵ�i������
            dfs(f,i,cost+p[pre][i],cnt+1);
            f[i] = 0;
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)){
        if(n==0 && m==0) break;
        memset(vis,false,sizeof(vis));
        memset(graph,'#',sizeof(graph));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&graph[i][j]);
                if(graph[i][j]=='@'){
                    sx = i;
                    sy = j;  //��¼���
                }
            }
        }
        node[0].x = sx;
        node[0].y = sy;
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d",&node[i].x,&node[i].y);
        memset(p,-1,sizeof(p));
        bool flag = 0;
        for(int i=0;i<=k;i++){   //ö���������Ҫ���������������·������bfs�����
            p[i][i] = 0;
            for(int j=0;j<=k;j++){
                if(p[i][j]==-1 && flag==0){
                    p[i][j] = p[j][i] = bfs(i,j);
                    if(p[i][j]==-1){
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        int f[10];
        memset(f,0,sizeof(f));
        res = INT_MAX;
        dfs(f,0,0,0);
        printf("%d\n",res);
    }
    return 0;
}
*/
