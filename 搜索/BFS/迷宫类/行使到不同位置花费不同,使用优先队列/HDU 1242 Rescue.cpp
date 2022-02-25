/*
����:һ��������ץ,�����и�����,��ͼ��'a'������'r'������������,
'#'����ǽ,'.'����·,'x'��������,�����������2��,����1��,����������
������������ȹ�����Ҫ������,������ܽ�����"Poor ANGEL has to stay in the prison all his life."
ע��:ʵ����Ŀ����ֻ��һ������,����ж������,��Ҫ���ǽ��������ͬʱ���,
�������ٵ���ÿ��λ�õ�����ʱ��,ÿ��λ��ͬ��ֻ�ᵽ��һ��.
n,m<=200.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1242
˼·:bfs,��·'.'��Ҫ1s,�����λ2s,��������ȶ���.
*/
//ac 93ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 210
using namespace std;

int n,m,d,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int bfs(int sx,int sy){
    priority_queue<State> Q;
    mp[sx][sy]='#';
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.top();
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(nx<1 || nx>n || ny<1 || ny>m || mp[nx][ny] == '#')
                continue;
            if(mp[nx][ny] == '.'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+1));
            }
            else if(mp[nx][ny] == 'x'){
                mp[nx][ny]='#';
                Q.push(State(nx,ny,tp.t+2));
            }
            else if(mp[nx][ny] == 'a')
                return tp.t+1;
        }
    }
    return -1;
}

int main(){
    int sx,sy,ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'r')
                    sx=i,sy=j;
            }
        }
        ans=bfs(sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("Poor ANGEL has to stay in the prison all his life.\n");
    }
    return 0;
}
