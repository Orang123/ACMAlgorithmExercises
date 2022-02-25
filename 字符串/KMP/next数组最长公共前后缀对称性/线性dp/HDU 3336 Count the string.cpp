/*
题意:字符串的每个前缀在原字符串中出现的次数和.
可以前缀可以重叠出现.
字符串长度<=200000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3336
思路:根据求解出的next数组去dp.
dp[i]表示以p[i-1]字符结尾的前缀新出现的个数.
转移方程就是dp[i]=dp[nxt[i]]+1.
这里的dp[nxt[i]]是p[0~i-1]中p[nxt[i]~i]后缀中与前缀相等
新出现的前缀的个数.
+1是p[0~i-1]新出现的长度为i的前缀,第一次出现,所以次数+1.
初始状态dp[0]=0.
*/
/*
样例分析
abababa
"a", 长度与出现次数4
"ab",长度与出现次数3
"aba", 长度与出现次数3
"abab", 长度与出现次数2
"ababa", 长度与出现次数2
"ababab", 长度与出现次数1
"abababa", 长度与出现次数1
4+3+3+2+2+1+1=16
*/
//ac 46ms
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 10007

int nxt[N],plen,ans,dp[N];
char p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&plen);
        scanf("%s",p);
        getNext();
        dp[0]=0;
        //同的i,nxt[i]可能是相同的
        for(int i=1;i<=plen;i++){
            dp[i]=dp[nxt[i]]+1;
            ans=(ans+dp[i])%mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 62ms 记忆化搜索
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 10007

int nxt[N],plen,ans,dp[N];
char p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

//不同的i,nxt[i]可能是相同的,因此记忆化搜索先从i值较大的地方计算
int dfs(int i){
	if(!i)
		return 0;
	if(dp[i])
		return dp[i];
	dp[i]=(dfs(nxt[i])+1)%mod;
	return dp[i];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(dp,0,sizeof(dp));
        scanf("%d",&plen);
        scanf("%s",p);
        getNext();
        for(int i=plen;i>=1;i--)
        	ans=(ans+dfs(i))%mod;
        printf("%d\n",ans);
    }
    return 0;
}
*/
