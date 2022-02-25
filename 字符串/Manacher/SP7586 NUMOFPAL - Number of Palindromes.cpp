/*
题意:求一个串中包含几个回文串.
|s|<=1000.
说明:回文串可以重复,并不要求本质不同,
如果要求本质不同的回文串,需要用回文树(PAM-回文自动机)来做.
链接:https://www.luogu.com.cn/problem/SP7586
思路:可以统计出最长回文子串的长度,对于这个回文子串,它的长度
的一般就是其包括的所有回文子串,因此可以用manacher算法,累加
回文半径/2,计算出所有回文串的数目.
这里不区分奇数长度回文和偶数长度回文.
实际奇数长度回文数目=长度/2+1
偶数长度回文数目=长度/2
但这里因为manacher预处理时加入了'#'分隔,两种情况都可以用回文半径/2来求解.

这个问题同样可以用字符串hash+二分或回文自动机来求解.
*/
//ac 0ms manacher
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1111
using namespace std;
char str1[N],str2[N<<1];
int len,p[N<<1];

void init(){
    int n=strlen(str1),k=1;
    str2[0]='$';
    for(int i=0;i<n;i++){
        str2[k++]='#';
        str2[k++]=str1[i];
    }
    str2[k++]='#';
    str2[k]='\0';
    len=k;
}

int Manacher(){
    init();
    int id=0,mx=0,sum=0;
    //p[0]=0;
    for(int i=1;i<len;i++){
        if(i<mx) p[i]=min(mx-i,p[2*id-i]);
        else p[i]=1;
        while(str2[i-p[i]] == str2[i+p[i]]) p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        /*可以这样理解p[i]/2代表当前扩展出的回文串以下标i为对称中心包含自己本身共含有多少回文子串
        列如像$#a#a#b#a#a# p[6]=6 6/2=3 公含b aba aabaa这几个以b会对称中心的回文子串,将所有枚举出来的
        对称中心经过扩展后的p[i]/2累加起来就是这个字符串中的所有回文串*/
        sum+=p[i]/2;
    }
    return sum;
}

int main(){
    scanf("%s",str1);
    printf("%d\n",Manacher());
    return 0;
}

/*
//ac PAM(回文自动机)
#include<cstdio>
#include<cstring>
#define N 1010

struct PAM{
    int s[N];
    int n;
    int p;
    int last;
    int next[N][26];
    int fail[N];
    int len[N];
    int cnt[N];
    int num[N];
    int sum;

    int newNode(int l){
        for(int i=0;i<26;i++) next[p][i]=0;
        len[p]=l;
        cnt[p]=0;
        num[p]=0;
        return p++;
    }

    void init(){
        p=0;
        newNode(0);
        newNode(-1);
        n=0;
        last=0;
        s[0]=-1;
        fail[0]=1;
        fail[1]=0;
        sum=0;
    }

    int getFail(int x){
        while(s[n-len[x]-1] != s[n]) x=fail[x];
        return x;
    }

    void add(int c){
        c-='a';
        s[++n]=c;
        int cur=getFail(last);
        if(!next[cur][c]){
            int now=newNode(len[cur]+2);
            fail[now]=next[getFail(fail[cur])][c];
            next[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }

    void countAllNum(){
        for(int i=p-1;i>=2;i--){
            cnt[fail[i]]+=cnt[i];
                sum+=cnt[i];//将更新后的所有结点代表的本质不同的回文串出现次数累加结果为该字符串所有回文串的个数 要排除0、1 偶根和奇根
        }
    }

}pam;

int main(){
    char a[N];
    scanf("%s",a);
    int len=strlen(a);
    pam.init();
    for(int i=0;i<len;i++)
        pam.add(a[i]);
    pam.countAllNum();
    printf("%d\n",pam.sum);
    return 0;
}

*/
