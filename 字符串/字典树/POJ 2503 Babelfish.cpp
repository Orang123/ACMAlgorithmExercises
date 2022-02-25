/*
题意:摘自网上
输入一个字典，字典格式为“英语 -> 外语”的一一映射关系
然后输入若干个外语单词，输出他们的 英语翻译单词，如果
字典中不存在这个单词，则输出“eh”
单词条数<=100000,每个单词长度<=10
链接:http://poj.org/problem?id=2503
思路:对外语建立字典树,将英语单独保存在一个对应节点的字符数组里,
查找即可.
注意输入 单词条数是以换行符作为结束符的.
*/
//ac 516ms
#include<cstdio>
#include<cstring>
#define N 100010
#define M 1000010

int cnt,word[M];
char s1[15],s2[15],tp[15];
struct S{
    int son[26];
    char str[15];
}tr[M];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt].son[i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        if(!tr[rt].son[child])
            tr[rt].son[child]=newNode();
        rt=tr[rt].son[child];
    }
    word[rt]=1;
    strcpy(tr[rt].str,s1);
}

void findWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        rt=tr[rt].son[child];
        if(!rt){
            printf("eh\n");
            return;
        }
    }
    if(word[rt])
        printf("%s\n",tr[rt].str);
    else
        printf("eh\n");
}

int main(){
    char x;
    cnt=-1;
    newNode();
    while(gets(tp) && tp[0]){//输入 换行符截止,gets会把换行符 转化为'\0'结束符
        sscanf(tp,"%s %s",s1,s2);
        insertWord();
    }
    while(scanf("%s",s2)!=EOF)
        findWord();
    return 0;
}

/*
//ac 547ms
#include<cstdio>
#include<cstring>
#define N 100010
#define M 1000010

int tr[M][26],cnt,word[M];
char str[M][15],s1[15],s2[15],tp[15];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        if(!tr[rt][child])
            tr[rt][child]=newNode();
        rt=tr[rt][child];
    }
    word[rt]=1;
    strcpy(str[rt],s1);
}

void findWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        rt=tr[rt][child];
        if(!rt){
            printf("eh\n");
            return;
        }
    }
    if(word[rt])
        printf("%s\n",str[rt]);
    else
        printf("eh\n");
}

int main(){
    char x;
    cnt=-1;
    newNode();
    while(gets(tp) && tp[0]){
        sscanf(tp,"%s %s",s1,s2);
        insertWord();
    }
    while(scanf("%s",s2)!=EOF)
        findWord();
    return 0;
}
*/
