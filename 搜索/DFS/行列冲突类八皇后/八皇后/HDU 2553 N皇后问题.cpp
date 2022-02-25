/*
题意:在N*N的方格棋盘放置了N个皇后，使得它们不相互攻击
（即任意2个皇后不允许处在同一排，同一列，也不允许处在与棋盘边框成45角的斜线上。
你的任务是，对于给定的N，求出有多少种合法的放置方法。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2553
思路:位运算实现8皇后
*/
#include<cstdio>
int n,cnt,ans[11];
void dfs(int k,int c,int l,int r){
	int sta,t;
	if(k == n+1){
		cnt++;
        return;
	}
    sta = c | l | r;
    for(int i=0;i<n;i++){
        t = 1<<i;
        if(~sta&t)
            dfs(k+1,c|t,(l|t)<<1,(r|t)>>1);
    }
}

int main(){
    for(int i=1;i<=10;i++){
        cnt=0;
        n=i;
        dfs(1,0,0,0);
        ans[i]=cnt;
    }
    while(scanf("%d",&n)&&n)
        printf("%d\n",ans[n]);
	return 0;
}
