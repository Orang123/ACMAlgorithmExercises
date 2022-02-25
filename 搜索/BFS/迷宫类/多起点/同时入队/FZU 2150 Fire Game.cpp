/*
����:n*m�Ĳݵ�,'#'�����,'.'����յ�,2��С��ͬʱ��ȼ2���ݵ�(������ʱ��),
ÿһ���Ż�ض���������һ���������������Ŀ�ݵ�'#',�յ�'.'�ǲ������ŵ�.
�������ٻ�����ʱ������յ����вݵ�,����ղ��������-1.
���ݱ�֤������һ���ݵ�.
1<=n,m<=10.
����:https://vjudge.net/problem/FZU-2150
˼·:����ö�����вݵص������ݵ���Ϊ��㿪ʼbfs,����������вݵص����ʱ��,
��¼�Ƚ�ÿ��bfs��ʱ����Сֵ��Ϊ��,ע������ݵظ���������2,�����軨��ʱ��
�û�����������,ֱ�Ӹտ�ʼ��ȼ1��2���ݵؼ������軨��ʱ��.
*/
//ac FZU�������ܽ���,�޷�����,Ӧ����û����� bfs
//���Ӷ�O(n*m*n*m*n*m)=10^6
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 15
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N],cnt;
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};
vector<pair<int,int>> node;
queue<State> Q;

int bfs(){
    State tp;
    int nx,ny,siz=2;//��ʼ�Ѿ���ȼ2���ݵ���
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx>=1 && nx<=n && ny>=1 && ny<=m && mp[nx][ny] =='#' && !vis[nx][ny]){
                vis[nx][ny]=1;
                siz++;
                if(siz == cnt)//���вݵ��ѱ���ȼ,������ʱ��tp.t+1
                    return tp.t+1;
                Q.push(State(nx,ny,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int T,cas=0,t,ans;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        cas++;
        node.clear();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '#'){
                    cnt++;//��¼�ݵظ���
                    node.push_back(make_pair(i,j));
                }
            }
        }
        if(cnt<=2){
            printf("Case %d: 0\n",cas);
            continue;
        }
        ans=INF;
        //ö�� ��ʼ��ȼ��2���ݵ���� ���Ӷ�O(100*100)
        for(int i=0;i<node.size();i++){
            for(int j=i+1;j<node.size();j++){
                while(!Q.empty()) Q.pop();
                memset(vis,0,sizeof(vis));
                vis[node[i].first][node[i].second]=1;
                vis[node[j].first][node[j].second]=1;
                Q.push(State(node[i].first,node[i].second,0));
                Q.push(State(node[j].first,node[j].second,0));
                t=bfs();//O(100)
                if(t!=-1)
                    ans=min(ans,t);
            }
        }
        if(ans!=INF)
            printf("Case %d: %d\n",cas,ans);
        else
            printf("Case %d: -1\n",cas);
    }
    return 0;
}
