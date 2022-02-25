/*
题意:摘自网上
给你一个串,要你在串头或尾添加最少的字符,使得该串至少有2个循环节,
问你最少需要加几个字符.
plen<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3746
思路:k=len-next[len]是循环节长度,如果next[len]为0,则说明,
需要把原先整个串复制一遍,才能有2个循环节.
如果len%(k)不为0,则说明并不能构成循环节,需要添加
的字符个数为k-len%k.
如果len%k为0,则说明原先本身就能构成完整的循环节,且个数至少为2.
下面博客有详细的分析,但没太看懂:
https://blog.csdn.net/u013480600/article/details/22954037
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#define N 100010

int plen,nxt[N];
char p[N];

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T,k;
    scanf("%d",&T);
    while(T--){
        scanf("%s",p);
        getNext();
        k=plen-nxt[plen];
        if(!nxt[plen])//需要把整个串再复制一遍
            printf("%d\n",plen);
        else if(plen%k)//不整除 原先整个串并不构成循环节,需要添加字符
            printf("%d\n",k-plen%k);
        else if(plen%k == 0)//整除 本身就能构成至少2个循环节
            printf("0\n");
    }
    return 0;
}
