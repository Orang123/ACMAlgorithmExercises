/*
题意:摘自网上
给出一个字符串矩阵，n个单词，要求n个单词去匹配这个矩阵，
单词可以出现矩阵任意位置，可以斜着，横着，竖着。
求出每个单词的首字母在矩阵中的位置，以及方向。
模式串长度<=1000
链接:http://poj.org/problem?id=1204
思路:AC自动机,只是对于文本串需要枚举各个起点的8个方向的子串,
可以按照行列划分,对于所有的行,分成左边起始点和右边起始点,分别
对应3个方向{东北、东、东南} ,{西北、西、西南}.
对于所有的列,分成顶部起始点和底部起始点,分别
对应3个方向{西南、南、东南} ,{西北、北、东北}.
*/
//ac 750ms 对遍历过的后缀子串标记
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000010
#define M 1100
using namespace std;

int dir[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int l,c,w,tr[N][26],fail[N],wordId[N],cnt,len[M],ans[M][3];
char p[M],mp[M][M];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son;
    len[id]=strlen(p);
    for(int i=0;i<len[id];i++){
        son=p[i]-'A';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordId[rt]=id;
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<26;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            son=tr[node][i];
            if(son){
                fail[son]=tr[fail[node]][i];
                Q.push(son);
            }
            else
                tr[node][i]=tr[fail[node]][i];
        }
    }
}

int check(int x,int y){
    if(x>=0 && x<l && y>=0 && y<c)
        return 1;
    return 0;
}

void query(int x,int y,int d){
    int rt=0;
    while(check(x,y)){
        rt=tr[rt][mp[x][y]-'A'];
        for(int i=rt;i && wordId[i]!=-1;i=fail[i]){
            if(wordId[i]){
                ans[wordId[i]][0]=x-dir[d][0]*(len[wordId[i]]-1);//这里-1要放在括号里,放在外面+1,有可能 x,y方向是不变的
                ans[wordId[i]][1]=y-dir[d][1]*(len[wordId[i]]-1);
                ans[wordId[i]][2]='A'+d;
            }
            wordId[i]=-1;//不对搜索过的后缀子串标记 时间为1204ms
        }
        x+=dir[d][0];
        y+=dir[d][1];
    }
}

int main(){
    scanf("%d%d%d",&l,&c,&w);
    for(int i=0;i<l;i++)
        scanf("%s",mp[i]);
    cnt=-1;
    newNode();
    for(int i=1;i<=w;i++){
        scanf("%s",p);
        insertWord(i);
    }
    build();
    for(int i=0;i<l;i++){
        //行左起始点 东北、东、东南
        query(i,0,1);
        query(i,0,2);
        query(i,0,3);
        //行右起始点 西北、西、西南
        query(i,c-1,5);
        query(i,c-1,6);
        query(i,c-1,7);
    }
    for(int i=0;i<c;i++){
        //列顶起始点 西南、南、东南
        query(0,i,3);
        query(0,i,4);
        query(0,i,5);
        //列底起始点 西北、北、东北
        query(l-1,i,7);
        query(l-1,i,0);
        query(l-1,i,1);
    }
    for(int i=1;i<=w;i++)
        printf("%d %d %c\n",ans[i][0],ans[i][1],ans[i][2]);
    return 0;
}

/*
//ac 2907ms 直接字典树dfs搜索
//摘自博客:https://blog.csdn.net/huyifan1/article/details/84812629
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char c[1005][1005];
int n,m,w,sx,sy;
int out[1005][3];
char str[1005];
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};
typedef struct Trie
{
    Trie *next[26];
    int v;
    int id;

};
Trie *root;
void createTrie(int num)
{
    Trie *p=root,*q;
    for(int i=0;i<strlen(str);i++)
    {
        int id=str[i]-'A';
        if(p->next[id]==NULL)
        {
           p->next[id]=new Trie();
           p=p->next[id];
        }
        else
        {
            p->next[id]->v++;
            p=p->next[id];
        }
    }
    p->id=num;
}
void dfs(Trie *p,int x,int y,int dir)
{
    if(p==NULL)
    {
        return;
    }
    if(p->id>0)                 //在这里不能返回，不然的只遍历了前缀子串就返回了，无法达到减少时间复杂度的目的
    {
        out[p->id][0]=sx;
        out[p->id][1]=sy;
        out[p->id][2]=dir;
    }
    if(x<0||x>=n||y<0||y>=m)
        return;
   dfs(p->next[c[x][y]-'A'],x+dx[dir],y+dy[dir],dir);   //减少了前缀子串的重新遍历

}
int main()
{
    scanf("%d%d%d",&n,&m,&w);
    for(int i=0; i<n; i++)
    {
        getchar();
        for(int j=0; j<m; j++)
        {
            scanf("%c",&c[i][j]);
        }
    }
    root=new Trie();
  for(int i=1;i<=w;i++)
   {
        scanf("%s",str);
        createTrie(i);  //将所有要查询的字符串构成一个字典树
   }
    Trie *p=root;
   for(int i=0;i<n;i++)
   {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<8;k++)
            {
                sx=i;
                sy=j;
                dfs(p,i,j,k);
            }
        }

   }

    for(int i=1;i<=w;i++)
    {
        printf("%d %d %c\n",out[i][0],out[i][1],out[i][2]+'A');
    }
    return 0;
}
*/
