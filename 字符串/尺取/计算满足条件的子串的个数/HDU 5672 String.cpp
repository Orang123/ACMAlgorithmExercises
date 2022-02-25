/*
题意:摘自网上
给T组样例，每组样例第一行是一串字符串s，第二行是一个整数k，
查找子字符串中至少含有k个不同字母的子字符串的个数.
10<=|s|<=10^6.1<=k<=26.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5672
思路:尺取.右指针移动条件是当当前[l,r]子串中含有不同字母
的个数未达到k个时,右指针向右移动.
*/
//ac 530ms
//下标从0开始,++r,++l,初始化r=l=-1
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=-1;
        while(1){//结束条件不能是r<len-1,因为右指针到达末尾时,随着l不断左移,当前子串 含有不同字母个数还是k个,这时还需要累加子串个数.
            while(r<len-1 && !check())
                num[s[++r]-'a']++;
            if(!check())//结束条件是 当右指针移动当尾端,当前子串[l,r]子串含有的不同字母个数也未达到k个
                break;
            //这里可能r 是不变的,l一直在向前移动,可能连续字符代表的字母相同,当前子串中不同字母个数一直满足k个
            //这里实际满足条件的子串是[l,r] [l,r+1] [l,r+2] ...[l,len-1] 因此是累加的个数是len-r
            ans+=len-r;
            num[s[++l]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 140ms cnt直接记录是否达到了k个不同的字符,无需循环判断
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26],cnt;
ll ans;
char s[N];

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=-1;
        cnt=0;
        while(1){
            while(r<len-1 && cnt!=k){
            	if(!num[s[++r]-'a'])
            		cnt++;
            	num[s[r]-'a']++;
			}
            if(cnt!=k)
                break;
            ans+=len-r;
            num[s[++l]-'a']--;
            if(!num[s[l]-'a'])
            	cnt--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 546ms
//下标从0开始,r++,l++,初始化r=l=0
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s);
        scanf("%d",&k);
        len=strlen(s);
        l=r=0;
        while(1){
            while(r<len && !check())
                num[s[r++]-'a']++;
            if(!check())
                break;
            ans+=len-r+1;
            num[s[l++]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 608ms
//下标从1开始,++r,++l,初始化r=l=0
#include<cstdio>
#include<cstring>
#define N 1000010
typedef long long ll;

int k,num[26];
ll ans;
char s[N];

int check(){
    int cnt=0;
    for(int i=0;i<26;i++){
        if(num[i])
            cnt++;
    }
    return cnt == k;
}

int main(){
    int T,l,r,len;
    scanf("%d",&T);
    while(T--){
        memset(num,0,sizeof(num));
        ans=0;
        scanf("%s",s+1);
        scanf("%d",&k);
        len=strlen(s+1);
        l=r=0;
        while(1){
            while(r<len && !check())
                num[s[++r]-'a']++;
            if(!check())
                break;
            ans+=len-r+1;
            num[s[++l]-'a']--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/

