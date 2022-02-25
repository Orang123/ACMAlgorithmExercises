/*
题意:摘自网上
给定一个字符串，判断该字符串是否由两个非空的回文串组成，
在判断是否是一个回文。
字符串长度<=200000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2988
思路:manacher.把连续相同的字符缩写成一个字符,之后
进行manacher求解回文半径,答案是 最大的回文半径/2.
*/
//ac 80ms 判断遍历<len
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

char s1[N],s2[N<<1];
int n,p[N<<1],id,mx,len,maxLen;

void manacher(){
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    maxLen=mx=0;
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
        if(p[i]-1>maxLen)
            maxLen=p[i]-1;
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s1);
        n=len=strlen(s1);
        manacher();
        int flag=0;
        for(int i=2;i<len;i++){
            if(p[i] == i){
                int r=p[i]+i;
                int mid=(r+len-1)/2;
                //r<len 不然对于aabaa,i == 6时,mid=11,mid+p[mid] == 12(len) 这样会错判 能分割成两个回文串
                if(r<len && mid+p[mid] == len){
                    flag=1;
                    break;
                }
            }
        }
        if(flag)//能分割成2个回文串
            printf("alindrome\n");
        else{
            if(maxLen == n)//原串是回文串
                printf("palindrome\n");
            else//原串不是回文串
                printf("simple\n");
        }
    }
    return 0;
}

/*
//ac 80ms 判断遍历 到<len/2
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

char s1[N],s2[N<<1];
int n,p[N<<1],id,mx,len,maxLen;

void manacher(){
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    maxLen=mx=0;
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
        if(p[i]-1>maxLen)
            maxLen=p[i]-1;
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s1);
        n=len=strlen(s1);
        manacher();
        int flag=0;
        for(int i=2;i<len/2;i++){
            if(p[i] == i){
                int r=p[i]+i;
                int mid=(r+len-1)/2;
                if(mid+p[mid] == len){
                    flag=1;
                    break;
                }
            }
        }
        if(flag)
            printf("alindrome\n");
        else{
            if(maxLen == n)
                printf("palindrome\n");
            else
                printf("simple\n");
        }
    }
    return 0;
}
*/
