/*
题意:给你两个字符串s和p，求s中包含了几个不重叠的p串。
slen,plen<=1000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2087
思路:和POJ 3461很像,只是那道题可以重叠,这道题不可重叠,
那么在匹配时,当模式串p匹配完后,计数+1,p的下标j需要从0
从头开始匹配.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#define N 1010

int slen,plen,next[N];
char s[N],p[N];

void getNext(){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(){
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
        if(j == plen){
            cnt++;
            j=0;
        }
    }
    return cnt;
}

int main(){
    while(scanf("%s",s) && s[0]!='#'){
        scanf("%s",p);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}
