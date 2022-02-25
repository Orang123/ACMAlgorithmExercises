/*
题意:摘自网上
给你一个由很多01字符串组成的集合,问你集合中有没有一个
字符串是其他另外一个或多个字符串的前缀.
链接:http://poj.org/problem?id=1056
思路:建立字典树,同HDU 1671.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#define N 100010

int n,tr[N][2],cnt,word[N],flag;
char s[15];

int newNode(){
    ++cnt;
    for(int i=0;i<2;i++)
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
        for(int i=0;i<2;i++){
            if(tr[rt][i]){
                flag=1;
                return;
            }
        }
    }
}

int main(){
    int x=0;
    for(int cas=1;;cas++){
        cnt=-1;
        newNode();
        flag=0;
        while(1){
            if(scanf("%s",s) == EOF){
                x=1;
                break;
            }
            if(s[0] == '9')
                break;
            if(!flag)
                insertWord();
        }
        if(x)
            break;
        if(!flag)
            printf("Set %d is immediately decodable\n",cas);
        else
            printf("Set %d is not immediately decodable\n",cas);
    }
    return 0;
}
