/*
题意:
n个的串，求出它们的最长公共子串，如果不存在这个子串，则输出“IDENTITY LOST”，
如果存在多个最长公共子串，则输出字典序最小的那一个。
n<=4000,每个串长度<=200.
链接:http://poj.org/problem?id=3450
思路:枚举第一个串的各个后缀去和其余串匹配,求出最小的匹配长度,
在各个最小匹配长度下取最大的匹配长度,如果长度一样,则取字典序较小的.

自己在下面写了个二分最大长度的做法,但是pos第一个样例输出了个错误的35,不知何原因
*/
//ac 422ms 枚举第一个串的各个子串分别和剩下的串开始匹配,记录最小的公共子串,再在各个公共子串中输出最大的
//时间复杂度O(200*4000*200)=1.6*10^8 按道理是很耗时的,但也过了
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,plen,ans;
char s[N][M];

void getNext(char *p){
    plen=strlen(p);
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
            cnt=max(cnt,j);//记录最大的匹配长度
        }
        else
            j=nxt[j];
    }
    return cnt;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        //O(200*4000*200)=1.6*10^8 按道理是很耗时的,但也过了
        for(int i=0;i<len;i++){//第一个串从位置i开始的后缀
            tp=INF;
            for(int j=1;j<n;j++)//s[0]+i作为模式串去和其它串匹配 求最小公共匹配长度,便是当前公共子串
                tp=min(tp,kmp(s[j],s[0]+i));
            if(tp>ans || (tp == ans && strcmp(s[0]+i,s[0]+pos)<0)){
                ans=tp;//记录公共子串长度
                pos=i;//记录后缀开始的位置
            }
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0][i]);
        }
        else//不存在公共子串
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}

/*
//ac 438ms 按照长度从小到大排序,选择长度最小的子串作为模式串和其它文本串匹配
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,plen,ans;
struct S{
	char str[M];
	int len;
	bool operator <(const S &x)const{
		return len<x.len;//按照长度从小到达排序
	}
}s[N];

void getNext(char *p){
    plen=strlen(p);
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
            cnt=max(cnt,j);
        }
        else
            j=nxt[j];
    }
    return cnt;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++){
            scanf("%s",s[i].str);
        	s[i].len=strlen(s[i].str);
		}
		sort(s,s+n);
        for(int i=0;i<s[0].len;i++){
            tp=INF;
            for(int j=1;j<n;j++)
                tp=min(tp,kmp(s[j].str,s[0].str+i));
            if(tp>ans || (tp == ans && strcmp(s[0].str+i,s[0].str+pos)<0)){
                ans=tp;
                pos=i;
            }
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0].str[i]);
        }
        else
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 360ms strstr函数 枚举第一个串的所有子串
//strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
//如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,len,ans;
char s[N][M],str[M];

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        for(int i=0;i<len;i++){//枚举第一个串的初始位置
        	int k=0;
        	for(int j=i;j<len;j++){//枚举第一个串的结束位置j
        		str[k++]=s[0][j];
        		str[k]='\0';
        		int flag=0;
        		for(int j=1;j<n;j++){//判断其余串是否包含str
        			if(!strstr(s[j],str)){//如果存在一个串不包含这个子串str,则说明str不是最长公共子串
        				flag=1;
        				break;
					}
				}
				if(!flag && (k>ans || (k == ans && strcmp(str,s[0]+pos)<0))){
        			ans=k;
        			pos=i;
				}
			}
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0][i]);
        }
        else
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/

/*
//参考博客:https://blog.csdn.net/kalilili/article/details/43868029
//我自己写的二分答案 有点问题
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,pos;
char s[N][M];

void getNext(char *p,int plen){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p,int plen){
    getNext(p,plen);
    slen=strlen(s);
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

int check(int mid){
	int flag1,flag2=0;
	pos=-1;
	printf("len-mid=%d\n",len-mid);
	for(int i=0;i<=len-mid;i++){
		flag1=0;
		for(int j=1;j<n;j++){
			if(!kmp(s[j],s[0]+i,mid)){
				flag1=1;
				break;
			}
		}
		if(!flag1 && (pos == -1 || strcmp(s[0]+i,s[0]+pos))){
			pos=i;
			printf("pos=%d\n",pos);//不知为为什么第一个样例 最后一个pos会莫名等于35。。。
			flag2=1;
		}
	}
	return flag2;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        int l=0,r=len,mid;
        while(l<r){
        	mid=(l+r)/2;
        	//printf("mid=%d\n",mid);
        	if(check(mid))
        		l=mid+1;
        	else
        		r=mid;
		}
		printf("pos=%d\n",pos);
        if(mid){
            for(int i=pos;i<pos+mid;i++)
                printf("%c",s[0][i]);
        }
        else//不存在公共子串
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/
