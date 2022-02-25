/*
题意:摘自网上
给你p个商品名称,然后输入q个字符串查询,
对每个查询输出含有查询串为子串的商品个数.
p<=10000,q<=100000. |s|<=20.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2846
思路:字典树,因为是在多个文本串中判断是否包含模式串.
ac自动机是1个文本串匹配多个模式串.
可以考虑将每个字符串的后缀子串插入字典树,这样每个后缀子串
的前缀就构成了这个串的所有子串,然后计数,只是要判断对于同一个
串的相同子串 不能重复计数,如:abab"的"ab".
*/
//ac 187ms
#include<cstdio>
#include<cstring>
#define N 4000010//20*20*10000

int p,q,tr[N][26],cnt,wordCnt[N],id[N];
char s[25];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=id[cnt]=0;
    return cnt;
}

void insertWord(char *s,int k){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        if(id[rt]!=k){//同样的子串 同一个串只统计一次
            wordCnt[rt]++;
            id[rt]=k;
        }
    }
}

int findWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            return 0;
        rt=tr[rt][son];
    }
    return wordCnt[rt];
}

int main(){
    int len;
    cnt=-1;
    newNode();
    scanf("%d",&p);
    for(int i=1;i<=p;i++){
        scanf("%s",s);
        len=strlen(s);
        for(int j=0;j<len;j++)
            insertWord(s+j,i);
    }
    scanf("%d",&q);
    while(q--){
        scanf("%s",s);
        printf("%d\n",findWord());
    }
    return 0;
}
