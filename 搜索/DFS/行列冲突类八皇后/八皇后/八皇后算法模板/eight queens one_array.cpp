/*
背景:在8×8格的国际象棋上摆放8个皇后，使其不能互相攻击，
即任意两个皇后都不能处于同一行、同一列或同一斜线上，问有多少种摆法。
*/
#include<cstdio>//一位数组效率较高,空间换时间O(1)判断矛盾
#define N 8
//八皇后是NPC(Non-deterministic Polynomial Complete)即多项式复杂程度的非确定性问题,NP完全的
//求解的时间复杂度O(N^N)
/*
lr:代表从上到下由左向右的主对角线,主对角线上的格子行和列的差为定值.
y-x做减法得到的下标是唯一的,因为数组下标不能为负,所以要在差值的基础上加n.1<=y-x+n<=n*n-1
rl:代表从上到下由右向左的副对角线,副对角线上的格子行和列的和为定值.
x+y做加法得到的下标是唯一的.2<=x+y<=2*n
col[i]:代表当前行的之一列有没有放置过皇后
*/

int col[N+1],lr[2*N],rl[2*N+1];
int cnt,a[N],n=8;
void dfs(int k){
	int i;
	if(k == n+1){
		cnt++;
		for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==j) printf("1");
                else printf("0");
            }
            printf("\n");
		}
		printf("\n");
		return;
		//for(i=1;i<=n;i++) printf("%d ",a[i]);每一个数字代表这一行皇后放在在第几列
		//printf("\n\n");
	}
    for(i=1;i<=n;i++){
        if(!col[i] && !lr[i-k+n] && !rl[k+i]){//判断列 主对角线 副对角线上有没有皇后 O(1)判断无需再循环遍历上面的行
            a[k] = i;
            col[i] = lr[i-k+n] = rl[k+i] = 1;
            dfs(k+1);
            col[i] = lr[i-k+n] = rl[k+i] = 0;
        }
    }
}
int main(){
    dfs(1);
    printf("%d\n",cnt);
    return 0;
}

/*
#include<stdio.h>
int a[8], n = 8, cnt;//之所以是a[8],因为实际上位置的放置永远也只赋了8次值，某一个位置永远也只能赋一次值，会被覆盖的
void DFS(int row)
{
	if (row == n)
	{
		cnt++;
		printf("第%d种摆放方案:\n", cnt);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n;j++)
			if (a[i] == j) printf("1 ");//代表放置有皇后
			else printf("0 ");
			putchar('\n');
		}
		putchar('\n');
	}
	else
	{
		bool flag;
		for (int i = 0; i < n; i++)
		{
			a[row] = i;//代表第row行,第i列
			flag = true;
			for (int j = 0; j < row; j++)//只需要考虑row行之前的行是否冲突,row行之后假定还没放置皇后,因为前面的一次方案里row行之后可能会有不必要的冲突
			if (a[row] == a[j] || row - j == a[row] - a[j] || row - j == a[j] - a[row])//分别为同一列是否冲突,主对角线是否冲突,次对角线是否冲突
			{
				flag = false;//说明有冲突,置标记为0,重新判断别的行而不进入下一行的dfs
				break;
			}
			if (flag) DFS(row + 1);
		}
	}
}
int main()
{
	DFS(0);
	printf("八皇后问题总共有%d种摆放方案\n", cnt);
	return 0;
}
*/
