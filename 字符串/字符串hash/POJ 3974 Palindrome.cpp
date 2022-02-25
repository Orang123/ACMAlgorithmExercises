/*
题意:求最长回文子串的长度
链接:http://poj.org/problem?id=3974
思路:manacher裸题,或字符串hash.
*/
//ac 594ms 最长回文串长度线性增加回文半径 非二分
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007也可
#define N 1000100
using namespace std;
typedef unsigned long long ull;
ull h1[N*2],h2[N*2],powr[N];
char s[N],str[2*N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    int index=1;
    while(scanf("%s",s+1) && strcmp(s+1,"END")){
        len=strlen(s+1);
        int j=0;
        for(int i=1;i<=len;i++){
            str[++j]='#';
            str[++j]=s[i];
        }
        str[++j]='#';
        h1[0]=0;
        for(int i=1;i<=j;i++)
            h1[i]=h1[i-1]*p+(str[i]-'a'+1);
        h2[j+1]=0;
        for(int i=j;i>=1;i--)
            h2[i]=h2[i+1]*p+(str[i]-'a'+1);
        int l=0;
        for(int i=1;i<=j;i++){//枚举回文对称中心点
            if(i-l<1 || i+l>j) break;//如果某个中心点 尝试当前最长回文半径越界,后面的点只会更不对称,回文半径便不可再增加,即结束
            while(h1[i-1]-h1[i-l-1]*powr[l] == h2[i+1]-h2[i+l+1]*powr[l] && i-l>=1 && i+l<=j) l++;//若左右子串对称的hash值相等就依次线性增加回文半径
        }
        printf("Case %d: %d\n",index,l-1);//因为str是添加#预处理之后的回文半径就是这个回文串的长度
        index++;
    }
    return 0;
}
