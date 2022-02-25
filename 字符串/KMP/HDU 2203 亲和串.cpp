/*
题意:摘自网上
给定两个字符串s1和s2,如果能通过s1循环移位，使s2包含在s1中，那么我们就说s2是s1的亲和串。
s1,s2<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2203
思路:直接枚举移位n次,每次做一次kmp,复杂度O(n^2),n<=10^5,显然不行,
可以将s1拼接起来首尾相接,长度2n,只做一次kmp便可在O(s1len*2+s2len)时间
内求出是否包含.
*/
//ac 15ms 普通next数组
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N<<1],p[N],tp[N];

void getNext(char *p){
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
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j == plen;
}

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);//直接用s拼接s strcat(s,s)会死循环,得先复制一个才行
        printf("%s\n",kmp()?"yes":"no");
    }
    return 0;
}

/*
//ac 15ms strstr函数使用,这个复杂度 一般是比kmp要大的
//strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
//如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。
#include<cstdio>
#include<cstring>
#define N 100100

char s[N<<1],p[N],tp[N];

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);
        printf("%s\n",strstr(s,p)?"yes":"no");
    }
    return 0;
}
*/

/*
strstr函数原型
函数原型 strstr（char *a， char *b），在a中是否包含b这个字符串，
包含返回第一个子串的位置，否则返回NULL。
思路：其实这个就是找子串的问题。特殊情况，当b为空的时候，直接返回a；
当b不为空的时候，指定start指针，通过两次循环，逐一对strstr中的子串和b进行匹配，
如果b走到末尾，表示找到，start指针指向开始位置，否则start继续往前，
//复杂度O(slen*plen) 就是个暴力做法
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        if (!*needle)
            return haystack;
        char *start = haystack;
        char *temp1 = haystack, *temp2 = needle;
        while (*start){
            temp1 = start;
            temp2 = needle;
            while (*temp2 && temp1 && !(*temp2 - *temp1))
                temp2++, temp1++;
            if (!*temp2)
                return start;
            start++;
        }
        return NULL;
    }
};
*/

/*
//ac 0ms next数组优化
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N<<1],p[N],tp[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j]){
        	if(p[++i] != p[++j])
        		next[j]=i;
        	else
        		next[j]=next[i];
		}
        else
            i=next[i];
    }
}

int kmp(){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j == plen;
}

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);
        printf("%s\n",kmp()?"yes":"no");
    }
    return 0;
}
*/
