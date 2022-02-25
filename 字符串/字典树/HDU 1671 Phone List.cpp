/*
题意:摘自网上
给出n个数，看其中是否有一个数是另一个数的前缀，
例如123就是12345的前缀，有这种情况时输出NO，反之输出YES.
n<=10000,每个数数字长度<=10
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1671
思路:字典树,对于插入先插较短的后插较长的,插入时判断前缀是否
已经存在插入的单词了,对于先插较长的后插较短的,判断较短的单词
尾节点后面是否还有儿子.
*/
//ac 78ms
#include<cstdio>
#include<cstring>
#define N 100010

int n,tr[N][10],cnt,word[N],flag;
char s[15];

int newNode(){
    ++cnt;
    for(int i=0;i<10;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,len=strlen(s),son;
    for(int i=0;i<len;i++){
        son=s[i]-'0';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        if(word[rt]){
            flag=1;
            return;
        }
    }
    word[rt]=1;
    if(!flag){
        for(int i=0;i<10;i++){
            if(tr[rt][i]){
                flag=1;
                return;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        flag=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            if(!flag)
                insertWord();
        }
        if(!flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
