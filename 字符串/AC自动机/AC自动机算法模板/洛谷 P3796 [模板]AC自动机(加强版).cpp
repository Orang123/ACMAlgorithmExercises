/*
同UVA 1449 Dominating Patterns
题意:有N个由小写字母组成的模式串以及一个文本串T。
每个模式串可能会在文本串中出现多次。你需要找出哪些
模式串在文本串T中出现的次数最多。
保证不存在两个相同的模式串。
N<=150,每个模式串长度<=70.文本串T长度<=10^6.
说明:一般统计出现次数都是可以重叠的.
链接:https://www.luogu.com.cn/problem/P3796
思路:因为要统计模式串出现的次数,那么在遍历文本串当前前缀的
后缀子串时,就无需标记,每次都增加后缀子串中模式串出现次数.
需要标记字典树中单词对应模式串中的id.即wordId[root]=index;
root是字典树一维编号,index是模式串的输入编号,最后比较求出出现
次数最多的模式串即可.
*/
//ac 2.74s
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 11000//150*70=10500 字典树最坏存储空间一维编号
#define max_len 1000010
using namespace std;

int trie[N][26];
//wordId记录字典树单词对应模式串的输入编号
int fail[N],wordId[N],cntWord[N],tot,cnt[160],res;
char s[160][80],str[max_len];

void init(){
    memset(trie,0,sizeof(trie));
    memset(wordId,0,sizeof(wordId));
    memset(cntWord,0,sizeof(cntWord));
    res=tot=0;
}

void insertWords(char *s0,int index){
    int root = 0,next;
    int len = strlen(s0);
    for(int i=0; i<len ;i++){
        next=s0[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++tot;
        root=trie[root][next];
    }
    //保证不存在两个相同的模式串。
    wordId[root]=index;//构造trie数时只标记模式串对应的二维数组一维编号
}

void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            fail[node]=0;
            Q.push(node);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            if(trie[node][i]){
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);
            }
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

int solve(){
    int now=0;
    int len=strlen(str);
    for(int i=0;i<len;i++){
        now=trie[now][str[i]-'a'];
        for(int j=now;j;j=fail[j])//这里因为不用设置避免重复，因为本身就是要统计重复出现次数的
            if(wordId[j])//如果当前节点代表一个模式串 则这个模式串出现次数+1
                cntWord[j]++;
    }
    for(int i=1;i<=tot;i++){
        if(wordId[i]){
            res=max(cntWord[i],res);//记录文本串出现次数最多的次数
            cnt[wordId[i]]=cntWord[i];//构造映射 cnt[模式串编号]=模式串在文本串出现次数
        }
    }
    return res;
}

int main(){
    int n;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]);
            insertWords(s[i],i);
        }
        scanf("%s",str);
        build();
        solve();
        printf("%d\n",res);
        for(int i=1;i<=n;i++){
            if(cnt[i] == res)
                printf("%s\n",s[i]);
        }
    }
    return 0;
}

/*
//ac 1.83s 洛谷P3796
//trie初始化 将新节点的26个儿子节点置为空
//ac 70ms UVA 1449 Dominating Patterns
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 11000//150*70=10500 字典树最坏存储空间一维编号
#define max_len 1000010
using namespace std;

int trie[N][26];
//wordId记录字典树单词对应模式串的输入编号
int fail[N],wordId[N],cntWord[N],tot,cnt[160],res;
char s[160][80],str[max_len];

//将新节点的26个儿子节点置为空
int newNode(){
    ++tot;
    for(int i=0;i<26;i++)
        trie[tot][i]=0;
    wordId[tot]=0;
    return tot;
}

void init(){
    tot=-1;
    newNode();
    memset(cntWord,0,sizeof(cntWord));
    res=tot=0;
}


void insertWords(char *s0,int index){
    int root = 0,next;
    int len = strlen(s0);
    for(int i=0; i<len ;i++){
        next=s0[i]-'a';
        if(!trie[root][next])
            trie[root][next]=newNode();
        root=trie[root][next];
    }
    //保证不存在两个相同的模式串。
    wordId[root]=index;//构造trie数时只标记模式串对应的二维数组一维编号
}

void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            fail[node]=0;
            Q.push(node);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            if(trie[node][i]){
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);
            }
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

int solve(){
    int now=0;
    int len=strlen(str);
    for(int i=0;i<len;i++){
        now=trie[now][str[i]-'a'];
        for(int j=now;j;j=fail[j])//这里因为不用设置避免重复，因为本身就是要统计重复出现次数的
            if(wordId[j])//如果当前节点代表一个模式串 则这个模式串出现次数+1
                cntWord[j]++;
    }
    for(int i=1;i<=tot;i++){
        if(wordId[i]){
            res=max(cntWord[i],res);//记录文本串出现次数最多的次数
            cnt[wordId[i]]=cntWord[i];//构造映射 cnt[模式串编号]=模式串在文本串出现次数
        }
    }
    return res;
}

int main(){
    int n;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]);
            insertWords(s[i],i);
        }
        scanf("%s",str);
        build();
        solve();
        printf("%d\n",res);
        for(int i=1;i<=n;i++){
            if(cnt[i] == res)
                printf("%s\n",s[i]);
        }
    }
    return 0;
}
*/

/*
//ac 1.33s 避免每次都遍历所有的fail后缀子串
#include <bits/stdc++.h>
using namespace std;
#define io_speed_up ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define per(i,a,b) for (int i=a;i>=b;i--)
#define ms(a,b)  memset(a,b,sizeof a)
#define sz(x) (int)x.size()
using ll = long long;
const int inf = 0x3f3f3f3f;
const int maxn = 1e5+5;
const int mod = 1e9+7;
int n;
string str[maxn];

struct Trie {
    int nxt[maxn][26];
    int fail[maxn];
    int end[maxn];
    int num[maxn];
    int tot,root;

    int a[maxn],N;
    int newnode() {
        memset(nxt[tot],-1,sizeof nxt[tot]);
        end[tot] = num[tot] = 0;
        return tot++;
    }
    void init() {
        tot = N = 0;
        root = newnode();
    }
    void insert(string &s,int k) {
        int p = root;
        for(int i=0;i<s.size();i++) {
            int x = s[i] - 'a';
            if(nxt[p][x]==-1) nxt[p][x] = newnode();
            p = nxt[p][x];
        }
        end[p] = k;//记录p节点对应的模式串编号
    }
    void build() {
        queue<int> q;
        fail[root] = root;
        for(int i=0;i<26;i++)
            if(nxt[root][i]==-1) nxt[root][i] = root;
            else fail[nxt[root][i]] = root,q.push(nxt[root][i]);

        while(!q.empty()) {
            int p = q.front(); q.pop();
            a[++N] = p;
            for(int i=0;i<26;i++)
                if(nxt[p][i]==-1)
                    nxt[p][i] = nxt[fail[p]][i];
                else
                    fail[nxt[p][i]] = nxt[fail[p]][i], q.push(nxt[p][i]);
        }
    }
    void solve(string &t) {
        int p = root;
        for(int i=0;i<t.size();i++) {
            p = nxt[p][t[i]-'a'];//p=0 实际表示字典树中 没有当前字符作为后缀的单词,没找到模式串匹配
            num[p]++;//只记录文本串当前前缀最后一个节点出现次数
        }
        //这里是仿照回文树那个利用当前回文出现次数累加更新最长后缀回文次数的概念
        //这里是从末尾结点代表的较长串去更新前面的较长后缀串
        //原先前缀出现了几次,对应的最长后缀也会出现几次
        for(int i=N;i>=1;i--)//num[0] 0号根节点是没意义的,表示没有模式串匹配
            num[fail[a[i]]] += num[a[i]];

        int mx = 0;
        //实际字典树 0号根节点
        for(int i=1;i<tot;i++) {//1号节点开始 才表示合法模式串 被匹配到了
            if(end[i] && num[i]>mx) mx = num[i];//统计模式串出现次数
        }
        vector<int> ans;
        for(int i=1;i<tot;i++) {
            if(end[i] && num[i]==mx) ans.push_back(end[i]);
        }
        sort(ans.begin(),ans.end());//按输入顺序 输出
        cout<<mx<<"\n";
        for(auto x:ans)
            cout<<str[x]<<"\n";
    }

}ac;
string t;
int main()
{
    io_speed_up;
    while(cin>>n && n) {
        ac.init();
        rep(i,1,n) {
            cin>>str[i];
            ac.insert(str[i],i);
        }
        ac.build();
        cin>>t;
        ac.solve(t);
    }
    return 0;
}
*/
