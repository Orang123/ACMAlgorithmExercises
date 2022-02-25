/*
����:����һ����λ��,�����������һ����λ��
��2�ֲ���:
1.��һ�����ּ�1���߼�1��9��1���0,��1��1���9.
2.��һ�����ֺ����������ڵ����ֽ���
ÿ��������1��,����Ŀ����λ������Ҫ�����ٲ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1195
˼·:��Ϊ4λ����,����״̬���Ϊ1111~9999֮�����.
bfsģ��״̬ת�Ƽ���.2������,+-1�򽻻�����λ.
*/
//ac 15ms bfs vis��ά������״̬
//ʱ�临�Ӷ�O(n*n*n*n)=10000 vis[10][10][10][10]
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

//vis[a][b][c][d]=0/1 ��ʾabcd����4λ���ֹ��ɵ�����û����չ��
int ea,eb,ec,ed,vis[N][N][N][N];
struct State{
    int a,b,c,d,s;
    State(int a=0,int b=0,int c=0,int d=0,int s=0):a(a),b(b),c(c),d(d),s(s){}
};
queue<State> Q;

//���ּ�1��1
int plus_minus(int x,int val){
    if(x+val == 10)
        x=1;
    else if(x+val == 0)
        x=9;
    else
        x=x+val;
    return x;
}

//����µ�״̬
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
        //ǧλ��1
        na=plus_minus(tp.a,1);
        add(na,tp.b,tp.c,tp.d,tp.s+1);
        //ǧλ��1
        na=plus_minus(tp.a,-1);
        add(na,tp.b,tp.c,tp.d,tp.s+1);

        //��λ��1
        nb=plus_minus(tp.b,1);
        add(tp.a,nb,tp.c,tp.d,tp.s+1);
        //��λ��1
        nb=plus_minus(tp.b,-1);
        add(tp.a,nb,tp.c,tp.d,tp.s+1);

        //ʮλ��1
        nc=plus_minus(tp.c,1);
        add(tp.a,tp.b,nc,tp.d,tp.s+1);
        //ʮλ��1
        nc=plus_minus(tp.c,-1);
        add(tp.a,tp.b,nc,tp.d,tp.s+1);

        //��λ��1
        nd=plus_minus(tp.d,1);
        add(tp.a,tp.b,tp.c,nd,tp.s+1);
        //��λ��1
        nd=plus_minus(tp.d,-1);
        add(tp.a,tp.b,tp.c,nd,tp.s+1);

        //����ǧλ�Ͱ�λ
        na=tp.b;nb=tp.a;
        add(na,nb,tp.c,tp.d,tp.s+1);

        //������λ��ʮλ
        nb=tp.c;nc=tp.b;
        add(tp.a,nb,nc,tp.d,tp.s+1);

         //����ʮλ�͸�λ
        nc=tp.d;nd=tp.c;
        add(tp.a,tp.b,nc,nd,tp.s+1);
    }
    return tp.s;
}

//���������ʼ��Ŀ����λʮ������ �ֽ������λ�ϵ�����
//aǧλ b��λ cʮλ d��λ
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
        scanf("%d",&s);//������һ��4λ��ʮ������
        scanf("%d",&e);
        cal(s,sa,sb,sc,sd);
        cal(e,ea,eb,ec,ed);
        printf("%d\n",bfs(sa,sb,sc,sd));
    }
    return 0;
}

/*
//ac 62ms bfs visһά������vis[10000]
//ʱ�临�Ӷ�O(n)=10000 vis[10000]
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 10000
using namespace std;

//vis[val]=0/1��ʾʵ��4λ�������ʮ������ֵval ��û����չ��
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
        //����λ���ּ�1 ��չ״̬
        for(int i=1;i<=4;i++){
            next=tp;
            next.digit[i]++;
            next.s++;
            if(next.digit[i] == 10)
                next.digit[i]=1;
            //valʵ�ʱ�ʾ��4λ ʮ������ֵ
            int val=next.digit[1]*1000+next.digit[2]*100+next.digit[3]*10+next.digit[4];
            if(!vis[val]){
                vis[val]=1;
                Q.push(next);
            }
        }

		//����λ���ּ�1 ��չ״̬
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

		//����λ���� ��չ״̬
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
//ac 31ms ˫��bfs ˫�˶��� �ӳ�ʼ��λ����Ŀ����λ��ͬʱ��ʼbfs
//˫�˶����������Ӧ���Ǳȵ��˵㿪ʼ�ĵ���bfsҪ���絽����ֹ�غ�״̬,ʱ�����ܽ���Щ.
//ժ�Բ���:https://www.cnblogs.com/H-Vking/p/4336279.html
//��Ԥ����һ�£���1111��9999�����е���й�ͼ(������1~9�ģ����Գ�ȥ����0Ԫ�ص�����)��
//�ܽ���һ�α任��ɵ��������ʾ����֮����ͨ��Ȼ��ӳ�̬��Ŀ̬���������BFS������й켣�غϵľͷ���·�̺͡�
//����ע��˫��BFSҪһ��һ��Ľ�����������Ȼ�Ļ�������������ڴ���ԭ����˼���С���
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
            } else {//vis[j]�ѷ��� ˵�����˿�ʼ״̬��һ���غ�,��ôdist[j]+dist[u]+1�ͱ�ʾ���˿�ʼ�Ķ��й������˶�β�����
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
