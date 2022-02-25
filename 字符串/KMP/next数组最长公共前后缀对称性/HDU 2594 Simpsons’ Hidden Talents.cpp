/*
题意:摘自网上
给两个字符串p和s, 求出是p的前缀且是s的后缀的最长的字符串
plen,slen<=50000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2594
思路:类似POJ 2752,可以将s拼接到p的后面,然后根据next数组
的对称性,找到最长得到前后缀,但要注意长度不能大于原先s和p
的原始串的长度,不然就不是原串的前缀或后缀了.
*/
//ac 15ms
#include<cstdio>
#include<cstring>
#define N 50010

int plen,nxt[N<<1];
char p[N<<1],s[N];

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
    int len1,len2;
    while(scanf("%s %s",p,s)!=EOF){
        len1=strlen(p);
        len2=strlen(s);
        strcat(p,s);
        getNext();
        if(!nxt[plen]){
            printf("0\n");
            continue;
        }
        int i=plen;
        while(nxt[i]>len1 || nxt[i]>len2)//必须同时满足nxt[i]<=len1 && nxt[i]<=len2的最大长度
            i=nxt[i];
        p[nxt[i]]='\0';
        printf("%s %d\n",p,nxt[i]);
    }
    return 0;
}
