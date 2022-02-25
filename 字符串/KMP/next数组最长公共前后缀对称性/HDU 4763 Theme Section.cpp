/*
题意:摘自网上
现有一字符串S，要求在S中找到最长的子串E，使得S满足格式“EAEBE”，
其中A，B可以为任意的S子串。也就是说子串E既是S的前缀也是S的后缀，
同时还在S中间出现，但不与前缀E与后缀E重叠。
字符串商都<=10^6.
说明:这3个"E"都是不会重叠的.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4763
思路:2种解法
解法1:枚举原串最长公共前后缀i,从文本串为s+i,长度为len-2*i,模式串为s,
长度为i,kmp判断文本串中是否存在模式串
解法2:枚举原串最长公共前后缀x,"EAEBE"中的前2/3,判断EAEB最长公共前后缀
是否大于等于x,若存在大于等于x的最长公共前后缀,则远程中间一定存在长度为x的E.
*/
//ac 46ms 枚举原串最长公共前后缀i,从文本串为s+i,长度为len-2*i,模式串为s,长度为i,kmp判断文本串中是否存在模式串
#include<cstdio>
#include<cstring>
#define N 1000100

int nxt[N],len;
char s[N];

void getNext(char *p){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,int slen,char *p,int plen){
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=nxt[j];
    }
    return j == plen;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        len=strlen(s);
        getNext(s);
        int i=len;
        while(i){
            i=nxt[i];
            if(i<=len/3 && kmp(s+i,len-2*i,s,i))//i>len/3的话 有可能重叠
                break;//第一次满足 直接结束,因为是最长子串E
        }
        printf("%d\n",i);
    }
    return 0;
}

/*
//ac 31ms 枚举原串最长公共前后缀x,"EAEBE"中的前2/3,
//判断EAEB最长公共前后缀是否大于等于x,若存在大于等于x的最长公共前后缀,则远程中间一定存在长度为x的E,则输出
#include<cstdio>
#include<cstring>
#define N 1000100

int nxt[N],len;
char s[N];

void getNext(char *p){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int check(int x){
    //判断前2/3的子串“EAEB”的最长公共前后缀是否大于等于 之前枚举的原串的最长公共前后缀x的长度,若大于等于,则中间一定存在E
	for(int i=x*2;i<=len-x;i++){
		if(nxt[i]>=x)
			return 1;
	}
	return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        len=strlen(s);
        getNext(s);
        int i=len;
        while(i){
            i=nxt[i];
            if(i<=len/3 && check(i))
                break;
        }
        printf("%d\n",i);
    }
    return 0;
}
*/
