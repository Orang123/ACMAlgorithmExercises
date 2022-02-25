/*
//题意摘自网上
//题解可参考几篇博客:
https://blog.csdn.net/qq_33279781/article/details/61237682
https://www.cnblogs.com/kedebug/archive/2013/03/26/2983143.html
http://www.voidcn.com/article/p-mdlqpdlw-dy.html
http://blog.sina.com.cn/s/blog_a16dd6d10101585j.html
题意:在n*m的地图上,给出长度为L的蛇身体各个节位置,以及有k个点是墙,
问蛇从初始位置走到(1,1)点的最小步数.蛇不能撞墙,不能撞自己的身体.
1<=n,m<=20.1<=L<=8.
注意:走到(1,1)点是指蛇头到达(1,1)点,而不是蛇尾刚离开(1,1)点.
链接:http://poj.org/problem?id=1324
思路:思路摘自博客:https://blog.csdn.net/qq_33279781/article/details/61237682
在最基本的bfs里，我们要记录每个状态是否已经访问过，在基础题里通常只是一个点，
设置一个vis[x][y]=true就ok了。在这题中，我们要把蛇身整体在某一位置看成一个状态，
要表达L长度的身体，需要的空间很大，将是400^8;我们把蛇头单独抽取出来，作为vis数组的前两维。
第三维，我们将蛇的身体压缩到一个数字中，蛇的身体的每一节，相对于前面一节的位置，只有4种可能，
即前后左右4种可能，蛇身最长为7，那么我们用两个2进制位表示每一节身体相对前一节的位置，
然后左移两位，之后重复操作整个蛇身。那么压缩后，占用的空间为2^14=16384。
*/
//用stl的queue可能会TLE,下面代码就TLE了,网上别的stl queue代码 基本也是4900ms+ 或刚好5000ms
//手写队列可优化常数时间O2 会快点 可达1800ms,代码在后面会给出
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct snake{
    int x[8],y[8];
    int cnt;
}body;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};//顺时针方向 左上右下分别对应数组下标0,1,2,3
char map[25][25];
//vis前两维表示蛇头的位置，后一维中的二进制中每两位表示蛇身体相对于
//前一节身体的方向，正好0,1,2,3四个数表示四个方向。这样就可以把蛇的
//状态标识出来了。
bool visit[25][25][1<<14],n,m,l;

bool judgeGo(int x,int y){
    if(x<1||x>n||y<1||y>m||map[x][y]=='1')
        return false;
    for(int i=1;i<l;i++){//判断蛇身是否对蛇头形成障碍
        if(x==body.x[i]&&y==body.y[i])
            return false;
    }
    return true;
}

//判断后一个蛇身(x2,y2)相对于前一个蛇身(x1,y1) 在其哪个方向
//有4种可能方向 因此需要用2位二进制位的1 因此后面的移位要移动2位
int judgeDir(int x1,int y1,int x2,int y2){
    if(x1==x2&&y1-y2==1) return 0;//相对前一个蛇身在其左侧
    if(x1-x2==1&&y1==y2) return 1;//上侧
    if(x1==x2&&y1-y2==-1) return 2;//右侧
    if(x1-x2==-1&&y1==y2) return 3;//下侧
}
int bfs(){
    queue<snake> Q;
    snake btmp;
    Q.push(body);
    int state,dir0;
    while(!Q.empty()){
        body=Q.front();
        Q.pop();
        //蛇头到达(1,1)点
        if(btmp.x[0]==1&&btmp.y[0]==1) return btmp.cnt;
        for(int i=0;i<4;i++){
            state=0;
            btmp=body;
            //移动蛇头
            int xx=btmp.x[0]+dir[i][0];
            int yy=btmp.y[0]+dir[i][1];
            //判断移动蛇头是否会触碰到墙或当前状态的蛇身
            if(judgeGo(xx,yy)){
                //将蛇头之后的蛇身向蛇身前一个位置依次移动
                for(int j=l-1;j>=1;j--){
                    btmp.x[j]=btmp.x[j-1];
                    btmp.y[j]=btmp.y[j-1];
                }
                //新蛇头 位置为(xx,yy)
                btmp.x[0]=xx,btmp.y[0]=yy;
                //标记贪吃蛇新的状态 新蛇头(xx,yy) 新蛇身相对上一个身位的 二进制状态压缩
                for(int k=0;k<l-1;k++){
                    dir0=judgeDir(btmp.x[k],btmp.y[k],btmp.x[k+1],btmp.y[k+1]);//判断蛇身的每一部分相对它上一节的相对位置
                    state|=dir0;//保存其方向状态
                    state<<=2;//每个蛇身占据2个二进制位,因此左移2位
                }
                if(!visit[xx][yy][state]){//判断这个蛇身状态之前是否有过扩展
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
    int k,x,y,state,dir0,cnt=1;//cnt为案例号
    while(scanf("%d%d%d",&n,&m,&l)&&n&&m&&l){//蛇身长度为l
        state=0;
        memset(map,'0',sizeof(map));
        memset(visit,false,sizeof(visit));
        body.cnt=0;
        for(int i=0;i<l;i++)
            scanf("%d%d",&body.x[i],&body.y[i]);
        //贪吃蛇初始状态
        for(int i=0;i<l-1;i++){
            dir0=judgeDir(body.x[i],body.y[i],body.x[i+1],body.y[i+1]);
            state|=dir0;
            state<<=2;
        }
        visit[body.x[0]][body.y[0]][state]=true;
        scanf("%d",&k);//k个墙
        for(int i=0;i<k;i++){
            scanf("%d%d",&x,&y);
            map[x][y]='1';//1代表墙 不能走
        }
        printf("Case %d: %d\n",cnt++,bfs());

    }
    return 0;
}

/*
//ac 1875ms 手写实现队列queue
//摘自博客:http://www.voidcn.com/article/p-mdlqpdlw-dy.html
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
int get_position(snake_locat& now)//把整条蛇的相对位置转化为一个4进制数
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
//ac 4735ms 使用stl 中的queue
//摘自博客:https://blog.csdn.net/qq_33279781/article/details/61237682
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
			if(x<0||y<0||x>=n||y>=m||tu[x][y]) continue;  //判断蛇头是否在边界内以及是否为石头

			if(x==now.snake[l-1].x&&y==now.snake[l-1].y) continue; //特殊情况不允许头追尾
			SnakeMove(now, temp);                  //move and step+1
			if(judgeBody(now)) continue;           //判断蛇头是否和身体相撞

			int z = cal(now);
			if(vis[x][y][z]) continue;            //判断是否访问过
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
//ac 266ms A*启发式搜索+上界剪枝
//摘自博客:https://www.cnblogs.com/kedebug/archive/2013/03/26/2983143.html
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
