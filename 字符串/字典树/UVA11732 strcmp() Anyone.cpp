/*
题意:摘自网上
给出n个字符串, 计算两两比较的次数. 每次比较都需要比较
(str1[i] == str2[i])和 (str1[i] == '\0'各一次).
n<=4000,字符串长度<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2832
思路:字典树.
思路参考自博客:https://www.cnblogs.com/TheRoadToTheGold/p/6958455.html
每两个字符串，要么全部匹配，要么中间停止匹配
如果全部匹配，比较次数为 2*len+2（‘\0’两次匹配）
如果中间停止匹配，比较次数为 2*相同前缀长度+1 （1次失败匹配后退出）
所以
1、对于第i个字符串，先加上i-1，即假设全部 中间停止匹配
这样最后再加上全部匹配数
2、匹配一个就+sum*2
*/
//ac 730ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4000010
#define M 1100
using namespace std;
typedef long long ll;

//end0表示字符串结尾的'\0'的配对.
int n,tr[N][62],end0[N],sum[N],cnt;
char s[M];
ll ans;//计数非常大,要用ll,否则会溢出wa

int newNode(){
    cnt++;
    for(int i=0;i<62;i++)
        tr[cnt][i]=0;
    sum[cnt]=end0[cnt]=0;
    return cnt;
}

int check(char x){
    if(x>='0' && x<='9')
        return x-'0';
    if(x>='a' && x<='z')
        return x-'a'+10;
    if(x>='A' && x<='Z')
        return x-'A'+36;
}

void insertWord(int num){
    ans+=num;//这里是假设和前面i-1个都没有完全配对,即最后只配对比较一次
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=check(s[i]);
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        ans+=sum[rt]*2;//当前字符串和前面输入的字符串前缀配对,因为每个 都是2次
        sum[rt]++;
    }
    ans+=end0[rt];//这里是计算末尾'\0' 完全配对,这样就能把前面 ans+=num的 i-1字符串假设没有完全配对的补足配对的次数
    end0[rt]++;
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        cnt=-1;
        newNode();
        ans=0;
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            insertWord(i-1);
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
