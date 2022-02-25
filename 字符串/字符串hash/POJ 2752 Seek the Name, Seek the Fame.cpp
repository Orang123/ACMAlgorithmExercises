/*
题意:摘自网上
给你一个串p,找出串p的子串,该串既是p的前缀也是p的后缀。
从小到大输出所有符合要求的串的长度。
plen<=4*10^5.
链接:http://poj.org/problem?id=2752
思路:摘自博客:https://blog.csdn.net/niushuai666/article/details/6968507
next数组的对称性.
这道题也是next数组的一个应用。
既然是求模式串匹配，所以要先求出模式串的next数组。这是第一步。
然后我们开始分析怎么用next数组来完成查找前缀后缀的匹配。
我们还是用上面那个字符串为例子来说明一下。
  下标   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
  模式串 a  b  a  b  c  a  b  a  b  a  b  a  b  c  a  b  a  b
 next[i] -1 0  0  1  2  0  1  2  3  4  3  4  3  4  5  6  7  8  9
1）当i = len时，next[len] = next[18] = 9，说明整个字符串前9个字符和后9个字符相同，所以9是满足要求的。
2）next[9] = 4，说明在0-8中前4个字符和后4个字符相同。因为由1）得前9个字符和后9个字符相同，所以，S串
的0-3等于5-8，而0-3又等于9-12,5-8又等于14-17，所以结果是0-3等于14-17，即4也是满足题意的。
3）next[4]=2，同2，我们可以得到2也是满足题意的。
4）next[2]=0，表明没有相同的前缀和后缀了，这时，就已经找到了这个S串的所有前缀和后缀。
5）结果就是2,4,9,18.
所以，我们可以推得这样的结论：凡是next[i]！=0的，都是模式串的前缀和后缀相同的字符数。
*/

//ac 516ms 字符串hash
#include<cstdio>
#include<cstring>
#define p 233 //1000007也可
#define N 400100
typedef unsigned long long ull;
ull h[N],powr[N];
char s[N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        h[0]=0;
        for(int i=1;i<=len;i++)
            h[i]=h[i-1]*p+(s[i]-'A'+1);
        for(int i=1;i<=len;i++)
            if(h[i] == h[len]-h[len-i]*powr[i])
                printf("%d ",i);
        printf("\n");
    }
    return 0;
}

/*
//ac 719ms kmp
#include<cstdio>
#include<cstring>
#include<vector>
#define N 400010
using namespace std;

int plen,nxt[N];
char p[N];
vector<int> ans;

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
    while(scanf("%s",p)!=EOF){
        ans.clear();
        getNext();
        ans.push_back(plen);
        for(int i=plen;nxt[i];i=nxt[i])
            ans.push_back(nxt[i]);
        for(int i=ans.size()-1;i>=0;i--){
            printf("%d",ans[i]);
            if(i)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
*/
