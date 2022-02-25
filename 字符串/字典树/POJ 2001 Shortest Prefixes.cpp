/*
题意:摘自网上
给你若干个单词的字典，求字典中每一个单词的最短唯一前缀。
最短唯一前缀：找出这个单词中的一个前缀，要求这个前缀只
在这个单词中出现过，并且要求这个前缀最短。
如果不存在唯一前缀就输出这个单词本身.
单词个数<=1000,每个单词长度<=20.
链接:http://poj.org/problem?id=2001
思路:建立字典树,统计每个节点下面单词的数目,查找时输出截止到
第一个节点下面单词个数为1的字符.就是最短唯一前缀.
*/

//ac 547ms
#include<cstdio>
#include<cstring>
#define N 1100
#define M 20010

int tr[M][26],cnt,num[M],len[N];
char s[N][25];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    num[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son;
    len[id]=strlen(s[id]);
    for(int i=0;i<len[id];i++){
        son=s[id][i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        num[rt]++;
    }
}

void findWord(int id){
    printf("%s ",s[id]);
    int rt=0,son;
    for(int i=0;i<len[id];i++){
        son=s[id][i]-'a';
        rt=tr[rt][son];
        if(num[rt] == 1){
            for(int j=0;j<=i;j++)
                printf("%c",s[id][j]);
            printf("\n");
            return;
        }
    }
    printf("%s\n",s[id]);//不存在唯一前缀,输出单词本身.
}

int main(){
    cnt=-1;
    newNode();
    int siz=0;
    while(scanf("%s",s[++siz])!=EOF)
        insertWord(siz);
    for(int i=1;i<=siz;i++)
        findWord(i);
    return 0;
}
