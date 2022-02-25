/*
题意:摘自网上
给你两个字符串s,p，让你连接起来，没有前后顺序，要求是长度最短优先，
其次是字典序最小。
plen,slen<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1867
思路:用kmp 在s中匹配p,和在p中匹配s,输出匹配长度较大的情况,
如果长度一样,输出字典序较小的即可.
*/
//ac 46ms 普通next数组
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N],p[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    //因为模式串在文本串中间匹配完了后,并不能结束要根据next[plen]继续匹配,所以j<plen
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    //匹配结束条件是文本串到达末尾,而不是模式串匹配完成,因为主要考虑的是模式串的前缀和文本串的后缀匹配的最大长度
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j;
}

int main(){
    int len1,len2;
    while(scanf("%s %s",s,p)!=EOF){
        len1=kmp(s,p);
        len2=kmp(p,s);
        if(len1 == len2){
            if(strcmp(s,p)<0){
                printf("%s",s);
                printf("%s",p+len1);
            }
            else{
                printf("%s",p);
                printf("%s",s+len2);
            }
        }
        else if(len1>len2){
            printf("%s",s);
            printf("%s",p+len1);
        }
        else if(len1<len2){
            printf("%s",p);
            printf("%s",s+len2);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 46ms next数组优化
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N],p[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen){//因为会用到next[plen],所以j<plen
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

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j;
}

int main(){
    int len1,len2;
    while(scanf("%s %s",s,p)!=EOF){
        len1=kmp(s,p);
        len2=kmp(p,s);
        if(len1 == len2){
            if(strcmp(s,p)<0){
                printf("%s",s);
                printf("%s",p+len1);
            }
            else{
                printf("%s",p);
                printf("%s",s+len2);
            }
        }
        else if(len1>len2){
            printf("%s",s);
            printf("%s",p+len1);
        }
        else if(len1<len2){
            printf("%s",p);
            printf("%s",s+len2);
        }
        printf("\n");
    }
    return 0;
}
*/
