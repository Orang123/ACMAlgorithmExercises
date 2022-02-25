/*
题意:给一个字符串,长度不超过200个字符
求其不重复的全排列,输出不超过2M字节.
链接:http://poj.org/problem?id=1731
思路:摘自Eric的课件.
扩展一下visit数组的含义,让它记录各种元素和个数.
当剩余的个数大于0时才发生递归
vis[i].first表示字符串第i个数值,
vis[i].second表示字符串中第i个数值元素的个数.
*/
//ac 438ms dfs暴力枚举 含有数值相同的元素 产生不重复排列
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int len,cnt;
pair<int,int> vis[N];
char a[N],b[N];

//计算实际不重复的子串
//cnt表示各不相同字符的个数
void init(){
    cnt=0;
    for(int i=1;i<=len;i++){
        int j;
        for(j=1;j<=cnt && vis[j].first!=a[i];j++);//判断a[i]是否和之前记录的 字符是否是相同的
        if(j>cnt)//a[i]是新的字符,记录进vis 个数为1
            vis[++cnt]=make_pair(a[i],1);
        else//a[i]数值之前已经记录过,只增加数值为a[i]的字符的个数
            vis[j].second++;
    }
}

void dfs(int k){
    if(k == len+1){
        printf("%s\n",b+1);
        return;
    }
    //之所以不会产生重复的排列是因为 相同字符在cnt个字符里 是以字符种类 占据第i种字符,
    //同一种字符的不同个数是作为一个整体放在cnt里枚举的,因此不会出现将 第一个1 放置在第一位,
    //第二个1放置在第二位,再次枚举第二个1放置在第一位,第一个1放置在第二位这种情况 结果11、11 这两种重复情况
    //枚举时只是判断其数量,而不会单独把相同的字符都作为一位去单独枚举,那样就会有重复排列
    for(int i=1;i<=cnt;i++){
        if(vis[i].second){
            vis[i].second--;
            b[k]=vis[i].first;//第k个位置放置vis[i].first
            dfs(k+1);
            vis[i].second++;
        }
    }
}

int main(){
    while(scanf("%s",a+1)!=EOF){
        memset(b,'\0',sizeof(b));
        len=strlen(a+1);
        sort(a+1,a+1+len);
        init();
        dfs(1);
    }
    return 0;
}

/*
//ac 454ms 在确保初始序列字典序的前提下,第k位放置的元素不能和之前相同,否则会出现重复排列 b[k]!=a[i]
//最精简做法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int len,cnt,vis[N];
char a[N],b[N];

void dfs(int k){
    if(k == len+1){
        printf("%s\n",b+1);
        return;
    }
    for(int i=1;i<=len;i++){
        //在确保初始序列字典序的前提下,第k位放置的元素不能和之前相同,否则会出现重复排列
        if(!vis[i] && b[k]!=a[i]){
            vis[i]=1;
            b[k]=a[i];
            dfs(k+1);
            vis[i]=0;
        }
    }
    //这里第k位放置的 元素的情况都枚举完毕时,回溯时要重置b[k]为'\0'
    //如果不重置,会导致1..k-1位重新枚举新的位时,第k位可能会出现和之前枚举相同的元素,
    //而导致判断条件返回为1,导致程序无法成功枚举完所有的len位,而实际前面1~k-1位和之前是不同的,
    //这个序列是合法的和之前不同的序列.
    b[k]='\0';
}

int main(){
    while(scanf("%s",a+1)!=EOF){
        len=strlen(a+1);
        sort(a+1,a+1+len);
        dfs(1);
    }
    return 0;
}
*/

/*
//ac 469ms 设置一个临时变量记录之前放入的 去重,前提是 初始数组字典序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int len,cnt,vis[N];
char a[N],b[N];

void dfs(int k){
    if(k == len+1){
        printf("%s\n",b+1);
        return;
    }
    char tp='A';//保证还未放入第k个字符时,一定不会重复,因为输入是a~z
    for(int i=1;i<=len;i++){
        if(!vis[i] && tp!=a[i]){
            vis[i]=1;
            tp=b[k]=a[i];
            dfs(k+1);
            vis[i]=0;
        }
    }
}

int main(){
    while(scanf("%s",a+1)!=EOF){
        len=strlen(a+1);
        sort(a+1,a+1+len);
        dfs(1);
    }
    return 0;
}
*/

/*
//ac 32ms stl next_permutation(使用之前要排序) 这个默认产生的就是不可重复的排列(在有重复元素时)
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int main()
{
    char a[201];
    int len;
    while(scanf("%s",a)!=EOF)
    {
        len=strlen(a);
        sort(a,a+len);
        puts(a);
        while(next_permutation(a,a+len))
            puts(a);
    }
    return 0;
}
*/
