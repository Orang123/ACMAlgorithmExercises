/*
题意:摘自网上
给定一个字符串，向某个位置插入一个字符C使得两个或多个字符C相邻，
然后消除这些字符，消除后得到左右两个新字符串，连接两个新字符串，
如果连接处是两个或多个相同的字符，则同样消除掉，以此类推.
字符串长度<=100000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3800
思路:manacher.把连续相同的字符缩写成一个字符,之后
进行manacher求解回文半径,答案是 最大的回文半径/2.
*/
//ac 10ms
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
        if(s1[i] == s1[i+1])
            continue;
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';//这个s2末尾要加上'\0',否则会导致,不同样例 在对比向两边扩展对比时 超出数组范围时,之前s2存储的值会影响回文半径的大小.
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
        if(p[i]>ans)
            ans=p[i];
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%s",s1);
        manacher();
        printf("%d\n",ans/2);
    }
    return 0;
}
