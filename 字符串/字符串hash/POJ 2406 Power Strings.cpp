/*
题意:给你一个字符串,让你求这个字符串是由多少个相同的子串构成的,
要求子串数量尽量多.这些子串之间不能有重叠,即位置不能有交集,必须
是分隔且刚好紧邻连续的.
释义:
给定一个串,求其一个重复不重叠子串,重复次数的最大值,
也就是串最小循环节,最小周期.
字符串长度不会超过10^6
链接:http://poj.org/problem?id=2406
思路:next数组和循环节存在这样一个性质.以下内容摘自https://blog.csdn.net/wangcong9614/article/details/47271539
长度为len的字符串，最小循环节的长度是len-next[len]，我们把它定为s。
那么如果len%s==0，也就是字符串长度能整除循环节长度，就说明这个字符串是完全循环的，
也就是类似abcabc、ababab的情况。那么在本题中，如果字符串是完全循环完毕的，我们只
要输出len/s就ok了。如果len%s!=0，说明字符串不是完全循环完毕的，比如abcdab、abcabce这样，
我们输出1就好了。
对于aabaabaa,next[8]=5,8%(8-5)!=0,实际整个串的最长相同前后缀是aabaa(前缀下标范围0~4)
aabaa(后缀下标范围3~7),发现3~4这两个位置的子串"aa"是重叠的,并不构成连续分隔的子串,
也就是并不构成循环节,那么对于len不能整除(len-next[len])的情况,就是整个串作为一个单独
的循环节,输出1.

注意j-nxt[j]求得是最短循环节的长度,j/(j-nxt[j])是最多的循环次数.
而j-nxt[tp],nxt[tp]<nxt[j],j-nxt[tp]求得的不是最短循环节,循环节较大,循环次数较少.
*/
//ac 392ms 字符串hash
#include<cstdio>
#include<cstring>
#define p 233
#define N 1000100
typedef unsigned long long ull;
ull h[N],powr[N];
char s[N];
int len;
bool check(int x,ull hVal){
    for(int i=x;i<=len-x;i+=x){
        if(h[i+x]-h[i]*powr[x] != hVal)
            return false;
    }
    return true;
}
int main(){
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1) && strcmp(s+1,".")!=0){
        len=strlen(s+1);
        h[0]=0;
        for(int i=1;i<N;i++)
            h[i]=h[i-1]*p+(s[i]-'a'+1);
        for(int i=1;i<=len;i++){
            if(len % i == 0 && check(i,h[i])){
                printf("%d\n",len/i);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 125ms 下标从0开始 next数组应用求解最小循环节 kmp
#include<cstdio>
#include<cstring>
#define N 1000010

int next[N],len;
char str[N];

void getNext(){
    len=strlen(str);
    int i=-1,j=0;
    next[0]=-1;
    while(j<len){
        if(i == -1 || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    while(scanf("%s",str) && str[0]!='.'){
        getNext();
        if(len%(len-next[len]) == 0)
            printf("%d\n",len/(len-next[len]));
        else
            printf("1\n");
    }
    return 0;
}
*/

/*
//ac 110ms 下标从1开始
#include<cstdio>
#include<cstring>
#define N 1000010

int next[N],len;
char str[N];

void getNext(){
    len=strlen(str+1);
    int i=0,j=1;
    next[1]=0;
    while(j<=len){
        if(!i || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    while(scanf("%s",str+1) && str[1]!='.'){
        getNext();
        if(len%(len+1-next[len+1]) == 0)
            printf("%d\n",len/(len+1-next[len+1]));
        else
            printf("1\n");
    }
    return 0;
}
*/
