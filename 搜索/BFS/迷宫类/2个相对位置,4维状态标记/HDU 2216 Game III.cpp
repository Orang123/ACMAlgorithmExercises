/*
����:n*m������,'.'��ʾ��λ,'X'��ʾǽ,'Z'��ʾZjt,'S'��ʾSara.
���Zjt�ƶ�һ����λ,Sara�����෴�����ƶ�һ����λ,���Sara����
ǽ'X'��Խ��,���Բ��ƶ�,����Zjt���뱣֤�ƶ�,�������Zjt��Sara��
����������,��ֹͣ,�������Zjt��Sara������������Ҫ�ƶ������ٲ���,
��������������������"Bad Luck!".
ע��:���������������,��scanf(" %c",&mp[i][j])��wa ��֪��ԭ��.
n,m<=200.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2216
˼·:bfs,״̬�����Ҫ���ó���ά��vis[zx][zy][sx][sy]��ʾZjt��Sara
�Ƿ񵽴����ǰ�����λ��״̬,(zx,zy)��ʾZjt,(sx,sy)��ʾSara.
*/
//ac 15ms bfs
#include<cstdio>
#include<queue>
#include<cstring>
#define N 25
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][N][N];
char mp[N][N];
struct State{
    int zx,zy,sx,sy,t;
    State(int zx=0,int zy=0,int sx=0,int sy=0,int t=0):zx(zx),zy(zy),sx(sx),sy(sy),t(t){}
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>m || mp[x][y] == 'X')
        return 1;
    return 0;
}

int bfs(int zx,int zy,int sx,int sy){
    queue<State> Q;
    vis[zx][zy][sx][sy]=1;
    Q.push(State(zx,zy,sx,sy,0));
    State tp;
    int nzx,nzy,nsx,nsy;
    while(!Q.empty()){
        tp=Q.front();
        //�ж�Zjt��Sara�Ƿ�����
        for(int i=0;i<4;i++){
            if((tp.zx+dir[i][0] == tp.sx) && (tp.zy+dir[i][1] == tp.sy))
                return tp.t;
        }
        //�ж�Zjt��Sara�Ƿ�����
        if(tp.zx == tp.sx && tp.zy == tp.sy)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nzx=tp.zx+dir[i][0];
            nzy=tp.zy+dir[i][1];
            nsx=tp.sx-dir[i][0];//Sara���෴����
            nsy=tp.sy-dir[i][1];
            if(check(nzx,nzy))//Zjt�����ƶ�
                continue;
            if(check(nsx,nsy)){//Sara���Բ��ƶ�
                nsx=tp.sx;
                nsy=tp.sy;
            }
            if(vis[nzx][nzy][nsx][nsy])
                continue;
            vis[nzx][nzy][nsx][nsy]=1;
            Q.push(State(nzx,nzy,nsx,nsy,tp.t+1));
        }
    }
    return -1;
}

int main(){
    int zx,zy,sx,sy,ans;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            //���������������,��scanf(" %c",&mp[i][j])��wa ��֪��ԭ��
            scanf("%s",mp[i]+1);
            for(int j=1;j<=m;j++){
                if(mp[i][j] == 'Z')
                    zx=i,zy=j;
                else if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        ans=bfs(zx,zy,sx,sy);
        if(ans!=-1)
            printf("%d\n",ans);
        else
            printf("Bad Luck!\n");
    }
    return 0;
}
