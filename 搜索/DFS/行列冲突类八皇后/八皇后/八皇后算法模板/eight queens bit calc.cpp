#include<cstdio>
#define N 10
int n=8,cnt,a[N];
/*
c:代表当前第k行纵列被禁用的位置的二进制表示 1代表被禁用 0代表可用 的位置
l:代表从上到下从右往左的副对角线在当前第k行被禁用的位置的二进制表示
r:代表从上到下从左往右的主对角线在当前第k行被禁用的位置的二进制表示
k:代表准备在第k行放置皇后
*/
void dfs(int k,int c,int l,int r){
	int sta,t;
	if(k == n+1){
		cnt++;
        return;
	}
    sta = c | l | r;//sta代表综合 纵列和主副对角线后的第k行被禁用的位置 二进制表示
    for(int i=0;i<n;i++){
        t = 1<<i;//代表第(i+1)列的位置为1 因为第1列是1<<0
        if(~sta&t){//sta按位取反1就代表可用的位置 和t 按位与 结果为1代表一列可用,为0代表这一列被禁用
            //a[k] = i;
            //对于第k+1行的 纵列的状态 需要上一行纵列c|t,副对角线因为要向下延伸,占位会向左移1位,所以l|t后要向左移1位,主对线同理要向下延伸要右移动一位
            dfs(k+1,c|t,(l|t)<<1,(r|t)>>1);
        }
    }
}

int main(){
	dfs(1,0,0,0);
	printf("%d\n",cnt);
	return 0;
}

/*
另一种做法 和上面位运算效率是一样的
https://www.cnblogs.com/lukelmouse/p/10579916.html
#include <bits/stdc++.h>
using namespace std;
int n,tot,goal = (1<<8) - 1;
void dfs(int lvis,int rvis,int row){
    int safe,next;
    if(row != goal){
        safe = goal & (~ (row|lvis|rvis));//得到可行解
        while(safe){//
            next = safe & (~safe + 1);// 得到 最右边的一个位置,safe & (-safe)
            safe ^= next;// 删除最右边的一个解
            bfs((lvis|next)<<1,(rvis|next)>>1,row|next);
        }
    }
    else
        tot++;
}
int main(){
    //cin>>n;
    n = 8;
    dfs(0,0,0);
    cout<<tot<<endl;
    return 0;
}
*/
