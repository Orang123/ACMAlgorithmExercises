/*
题意:给你两个字符串p和s，求出p在s中出现的次数。
plen<=10^4,slen<=10^6.
注意:出现的子串之间是可以重叠的,因此这并不是循环节的问题.
链接:http://poj.org/problem?id=3461
思路:kmp 求p在s中匹配,当p匹配完成时,令p的下标j=next[j],这样
便可继续匹配,每次p==plen时,计数+1.
*/
//ac 79ms 下标从0开始
#include<cstdio>
#include<cstring>
#define N 10010
#define M 1000010

int slen,plen,next[N];
char s[M],p[N];

void getNext(){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen){//因为会用到next[plen],所以j<plen
        if(i == -1 || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(){
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
        if(j == plen){
            cnt++;
            j=next[j];
        }
    }
    return cnt;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",p);
        scanf("%s",s);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}

/*
//ac 125ms 下标从1开始
#include<cstdio>
#include<cstring>
#define N 10010
#define M 1000010

int slen,plen,next[N];
char s[M],p[N];

void getNext(){
    plen=strlen(p+1);
    next[1]=0;
    int i=0,j=1;
    while(j<=plen){
        if(!i || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(){
    slen=strlen(s+1);
    int i=1,j=1,cnt=0;
    while(i<=slen){
        if(!j || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
        if(j == plen+1){
            cnt++;
            j=next[j];
        }
    }
    return cnt;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",p+1);
        scanf("%s",s+1);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}
*/

/*
//ac 235ms 字符串hash
//这里所采用的的hash函数为 BKDR Hash
//hash前缀:hash[i]=(hash[i-1]*p+idx(s[i]))%mod idx=s[i]-'a'+1
//p取一个6到8位的素数，避免发生冲突，即避免不同的子串映射结果相同，
//mod取一个大素数，一般取1e9+7或1e9+9,利用unsigned long long的范围自然溢出：
//即当存储的数据大于unsigned long long的存储范围时，会自动mod 264−1，
//就不用mod其他质数来保证唯一性了。
//hash子串 hash[r,l]=(hash[r]-hash[l-1]*p^(r-l+1))%mod p的指数为其字符串长度
//详情参考:http://planetmath.org/goodhashtableprimes
#include<cstdio>
#include<cstring>
#define p 233 //1000007也可 若结果错误 可换别的大素数试试
#define N2 1000100
#define N1 10100
typedef unsigned long long ull;
ull h[N2],powr[N1],s;
char w[N1],t[N2];
int main(){
    int T,len1,len2,ans;
    powr[0]=1;
    for(int i=1;i<N1;i++)
        powr[i]=powr[i-1]*p;//powr[i]=p^i
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%s",w+1);
        scanf("%s",t+1);
        len1=strlen(w+1);
        len2=strlen(t+1);
        s=0;
        for(int i=1;i<=len1;i++)
            s=s*p+(w[i]-'A'+1);
        h[0]=0;
        for(int i=1;i<=len2;i++)
            h[i]=h[i-1]*p+(t[i]-'A'+1);
        for(int i=0;i<=len2-len1;i++)
            if(h[i+len1]-h[i]*powr[len1] == s)
                ans++;
        printf("%d\n",ans);
    }
    return 0;
}
*/
