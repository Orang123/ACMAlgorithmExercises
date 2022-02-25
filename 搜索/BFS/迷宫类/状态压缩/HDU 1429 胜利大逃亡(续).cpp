/*
����:Ignatius�ٴα�ħ��ץ����(�㲻����զ��ô��ħ��ϲ��)���ħ����ȡ���ϴεĽ�ѵ,
��Ignatius����һ��n*m�ĵ�����,���ڵ��ε�ĳЩ�ط���װ�˴�������,Կ�ײ��ڵ��������ĳЩ�ط�.
�տ�ʼIgnatius������(sx,sy)��λ��,�뿪���ε�����(ex,ey)��λ��.Ignatiusÿ����ֻ�ܴ�һ������
�ߵ������ĸ������е�����һ��.ħ��ÿt���ӻص����Ӳ�һ��,������Ignatius����ԭλ�ñ�������ȥ.
�������ɴεĳ���,Ignatius�ѻ����������εĵ�ͼ.����������������ܷ��ٴγɹ�����.ֻҪ��ħ���´�
�Ӳ�֮ǰ�ߵ����ھ����뿪����,���ħ��������ʱ��պ��ߵ����ڻ�δ�����ڶ�������ʧ��.
. ����·
* ����ǽ
@ ����Ignatius����ʼλ��
^ ������εĳ���
A-J �����������,��Ӧ��Կ�׷ֱ�Ϊa-j
a-j ����Կ�ף���Ӧ���ŷֱ�ΪA-J
2<=n,m<=20.t>0.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1429
˼·:״̬ѹ��bfs,�Զ���a~j 10��Կ��,��10��������λ1����ʾ ��Ӧ��10������ֵ Ϊ0~(2^10-1).
���״̬�������Ϊvis[N][N][1<<10].
*/
//ac 343ms bfs a~j��״̬�ж�Ϊ!vis[nx][ny][tp.sta|1<<(ch-'a')],֮ǰ��״̬Ҫ��õ�ǰ��Կ������(nx,ny)��λ�����ж�Կ�׵�״̬�Ƿ���ֹ�
//vis�жϱ�Ƿ������з�֧��
//ʱ�临�Ӷ�O(20*20*1024)=4*10^6
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

//a~j���10��Կ�� ��10��������λ1����ʾ ��Ӧ��10������ֵ Ϊ0~(2^10-1)
int n,m,t,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][1<<10];
char mp[N][N];
struct State{
    int x,y,m,sta;
    State(int x=0,int y=0,int m=0,int sta=0):x(x),y(y),m(m),sta(sta){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0,0));
    State tp;
    int nx,ny,ch;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '^'){
            if(tp.m<t)
                return tp.m;
            else
                return -1;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<1 || nx>n || ny<1 || ny>m)
                continue;
            ch=mp[nx][ny];
            if(ch == '*')
                continue;
            if(ch>='a' && ch<='j' && !vis[nx][ny][tp.sta|1<<(ch-'a')]){
                vis[nx][ny][tp.sta|1<<(ch-'a')]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta|1<<(ch-'a')));
            }
            else if(ch>='A' && ch<='J' && (tp.sta & 1<<(ch-'A')) && !vis[nx][ny][tp.sta]){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
            //ע������һ��Ҫ����(ch == '.' || ch == '@' || ch == '^')���ж� ����,ǰ�治�����Կ�׵������� !vis[nx][ny][tp.sta]����������ͻ������� ����debug�˺þ�
            else if((ch == '.' || ch == '@' || ch == '^') && !vis[nx][ny][tp.sta]){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d%d",&n,&m,&t)!=EOF){
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
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 296ms bfs  a~j��״̬�ж�Ϊ!vis[nx][ny][tp.sta] ��:����(nx,ny)��״̬�жϲ�������(nx,ny)�ϵ�Կ��
//vis�ж�ͳһ���� ���з�֧֮ǰ
//�����жϱ������ ʵ�ʸ��Ӷ���ƫ���,��Ϊ�����(nx.ny)��a~j��δ��vis[nx][ny][tp.sta]���
//������б�Ľϳ�·�� ����õ��֮ǰ״̬һ�����ظ����
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int n,m,t,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][1<<10];
char mp[N][N];
struct State{
    int x,y,m,sta;
    State(int x=0,int y=0,int m=0,int sta=0):x(x),y(y),m(m),sta(sta){}
};

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0,0));
    State tp;
    int nx,ny,ch;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == '^'){
            if(tp.m<t)
                return tp.m;
            else
                return -1;
        }
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            //����(nx,ny)��a~jԿ�׵���� ʵ��ֻ���ж� ֮ǰ��״̬Ϊδ��ø�λ��Կ��ʱ��״̬�Ƿ���ֹ�����
            //�����жϱ������ ʵ�ʸ��Ӷ���ƫ���,��Ϊ�����(nx.ny)��a~j��δ��vis[nx][ny][tp.sta]���
            //������б�Ľϳ�·�� ����õ��֮ǰ״̬һ�����ظ����
            if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny][tp.sta])
                continue;
            ch=mp[nx][ny];
            if(ch == '*')
                continue;
            if(ch>='a' && ch<='j'){
                vis[nx][ny][tp.sta|1<<(ch-'a')]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta|1<<(ch-'a')));
            }
            else if(ch>='A' && ch<='J' && (tp.sta & 1<<(ch-'A'))){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
            else if(ch == '.' || ch == '@' || ch == '^'){
                vis[nx][ny][tp.sta]=1;
                Q.push(State(nx,ny,tp.m+1,tp.sta));
            }
        }
    }
    return -1;
}

int main(){
    int sx,sy;
    while(scanf("%d%d%d",&n,&m,&t)!=EOF){
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
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/
