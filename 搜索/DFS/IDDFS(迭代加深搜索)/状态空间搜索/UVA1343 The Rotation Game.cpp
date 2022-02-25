/*
题意:摘自网上
每个格子是1或2或3，一共8个1，8个2，8个3.有A~H一共8种合法操作，
比如A代表把A这一列向上移动一个，最上面的格会补到最下面。
求：使中心8个格子数字一致的最少步骤，要输出具体的操作步骤及
最终中心区域的数字。如果有多个解，输出字典序最小的操作步骤。
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4089
思路:一共24个数字,可以移动的方式有A~H八种,可以dfs每次枚举这8个方向,
而这8个方向每次移动的次数是无限的,而现在是dfs深度优先枚举的,如果在
某个方向是一直无解的,则会死循环,因此dfs枚举需要设置一个操作步骤的
上限,当当前操作次数大于这个上限时就及时退出,因此依次增加操作次数,
迭代加深搜索.
一个剪枝是:当当前步数+中心区域最少不同的数字个数(实际最少需要移动次数)>当前指定
的操作次数时,返回.
*/
//ac 250ms IDA*(iterative deepening A*)  (IDDFS iterative deepening depth-first search)
//时间复杂度O(8^n)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 24
using namespace std;
/*
24个数从上到下,从左到右,编号.
        A     B
        00    01
        02    03
H 04 05 06 07 08 09 10 C
        11    12
G 13 14 15 16 17 18 19 D
        20    21
        22    23
        F     E
*/
//oper按照字典序 操作枚举 这里最高次数设置为100
char oper[10]="ABCDEFGH",ans[100];
int mp[8][7]={{0,2,6,11,15,20,22},//A 0
              {1,3,8,12,17,21,23},//B 1
              {10,9,8,7,6,5,4},//C 2 由于move函数是a[mp[k][i]]=a[mp[k][i+1]],所以这里要逆序
              {19,18,17,16,15,14,13},//D 3 同上
              {23,21,17,12,8,3,1},//E 4
              {22,20,15,11,6,2,0},//F 5
              {13,14,15,16,17,18,19},//G 6
              {4,5,6,7,8,9,10}};//H 7
int a[N];
//center是中心区域下标编号
int center[8]={6,7,8,11,12,15,16,17};
//rec是8个操作方向 回溯用来恢复的反方向.
int rec[8]={5,4,7,6,1,0,3,2};

void move(int k){
    int tp=a[mp[k][0]];
    for(int i=0;i<6;i++)
        a[mp[k][i]]=a[mp[k][i+1]];
    a[mp[k][6]]=tp;
}

int check(){
    for(int i=0;i<7;i++){
        if(a[center[i]]!=a[center[i+1]])
            return 0;
    }
    return 1;
}

int diff(int val){
    int cnt=0;
    for(int i=0;i<8;i++){
        if(a[center[i]] != val)
            cnt++;
    }
    return cnt;
}

int surplusStep(){//判断中心区域 假设最终数字都是1、2、3时有几个数是不同的,取最小值 就是实际 还需最少操作的次数
    return min(diff(1),min(diff(2),diff(3)));
}

int dfs(int k,int maxs){
    if(k == maxs){
        if(check())
            return 1;
        else
            return 0;
    }
    //当当前步数+中心区域最少不同的数字个数(实际最少需要移动次数)>当前指定
    //的操作次数时,返回.
    if(k+surplusStep() > maxs)
        return 0;
    for(int i=0;i<8;i++){
        move(i);
        ans[k]=oper[i];
        if(dfs(k+1,maxs))
            return 1;
        move(rec[i]);//回溯 恢复a数组的状态 i的反方向是rec[i]
    }
    return 0;
}

int main(){
    while(scanf("%d",&a[0]) && a[0]){
        for(int i=1;i<24;i++)
            scanf("%d",&a[i]);
        if(check()){
            printf("No moves needed\n");
            printf("%d\n",a[6]);
            continue;
        }
        for(int i=1;;i++){
            if(dfs(0,i)){
                for(int j=0;j<i;j++)
                    printf("%c",ans[j]);
                printf("\n%d\n",a[6]);
                break;
            }
        }
    }
    return 0;
}

/*
dfs+爆搜肯定会超时,因为这个转态空间搜索,如果一直朝着i=0的方向移位,
是一定会回到初始状态的,如果这个过程中不能使得中间8个数字相等,
本身会有重复的情况不可避免,因为要遍历所有情况,会导致无限递归,如果
不采用IDA设置搜索步长,普通的dfs是没有结束条件的,会死循环.
*/

/*
//摘自博客:https://www.cnblogs.com/asdfsag/p/10357259.html
//这个状态的表示 位运算没太看明白
//但如果预先假定一个数是正确答案，那么剩下的两个数就没有区别了，所以状态可以用0和1来表示，
//这样总状态数就缩小到了C(24,8)=735471，在可接受范围内了。把原状态分解成三个子状态跑一遍
//bfs即可得到正确结果。但是如果对每个输入都跑一遍bfs的话依然会TLE，而我们发现对于每组输入，
//所有的状态表示的含义都是一样的，因此可以预先对末状态跑一遍bfs，记录下所有状态到末状态的最短距离，
//这样每接受一组输入都可以直接通过bfs树得到路径。
//这个状态表示的技巧不太好理解

//ac 310ms bfs+hash判重
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N=24+2,inf=0x3f3f3f3f;
const int b[][10]= {
    {0,2,6,11,15,20,22},
    {1,3,8,12,17,21,23},
    {10,9,8,7,6,5,4},
    {19,18,17,16,15,14,13},
    {23,21,17,12,8,3,1},
    {22,20,15,11,6,2,0},
    {13,14,15,16,17,18,19},
    {4,5,6,7,8,9,10},
};
int t[]= {0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0,0,0,0};
void rot(int* c,int x) {
    const int* bb=b[x];
    for(int i=0; i<6; ++i)swap(c[bb[i]],c[bb[i+1]]);
}
void enc(int* c,int& x) {
    x=0;
    for(int i=23; i>=0; --i)x=x<<1|c[i];
}
void dec(int* c,int x) {
    for(int i=0; i<24; ++i)c[i]=0;
    for(int i=0; i<24; ++i)c[i]=x&1,x>>=1;
}
struct Hashmap {
    static const int N=1e6+10;
    static const int mod=1e6+3;
    int hd[mod],nxt[N],tot,key[N],val[N];
    int H(int x) {return (x+233)%mod;}
    void clear() {tot=0; memset(hd,-1,sizeof hd);}
    int count(int x) {
        for(int u=hd[H(x)]; ~u; u=nxt[u])if(key[u]==x)return 1;
        return 0;
    }
    int& operator[](int x) {
        int h=H(x);
        for(int u=hd[h]; ~u; u=nxt[u])if(key[u]==x)return val[u];
        nxt[tot]=hd[h],key[tot]=x,val[tot]=0,hd[h]=tot;
        return val[tot++];
    }
} d;

int c[N],cc[N],s[N],ss,tt,mi,ans;
string str1,str2;

void bfs() {
    d.clear();
    queue<int> q;
    q.push(tt),d[tt]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        dec(c,u);
        for(int i=0; i<8; ++i) {
            memcpy(cc,c,sizeof c);
            rot(cc,i);
            int v;
            enc(cc,v);
            if(!d.count(v)) {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
}

int input() {
    for(int i=0; i<24; ++i)if(scanf("%d",&s[i])!=1)return 0;
    return 1;
}

int main() {
    enc(t,tt);
    bfs();
    while(input()) {
        mi=inf;
        for(int i=1; i<=3; ++i) {
            for(int j=0; j<24; ++j)c[j]=s[j]==i?1:0;
            int u;
            enc(c,u);
            mi=min(mi,d[u]);
        }
        str1="Z";
        for(int i=1; i<=3; ++i) {
            for(int j=0; j<24; ++j)c[j]=s[j]==i?1:0;
            int u;
            enc(c,u);
            if(d[u]==mi) {
                str2.clear();
                while(u!=tt) {
                    dec(c,u);
                    for(int j=0; j<8; ++j) {
                        memcpy(cc,c,sizeof c);
                        rot(cc,j);
                        int v;
                        enc(cc,v);
                        if(d.count(v)&&d[v]==d[u]-1) {
                            str2.push_back(j+'A');
                            u=v;
                            break;
                        }
                    }
                }
                if(str2<str1)str1=str2,ans=i;
            }
        }
        if(mi==0)printf("No moves needed\n");
        else printf("%s\n",str1.c_str());
        printf("%d\n",ans);
    }
    return 0;
}
*/
