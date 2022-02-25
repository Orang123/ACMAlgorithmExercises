#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<string>
#define N 2100
using namespace std;
//ac 250ms 最小边覆盖
/*
题意:给出m个长度为n"01"串,某些串含有'*',这样的串可以将
'*'代替为'0'或'1'表示成2个串,重复的串只算一种类型,现在
要消灭所有的串,如果两个串只有一位不同,则两个串可以1次操作
同时消除,否则每次操作只能消除一个串,现在要消灭所有的串最少
需要多少次操作.
eg:样例里*01 100 011可以表示为001 101 100 011,其中*01是表示成了
001和101.
链接:http://poj.org/problem?id=2724
思路:可以预处理所有的串,将带'*'的串代替为'0'和'1'2个串,set<string>判重,
不带'*'的串直接插入set即可,求出所有扩展后不重复串后,遍历所有串若两个串i、j,
只有一位不同,则建立i和j之间的双向边,那么串i和串j一定是一个含有奇数个1一个含
偶数个1,而且一定是奇数和偶数相邻的一个比一个只多1的情形,因为若2个串中1的个数都是
偶数或都是奇数,除非两个串完全相同,否则2个串至少会有2位不同,所以i和j之间建边
串的连接一定是偶-奇-偶-奇这样,满足交叉染色法,而且实际上这个问题应该也不会产生环,
因此构建的无向图一定是二分图,而二分图中的每条边代表的是一次可以消灭这2个串,
但实际按照一条边选择了2个串i,j消灭后,可能这个点i还连着别的点k,但这时i已经被消灭了,
但为了消灭这个剩下的串k,还需选择这条剩下的边i-k消灭,只消灭剩余的那个点所代表的串.
所以问题转化为了选择尽可能少的边覆盖所有的点,因此就是求解二分图中的最小边覆盖.
二分图中最小边覆盖=顶点数-最小顶点覆盖=顶点数-最大匹配.

注意:
1.此题实际构成的图可能会含有孤立点,也就是可能不存在最小边覆盖,因为孤立点永远
没有边能覆盖到,但这里只是用边表示消灭这个串而已,对于孤立点也只要单独消灭一次即可,
即最小边覆盖=顶点数-最大匹配,这个结果是正确的.
2.string不能在循环里值传递,string区别于char字符数组,是作为一个整体看待的,每次都会O(n)
复制一遍原字符串,会TLE要用引用或地址的传递,这样只需复制地址或直接引用string本身.

*/

int n,m,cnt,head[N],vis[N],match[N],ans;
vector<string> node;//node记录扩展后所有不重复的串
vector<int> G[N];
set<string> s;

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
//这里注意string值传递会TLE,因为每次都会O(n)赋值一份字符串,会增加一层的复杂度
//采取引用传递或者地址指针传递,这样就无需复制整个字符串
int judge(int x,int y){
    int num=0;
    for(int i=0;i<n;i++){
        if(node[x][i]!=node[y][i])
            num++;
    }
    return num == 1;
}

void init(){
    cnt=ans=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    s.clear();
    node.clear();
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int pos;
    string str,s1,s2;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            cin >> str;
            pos=str.find('*');
            if(pos!=-1){//若str当前输入串含'*'则返回的是'*'所在位置下标,否则返回-1
                s1=s2=str.substr(0);//s1、s2为str的复制串
                //string s1(str),s2(str);
                s1[pos]='0';//修改s1当前'*'为'0'
                s2[pos]='1';//修改s1当前'*'为'1'
                if(s.find(s1) == s.end()){//如果s中不含s1,返回的是s中最后一个元素的迭代器
                    s.insert(s1);//s中插入s1
                    node.push_back(s1);//记录所有不重复串
                }
                if(s.find(s2) == s.end()){
                    s.insert(s2);//s中插入s2
                    node.push_back(s2);
                }
            }
            else{//str不含'*'
                if(s.find(str) == s.end()){
                    s.insert(str);//s中插入无扩展位的str
                    node.push_back(str);
                }
            }
        }
        int len=node.size();
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                if(judge(i,j)){//判断串i和串j 是否只有一位不同
                    G[i+1].push_back(j+1);//建立双向边
                    G[j+1].push_back(i+1);
                }
            }
        }
        for(int i=1;i<=len;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",len-ans/2);//最小边覆盖=顶点数-最大匹配 因为考虑了所有点是无向图ans要除2
    }
    return 0;
}

/*
//ac 235ms string引用传递
//ac 219 string指针地址传递
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<string>
#define N 2100
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans;
vector<string> node;//node记录扩展后所有不重复的串
vector<int> G[N];
set<string> s;

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
//这里注意不要值传递string本身作为参数,会TLE
int judge(string &x,string &y){//指针地址传递 judge(string *x,string *y)
    int num=0;
    for(int i=0;i<n;i++){
        if(x[i]!=y[i])//指针地址传递 if((*x)[i]!=(*y)[i])
            num++;
    }
    return num == 1;
}

void init(){
    cnt=ans=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    s.clear();
    node.clear();
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int pos;
    string str,s1,s2;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            cin >> str;
            pos=str.find('*');
            if(pos!=-1){//若str当前输入串含'*'则返回的是'*'所在位置下标,否则返回-1
                s1=s2=str.substr(0);//s1、s2为str的复制串
                //string s1(str),s2(str);
                s1[pos]='0';//修改s1当前'*'为'0'
                s2[pos]='1';//修改s1当前'*'为'1'
                if(s.find(s1) == s.end()){//如果s中不含s1,返回的是s中最后一个元素的迭代器
                    s.insert(s1);//s中插入s1
                    node.push_back(s1);//记录所有不重复串
                }
                if(s.find(s2) == s.end()){
                    s.insert(s2);//s中插入s2
                    node.push_back(s2);
                }
            }
            else{//str不含'*'
                if(s.find(str) == s.end()){
                    s.insert(str);//s中插入无扩展位的str
                    node.push_back(str);
                }
            }
        }
        int len=node.size();
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                //指针地址传递 judge(&node[i],&node[j])
                if(judge(node[i],node[j])){//判断串i和串j 是否只有一位不同 不能传递string作为形式参数 会 TLE
                    G[i+1].push_back(j+1);//建立双向边
                    G[j+1].push_back(i+1);
                }
            }
        }
        for(int i=1;i<=len;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",len-ans/2);//最小边覆盖=顶点数-最大匹配 因为考虑了所有点是无向图ans要除2
    }
    return 0;
}
*/
