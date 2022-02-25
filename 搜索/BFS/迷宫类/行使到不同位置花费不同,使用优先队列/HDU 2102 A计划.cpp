/*
����:����������һ��������Թ���,�Թ��������S(1,1,0),������λ����'P'��ʾ,
ʱ�մ������'#'��ʾ,ǽ��'*'��ʾ,ƽ����'.'��ʾ.��ʿ��һ����ʱ�մ�����ͻ�
��ת����һ������λ��,�������ת����λ����ǽ�Ļ�,����ʿ�Ǿͻᱻײ��.��ʿ
����һ����ֻ��ǰ�������ƶ�,ÿ�ƶ�һ��1ʱ��.�����ƶ�ֻ��ͨ��ʱ�մ����,
�Ҳ���Ҫ�κ�ʱ��.�����ʿ���ܹ���Tʱ�����ҵ������������YES��,���������NO��.
1<=n,m<=10.
ע��:ժ�Ժ���Discussģ��
1.����'#'�����Ǳش��͵���һ��,û�еڶ���ѡ��,����ѡ����ͬ������������չ.
2.���߶��Ǵ�����ʱ,����һ���Ǵ�����һ����ǽʱ,�������������·.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2102
˼·:bfs,��Ϊ�����Ų���Ҫ����ʱ��,��˲������ȶ���.
*/
//ac 0ms bfs
//���Ӷ�O(n*m*2)=200
#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#define N 11
using namespace std;

//ǰ4����������ͬһ�����������ƶ�,��2���������ڲ�������ƶ�.
//��ΪҪ�ж��߹����Ƿ���'#'������ѡ���Ƿ�����ڲ���ƶ�,�����޷���mpԭͼ���һ�߹��ĵ������,ֻ����vis�����.
int n,m,t,dir[6][3]={{-1,0,0},{1,0,0},{0,-1,0},{0,1,0},{0,0,1},{0,0,-1}},vis[N][N][2];
char mp[N][N][2];
struct State{
    int x,y,z,t;
    State(int x=0,int y=0,int z=0,int t=0):x(x),y(y),z(z),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int bfs(){
    priority_queue<State> Q;
    vis[1][1][0]=1;
    Q.push(State(1,1,0,0));
    int nx,ny,nz;
    State tp;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y][tp.z] == 'P'){
            if(tp.t<=t)
                return 1;
            else
                return 0;
        }
        Q.pop();
        for(int i=0;i<6;i++){
            //���Ǵ����� �޷��ڲ���ƶ� ֻ����ǰ4�������ƶ�
            if(mp[tp.x][tp.y][tp.z]!='#' && i>=4)
                continue;
            //�Ǵ����� ֻ���ڲ���ƶ� ֻ���ں�2�������ƶ�
            if(mp[tp.x][tp.y][tp.z] == '#' && i<4)
                continue;
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            nz=tp.z+dir[i][2];
            if(nx<1 || nx>n || ny<1 || ny>m || nz<0 || nz>1 || mp[nx][ny][nz] == '*' || vis[nx][ny][nz])
                continue;
            //'#'������ ������������������ ֻ���ٴ�����
            if(mp[tp.x][tp.y][tp.z] == '#' && mp[nx][ny][nz] == '#')
                continue;
            if(i<4){
                vis[nx][ny][nz]=1;
                Q.push(State(nx,ny,nz,tp.t+1));
            }
            else{
                vis[nx][ny][nz]=1;
                Q.push(State(nx,ny,nz,tp.t));
            }
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d%d",&n,&m,&t);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j][0]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf(" %c",&mp[i][j][1]);
        }
        if(bfs())
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*
//ac 15ms dfs
//���ݽ��� ʵ�ʸ��Ӷȿɴ� 5^(10*10*2)=6^200
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[15][15][15];
int temp[15][15][15];
int n,m,t,sign;
int xx[]={1,0,-1,0};
int yy[]={0,-1,0,1};
void dfs(int x,int y,int z,int sum){
   int i;
   if(x<0||x>=m||y<0||y>=n||z<0||z>1||sign==1)      //��������ҵ��Ͳ�����
   return;
   if(sum>t)                                        //����ʱ��Ͳ�����
   return;
   if(str[x][y][z]=='P'){                           //�ҵ�֮����
   sign=1;
   return;
   }
   if(temp[x][y][z]==1||str[x][y][z]=='*')          //����·�Ѿ��߹�������ǽ�Ͳ�����
   return;
   if(str[x][y][z]=='#'){
   if(str[x][y][1-z]!='#')                          //���Ǵ�����ʱ����һ�˲���ǽʱ����
   dfs(x,y,1-z,sum);
   return;                                          //���һ��Ҫ���ݣ����߼������߶���
   }                                                //�����ŵĻ��ͻ���ѭ��
   temp[x][y][z]=1;
   for(i=0;i<4;i++)
   dfs(x+xx[i],y+yy[i],z,sum+1);
   temp[x][y][z]=0;
}
int main(){
    int cur,i,j,k;
    scanf("%d",&cur);
    while(cur--){
        scanf("%d%d%d",&m,&n,&t);
        getchar();
        for(i=0;i<2;i++)
        for(j=0;j<m;j++)
        for(k=0;k<n;k++)
        cin>>str[j][k][i];
        memset(temp,0,sizeof(temp));
        sign=0;
        dfs(0,0,0,0);
        if(sign)
        puts("YES");
        else
        puts("NO");
    }
    return 0;
}
*/
