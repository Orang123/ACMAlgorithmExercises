/*
//����ժ������
����:һ���г������ӱ��ֳ�5������,Ϳ��5�ֲ�ͬ��ɫ.
�ֱ����̡��ڡ��졢������,����ÿ˳ʱ����ǰת��һ��λ��,
�����������ɫ�ͻ��ɺ������ɫ,�統ǰ��ɫ��ǰת��1
��λ��,��ɫ�ͻ��������.���г�ÿ1��Ҫô�ﵽ��ǰ
�������һ������,Ҫô��ת������ת��ͷ90��,ֻ����
ԭλ�õ�ת�������ǰ��.һ��ʼ���г�ͷ����,����
�����������ɫΪ��,����Ŀ���ʱ,���ֽ������������
������ɫ��������ɫ,����ͷ����������.�󵽴�Ŀ�������ʱ��.
��ͼ��n*m������,'#'�������ߵķ���,���������ǿ����ߵ�.
'S'���������,'T'����Ŀ���.
1<=n,m<=25.
����:https://www.luogu.com.cn/problem/UVA10047
˼·:bfs,��ΪҪ�󵽴�Ŀ�����ɫΪ��ɫ,����ɫ�ı䶯ֻ�ͳ���ת��
��ʱ���й�,���̡��ڡ��졢�����׷ֱ���0��1��2��3��4�õ����ִ���,
��ô����Ŀ���ʱ���ֽ����������ɫ���ǳ�����ǰת����ʱ��tģ5,��t%5.
��������(x,y)״̬��ǳ�����Ҫ����ɫ�����,��Ӧ�����г��ĳ�ͷ������,
��Ϊ�п�����ɫ��ͬ,�������ų�ͷ����ͬ,�����ʱ�䲻ͬ,�ͻ�Ӱ������
����Ŀ���ʱ�ĳ�����ɫ.
vis[x][y][i][color]��ʾ��(x,y)λ��ʱ,���г��ķ���Ϊi,���������������������������ɫΪcolor.
�����ж����ҷ�����Խ�dir�����������ó�������˳ʱ�뷽�� ��(0)����(1)����(2)����(3),
���ڵķ�������պö���1.ֻ��ע�ⱱ������0,��1���С��0,���Ҫ����Ϊ3,��(3)+1����3
Ҫ����Ϊ0,�൱�ڽ���������0��1��2��3����һ����.
�����ǰ��ͷ����curDir+1/-1���Ե���ö�ٵ����ҷ���i,��ô˵������i���� ��������90�ȵķ���.
����˵����������ǵ�ǰ��ͷ�ķ�����(180��)���ܵ�ת.
ʵ�ʿ���ͨ��ȡģ(curDir+1)%4��(curDir+3)%4�ֱ��ʾ ��ǰ����curDir����ࡢ�Ҳ෽��.

ע��:���������ȶ��� ֱ�ӽ���ͷ��ת֮��ֱ�Ӱ���ת��ķ���ǰ��һ���� ����2s ���,�����޷���ԭλ��
��2���ֱ��ת90�� ��ת��ԭ���ķ�����180��,ʵ�ʻ��ѵ�ʱ����ܽϴ�,����ͻ�wa.
*/
//ac 0ms bfs+��ά״̬���
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#define N 30
using namespace std;

//green��black��red��blue��white 5����ɫ�ֱ��Ӧ����0 1 2 3 4
//vis[x][y][i][color]��ʾ��(x,y)λ��ʱ,���г��ķ���Ϊi,���������������������������ɫΪcolor.
//dir��������ǰ�˳ʱ�뷽�������ŷŵ� ��(0)����(1)����(2)����(3)
int n,m,dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},vis[N][N][4][5];
char mp[N][N];
struct State{
    int x,y,dir,col,t;
    State(int x=0,int y=0,int dir=0,int col=0,int t=0):
        x(x),y(y),dir(dir),col(col),t(t){}
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>m || mp[x][y] == '#')
        return 1;
    return 0;
}

int judgeDir(int i,int nextDir){
    if(nextDir<0)//С��0ʱ��Ӧ�ķ����ǻ��ϵ�3
        nextDir=3;
    else if(nextDir>3)//����3��Ӧ�����ǻ��ϵ�0
        nextDir=0;
    if(nextDir == i)//�������� ��ת90�ȷ���
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    vis[sx][sy][0][0]=1;
    Q.push(State(sx,sy,0,0,0));
    State tp;
    int nx,ny,nc;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == 'T' && tp.col == 0)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            if(tp.dir == i){//�ͳ�ͷ����һ�� ��ǰ��
                nx=tp.x+dir[i][0];
                ny=tp.y+dir[i][1];
                if(check(nx,ny))
                    continue;
                nc=(tp.col+1)%5;//��ɫ�����һλ
                if(!vis[nx][ny][i][nc]){
                    vis[nx][ny][i][nc]=1;
                    Q.push(State(nx,ny,i,nc,tp.t+1));
                }
            }
            //��ͷ����һ�� ֻ�ܵ�ת90�� ����1s ������ԭλ��,��ɫ����
            //else if(judgeDir(i,tp.dir+1) || judgeDir(i,tp.dir-1)){//ac
            else if((tp.dir+1)%4 == i || (tp.dir+3)%4 == i){//ac 2���ж�����90�ȷ���ķ�ʽ +1��ʾ+1 +3��ʾ-1
                if(!vis[tp.x][tp.y][i][tp.col]){
                    vis[tp.x][tp.y][i][tp.col]=1;
                    Q.push(State(tp.x,tp.y,i,tp.col,tp.t+1));
                }
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,sx,sy,ans;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        ans=bfs(sx,sy);
        if(cas!=1)//����֮��Ҫ�ճ�һ�� �����Presentation Error
            printf("\n");
        printf("Case #%d\n",cas);
        if(ans!=-1)
            printf("minimum time = %d sec\n",ans);
        else
            printf("destination not reachable\n");
    }
    return 0;
}
