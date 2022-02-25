/*
题意:Ignatius最近遇到一个难题,老师交给他很多单词(只有小写字母组成,
不会有重复的单词出现),现在老师要他统计出以某个字符串为前缀的单词数量
(单词本身也是自己的前缀).对于每个提问,给出以该字符串为前缀的单词的数量.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1251
思路:字典树模板.
*/
/*
字典树的空间复杂度最坏为为所有(模式串的长度和)*26,
插入节点和查找节点的复杂度为O(n),n为最长的模式串的长度.
*/
//ac 218ms 静态数组实现trie树
#include<cstdio>
#include<cstring>
#define maxn 1000010 //这里的1000010取得是个极限最大范围,实际如果节点较多很可能这个空间开销也是远远不够的,Tire是以空间换时间的一种策略

char s[20];
int trie[maxn][26];//每个父亲节点都最多有26的叶子节点代表26个英文字母
int cnt[maxn],pos=1;//pos代表每个字母对应的节点编号

void insertNode(){//O(n)
    int root=0,child;
    for(int i=0;s[i];i++){
        child=s[i]-'a';
        //同一父亲节点的儿子节点所在的 trie 二维数组行下标是在同一行的,
        //每个儿子节点绝对和父亲节点不在同一行下标,pos值也有可能相差很大
        if(!trie[root][child])
            trie[root][child]=pos++;//如果这个点无儿子节点就插入
        root=trie[root][child];
        cnt[root]++;//记录这个字符以前构成的子串对应的前缀出现了多少次
    }
}

int findNode(){//O(n)
    int root=0,child;
    for(int i=0;s[i];i++){
        child=s[i]-'a';
        if(!trie[root][child])//没有以该字符串为前缀的子串
            return 0;
        root=trie[root][child];//继续向下遍历对应的儿子节点
    }
    return cnt[root];
}

int main(){
    while(gets(s)){//O(n*len)
        if(s[0]==NULL) break;
        insertNode();
    }
    while(gets(s))
        printf("%d\n",findNode());
    return 0;
}

/*
//ac 171ms 链式结构指针实现trie树
#include<cstdio>
//这种链式结构只能在C++编辑器下运行,采用HDU的 G++会Memory Limit Exceeded 171ms 数组方式218ms 差不多
struct trie{
    trie *next[26];
    int cnt;
    trie(){
        for(int i=0;i<26;i++)
            next[i]=NULL;
        cnt=0;
    }
}node;
char s[20];
int pos=1;

void insertNode(){
    trie *root=&node;
    int c;
    for(int i=0;s[i];i++){
        c=s[i]-'a';
        if(!root->next[c])
            root->next[c]=new trie;//用malloc不会执行trie()构造函数 用new吧
        root=root->next[c];
        root->cnt++;
    }
}

int findNode(){
    trie *root=&node;
    int c;
    for(int i=0;s[i];i++){
        c=s[i]-'a';
         if(!root->next[c])
            return 0;
         root=root->next[c];
    }
    return root->cnt;
}

int main(){
    while(gets(s)){//O(n^2)
        if(s[0]==NULL) break;
        insertNode();
    }
    while(gets(s))
        printf("%d\n",findNode());
    return 0;
}
*/

/*
//ac 818ms map<string,int>实现
#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;
map<string,int> mp;
int main(){//811ms 映射和查询都会耗时 较慢
    string ss,s;

    while(getline(cin, s) && s != ""){//cin会读入回车符
        int len=s.size();
        ss="";
        for(int i=0;i<len;i++){
            ss+=s[i];
            mp[ss]++;
        }
    }
    while(cin >> s)
        cout << mp[s] <<endl;
    return 0;
}
*/
