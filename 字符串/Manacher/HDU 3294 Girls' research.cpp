/*
题意:摘自网上
给定一个字符和一个字符串，求转化后字符串出现的第一个最长回文
（即有很多相同长度，输出第一个），并输出起始终点位置，以及转
化后的回文串。
字符串长度<=200000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3294
思路:manacher.记录最大回文子串的在原串中的起始位置(i-p[i])/2.
则其实起始下标和终点下标为:(i-p[i])/2,(i-p[i])/2+maxLen-1.
最后输出转换后的字符串.
*/
//ac 187ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

char s1[N],s2[N<<1],mp[26];
int p[N<<1],id,mx,len,pos,maxLen;

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
    mx=maxLen=0;
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
        if(p[i]-1>maxLen){
            maxLen=p[i]-1;
            pos=(i-p[i])/2;
        }
    }
}

int main(){
    char x;
    mp[0]='z';
    for(int i=1;i<26;i++)
        mp[i]='a'+i-1;
    while(scanf("%c %s",&x,s1)!=EOF){
        getchar();
        manacher();
        if(maxLen<=1)
            printf("No solution!\n");
        else{
            int ed;
            ed=pos+maxLen-1;
            printf("%d %d\n",pos,ed);
            for(int i=pos;i<=ed;i++){
                int j=s1[i]-x;
                j++;
                j+=26;//避免出现下标为负,加26 再对26取余
                j%=26;
                printf("%c",mp[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
