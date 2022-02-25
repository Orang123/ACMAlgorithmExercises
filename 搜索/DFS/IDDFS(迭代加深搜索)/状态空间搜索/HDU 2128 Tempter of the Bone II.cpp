/*
����:m��n���Թ�,��S����ʾС�������,��D'��ʾС��Ҫ�ߵ����յ�,'.'��ʾ�յؿ�����,
��X����ʾǽ������,��1������9������ǰ��ըҩ������,������������һ������1����,�ߵ�
����ըҩ�ĵط�����һ���Խ�ըҩȫ������,������⻨��ʱ��,ըһ��ǽ��໨1����,
��С����S�ߵ�D������Ҫ����ʱ��.
2<=n,m<=8.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2128
˼·:bfs.ֻ��Ҫע���ߵ�ÿ�����ӿ���������������ϵ�ըҩʹ��������ӱ�Ϊ
�����Ŀյ�,�������ǰ���״̬��������ʱ����ط����ǿյ�û��ըҩ��,��Ϊ֮ǰ
�Ѿ��ù���,���Ƕ���֮ǰ������չ�ı��״̬�õ��Ծ�����ըҩ��.�Լ��ߵ�'X'ǽ��
����һ��ըҩ�໨��1���ӽ�������ʹ���ɿյؿ�������ͨ��,��֮���ٻص�����ط�ʱ,
���Ѿ��ǿյ���,��������bfs��ӵ�״̬�ٻص��õ�ʱ,��������ըҩ�Ϳ���ֱ��ͨ�����յ�,
��������ÿ��״̬��Ӧ�ĵ�ǰ���Թ��ĸ���״̬�ǲ�ͬ��.�����Ҫ��mp[N][N]����bfsҪ��չ��
ת̬State��.��Ϊ����'X'��Ҫ����2s���ܵ���õ�,�������յ�ֻ�軨��1s,��˶��в������
��չͬ�׶ε�״̬���ڲ�ͬ���򡢷���,���ѵ�ʱ�䲢��һ��,�п�������ӵ�������ȫ��'X',ʵ��
����ʱ��ϳ�,������ӵ�һֱ���߿յ�'.',���Ҫ�����ȶ���priority_queue ����ÿ��״̬����ʱ
���ٵ��ȳ���.

ע��:
�������Թ���λ��(x,y) �������ظ���������bfs�ظ������ͬ��״̬����MLE.
����ʵ�ʶ���ÿ��λ���ظ�����ʱ,����Я����ըҩ��������ͬ,���������水��
��ǰЯ��ը��������λ��(x,y)֮ǰ����ʱЯ��ը�����������ж��Ƿ���������չ״̬,
��Ϊÿ��״̬�Ķ�Ӧ���Թ�״̬�ǲ�ͬ��,��Ҫ�ߵ�'D'ʵ��Ҫը�ٵ�ǽ'X'����ĿҲ�ǲ�ͬ
��,��ʹ��ǰЯ����ըҩ������,����ʵ�ʵ�ǰ״̬��Ӧ���Թ�����'D'�ص�ǽ'X'Ҳ��,ʵ��
���ѵ�ʱ����ܽ���,��֮ǰ״̬��ȻЯ����ըҩ��,��֮ǰ״̬��Ӧ���Թ��е�ǽ'X'Ҳ�϶�,
�п���ըҩ������ը��������Ҫͨ����'X',���²��ܵ���'D'��,���߿�����Ҫը�ٵ�'X'ǽ�϶�,
ʵ�ʵ���'D'����Ҫ���ѵ�ʱ��Ҳ�϶�.
��˶����Թ���ÿ����(x,y)��״̬ �����ܵ��������Я��ըҩ���ж��ظ��߹��ľͲ�������,
���Ƕ����ظ�λ�õ�״̬Ҳ���������չ״̬,ֻ��Ϊ�˱���bfs MLE,Ҫ����ÿ��λ�� Я����ըҩ��
��״̬�������ӵĴ���������,����HDU�����ݽ���,ʵ������Ϊ5,��:vis[x][y][tp.num]<=5����,
��Ӱ��ʵ�ʽ��,Ϊ�˱���Ҳ�������õؽϴ�һ�� 50��100������.
*/
/*
//��������
input
6 5
S.XX1
X.1X1
XX.X.
XXXXX
XXXXX
XXXDX
2 6
S.1XXD
1..XXX
4 4
S1X1
XXXX
XXDX
XXXX
6 2
S1
..
1X
XX
XX
DX

output
17
9
8
9
*/
//ac 0ms bfs
//ʱ�临�Ӷ�>=N*N*M=64*576=36864
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
#define M 600
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},vis[N][N][M];
struct State{
    int x,y,s,num;
    char mp[N][N];
    bool operator < (const State &x)const{
        return s>x.s;//��Ϊ�ߵ�'X'���ߵ�'.'����ʱ�䲻ͬ �������ȶ��� ����ʱ�����ٳ���
    }
};

int bfs(State node){
    priority_queue<State> Q;
    vis[node.x][node.y][node.num]++;
    Q.push(node);
    State tp,next;
    while(!Q.empty()){
        tp=Q.top();
        Q.pop();
        for(int i=0;i<4;i++){
            next.x=tp.x+dir[i][0];
            next.y=tp.y+dir[i][1];
            //(x,y)Я��ը����num vis[x][y][num]����Ӵ������ܳ���5��,Ϊ�˽���bfs�ظ�״̬��ӵĴ���
            //ʵ��ÿ���� Я��ը������ʹ��ͬ��ͬ״̬����Ӧ���Թ�״̬��'X'����ĿҲ�ǲ�ͬ��,��˲��ܼ򵥶�(x,y)Я����ը������������
            //���Ǿ������������ �����������Ӵ��� �������øߵ� 50��100��.
            if(next.x<1 || next.x>n || next.y<1 || next.y>m || vis[next.x][next.y][tp.num]>5)
                continue;
            if(tp.mp[next.x][next.y] == '.'){
                next.num=tp.num;
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+1;
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y]>='1' && tp.mp[next.x][next.y]<='9'){
                next.num=tp.num+tp.mp[next.x][next.y]-'0';//ʵ�����ӵ�ըҩ��Ϊtp.mp[next.x][next.y]-'0'
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+1;
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                next.mp[next.x][next.y]='.';//ȡ��ըҩ�� �ͻ���'.'
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y] == 'X' && tp.num>=1){//Ҫը��'X' ������Ҫһ��ըҩ
                next.num=tp.num-1;
                vis[next.x][next.y][next.num]++;
                next.s=tp.s+2;//������Ҫ1s,�ߵ�'X'����Ҫ1s ��2s
                memcpy(next.mp,tp.mp,sizeof(tp.mp));
                next.mp[next.x][next.y]='.';//��ը֮�� 'X'�ͻ���'.'
                Q.push(next);
            }
            else if(tp.mp[next.x][next.y] == 'D')//����'D'�� �軨��tp.s+1
                return tp.s+1;
        }
    }
    return -1;
}

int main(){
    State node;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&node.mp[i][j]);
                if(node.mp[i][j] == 'S'){
                    node.x=i;
                    node.y=j;
                    node.num=0;
                    node.s=0;
                    node.mp[i][j]='.';//����һ��Ҫ'S'��ʼλ������Ϊ'.',��Ϊ'S'������ٴ��߹�ʱЯ����ը����Ŀ��ͬ
                }
            }
        }
        printf("%d\n",bfs(node));
    }
    return 0;
}

/*
//ac 15ms IDA* �����پ����֦+ը�����Я����Ŀ��֦
//dp[x][y]��ʾ(x,y)��֮ǰ�߹�״̬��Я��������ը����Ŀ
//���������ʵҲ���е������,dp[x][y]��¼��ը����Ŀֻ�ܸ����ʱ��Ż���չ,
//��ʵ��Я��ը����Ŀ��ͬʱ,�����״̬Ҳ��ͬ��,ǽ����ĿҲ�ǲ�ͬ��,ֻ��˵���ݽ�ˮ.
//����Ӧ��ֻ��IDA*+�����پ����֦,ֻ��һ����֦,��������������Ӷ�̫��,��TLE.
//�ο�����:https://blog.csdn.net/Force_CHL/article/details/76855997
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 600
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},dp[N][N],ex,ey,flag;
char mp[N][N];

//sΪ�ߵ���ǰ(x,y)���ѵ�ʱ�� totΪ�����'S'�����յ�'D' �涨Ҫ���ѵ�ʱ��
int dfs(int x,int y,int num,int s,int tot){
    //��֦1:�����ǰ���߷��� Я����ը����Ŀ���ܱ�֮ǰ���� �ͷ���
    if(dp[x][y]>=num)
        return 0;
    dp[x][y]=num;
    if(s == tot)
        return mp[x][y] == 'D';
    if(s>tot)//ע����Ϊ ը��ǽҪ2s,�����п���ʱ���պ�����tot,��ͻᵼ�� ����D״̬ �������¼ը����Ŀ,���º����С�� ʱ�� �ᱻ�����֦,�𰸴���
        return 0;
    //��֦2:�����پ����֦ �����ǰλ�ò����Ǻ���·����'X'�������·��ֱ�����ߵ�'D'�㻹��Ҫ���ѵ�ʱ���Ѿ������涨��ʱ��tot-s �ͷ���
    //(ex,ey)Ϊ'D'������
    //if(s+abs(ex-x)+abs(ey-y)>tot)//������������ټ�֦ Ҳ��15ms ac
    	//return 0;
    int nx,ny,q;
    char tp;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        tp=mp[nx][ny];
        if(nx<1 || nx>n || ny<1 || ny>m)
            continue;
        if(mp[nx][ny] == '.' || mp[nx][ny] == 'D' || mp[nx][ny] == 'S'){
            q=dp[nx][ny];
            if(dfs(nx,ny,num,s+1,tot))
                return 1;
            dp[nx][ny]=q;//���ݺ�dpֵҪ���¸�ֵ
        }
        else if(mp[nx][ny]>='1' && mp[nx][ny]<='9'){
            int p=mp[nx][ny]-'0';
            mp[nx][ny]='.';
            q=dp[nx][ny];
            if(dfs(nx,ny,num+p,s+1,tot))
                return 1;
            dp[nx][ny]=q;
            mp[nx][ny]=tp;
        }
        else if(mp[nx][ny] == 'X' && num>=1){
            mp[nx][ny]='.';
            q=dp[nx][ny];
            if(dfs(nx,ny,num-1,s+2,tot))
                return 1;
            dp[nx][ny]=q;
            mp[nx][ny]=tp;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S'){
                    sx=i;
                    sy=j;
                    mp[i][j]='.';//����һ��Ҫ'S'��ʼλ������Ϊ'.',��Ϊ'S'���ٴ��߹�ʱЯ����ը����Ŀ��ͬ
                }
                else if(mp[i][j] == 'D'){
                    ex=i;
                    ey=j;
                }
            }
        }
        //���������������,ö��������'S'��������'D'����໨�ѵ�ʱ��i
        //���ݵ�ǰλ��(x,y)����'D'���ʣ��ʱ����м�֦ ��������涨ʱ��i �򷵻�
        for(int i=1;i<=40;i++){//�����Ͻ������ȡ��,ʵ��Ӧ������ȡ�Ĵ�һЩ,��Ҫ������������������i����
            flag=0;
            memset(dp,-1,sizeof(dp));
            if(dfs(sx,sy,0,0,i)){//��Ϊi����,��һ������������i�������ʱ��
                flag=1;
                printf("%d\n",i);
                break;
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0;
}
*/

/*
//TLE IDA*+�����پ����֦
//�������������ϵ�����,����Ϊֻ�Ǹ���ÿ�ε����ȥ��֦,û�в���λ�õı������,�����ظ��ı��� ���ɱ���.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 600
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ex,ey,flag;
char mp[N][N];

//sΪ�ߵ���ǰ(x,y)���ѵ�ʱ�� totΪ�����'S'�����յ�'D' �涨Ҫ���ѵ�ʱ��
int dfs(int x,int y,int num,int s,int tot){
    //��֦2:�����پ����֦ �����ǰλ�ò����Ǻ���·����'X'�������·��ֱ�����ߵ�'D'�㻹��Ҫ���ѵ�ʱ���Ѿ������涨��ʱ��tot-s �ͷ���
    //(ex,ey)Ϊ'D'������
    if(s == tot)
        return mp[x][y] == 'D';
    if(s+abs(ex-x)+abs(ey-y)>tot)
        return 0;
    if(s>tot)
        return 0;
    int nx,ny;
    char tp;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        tp=mp[nx][ny];
        if(nx<1 || nx>n || ny<1 || ny>m)
            continue;
        if(mp[nx][ny] == '.' || mp[nx][ny] == 'D' || mp[nx][ny] == 'S'){
            if(dfs(nx,ny,num,s+1,tot))
                return 1;
        }
        else if(mp[nx][ny]>='1' && mp[nx][ny]<='9'){
            int p=mp[nx][ny]-'0';
            mp[nx][ny]='.';
            if(dfs(nx,ny,num+p,s+1,tot))
                return 1;
            mp[nx][ny]=tp;
        }
        else if(mp[nx][ny] == 'X' && num>=1){
            mp[nx][ny]='.';
            if(dfs(nx,ny,num-1,s+2,tot))
                return 1;
            mp[nx][ny]=tp;
        }
    }
    return 0;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S'){
                    sx=i;
                    sy=j;
                    mp[i][j]='.';//����һ��Ҫ'S'��ʼλ������Ϊ'.',��Ϊ'S'���ٴ��߹�ʱЯ����ը����Ŀ��ͬ
                }
                else if(mp[i][j] == 'D'){
                    ex=i;
                    ey=j;
                }
            }
        }
        //���������������,ö��������'S'��������'D'����໨�ѵ�ʱ��i
        //���ݵ�ǰλ��(x,y)����'D'���ʣ��ʱ����м�֦ ��������涨ʱ��i �򷵻�
        for(int i=1;i<=40;i++){//�����Ͻ������ȡ��,ʵ��Ӧ������ȡ�Ĵ�һЩ,��Ҫ������������������i����
            flag=0;
            if(dfs(sx,sy,0,0,i)){//��Ϊi����,��һ������������i�������ʱ��
                flag=1;
                printf("%d\n",i);
                break;
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0;
}
*/

/*
//ac 1887ms ��׼���� �жϵ�ͼ(x,y)��ͬըҩ����ʱ ��ͼ״̬�Ĳ�ͬ
//���� vector<State>vist[8][8][560]; //�ߵ���ͼÿ��λ�õõ���ͬըҩ�����ĵ�ͼ״̬��û�д��ڹ�
//��S��D����������ÿ��λ�õõ���ըҩ�������ܲ��ȣ�����õ���ըҩ������ȣ�
//��ÿ�����ﵱǰλ��ʱ�ĵ�ͼ��״̬��ͬ���������ǲ��������ж���ÿ��λ�õõ���ըҩ���Ƿ���ڹ���
//���һ�Ҫ�жϵõ�����Щըҩ������ͬ����²�ͬ��ͼ��״̬��
#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;

struct State
{
    short state[8];//��ͼÿ��ѹ����״̬��
};
struct node
{
    int x,y; //��ǰ�ߵ���λ��
    int time,explosiveNumb; //�߹���ʱ�䣬�õ���ըҩ����
    State s;  //�߹���ĵ�ͼ״̬
    friend bool operator<(const node &a,const node &b) //���ȶ�����ʱ����С��˳��ȡ
    {
        return a.time>b.time;
    }
};

int n,m;
char map[10][10];
vector<State>vist[8][8][560]; //�ߵ���ͼÿ��λ�õõ���ͬըҩ�����ĵ�ͼ״̬��û�д��ڹ�

void init()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        for(int k=0; k<559; k++)
        vist[i][j][k].clear();
}
bool judge(int x,int y,int numb,short state[])
{
    int length=vist[x][y][numb].size();
    for(int i = 0; i < length ;i++)
    {
        int j;
        for(j = 0; j<n ; j++)
            if(vist[x][y][numb][i].state[j]!=state[j])
            break;
        if(j==n) //��ǰ��Ҫ�ߵ�state[]��ͼ״̬�������ټ�����У����������ڹ���
            return false;
    }
    //��ǰ��Ҫ�ߵĵ�ͼ״̬û���ڹ�����������
    return true;
}
int bfs(int sx,int sy)
{
    int dir[4][2]={0,1,0,-1,1,0,-1,0};
    priority_queue<node>q;
    node p,tp;

    init();
    p.x=sx;
    p.y=sy;
    p.time=0;
    p.explosiveNumb=0;
    for(int i=0;i<n;i++)
    {
        p.s.state[i]=0;
        //ѹ��ÿ�е�ͼ��״̬��λ���� 1 ��ʾ�������κζ���
        for(int j=0;j<m;j++)
            if(map[i][j]=='.')
        p.s.state[i]|=(1<<j);
    }

    vist[sx][sy][0].push_back(p.s);
    q.push(p);
    while(!q.empty())
    {
        p=q.top();
        q.pop();
        for(int e=0;e<4;e++)
        {
            tp=p;
            tp.x+=dir[e][0];
            tp.y+=dir[e][1];
            tp.time++;
            if(tp.x>=0&&tp.x<n&&tp.y>=0&&tp.y<m)
            {
                if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]=='X'&&!tp.explosiveNumb) //��ʾ��Ҫ�ߵ�λ�������ڻ�ûը��ǽ����������û��ըҩ
                    continue ;
                if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]>'0'&&map[tp.x][tp.y]<='9') //��ʾ��Ҫ�ߵ�λ����û��ȡ�ߵ�ըҩ
                {
                    tp.explosiveNumb+=map[tp.x][tp.y]-'0';
                    tp.s.state[tp.x]|=1<<tp.y; //ȡ�ߺ��� "."
                }
                else if(!(tp.s.state[tp.x]&(1<<tp.y))&&map[tp.x][tp.y]=='X'&&tp.explosiveNumb)  //��ʾ��Ҫ�ߵ�λ�������ڻ�ûը��ǽ��������ըҩ
                {
                    tp.explosiveNumb--;
                    tp.s.state[tp.x]|=1<<tp.y; //ը����� "."
                    tp.time++;
                }
                else if(map[tp.x][tp.y]=='D')
                    return tp.time;
                if(judge(tp.x,tp.y,tp.explosiveNumb,tp.s.state)) //�ж��ߵ���ǰλ�õ�ըҩ�������ͼ״̬�Ƿ�û�д��ڹ���Ϊ��û���ڹ�������Ϊ���ڹ�
                vist[tp.x][tp.y][tp.explosiveNumb].push_back(tp.s),q.push(tp);
            }
        }
    }
    return -1;
}
int main()
{
    int sx,sy;
    while(scanf("%d%d",&n,&m)>0)
    {
        if(n==0&&m==0)
            break;
        for(int i=0;i<n;i++)
            scanf("%s",map[i]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            if(map[i][j]=='S')
            sx=i,sy=j;
        printf("%d\n",bfs(sx,sy));
    }
}
*/
