/*
题意:摘自网上
定义一个字符串的最大值值为：
该字符串各个前缀出现的次数与对应前缀的长度的乘积的最大值。
给定一个字符串，求该字符串的最大值。
plen<=10^5.
说明:前缀出现次数计算时,子串之间可以重叠.
链接:https://www.51nod.com/Challenge/Problem.html#problemId=1277
思路:仍然是next数组的对称性,初始每个前缀出现次数都是1,需要考虑
1~plen长度下的nxt数组的最长公共前后缀对称性,累加出现的次数,
即:cnt[nxt[i]]+=cnt[i].
长度为i的前缀,其nxt[i]表示其对应相同的前缀,这个长度为i的前缀的后缀中
出现 对应的长度为nxt[i]的前缀,因此cnt[nxt[i]]+=cnt[i],不同i对应的nxt[i]
可能是相同的.
*/
//ac 31ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

int plen,nxt[N];
ll cnt[N],ans;
char p[N];

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    scanf("%s",p);
    getNext();
    for(int i=plen;i>=1;i--){
        cnt[i]++;//长度为i的前缀整体出现一次 不能直接赋值,cnt[i]可能本身就有数值,值长度更长的前缀的后缀中出现过
        cnt[nxt[i]]+=cnt[i];
    }
    for(ll i=1;i<=plen;i++){
        //printf("cnt[%lld]=%lld\n",i,cnt[i]);
        ans=max(ans,i*cnt[i]);
    }
    printf("%lld",ans);
    return 0;
}
