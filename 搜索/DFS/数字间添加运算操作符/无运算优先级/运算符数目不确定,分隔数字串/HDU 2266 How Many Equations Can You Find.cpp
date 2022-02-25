/*
题意:求在原字符串str数字之间添加一些+、-号,使所得的值所给定值n相同,
有多少种不同的方法.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2266
思路:直接暴力枚举在哪些数字的间隔间加'+'或'-'.
*/
//ac 15ms dfs 暴力回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

char str[N];
int n,len,ans;

//时间复杂度O(2^len) 每个间隔考虑放不放置分隔符 总共2^len种情况
void dfs(int st,int sum){
    if(st == len+1){
        if(sum == n)
            ans++;
        return;
    }
    int res=0;
    for(int i=st;i<=len;i++){
        res=res*10+str[i]-'0';
        dfs(i+1,sum+res);
        if(st!=1)//注意开头的第一个数字 不能是减号
            dfs(i+1,sum-res);
    }
}

int main(){
    while(scanf("%s%d",str+1,&n)!=EOF){
        ans=0;
        len=strlen(str+1);
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}
