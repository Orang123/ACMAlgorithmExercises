/*
题意:给定一个四位数,将它变成另外一个四位数
有2种操作:
1.给一个数字加1或者减1给9加1变成0,给1减1变成9.
2.将一个数字和其左右相邻的数字交换
每个操作是1步,求变成目标四位数字需要的最少步数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1195
思路:因为4位数字,所有状态最多为1111~9999之间的数.
bfs模拟状态转移即可.2个操作,+-1或交换相邻位.
*/
//ac 15ms bfs vis四维数组标记状态
//时间复杂度O(n*n*n*n)=10000 vis[10][10][10][10]
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

//vis[a][b][c][d]=0/1 表示abcd这样4位数字构成的数有没有扩展过
int ea,eb,ec,ed,vis[N][N][N][N];
struct State{
    int a,b,c,d,s;
    State(int a=0,int b=0,int c=0,int d=0,int s=0):a(a),b(b),c(c),d(d),s(s){}
};
queue<State> Q;

//数字加1减1
int plus_minus(int x,int val){
    if(x+val == 10)
        x=1;
    else if(x+val == 0)
        x=9;
    else
        x=x+val;
    return x;
}

//入队新的状态
void add(int na,int nb,int nc,int nd,int ns){
    if(!vis[na][nb][nc][nd]){
        vis[na][nb][nc][nd]=1;
        Q.push(State(na,nb,nc,nd,ns));
    }
}

int bfs(int sa,int sb,int sc,int sd){
    add(sa,sb,sc,sd,0);
    State tp;
    int na,nb,nc,nd;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.a == ea && tp.b == eb && tp.c == ec && tp.d == ed)
            break;
        Q.pop();
        //千位加1
        na=plus_minus(tp.a,1);
        add(na,tp.b,tp.c,tp.d,tp.s+1);
        //千位减1
        na=plus_minus(tp.a,-1);
        add(na,tp.b,tp.c,tp.d,tp.s+1);

        //白位加1
        nb=plus_minus(tp.b,1);
        add(tp.a,nb,tp.c,tp.d,tp.s+1);
        //白位减1
        nb=plus_minus(tp.b,-1);
        add(tp.a,nb,tp.c,tp.d,tp.s+1);

        //十位加1
        nc=plus_minus(tp.c,1);
        add(tp.a,tp.b,nc,tp.d,tp.s+1);
        //十位减1
        nc=plus_minus(tp.c,-1);
        add(tp.a,tp.b,nc,tp.d,tp.s+1);

        //个位加1
        nd=plus_minus(tp.d,1);
        add(tp.a,tp.b,tp.c,nd,tp.s+1);
        //个位减1
        nd=plus_minus(tp.d,-1);
        add(tp.a,tp.b,tp.c,nd,tp.s+1);

        //交换千位和百位
        na=tp.b;nb=tp.a;
        add(na,nb,tp.c,tp.d,tp.s+1);

        //交换百位和十位
        nb=tp.c;nc=tp.b;
        add(tp.a,nb,nc,tp.d,tp.s+1);

         //交换十位和个位
        nc=tp.d;nd=tp.c;
        add(tp.a,tp.b,nc,nd,tp.s+1);
    }
    return tp.s;
}

//将输入的起始和目标四位十进制数 分解出各个位上的数字
//a千位 b百位 c十位 d个位
void cal(int x,int &a,int &b,int &c,int &d){
    d=x%10;
    x/=10;
    c=x%10;
    x/=10;
    b=x%10;
    x/=10;
    a=x%10;
    x/=10;
}

int main(){
    int T,s,e,sa,sb,sc,sd;
    scanf("%d",&T);
    while(T--){
        while(!Q.empty()) Q.pop();
        memset(vis,0,sizeof(vis));
        scanf("%d",&s);//输入是一个4位的十进制数
        scanf("%d",&e);
        cal(s,sa,sb,sc,sd);
        cal(e,ea,eb,ec,ed);
        printf("%d\n",bfs(sa,sb,sc,sd));
    }
    return 0;
}

/*
//ac 62ms bfs vis一维数组标记vis[10000]
//时间复杂度O(n)=10000 vis[10000]
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 10000
using namespace std;

//vis[val]=0/1表示实际4位数代表的十进制数值val 有没有扩展过
int ed,vis[N];
struct State{
    int digit[5],s;
};

int bfs(int sa,int sb,int sc,int sd){
    queue<State> Q;
    State tp,next;
    vis[sa*1000+sb*100+sc*10+sd]=1;
    next.digit[1]=sa;next.digit[2]=sb;next.digit[3]=sc;next.digit[4]=sd;
    next.s=0;
    Q.push(next);
    while(!Q.empty()){
        tp=Q.front();
        if(tp.digit[1]*1000+tp.digit[2]*100+tp.digit[3]*10+tp.digit[4] == ed)
            break;
        Q.pop();
        //各个位数字加1 扩展状态
        for(int i=1;i<=4;i++){
            next=tp;
            next.digit[i]++;
            next.s++;
            if(next.digit[i] == 10)
                next.digit[i]=1;
            //val实际表示的4位 十进制数值
            int val=next.digit[1]*1000+next.digit[2]*100+next.digit[3]*10+next.digit[4];
            if(!vis[val]){
                vis[val]=1;
                Q.push(next);
            }
        }

		//各个位数字减1 扩展状态
        for(int i=1;i<=4;i++){
            next=tp;
            next.digit[i]--;
            next.s++;
            if(next.digit[i] == 0)
                next.digit[i]=9;
            int val=next.digit[1]*1000+next.digit[2]*100+next.digit[3]*10+next.digit[4];
            if(!vis[val]){
                vis[val]=1;
                Q.push(next);
            }
        }

		//相邻位交换 扩展状态
        for(int i=1;i<=3;i++){
            next=tp;
            swap(next.digit[i],next.digit[i+1]);
            next.s++;
            int val=next.digit[1]*1000+next.digit[2]*100+next.digit[3]*10+next.digit[4];
            if(!vis[val]){
                vis[val]=1;
                Q.push(next);
            }
        }
    }
    return tp.s;
}

void cal(int x,int &a,int &b,int &c,int &d){
    d=x%10;
    x/=10;
    c=x%10;
    x/=10;
    b=x%10;
    x/=10;
    a=x%10;
    x/=10;
}

int main(){
    int T,st,sa,sb,sc,sd;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&st);
        scanf("%d",&ed);
        cal(st,sa,sb,sc,sd);
        printf("%d\n",bfs(sa,sb,sc,sd));
    }
    return 0;
}
*/

/*
//ac 31ms 双向bfs 双端队列 从初始四位数和目标四位数同时开始bfs
//双端队列正常情况应该是比单端点开始的单向bfs要较早到达终止重合状态,时间上能较优些.
//摘自博客:https://www.cnblogs.com/H-Vking/p/4336279.html
//先预处理一下，从1111到9999的所有点进行构图(由于是1~9的，所以除去含有0元素的数字)，
//能进行一次变换变成的数字则表示两点之间连通。然后从初态与目态两个点进行BFS，如果有轨迹重合的就返回路程和。
//这里注意双向BFS要一层一层的进行搜索，不然的话会产生错误，至于错误原因还在思考中。。
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;
#define LL __int64
#define eps 1e-8
#define INF 1e8
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int MOD = 2333333;
const int maxn = 10000 + 5;
vector <int> e[maxn];
int vis[maxn] , dist[maxn];

void solve(int x)
{
    int num[4] , i , tmp , y;
    i = 0;
    tmp = x;
    while(tmp) {
        num[i++] = tmp % 10;
        tmp /= 10;
    }
    for(i = 0 ; i < 4 ; i++)
        if(num[i] == 0)
            return;
    for(i = 0 ; i < 4 ; i++) {
        if(i < 3) {
            swap(num[i] , num[i + 1]);
            y = num[3] * 1000 + num[2] * 100 + num[1] * 10 + num[0];
            e[x].push_back(y);
            e[y].push_back(x);
            swap(num[i] , num[i + 1]);
        }
        tmp = num[i];
        if(num[i] == 9)
            num[i] = 1;
        else
            num[i]++;
        y = num[3] * 1000 + num[2] * 100 + num[1] * 10 + num[0];
        e[x].push_back(y);
        e[y].push_back(x);
        num[i] = tmp;

        if(num[i] == 1)
            num[i] = 9;
        else
            num[i]--;
        y = num[3] * 1000 + num[2] * 100 + num[1] * 10 + num[0];
        e[x].push_back(y);
        e[y].push_back(x);
        num[i] = tmp;
    }
}
int BFS_2(int start , int end)
{
    if(start == end)
        return 0;
    memset(vis , 0 , sizeof(vis));
    queue <int> que[2];
    vis[start] = 1;
    vis[end] = 2;
    que[0].push(start);
    que[1].push(end);
    dist[start] = dist[end] = 0;
    while(!que[0].empty() && !que[1].empty()) {
        int k = 0;
        if(que[0].size() < que[1].size())
            k++;
        int u = que[k].front();
        que[k].pop();
        for(int i = 0 ; i < e[u].size() ; i++) {
            int j = e[u][i];
            if(!vis[j]) {
                vis[j] = vis[u];
                que[k].push(j);
                dist[j] = dist[u] + 1;
            } else if(vis[j] == vis[u]) {
                continue;
            } else {//vis[j]已访问 说明两端开始状态第一次重合,那么dist[j]+dist[u]+1就表示两端开始的队列共进行了多次步操作
                return dist[j] + dist[u] + 1;
            }
        }
    }
    return -1;
}
int main()
{
    int T , a , b;
    for(int i = 1111 ; i <= 9999 ; i++)
        solve(i);
    cin >> T;
    while(T--) {
        scanf("%d %d" , &a , &b);
        printf("%d\n" , BFS_2(a , b));
    }
    return 0;
}
*/
