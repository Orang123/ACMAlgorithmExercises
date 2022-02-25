/*
题意:给出一个只由小写英文字符a,b,c...y,z组成的字符串S,求S中最长回文串的长度.
回文就是正反读都是一样的字符串,如aba, abba等.
字符串长度<=110000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3068
思路:manacher算法模板题.
*/

/*
朴素暴力算法O(n^2)
该算法通过下述方式工作：对每个中心位置 ，在比较一对对应字符后，只要可能，该算法便尝试将答案加 。
// C++ Version
vector<int> d1(n), d2(n);
for (int i = 0; i < n; i++) {
  //枚举奇数回文串
  d1[i] = 1;
  while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
    d1[i]++;
  }
  //枚举偶数回文串
  d2[i] = 0;
  while (0 <= i - d2[i] - 1 && i + d2[i] < n &&
         s[i - d2[i] - 1] == s[i + d2[i]]) {
    d2[i]++;
  }
}
manacher算法好的视频讲解:
兰陵大大笑笑生 总共5部分.
https://www.bilibili.com/video/BV1zg411c7J3?from=search&seid=490781355636966904&spm_id_from=333.337.0.0
博客:https://www.jianshu.com/p/392172762e55
说明:
manacher能解决的问题PAM一定能解决,PAM能解决的 manacher解决起来可能会很繁琐,但有些简单问题manacher解决效率要高些
*/

//ac 234ms
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 111111
using namespace std;//218ms

//预处理后的长度为2n+1+1 #+$
char str1[N],str2[N<<1];
//p[i]表示以str2[i]为对称中心的回文串半径,len表示预处理后的str2的长度
int len,p[N<<1];
//记录最长回文子串的源字符串起始下标,start=(i-p[i])/2 方便输出最长回文子串
//int start;

//预处理将其统一变为奇回文,在原字符串两端插入#号分隔符,这样搜索最长回文只需不断枚举对称字符即可
//并且再开始加入不同于中间符号'#'的符号'$',这是为了求解记录最长回文子串的源字符串起始下标不出现负数,对于奇回文可能会出现负数
void init(){
    int n=strlen(str1),k=1;
    //str2[0]='$'无意义,是为了避免奇数子串预处理后
    //计算源串起始下标时,实际下标为0,计算为负数而在头部多插入的'$' 使其i-p[i]等于0
    str2[0]='$';//这个起始字符必须要保证和'#'和原字符串的字符不同
    for(int i=0;i<n;i++){
        str2[k++]='#';//中间所添加的字符 并不要求和原字符串的字符不同,因为比较时永远都是#和#比较或原字符串和原字符串比较
        str2[k++]=str1[i];
    }
    str2[k++]='#';
    //这个s2末尾要加上'\0',否则会导致,不同样例 在对比向两边扩展对比时 超出数组范围时,
    //之前s2存储的值会影响回文半径的大小.
    str2[k]='\0';
    len=k;
    /*
    str2[0]='$';//这个起始字符必须要保证和'#'和原字符串的字符不同
    for(int i=0;i<n;i++){
        str2[i*2+1]='#';//中间所添加的字符 并不要求和原字符串的字符不同,因为比较时永远都是#和#比较或原字符串和原字符串比较
        str2[i*2+2]=str1[i];
    }
    str2[n*2+1]='#';
    str2[n*2+1]='\0';
    len=n*2+2;
    */
}

//时间复杂度O(len) 因为while的循环只有情况1、4才会进行,这里都是i对mx的增大,实际mx最大只能是len所以while的复杂度是常数时间len
//因此总的Manacher时间复杂度为O(len) 暴力枚举所有的对称中心 复杂度为O(n^2)
int Manacher(){
    init();
    //id是所有回文子串中,能延伸到最右端位置的那个回文子串的中心点位置下标,
    //mx是该回文串能延伸到的最右端的位置,是该回文子串的能匹配到的最右端的下标的下一个不匹配的位置下标
    int id,mx=0,maxLen=0;//maxlen初始化为-1也行 id其实无需初始化,用到的时候已经更新过了
    //p[0]=0;//下标为0的回文半径为0,因为开始符号'$'无意义,这里无需初始化,因为根本用不到p[0]
    //从左到右开始遍历回文串的对称中心字符
    for(int i=1;i<len;i++){//i从2开始 做法也是没问题的
        /*
        根据对称性,以id为中心的回文串,右边的下标i,和左边对称的下标j,满足i+j=2*id,因此j=2*id-i.
        这里有4种情况:
        1.i不在之前统计的id为中心的回文串的半径内,即:i>=mx,这时需要以i为对称中心向两边扩展,p[i]初始化为1,从头开始暴力计算回文半径,并记录新的mx
        2.i在之前统计的id为中心回文串的半径内,并且以id为对称中心左边的对称点j(j=2*id-i)的回文串恰好在id的回文半径里,没有到达半径左边界.
        这时,因为对称性,p[i]=p[j]=p[2*id-i].
        3.i在之前统计的id为中心回文串的半径内,并且以id为对称中心左边的对称点j(j=2*id-i)的回文串恰好在id的回文半径的左边界,
        这时,根据对称性,p[i]=p[j]=p[2*id-i],但p[i]可能还会更大,因为还是继续会以i点为对称点,向连边扩展,只是比较的起始下标是
        i-p[i]和i+p[i],i+p[i]初始等于mx,继续延展i点的回文半径看是否能更大,以及更新mx.
        4.i在之前统计的id为中心回文串的半径内,并且以id为对称中心左边的对称点j(j=2*id-i)的回文串的左边界超过了id的回文串的左边界,
        这时,根据对称性,p[i]=mx-i.
        */
        if(i<mx) p[i]=min(mx-i,p[2*id-i]);//情况2 3 4
        else p[i]=1;//情况1
        //这里并没有判断数组越界的情况,因为str2[0]='$'和str2[len]='\0'是不可能相等的.
        //这里针对情况1、4
        while(str2[i-p[i]] == str2[i+p[i]]) p[i]++;//这里是遍历 当i+p[i]超出mx之外的字符是否有更多对称的字符，是否能找到更右端的回文串
        if(i+p[i]>mx){//找到了更右端的回文串,这样后续p[i]的计算就有可对称的p[2*id-i]去参考
            mx=i+p[i];//更新右端点和对称中心
            id=i;
        }
        if(p[i]-1>maxLen){//更新最长回文子串的长度
            maxLen=p[i]-1;//回文串的长度等于 回文半径-1
            //start=(i-p[i])/2; //最长回文子串的源字符串起始下标 即:str1[start]~str1[start+maxLen-1]
        }
    }
    //str1[start+maxLen]='\0';//将最长回文子串的结尾字符后加入结束符'\0'方便直接输出
    return maxLen;
}

int main(){
    while(scanf("%s",str1)!=EOF){
        printf("%d\n",Manacher());
        //printf("%s\n",str1+start);//输出最长回文子串
    }
    return 0;
}

/*
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
*/

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
