/*
题意:摘自网上
给出邮票数量h，和邮票面值种类k，要求你选出k种面值的邮票，
通过这些1 ~ h张邮票所组成的面值数连续最大。连续是指从1开始计数能得到最大的连续面值.
比如：选择1 和 2，（在h= 3时)可以组成的面值数有1、2、3、4、5、6，所以此时最大连续面额就为6
但如果选择1 和3 的话，可组成的面值数就有1、2、3、4、5、6、7、  9，注意，没有8，所以最大连续面额为7.
链接:https://www.luogu.com.cn/problem/UVA165
思路:需要枚举邮票面值的上限,这个上限就是前cur个选定的邮票获得最大连续面值+1,
这样就可以使得cur+1张邮票的面值构成的新的面值能和前面的连续.
当前第cur张邮票的 下界是第cur张邮票的面值+1,同样是为了使得得到更大连续面值的
邮票.
*/
//ac 10ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 200
using namespace std;

//a[cur]表示第cur章邮票的面值
//b[cur]表示前cur张邮票组成的最大连续的邮票的面值
//vis[sum]=1表示能构成sum面值的邮票
int h,k,a[N],b[N],vis[M],ans,res[N];

//计算选出的前cur张邮票 所能得到哪些面值
void cal(int cur,int num,int sum){
    //这里不能拿vis[sum]标价剪枝,因为面值相同 也许数量不同,
    //而这里也不能将其开成二维vis[num][sum]标记,这样不好判断最大连续面值,因为不知道数量
    vis[sum]=1;
    if(num == h)
        return;
    for(int i=0;i<=cur;i++)
        cal(cur,num+1,sum+a[i]);
}

void dfs(int cur){
    if(cur == k){
        if(b[cur-1]>ans){
            ans=b[cur-1];
            memcpy(res,a,sizeof(a));
        }
        return;
    }
    for(int i=a[cur-1]+1;i<=b[cur-1]+1;i++){//枚举第cur张邮票的可能面值 下界是a[cur-1]+1,上界是b[cur-1]+1
        a[cur]=i;
        memset(vis,0,sizeof(vis));
        cal(cur,0,0);
        int j=1;
        while(vis[j])//从j=1开始判断最大的连续面值,第一个vis[j]==0的值结束,则最大面值就是j-1
            j++;
        b[cur]=j-1;
        dfs(cur+1);
    }
}

int main(){
    while(scanf("%d%d",&h,&k) && h+k){
        ans=0;
        a[0]=1;
        b[0]=h;
        dfs(1);
        for(int i=0;i<k;i++)
            printf("%3d",res[i]);
        printf(" ->%3d\n",ans);
    }
    return 0;
}
