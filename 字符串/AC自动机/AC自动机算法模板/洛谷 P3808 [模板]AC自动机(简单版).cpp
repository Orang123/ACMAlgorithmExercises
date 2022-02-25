/*
题意:给定n个模式串si,和一个文本串t，
求有多少个不同的模式串在文本串里出现过。
两个模式串不同当且仅当他们编号不同。
n<=10^6,|t|<=10^6,∑|si|<=10^6.
链接:https://www.luogu.com.cn/problem/P3808
思路:多模式串匹配问题,AC自动机,已遍历过的后缀子串要标记,
不能重复遍历.
*/

/*
Aho-Corasick automaton AC自动机 是Alfred Aho 和Margaret Corasick在1975年于贝尔实验室发明的多模式匹配算法
实际上AC自动机是通过预处理构造fail指针和扩展出符合文本串轨迹的连边来使得
匹模式串时可通过当前最长后缀以匹配的字符串直接跳转到某个模式串分支的前缀串后的文本串字符的那个结点去匹配
   这里省略了重新从根节点考虑前缀和其中间某个子串匹配的过程，节省了要走的路径数，自然提高了时间界。
fail指针提出的理论依据是建立在trie树的某个分支上一定是存在至少一个模式串的,我们跳转到某个字符看后续路径是否
能出现模式串，若出现即文本串包含这个模式串。

AC自动机和kmp算法的比较:
对于多模式串的匹配问题如果用kmp算法,那么每个模式串都需要单独计算next数组,n个模式串
都需要和文本串执行一次匹配,这个复杂度很明显n*(slen+plen),n为模式串的个数
对于只有一个模式串和文本串匹配,AC自动机查找的时间界仍然是线性时间界,和kmp算法差不多,
但是kmp能精准返回模式串在文本串中匹配的位置下标,而AC自动机本身构造trie树要耗费巨大的空间复杂度,
而kmp空间复杂度是线性的,trie树是C*L,C=26,L是所有模式串长度和.要实现返回模式串在文本串匹配下标还需要
记录模式串在字典树前缀的当前长度,相对要更耗费空间

理解AC自动机参考博客:
https://oi-wiki.org/string/ac-automaton/
https://www.cnblogs.com/hyfhaha/p/10802604.html
https://blog.csdn.net/bestsort/article/details/82947639

https://blog.csdn.net/mobius_strip/article/details/22549517 (这个博客详细说明了优化改进)
(实际我现在写的版本是字典图优化版本,fail指针还构建了原字典树中不存在的边,
这样方便在所有的后缀子串下一个字母都没有当前前缀的下一个字母时 能直接O(1)跳到0号根节点)
未优化 字典树
setfail()
{
	Q[0] = root;
	root->fail = NULL;
	for ( int move = 0,save = 1 ; move < save ; ++ move ) {//利用bfs求解
		tnode* now = Q[move];
		for ( int i = 0 ; i < dictsize ; ++ i )
			if ( now->next[i] ) {
			tnode* p = now->fail;//从父节点的fail节点开始
			while ( p && !p->next[i] ) p = p->fail;//寻找本节点的fail节点
			now->next[i]->fail = p?p->next[i]:root;//不存在fail赋值为root
			Q[save ++] = now->next[i];
		}
	}
}

优化改进字典图
setfail()
{
	Q[0] = root;
	root->fail = NULL;
	for ( int move = 0,save = 1 ; move < save ; ++ move ) {
		tnode* now = Q[move];
		for ( int i = 0 ; i < dictsize ; ++ i )
		if ( now->next[i] ) {
			tnode* p = now->fail;
			while ( p && !p->next[i] ) p = p->fail;
			now->next[i]->fail = p?p->next[i]:root;
			Q[save ++] = now->next[i];
		}else now->next[i] = now!=root?now->fail->next[i]:root;//其实只多了这一句
	}
}
*/
//ac 332ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
using namespace std;

//字典树的一维大小 是按照模式串所有子串的长度和计算的,
//这是最坏情况,实际不可能超过这个最坏情况,就是每个字符
//都单独占据一个编号,实际26个英文字母一定会有前缀重复的部分.
int trie[N][26];
//faikl[x]=k:字典树中编号为x的节点的字符结尾指向的最大后缀的节点的编号为k(实际别的模式串的前缀)
int fail[N];
//cntWord[x]表示在字典树中编号为x的节点的字符结尾的单词出现的次数
//cnt为字典树节点标号
int cntWord[N],cnt;
char s[N];

//插入单词 构建字典树 设所有模式的长度和为L，文本长度为m，时间复杂度的总和为O(L+m) 空间复杂度为O(C*L)，
//其中C为使用的字符集(26个字母)的大小（用于建立前缀树）
void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++cnt;
        root=trie[root][next];
    }
    cntWord[root]++;
}

//构建fail指针,同时不存在的字符扩展为字典树的连接边构造字典图
//队列bfs时间复杂度、空间复杂度O(∑|s[i]|),|s[i]|模式串的长度,是个线性复杂度,
//因为每次入队只会对存在的模式串字符入队,不存在的边只是扩展成字典图,并不入队,实际因为模式串存在公共前缀 复杂度要比这个还小
void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            //第二层结点的fail指针都指向根节点，因为除了字母本身外最长后缀为null
            fail[node]=0;
            Q.push(node);
        }
    }
    /*
    采取广度优先遍历，去扩展fail链接，之所以bfs，是因为在扩展下一个结点的fail
    指针时必须要保证前面的父节点的fail指针已经求出来,因为要根据其父节点的fail
    去设置当前节点的fail
    */
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        //扩展26个字母的儿子结点的fail指针和连边
        for(int i=0;i<26;i++){
            //如果有儿子就构建fail 当前以第i个字母结尾的前缀的最长后缀(别的模式串的前缀)
            if(trie[node][i]){
                //当前结点的fail为其父亲节点的fail结点的指向连接i字母的那个儿子结点
                //即父亲的最长后缀因为加上i字符就扩展为当前结点的最长后缀了
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);//当前扩展fail后的结点入队作为下一次出队时的父亲结点去扩展后面的儿子结点
            }
            //这里是将字典树构建为字典图,这些本身没有的连边是为了方便文本串后面字符的匹配,
            //没有后续的字符就考虑当前前缀的最长后缀中下一个字符是否能继续匹配.
            //可以直接跳到别的模式串,可能别的模式串后面的字符恰好等于当前文本串的字符,也有
            //可能别的模式串末尾都没有文本串当前字符,最终这个指针会回到0号根节点.
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

//多模式串匹配查找的时间复杂度O(∑|s[i]|+|S|)
//∑|s[i]|是所有模式串的字符总和,|S|是文本串的字符总和
int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        //now节点编号可能会重复遍历到,文本串中的子串本身就可能有重复,某个节点失配后会回到0号根节点
        now=trie[now][s[i]-'a'];
        /*
        这里now结点所代表的前缀字符串可能不是某个模式单词,但是当前前缀字符串的
        后缀子串可能是模式串单词,其所指向的后续的多个fail结点所代表的最长后缀
        (其实是当前前缀的多个后缀子串),最长后缀会不断往回跳跃,不断尝试别的较短
        的模式串前缀是否有可能是某个模式串单词,如果最长后缀都不是是模式串,
        最终j=fail[j]会跳跃到0号根节点.
        */
        //遍历当前前缀的所有后缀子串,实际就是枚举文本串的子串当前字符之前的所有子串,看是否能找到模式串单词,
        //结束条件是遍历到0号根节点或当前后缀子串j之前已经遍历过
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){//这个每次向上遍历fail时，沿着fail指针最多移动的深度为这个分支的长度 所以总共累加才为O(n)因此单独的一个循环可作为O(1)看待
            //累加j结尾的模式串单词的数量
            res+=cntWord[j];
            //需要对判断过的后缀子串作标记,如果本身后缀子串是模式串单词则累加过得不再累加,
            //如果本身后缀子串不是模式串单词,已经判断过不是的也不再重复判断.
            cntWord[j]=-1;
        }
    }
    return res;//返回文本串中包含多少个模式串
}

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",s);
        insertWords();
    }
    scanf("%s",s);
    build();
    printf("%d\n",query());
    return 0;
}

/*
//ac 374ms HDU 2222 Keywords Search
//memset初始化trie树 为0
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
#define M 500010
using namespace std;

int trie[M][26];
int fail[M];
int cntWord[M],cnt;
char s[N];

void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++cnt;
        root=trie[root][next];
    }
    cntWord[root]++;
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

int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        now=trie[now][s[i]-'a'];
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){
            res+=cntWord[j];
            cntWord[j]=-1;
        }
    }
    return res;
}

int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        memset(trie,0,sizeof(trie));
        memset(cntWord,0,sizeof(cntWord));
        cnt=0;
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWords();
        }
        scanf("%s",s);
        build();
        printf("%d\n",query());
    }
    return 0;
}
*/

/*
//ac 234ms HDU 2222 Keywords Search
//trie初始化 将新节点的26个儿子节点置为空
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
#define M 500010
using namespace std;

int trie[M][26];
int fail[M];
int cntWord[M],cnt;
char s[N];

//将新节点的26个儿子节点置为空
int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        trie[cnt][i]=0;
    cntWord[cnt]=0;
    return cnt;
}

void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=newNode();
        root=trie[root][next];
    }
    cntWord[root]++;
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

int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        now=trie[now][s[i]-'a'];
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){
            res+=cntWord[j];
            cntWord[j]=-1;
        }
    }
    return res;
}

int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();//0号根节点 26个字母的儿子置为空
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWords();
        }
        scanf("%s",s);
        build();
        printf("%d\n",query());
    }
    return 0;
}
*/

/*
//ac 327ms HDU 2222 Keywords Search
//指针链式结构 fail字典树未优化版本,并不是字典图,只有字典树存在的模式串的边
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
	int cnt;//是否为该单词的最后一个结点
	Node *fail;//失败指针
	Node *next[26];//Trie中每个结点的各个节点
}*queue[500005];//队列，方便用BFS构造失败指针
char s[1000005];//主字符串
char keyword[55];//需要查找的单词
Node *root;//头结点
void Init(Node *root)//每个结点的初始化
{
	root->cnt=0;
	root->fail=NULL;
	for(int i=0;i<26;i++)
		root->next[i]=NULL;
}
void Build_trie(char *keyword)//构建Trie树
{
	Node *p,*q;
	int i,v;
	int len=strlen(keyword);
	for(i=0,p=root;i<len;i++)
	{
		v=keyword[i]-'a';
		if(p->next[v]==NULL)
		{
			q=(struct Node *)malloc(sizeof(Node));
			Init(q);
			p->next[v]=q;//结点链接
		}
		p=p->next[v];//指针移动到下一个结点
	}
	p->cnt++;//单词最后一个结点cnt++，代表一个单词
}
void Build_AC_automation(Node *root)
{
	int head=0,tail=0;//队列头、尾指针
	queue[head++]=root;//先将root入队
	while(head!=tail)
	{
		Node *p=NULL;
		Node *temp=queue[tail++];//弹出队头结点
		for(int i=0;i<26;i++)
		{
			if(temp->next[i]!=NULL)//找到实际存在的字符结点
			{ //temp->next[i] 为该结点，temp为其父结点
				if(temp==root)//若是第一层中的字符结点，则把该结点的失败指针指向root
					temp->next[i]->fail=root;
				else
				{
					//依次回溯该节点的父节点的失败指针直到某节点的next[i]与该节点相同，
                	//则把该节点的失败指针指向该next[i]节点；
                	//若回溯到 root 都没有找到，则该节点的失败指针指向 root
					p=temp->fail;//将该结点的父结点的失败指针给p
					while(p!=NULL)
					{
						if(p->next[i]!=NULL)
						{
							temp->next[i]->fail=p->next[i];
							break;
						}
						p=p->fail;
					}
					//让该结点的失败指针也指向root
					if(p==NULL)
						temp->next[i]->fail=root;
				}
				queue[head++]=temp->next[i];//每处理一个结点，都让该结点的所有孩子依次入队
			}
		}
	}
}
int query(Node *root)
{ //i为主串指针，p为模式串指针
	int i,v,count=0;
	Node *p=root;
	int len=strlen(s);
	for(i=0;i<len;i++)
	{
		v=s[i]-'a';
		//由失败指针回溯查找，判断s[i]是否存在于Trie树中
		while(p->next[v]==NULL && p!=root)
			p=p->fail;
		p=p->next[v];//找到后p指针指向该结点
		if(p==NULL)//若指针返回为空，则没有找到与之匹配的字符
			p=root;
		Node *temp=p;//匹配该结点后，沿其失败指针回溯，判断其它结点是否匹配
		while(temp!=root)//匹配结束控制
		{
			if(temp->cnt>=0)//判断该结点是否被访问
			{
				count+=temp->cnt;//由于cnt初始化为 0，所以只有cnt>0时才统计了单词的个数
				temp->cnt=-1;//标记已访问过
			}
			else//结点已访问，退出循环
				break;
			temp=temp->fail;//回溯 失败指针 继续寻找下一个满足条件的结点
		}
	}
	return count;
}
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		root=(struct Node *)malloc(sizeof(Node));
		Init(root);
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("\n%s",keyword);
			Build_trie(keyword);
		}
		Build_AC_automation(root);
		scanf("\n%s",s);
		printf("%d\n",query(root));
	}
	return 0;
}
*/

/*
//ac 280ms 字典树 没有扩展字典图,但是采用了last数组,last[i]记录的是 最长后缀永远是一个模式串,减少了fail失配指针跳跃次数
//摘自博客:https://blog.csdn.net/u013480600/article/details/23345221
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int maxnode=500000+100;
const int sigma_size=26;
int ans;
struct AC_Automata
{
    int ch[maxnode][sigma_size];
    int val[maxnode];//用于保存当前单词输入了几遍,当用find扫描文本的时候,只要遇到该单词就+val[i]且让vis[i]=false,使得下次遇到该模板不会重复计算
    int f[maxnode];
    int last[maxnode];
    bool vis[maxnode];//非单词节点vis=0,单词节点vis=1.如果用find找到了单词i节点,那么vis=0.
    int sz;
    void init()
    {
        sz=1;
        memset(ch[0],0,sizeof(ch[0]));
        vis[0]=false;
        last[0]=f[0]=val[0]=0;
    }
    void insert(char *s)
    {
        int n=strlen(s),u=0;
        for(int i=0;i<n;i++)
        {
            int id=s[i]-'a';
            if(ch[u][id]==0)
            {
                vis[sz]=false;
                ch[u][id]=sz;
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz++]=0;
            }
            u=ch[u][id];
        }
        vis[u]=true;
        val[u]++;
    }
    void print(int i)
    {
        if(val[i])
        {
            if(vis[i])
            {
                ans+=val[i];
                vis[i]=false;
            }
            print(last[i]);
        }
    }
    void find(char *s)
    {
        int n=strlen(s),j=0;
        for(int i=0;i<n;i++)
        {
            int id=s[i]-'a';
            while(j && ch[j][id]==0) j=f[j];
            j=ch[j][id];
            if(val[j]) print(j);
            else if(last[j]) print(last[j]);
        }
    }
    void getFail()
    {
        queue<int> q;
        f[0]=0;
        for(int i=0;i<sigma_size;i++)
        {
            int u=ch[0][i];
            if(u)
            {
                last[u]=f[u]=0;
                q.push(u);
            }
        }
        while(!q.empty())
        {
            int r=q.front();q.pop();
            for(int i=0;i<sigma_size;i++)
            {
                int u=ch[r][i];
                if(!u) continue;
                q.push(u);
                int v=f[r];
                while(v && ch[v][i]==0) v=f[v];
                f[u]=ch[v][i];
                last[u] = val[f[u]]?f[u]:last[f[u]];
            }
        }
    }
};
AC_Automata ac;
const int MAXN=1000000+100;
char text[MAXN],word[100];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ans=0;
        ac.init();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",word);
            ac.insert(word);
        }
        ac.getFail();
        scanf("%s",text);
        ac.find(text);
        printf("%d\n",ans);
    }
    return 0;
}
*/
