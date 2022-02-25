/*
题意:
有一种纸牌游戏，很有意思，给你N张纸牌，一字排开，纸牌有正反两面，
开始的纸牌可能是一种乱的状态（有些朝正，有些朝反），现在你需要整理
这些纸牌。但是麻烦的是，每当你翻一张纸牌（由正翻到反，或者有反翻到正）时，
他左右两张纸牌（最左边和最右边的纸牌，只会影响附近一张）也必须跟着翻动，
现在给你一个乱的状态，问你能否把他们整理好，使得每张纸牌都正面朝上，
如果可以，最少需要多少次操作。
一段长度不超过20的字符串,1表示反面朝上，0表示正面朝上。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2209
思路:只有两种情况,第一种是第一个翻,第二种是第一个不翻,
判断的时候判断a[i-1]如果是1的话,翻转a[i-1]、a[i]、a[i+1].
a[i-1]=!a[i-1];
a[i]=!a[i];
a[i+1]=!a[i+1];i<len,
最后一张牌单独哦安短 是否被翻转成正面0.
如果是反面1,则说明该方式无解.
*/
//ac 0ms 暴力
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int a[N],len,ans;
char str[N];

int cal(int cnt){
    for(int i=1;i<len;i++){
        if(a[i-1]){
            a[i-1]=!a[i-1];
            a[i]=!a[i];
            a[i+1]=!a[i+1];
            cnt++;
        }
    }
    if(a[len-1])
        return INF;
    else
        return cnt;
}

int main(){
    while(scanf("%s",str)!=EOF){
        ans=INF;
        len=strlen(str);
        for(int i=0;i<len;i++)
            a[i]=str[i]-'0';
        a[0]=!a[0];
        a[1]=!a[1];
        ans=min(ans,cal(1));
        for(int i=0;i<len;i++)
            a[i]=str[i]-'0';
        ans=min(ans,cal(0));
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("NO\n");
    }
    return 0;
}
