/*
题意:
找出能有已知给定两个单词组成的单词。
n<=50000,每个单词长度<=10
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1247
思路:字典树,先将所有单词插入到字典树中.再分别对每个单词进行查找,
当某个单词前缀已经构成别的单词时,再查找剩下的字符是否能构成另一个单词.
*/
//ac 31ms
#include<cstdio>
#include<cstring>
#define N 50010
#define M 500010

int n,tr[M][26],cnt,word[M],num,len[N];
char s[N][20];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
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
    }
    word[rt]=1;
}

int find2(int st,int id){
    int rt=0,son;
    for(int i=st;i<len[id];i++){
        son=s[id][i]-'a';
        rt=tr[rt][son];
        if(!rt)
            return 0;
    }
    return word[rt];
}

int find1(int id){
    int rt=0,son;
    for(int i=0;i<len[id]-1;i++){
        son=s[id][i]-'a';
        rt=tr[rt][son];
        if(word[rt]){
            if(find2(i+1,id))
                return 1;
        }
    }
    return 0;
}

int main(){
    cnt=-1;
    newNode();
    while(scanf("%s",s[++num])!=EOF)
        insertWord(num);
    for(int i=1;i<num;i++){
        if(find1(i))
            printf("%s\n",s[i]);
    }
    return 0;
}
