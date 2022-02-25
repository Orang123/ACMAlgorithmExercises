/*
题意:给出一个字符串，让你往后添加最少的字符，使其成为回文串。
字符个数<=10^5.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2470
思路:可以将原串s翻转作为模式串p,在s中去匹配p,找出模式串p
能匹配到的位置,那么p最后剩下的后缀字符就是最少要添加的字符,
便能使其成为回文.
*/
//ac 0ms 原串s翻转成p模式串去匹配原串s
#include<cstdio>
#include<cstring>
#define N 100010

int nxt[N],len;
char s[N],p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(){
    getNext();
    int i=0,j=0;
    while(i<len){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=nxt[j];
    }
    return j;
}

int main(){
    while(scanf("%s",s)!=EOF){
        len=strlen(s);
        for(int i=0;i<len;i++)
            p[i]=s[len-i-1];
        p[len]='\0';
        printf("%s",s);
        printf("%s\n",p+kmp());
    }
    return 0;
}

/*
//ac 0ms 将原串翻转成p,再将原串s拼接到p的后面,
//之后nxt[2*len]倒置字符串的前缀与原字符串的后缀的最大匹配长度,要添加的字符就是下标在nxt[2*len]~len/2-1的范围
#include<cstdio>
#include<cstring>
#define N 100010

int nxt[N<<1],len;
char s[N],p[N<<1];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    while(scanf("%s",s)!=EOF){
        len=strlen(s);
        for(int i=0;i<len;i++)
            p[i]=s[len-i-1];
        p[len]='\0';
        strcat(p,s);
        len*=2;
        getNext();
        printf("%s",s);
        for(int i=nxt[len];i<len/2;i++)
        	printf("%c",p[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 20ms manacher
//manacher 求出第一个构成后缀的回文串,即:i+p[i] == len,这个回文子串前面的部分倒序就是需要补齐的部分
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

char s1[N],s2[N<<1];
int p[N<<1],id,mx,len,ans;

void manacher(){
    len=strlen(s1);
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    mx=0;
    for(int i=1;i<len;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        if(i+p[i] == len){
            ans=(i-p[i])/2;
            break;
        }
    }
}

int main(){
    while(scanf("%s",s1)!=EOF){
        manacher();
        printf("%s",s1);
        for(int i=ans-1;i>=0;i--)
            printf("%c",s1[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
hash的做法
*/
