/*
题意 题解摘自博客:https://blog.csdn.net/hjt_fathomless/article/details/52548842
题意:给出2个整数n（n<10^100）和k（k<10000），求满足以下条件的整数m
1、m与n位数相同
2、m能被k整除
3、满足以上两点时，m和n在相同位置的地方，数字不同的个数最少
4、满足以上三点时，m值最小
链接:http://poj.org/problem?id=3373
思路:这题很容易想到怎么做：
dp[i][j][num]表示前i位数构成的数是j，改变了num次，记忆化搜索就好。
但是num最大是多少呢？
假设k的位数是m，那么n最多只要改变m为位就可以%k==0了！因为n的m位之前的数%k可以得到一个数X，后m位变成k-X就行了！
所以k最大为10000，最多改变5位就行！

不是很理解这里"假设k的位数是m，那么n最多只要改变m为位就可以%k==0了".
*/
//ac 1579ms 记忆化搜索
#include<cstdio>
#include<cstring>
const int N = 1e4 + 9;
int d[110][N][6], n, k,minn;
char s[110],ans[110];
void dfs(int pos,int pre,int num) {
    if(pos==n) {
        if(num<minn&&pre==0) {
            minn=num;
            strcpy(ans,s);
        }
        return;
    } else if(num<minn) {
        if(!d[pos][pre][num]) {
            d[pos][pre][num]=1;
            char t=s[pos];
            for(int i=0; i<=9; i++) {
                if(pos==0&&i==0)continue;
                s[pos]=i+'0';
                dfs(pos+1,(pre*10+i)%k,num+(i!=t-'0'));

            }
            s[pos]=t;
        }
    }
}
int main() {
    //freopen ("f.txt", "r", stdin);
    while (~scanf ("%s %d", s, &k) ) {
        n = strlen (s);
        memset(d,0,sizeof(d));
        minn=6;
        dfs (0, 0, 0);
        printf("%s\n",ans);
    }
    return 0;
}
