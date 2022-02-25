/*
题意:给出两个字符串，求最长公共子串的长度。
两个字符串长度<=10^5
链接:http://poj.org/problem?id=2774
思路:后缀数组,将两个字符串中间用'$'拼接起来,
根据height数组的性质,只要sa[i]或sa[i-1]的下标
在分隔符'$'的两边就可以合理表示两个字符串的
最长公共子串,而不会超过'$'发生两字符串重叠的相交
的情况,因为分隔符'$'保证了 lcp截止到'$'的位置.
*/
//ac 516ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

int n,sa[N],id[N],cnt[N],rk[N],oldrk[N],height[N];
char s[N],tp[N];

void SA(){
    int m;
    m=max(n,300);
    for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
    for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;
    for(int w=1;w<n;w<<=1){
        int p=0;
        for(int i=n;i>n-w;i--) id[++p]=i;
        for(int i=1;i<=n;i++){
            if(sa[i]>w)
                id[++p]=sa[i]-w;
        }
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) cnt[rk[i]]++;
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldrk,rk,sizeof(rk));
        int k=0;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=(oldrk[sa[i-1]] == oldrk[sa[i]] && oldrk[sa[i-1]+w] == oldrk[sa[i]+w])?k:++k;
        if(k == n) return;
        m=k;
    }
}

/*
//ac
void initHeight(){
    int j,k;
    for(int i=1;i<=n;i++){
        if(rk[i] == 1) continue;
        j=sa[rk[i]-1];
        k=max(0,height[rk[i-1]]-1);
        while(s[i+k] == s[j+k]) k++;
        height[rk[i]]=k;
    }
}
*/

void initHeight(){
    int j,k=0;
    for(int i=1;i<=n;i++){
        if(rk[i] == 1) continue;
        j=sa[rk[i]-1];
        if(k) k--;
        while(s[i+k] == s[j+k]) k++;
        height[rk[i]]=k;
    }
}

int main(){
    int len,ans=0;
    scanf("%s",s+1);
    scanf("%s",tp+1);
    n=strlen(s+1);
    s[n+1]='$';
    len=n+1;
    s[n+2]='\0';
    strcat(s+1,tp+1);
    n=strlen(s+1);
    SA();
    initHeight();
    for(int i=2;i<=n;i++){
        if(height[i]>ans){
            if(sa[i]<len && sa[i-1]>len)//只要排名为i和i-1的后缀 分别分布在分隔符'$'的两侧,就能保证lcp不会越过分隔符
                ans=height[i];
            if(sa[i]>len && sa[i-1]<len)
                ans=height[i];
        }
    }
    printf("%d",ans);
    return 0;
}
