/*
题意:给你一个长为n的字符串，求不同的子串的个数。
我们定义两个子串不同，当且仅当有这两个子串长度不一样
或者长度一样且有任意一位不一样。
子串的定义：原字符串中连续的一段字符组成的字符串。
输出不一样的子串个数。
n<=10^5
链接:https://www.luogu.com.cn/problem/P2408
思路:后缀数组.利用height数组的性质.
通过所有可能的后缀减去 字典序相邻的后缀的最长公共前缀,因为字典序相邻的匹配程度肯定最大,
具体子串的个数是通过每个后缀的前缀去枚举的,但前面的字典序可能出现过某个前缀因此要去重,因此减去height[i]
n-sa[i]+1是排名为i的后缀的所有前缀的个数因为sa[i]是下标,所以+1才是后缀的长度,,但由于排名为i的后缀的前缀
一部分前缀已经被排名为i-1的后缀累加过了,因此要减去重复的公共前缀,即减去height[i](排名为i的后缀和排名为i-1
的后缀的最长公共前缀,也就是实际重复累加的所有前缀的个数)
*/

/*
lcp(i,j):表示后缀下标从i开始和后缀下标从j开始的2个后缀的最长公共前缀的长度.
lcp:Longest Common Prefix.
height[i]=lcp(sa[i],sa[i-1])
height[i]表示排名第i的后缀和排名第i-1的后缀的最长公共前缀的长度.(i>=2,i==1时不存在 排名为0的后缀,无意义)
height[1]可以视作0.
height[rk[i]]>=height[rk[i-1]]-1  i为后缀的起始下标,height[rk[i]]前缀最少匹配了height[rk[i-1]]-1
可以通过这个性质在O(n)时间内快速求解height数组.
*/

//ac 145ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000100
char s[N];
int sa[N],rk[N],oldRk[N],cnt[N],id[N],height[N];

//时间复杂度 O(5nlog(n))=O(nlog(n))
void SA(int n){
    int p,k=max(n,126);
    for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
    for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;

    for(int w=1;w<n;w<<=1){//O(log(n))
        p=1;
        for(int i=n;i>n-w;i--) id[p++]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>w) id[p++]=sa[i]-w;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) ++cnt[rk[i]];//O(n)
        for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldRk,rk,sizeof(rk));
        k=0;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=(oldRk[sa[i-1]]==oldRk[sa[i]] && oldRk[sa[i-1]+w]==oldRk[sa[i]+w])?k:++k;
        if(k==n) return;
    }
}

/*
void initHeight(int n){
    for(int i=1,j,k=0;i<=n;i++){
        if(rk[i]==1) continue;
        //对于跳过的rk[i]=1,因为height[rk[i]]>=height[rk[i-1]]-1,实际k值所能匹配的最大公共前缀的数目是可以接着之前的配对的
        if(k) k--;
        j=sa[rk[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
}
*/

//O(n)
void initHeight(int n){//证明用到了 lcp=min(height)那条性质
    for(int i=1,j,k;i<=n;i++){
        if(rk[i]==1) continue;//只有height[1]是不计算的,因为排名为1和排名为0的后缀的最长公共前缀无意义,不存在排名为0的后缀
        j=sa[rk[i]-1];
        //height[rk[i]]>=height[rk[i-1]]-1  i为后缀的起始下标,height[rk[i]]前缀最少匹配了height[rk[i-1]]-1,
        //可以减少不必要的比较,增大步长,height[rk[i-1]]有可能本身就为0,height[rk[i-1]]-1为-1,这时k取0
        //对于height[rk[i-1]=1]的情况,因为height[1]是无意义的,没有排名为0的后缀,这时k是从0开始对比的
        k=max(0,height[rk[i-1]]-1);
        //所有的n次循环这里的while k最大为n,也就是说n次循环 while只判断了O(n),
        //这个判断的起始下标是随着上个rk[i-1]继续累加判断的,所以总共只会判断n个字符
        //因此整个计算height的时间复杂度为O(n)这个while的可以作为常数忽略
        while(s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
}

int main(){
    int n;
    long long sum=0;
    scanf("%d",&n);
    scanf("%s",s+1);
    SA(n);
    initHeight(n);
    for(int i=1;i<=n;i++)
        //通过所有可能的后缀减去 字典序相邻的后缀的最长公共前缀,因为字典序相邻的匹配程度肯定最大,
        //具体子串的个数是通过每个后缀的前缀去枚举的,但前面的字典序可能出现过某个前缀因此要去重,因此减去height[i]
        //n-sa[i]+1是排名为i的后缀的所有前缀的个数因为sa[i]是下标,所以+1才是后缀的长度,,但由于排名为i的后缀的前缀
        //一部分前缀已经被排名为i-1的后缀累加过了,因此要减去重复的公共前缀,即减去height[i](排名为i的后缀和排名为i-1
        //的后缀的最长公共前缀,也就是实际重复累加的所有前缀的个数)
        sum+=n-sa[i]+1-height[i];
    printf("%lld\n",sum);
    return 0;
}

/*
//ac sam 162ms
#include<cstdio>
#include<cstring>
#define N 100100
struct node{
    int ch[26],fa,len;
    node(){
        memset(ch,0,sizeof(ch));
        len=0;
    }
}t[N<<1];
char s[N];
int last=1,tot=1;
long long dp[N<<1];

void SAM(int c){
    int p=last,np=last=++tot;
    t[np].len=t[p].len+1;
    for(;p&&!t[p].ch[c];p=t[p].fa) t[p].ch[c]=np;
    if(!p) t[np].fa=1;
    else{
        int q=t[p].ch[c];
        if(t[q].len==t[p].len+1) t[np].fa=q;
        else{
            int nq=++tot;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].fa=t[np].fa=nq;
            for(;p&&t[p].ch[c]==q;p=t[p].fa) t[p].ch[c]=nq;
        }
    }
}

int main(){
    int n;
    long long sum=0;
    scanf("%d",&n);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        SAM(s[i]-'a');
    for(int i=2;i<=tot;i++)
        sum+=t[i].len-t[t[i].fa].len;
    printf("%lld\n", sum);
    return 0;
}
*/
