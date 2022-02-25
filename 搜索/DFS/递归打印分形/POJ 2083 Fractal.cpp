/*
题意:画分形图,n<=7.
链接:http://poj.org/problem?id=2083
思路:将要画的图形存在字符数组里,深度优先遍历的顺序是
左上角、右上角、最中间、左下角、右下角,注意是程序是递归的,
对于每个新的图形都是按照这个顺序遍历的,因为输出只能先输出
同一行的,再输出下一行.
*/
#include<stdio.h>
char G[730][730];//n<=7,行列最大为3^6=729
int dis(int k)
{
	int res=1;
	for (int i = 1; i < k-1; i++)
		res *= 3;//间隙是以3位单位倍增的
    return res;
}
void solve(int k,int row,int col)
{
	if (k == 1)
		G[row][col] = 'X';
	else
	{
		int dist = dis(k);//得到当前k值的图形之间的间隙
		solve(k - 1, row, col);//左上角
		solve(k - 1, row, col + 2 * dist);//右上角
		solve(k - 1, row + dist, col + dist);//最中间
		solve(k - 1, row + 2 * dist, col);//左下角
		solve(k - 1, row + 2 * dist, col + 2 * dist);//右下角
	}
}
void print(int k)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		if (G[i][j] == 'X')
			putchar(G[i][j]);
		else
			putchar(' ');
		putchar('\n');
	}
	puts("-");
}
int main()
{
	int k,dist;
	solve(7, 0, 0);
	while (scanf("%d", &k) && k!=-1)
	{
		dist = dis(k + 1);//这里因为要得到存储分形图形的最大的行列值,所以参数是k+1
		print(dist);//输出最大间隙的图形
	}
	return 0;
}
