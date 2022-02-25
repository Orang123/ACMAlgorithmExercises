/*
题意:给出一个只由小写英文字符a,b,c...y,z组成的字符串S,求S中最长回文串的长度.
回文就是正反读都是一样的字符串,如aba, abba等.
字符串长度<=110000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3068
思路:manacher算法模板题.这里用字符串hash搞搞.
字符串hash求解最大回文子串讲解博客:
https://blog.csdn.net/qq_43716912/article/details/98470518?spm=1001.2014.3001.5506
https://blog.csdn.net/Onebelieve_lxl/article/details/104040799?spm=1001.2014.3001.5506
*/
//ac 1528ms 字符串hash+二分
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007也可
#define N 110100
using namespace std;
typedef unsigned long long ull;
ull h1[N],h2[N],powr[N];
char s[N];
int main(){
    int len;
    powr[0]=1;
    int k=N/2;
    for(int i=1;i<k;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        h1[0]=0;
        for(int i=1;i<=len;i++)
            h1[i]=h1[i-1]*p+(s[i]-'a'+1);
        h2[len+1]=0;
        for(int i=len;i>=1;i--)
            h2[i]=h2[i+1]*p+(s[i]-'a'+1);
        int l,r,mid,ans=-1;
	/*
	二分的两种形式：
	1、范围缩小时，r = mid，l = mid + 1，取中间值时，mid = (l + r) >> 1.
	2、范围缩小时，l = mid，r = mid - 1，取中间值时，mid = (l + r + 1) >> 1;
	*/
        for(int i=1;i<=len;i++){
            l=0,r=min(i-1,len-i);//r为最大的回文半径 这里r=i-1 是以i会对称中心的奇回文串
            while(l<r){//只到左右边界不可再二分为止 便为最大的回文半径
                //对回文半径进行二分 这里第一次回文半径不能直接按照前面比较大的回文半径去尝试,
                //因为它本身所取的最大的回文半径可能没有这么大,会导致h数组越界异常
                mid=(l+r+1)>>1;
                //s[i-mid~i-1]是否和s[i+1~i+mid]相等 构成回文串
                //若当前半径构成的子串是回文串 则继续增大回文串半径 l=mid,这样下次的mid就更大了
                if(h1[i-1]-h1[i-mid-1]*powr[mid] == h2[i+1]-h2[i+mid+1]*powr[mid]) l=mid;
                else r=mid-1;//若当前半径构成的子串不是回文串 则需要缩小回文串半径 r=mid-1 这样下次mid就变小了
            }
            ans=max(ans,l*2+1);//回文长度为回文半径*2+对称中心(1)
            l=0,r=min(i,len-i);//这里r=i 是偶回文串
            while(l<r){
                mid=(l+r+1)>>1;//l+r+1 +1是为了避免mid=0 ab这样就会hash值都为0错误相等
                //s[i-mid+1~i]是否和s[i+1~i+mid-1]相等
                if(h1[i]-h1[i-mid]*powr[mid] == h2[i+1]-h2[i+mid+1]*powr[mid]) l=mid;
                else r=mid-1;
            }
            ans=max(ans,l*2);
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//405ms 字符串hash 最长回文串长度线性增加回文半径 非二分
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007也可
#define N 110100
using namespace std;
typedef unsigned long long ull;

ull h1[2*N],h2[2*N],powr[N];
char s[N],str[2*N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        int j=0;
        for(int i=1;i<=len;i++){//通过预处理间隔加入#将奇 偶回文都处理为奇回文 统一一种情形
            str[++j]='#';
            str[++j]=s[i];
        }
        str[++j]='#';
        h1[0]=0;
        for(int i=1;i<=j;i++)
            h1[i]=h1[i-1]*p+(str[i]-'a'+1);
        h2[j+1]=0;
        for(int i=j;i>=1;i--)//反过来就算对称子串的hash值
            h2[i]=h2[i+1]*p+(str[i]-'a'+1);
        int l=0;
        for(int i=1;i<=j;i++){//枚举回文对称中心点
            if(i-l<1 || i+l>j) break;//如果某个中心点 尝试当前最长回文半径越界,后面的点只会更不对称,回文半径便不可再增加,即结束
            if(h1[i-1]-h1[i-l-1]*powr[l] != h2[i+1]-h2[i+l+1]*powr[l]) continue;//比较以对称中心的两子串hash值是否相等
            while(str[i-l-1] == str[i+l+1] && i-l-1>=1 && i+l+1<=j) l++;//若原先最大回文半径构成的回文串两端点相等就线性增加回文半径
            //while(h1[i-1]-h1[i-l-1]*powr[l] == h2[i+1]-h2[i+l+1]*powr[l] && i-l>=1 && i+l<=j) l++; 这种每次都采用hash值比较整体 会慢一点 452ms
        }
        printf("%d\n",l);//因为str是添加#预处理之后的回文半径就是这个回文串的长度
    }
    return 0;
}
*/

/*
manacher算法 线性O(n)时间求解最长回文子串 在manacher专题中
*/
