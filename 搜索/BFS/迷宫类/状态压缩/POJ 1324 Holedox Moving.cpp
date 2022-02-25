/*
//����ժ������
//���ɲο���ƪ����:
https://blog.csdn.net/qq_33279781/article/details/61237682
https://www.cnblogs.com/kedebug/archive/2013/03/26/2983143.html
http://www.voidcn.com/article/p-mdlqpdlw-dy.html
http://blog.sina.com.cn/s/blog_a16dd6d10101585j.html
����:��n*m�ĵ�ͼ��,��������ΪL�������������λ��,�Լ���k������ǽ,
���ߴӳ�ʼλ���ߵ�(1,1)�����С����.�߲���ײǽ,����ײ�Լ�������.
1<=n,m<=20.1<=L<=8.
ע��:�ߵ�(1,1)����ָ��ͷ����(1,1)��,��������β���뿪(1,1)��.
����:http://poj.org/problem?id=1324
˼·:˼·ժ�Բ���:https://blog.csdn.net/qq_33279781/article/details/61237682
���������bfs�����Ҫ��¼ÿ��״̬�Ƿ��Ѿ����ʹ����ڻ�������ͨ��ֻ��һ���㣬
����һ��vis[x][y]=true��ok�ˡ��������У�����Ҫ������������ĳһλ�ÿ���һ��״̬��
Ҫ���L���ȵ����壬��Ҫ�Ŀռ�ܴ󣬽���400^8;���ǰ���ͷ������ȡ��������Ϊvis�����ǰ��ά��
����ά�����ǽ��ߵ�����ѹ����һ�������У��ߵ������ÿһ�ڣ������ǰ��һ�ڵ�λ�ã�ֻ��4�ֿ��ܣ�
��ǰ������4�ֿ��ܣ������Ϊ7����ô����������2����λ��ʾÿһ���������ǰһ�ڵ�λ�ã�
Ȼ��������λ��֮���ظ���������������ôѹ����ռ�õĿռ�Ϊ2^14=16384��
*/
//��stl��queue���ܻ�TLE,��������TLE��,���ϱ��stl queue���� ����Ҳ��4900ms+ ��պ�5000ms
//��д���п��Ż�����ʱ��O2 ���� �ɴ�1800ms,�����ں�������
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct snake{
    int x[8],y[8];
    int cnt;
}body;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//˳ʱ�뷽�� �������·ֱ��Ӧ�����±�0,1,2,3
char map[25][25];
//visǰ��ά��ʾ��ͷ��λ�ã���һά�еĶ�������ÿ��λ��ʾ�����������
//ǰһ������ķ�������0,1,2,3�ĸ�����ʾ�ĸ����������Ϳ��԰��ߵ�
//״̬��ʶ�����ˡ�
bool visit[25][25][1<<14],n,m,l;

bool judgeGo(int x,int y){
    if(x<1||x>n||y<1||y>m||map[x][y]=='1')
        return false;
    for(int i=1;i<l;i++){//�ж������Ƿ����ͷ�γ��ϰ�
        if(x==body.x[i]&&y==body.y[i])
            return false;
    }
    return true;
}

//�жϺ�һ������(x2,y2)�����ǰһ������(x1,y1) �����ĸ�����
//��4�ֿ��ܷ��� �����Ҫ��2λ������λ��1 ��˺������λҪ�ƶ�2λ
int judgeDir(int x1,int y1,int x2,int y2){
    if(x1==x2&&y1-y2==1) return 0;//���ǰһ�������������
    if(x1-x2==1&&y1==y2) return 1;//�ϲ�
    if(x1==x2&&y1-y2==-1) return 2;//�Ҳ�
    if(x1-x2==-1&&y1==y2) return 3;//�²�
}
int bfs(){
    queue<snake> Q;
    snake btmp;
    Q.push(body);
    int state,dir0;
    while(!Q.empty()){
        body=Q.front();
        Q.pop();
        //��ͷ����(1,1)��
        if(btmp.x[0]==1&&btmp.y[0]==1) return btmp.cnt;
        for(int i=0;i<4;i++){
            state=0;
            btmp=body;
            //�ƶ���ͷ
            int xx=btmp.x[0]+dir[i][0];
            int yy=btmp.y[0]+dir[i][1];
            //�ж��ƶ���ͷ�Ƿ�ᴥ����ǽ��ǰ״̬������
            if(judgeGo(xx,yy)){
                //����ͷ֮�������������ǰһ��λ�������ƶ�
                for(int j=l-1;j>=1;j--){
                    btmp.x[j]=btmp.x[j-1];
                    btmp.y[j]=btmp.y[j-1];
                }
                //����ͷ λ��Ϊ(xx,yy)
                btmp.x[0]=xx,btmp.y[0]=yy;
                //���̰�����µ�״̬ ����ͷ(xx,yy) �����������һ����λ�� ������״̬ѹ��
                for(int k=0;k<l-1;k++){
                    dir0=judgeDir(btmp.x[k],btmp.y[k],btmp.x[k+1],btmp.y[k+1]);//�ж������ÿһ�����������һ�ڵ����λ��
                    state|=dir0;//�����䷽��״̬
                    state<<=2;//ÿ������ռ��2��������λ,�������2λ
                }
                if(!visit[xx][yy][state]){//�ж��������״̬֮ǰ�Ƿ��й���չ
                    btmp.cnt++;
                    Q.push(btmp);
                    visit[xx][yy][state]=true;
                }
            }
        }
    }
    return -1;
}

int main(){
    int k,x,y,state,dir0,cnt=1;//cntΪ������
    while(scanf("%d%d%d",&n,&m,&l)&&n&&m&&l){//������Ϊl
        state=0;
        memset(map,'0',sizeof(map));
        memset(visit,false,sizeof(visit));
        body.cnt=0;
        for(int i=0;i<l;i++)
            scanf("%d%d",&body.x[i],&body.y[i]);
        //̰���߳�ʼ״̬
        for(int i=0;i<l-1;i++){
            dir0=judgeDir(body.x[i],body.y[i],body.x[i+1],body.y[i+1]);
            state|=dir0;
            state<<=2;
        }
        visit[body.x[0]][body.y[0]][state]=true;
        scanf("%d",&k);//k��ǽ
        for(int i=0;i<k;i++){
            scanf("%d%d",&x,&y);
            map[x][y]='1';//1����ǽ ������
        }
        printf("Case %d: %d\n",cnt++,bfs());

    }
    return 0;
}

/*
//ac 1875ms ��дʵ�ֶ���queue
//ժ�Բ���:http://www.voidcn.com/article/p-mdlqpdlw-dy.html
#include<stdio.h>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
struct node
{
	int x,y;
};
struct snake_locat
{
	int dis;
	int body[8][2];
}w,v,q[5000004];
int n,m,l;
node add[4];
bool a[21][21];
bool b[21][21][17000];
bool check(node &nn,snake_locat &t)
{
	if(nn.x>=1&&nn.x<=n&&nn.y>=1&&nn.y<=m&&a[nn.x][nn.y]==0)
	{
		for(int i=0;i<l;i++)
		{
			if(nn.x==t.body[i][0]&&nn.y==t.body[i][1])
				return 0;
		}
		return 1;
	}
		return 0;
}
int position(int &nx,int &ny,int &px,int &py)
{
	if(nx==px)
	{
		if(ny>py)
			return 0;
		else
			return 1;
	}
	else
	{
		if(nx>px)
			return 2;
		else
			return 3;
	}
}
int get_position(snake_locat& now)//�������ߵ����λ��ת��Ϊһ��4������
{
	int s=0,i;
	for(i=0;i<l-1;i++)
		s=s*4+position(now.body[i][0],now.body[i][1],now.body[i+1][0],now.body[i+1][1]);
	return s;
}
int bfs(void)
{
	if(w.body[0][0]==1&&w.body[0][1]==1)
		return 0;
	int i,j,head,tair;
	head=tair=0;
	w.dis=0;
	q[tair]=w;
	tair++;
	int sta;
	sta=get_position(w);
	b[w.body[0][0]][w.body[0][1]][sta]=1;
	while(head<tair)
	{
		w=q[head++];
		for(i=0;i<4;i++)
		{
			node nn;
			nn.x=w.body[0][0]+add[i].x;
			nn.y=w.body[0][1]+add[i].y;
			if(nn.x==1&&nn.y==1)
			return w.dis+1;
			if(check(nn,w))
			{
				v.dis=w.dis+1;
				v.body[0][0]=nn.x;
				v.body[0][1]=nn.y;
				for(j=l-1;j>0;j--)
				{
					v.body[j][0]=w.body[j-1][0];
					v.body[j][1]=w.body[j-1][1];
				}
				int ck;
				ck=get_position(v);
				if(b[nn.x][nn.y][ck]==0)
				{
					q[tair++]=v;
					b[nn.x][nn.y][ck]=1;
				}
			}
		}
	}
	return -1;
}
int main()
{
	int i,ca=0;
	add[0].x=1;add[0].y=0;
	add[1].x=0;add[1].y=1;
	add[2].x=-1;add[2].y=0;
	add[3].x=0;add[3].y=-1;
	while(scanf("%d%d%d",&n,&m,&l)&&n&&m&&l)
	{
		ca++;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(i=0;i<l;i++)
		{
			scanf("%d%d",&w.body[i][0],&w.body[i][1]);
		}
		int block;
		scanf("%d",&block);
		for(i=0;i<block;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			a[x][y]=1;
		}
		int sum;
		sum=bfs();
		printf("Case %d: %d\n",ca,sum);
	}
	return 0;
}
*/

/*
//ac 4735ms ʹ��stl �е�queue
//ժ�Բ���:https://blog.csdn.net/qq_33279781/article/details/61237682
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
const int MAXN = 20+2;
int n, m, l;
bool tu[MAXN][MAXN];
bool vis[MAXN][MAXN][1<<14];

struct Tuple
{
	int x, y;
};

struct Node
{
	int step;
	Tuple snake[8];
};

Node st;

inline bool judge(int x, int y, int z){
	return (0<=x&&x<n && 0<=y&&y<m && !tu[x][y] && !vis[x][y][z]);
}

int getDirect(int x, int y, int tx, int ty){
	if(x==tx){
		if(y==ty-1) return 0;  //up
		else return 1;         //down
	}
	else{
		if(x-1==tx) return 2;  //left
		else return 3;         //right
	}
}

int cal(Node &t){
	int ret = 0;
	for(int i=1; i<l; ++i){
		ret = (ret<<2) + getDirect(t.snake[i-1].x, t.snake[i-1].y, t.snake[i].x, t.snake[i].y);
	}
	return ret;
}

void SnakeMove(Node &now, Node &pre){
	for(int i=1; i<l; ++i){
		now.snake[i].x = pre.snake[i-1].x;
		now.snake[i].y = pre.snake[i-1].y;
	}
	++now.step;
}

bool judgeBody(Node &now){
	for(int i=1; i<l; ++i){
		if(now.snake[i].x==now.snake[0].x && now.snake[i].y==now.snake[0].y)
			return true;
	}
	return false;
}

int bfs(){
	queue<Node> q;
	st.step = 0;
	q.push(st);
	vis[st.snake[0].x][st.snake[0].y][cal(st)] = true;
	while(!q.empty()){
		Node temp = q.front(); q.pop();
		for(int i=0; i<4; ++i){
			Node now = temp;
			now.snake[0].x += dx[i];
			now.snake[0].y += dy[i];
			int x = now.snake[0].x;
			int y = now.snake[0].y;
			if(x<0||y<0||x>=n||y>=m||tu[x][y]) continue;  //�ж���ͷ�Ƿ��ڱ߽����Լ��Ƿ�Ϊʯͷ

			if(x==now.snake[l-1].x&&y==now.snake[l-1].y) continue; //�������������ͷ׷β
			SnakeMove(now, temp);                  //move and step+1
			if(judgeBody(now)) continue;           //�ж���ͷ�Ƿ��������ײ

			int z = cal(now);
			if(vis[x][y][z]) continue;            //�ж��Ƿ���ʹ�
			if(x==0&&y==0) return now.step;
			q.push(now);
			vis[x][y][z] = true;
		}
	}
	return -1;
}

int main(){
	int x, y, cas=0;
	while(scanf("%d%d%d", &n, &m, &l)!=EOF){
		if(n==0&&m==0&&l==0) break;
		memset(tu, 0, sizeof(tu));
		memset(vis, 0, sizeof(vis));
		for(int i=0; i<l; ++i){
			scanf("%d%d", &x, &y);
			st.snake[i].x = x-1;
			st.snake[i].y = y-1;
		}
		int stone;
		scanf("%d", &stone);
		for(int i=0; i<stone; ++i){
			scanf("%d%d", &x, &y);
			tu[x-1][y-1] = true;
		}
		if(st.snake[0].x==0 && st.snake[0].y==0)
            printf("Case %d: %d\n", ++cas, 0);
        else
            printf("Case %d: %d\n", ++cas, bfs());
	}
	return 0;
}
*/

/*
//ac 266ms A*����ʽ����+�Ͻ��֦
//ժ�Բ���:https://www.cnblogs.com/kedebug/archive/2013/03/26/2983143.html
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

bool vis[21][21][1<<14];
bool stone[21][21];
int row, col, L, K;

const int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

struct Body {
    int x, y;
} body[10];

struct ST {
    int x, y, step, state, f;
    ST(int _x, int _y, int _step, int _state, int _f)
        : x(_x), y(_y), step(_step), state(_state), f(_f) {}
    bool operator < (const ST& other) const { return f > other.f; }
};

void setstone() {
    for (int i = 1; i < L; i++)
        stone[body[i].x][body[i].y] = true;
}

void clearstone() {
    for (int i = 1; i < L; i++)
        stone[body[i].x][body[i].y] = false;
}

int getstate(int x, int y) {
    int state = 0;
    for (int i = 1; i < L; i++) {
        state <<= 2;
        if (body[i].x > body[i-1].x)        // up
            state |= 0;
        else if (body[i].x < body[i-1].x)   // down
            state |= 1;
        else if (body[i].y > body[i-1].y)   // left
            state |= 2;
        else if (body[i].y < body[i-1].y)   // right
            state |= 3;
    }
    return state;
}

void setbody(int x, int y, int state) {
    const int MASK = 3;
    body[0].x = x, body[0].y = y;
    for (int i = 1; i < L; i++) {
        int val = (state >> ((L-i-1)*2)) & MASK;
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
        if (val == 0) body[i].x += 1;
        else if (val == 1) body[i].x -= 1;
        else if (val == 2) body[i].y += 1;
        else if (val == 3) body[i].y -= 1;
    }
}

bool judge(int x, int y) {
    if (0 < x && x <= row && 0 < y && y <= col && !stone[x][y]) {
        return true;
    }
    return false;
}

inline int getdiff(int x, int y) {
    return abs(x - 1) + abs(y - 1);
}

int astar() {
    priority_queue<ST> Q;
    int x = body[0].x, y = body[0].y;
    int state = getstate(x, y);
    int f = getdiff(x, y);
    Q.push(ST(x, y, 0, state, f));
    vis[x][y][state] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        if (u.x == 1 && u.y == 1)
            return u.step;

        setbody(u.x, u.y, u.state);
        setstone();
        for (int i = 0; i < 4; i++) {
            x = u.x + dir[i][0];
            y = u.y + dir[i][1];
            state = (L<2) ? 0 : (u.state>>2) | (i<<((L-2)*2));
            if (judge(x, y) && !vis[x][y][state]) {
                vis[x][y][state] = true;
                f = u.step + 1 + getdiff(x, y);
                Q.push(ST(x, y, u.step + 1, state, f));
            }
        }
        clearstone();
    }
    return -1;
}

int bfs() {
    bool visit[21][21];
    memset(visit, false, sizeof(visit));
    priority_queue<ST> Q;
    int x = body[0].x, y = body[0].y;
    int f = getdiff(x, y);
    Q.push(ST(x, y, 0, 0, f));
    visit[x][y] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        if (u.x == 1 && u.y == 1)
            return u.step;

        for (int i = 0; i < 4; i++) {
            x = u.x + dir[i][0];
            y = u.y + dir[i][1];
            if (judge(x, y) && !visit[x][y]) {
                visit[x][y] = true;
                f = u.step + 1 + getdiff(x, y);
                Q.push(ST(x, y, u.step + 1, 0, f));
            }
        }
    }
    return -1;
}

int main() {
    int cases = 0;
    while (scanf("%d%d%d", &row, &col, &L) && row && col && L) {
        for (int i = 0; i < L; i++)
            scanf("%d%d", &body[i].x, &body[i].y);
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                stone[i][j] = false;
                memset(vis[i][j], false, sizeof(vis[0][0]));
            }
        }
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            stone[x][y] = true;
        }
        int ans;
        int minstep = bfs();
        setstone();
        int maxstep = bfs();
        clearstone();

        if (minstep == -1)
            ans = -1;
        else if (minstep == maxstep)
            ans = minstep;
        else
            ans = astar();

        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
*/
