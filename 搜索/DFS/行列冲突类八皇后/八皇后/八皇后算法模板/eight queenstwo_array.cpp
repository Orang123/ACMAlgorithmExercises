#include<stdio.h>
int row, n = 8,cnt;
bool judge_attack(int row, int col, int(*a)[8])
{
	static bool flag1, flag2, flag3, flag4;
	flag1 = flag2 = flag3 = flag4 = true;
	for (int i = 0; i < row;i++)
	if (a[i][col])
	{
		flag1 = false;
		break;
	}
	for (int i = row, j = col; i >= 0 && j >= 0;i--,j--)
	if (a[i][j])
	{
		flag2 = false;
		break;
	}
	for (int i = row, j = col; i >= 0 && j < n;i--,j++)
	if (a[i][j])
	{
		flag3 = false;
		break;
	}
	if (flag1&&flag2&&flag3)
		return true;
	else
		return false;
}
void DFS(int row, int(*s)[8])
{
	if (row == n)
	{
		cnt++;
		printf("八皇后问题的第%d种方案:\n", cnt);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				printf("%d ", s[i][j]);
			putchar('\n');
		}
	}
	else
	{
		/*int s[8][8];//这里的这一次二维数组空间开销是为了将来回溯时能回到当时递归进入时n皇后的布局
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			s[i][j] = a[i][j];*/
		for (int i = 0; i < n; i++)//判断每一列
		{
			if (judge_attack(row, i,s))//判断是否会相互攻击
			{
				/*
				//这种方法太笨了,看57行,把s[row][i]再改回0不久行了,这里不可省略,
				//原因是回溯准备尝试这一行的其它列时基本会把这一行的所有位置都填满,
				//导致后面的递归都会导致同一列的冲突所以就永远也没有进入DFS了,row自然也就不会到8,
				//但感觉去掉后一种方案都没有有点想不通,事实上感觉应该是会出8种左右的,应该是循环这
				//种非随机枚举导致前几次本身也没构成八皇后,后面几次同一行放置的没请掉越来越多导致后面
				//的递归也全部失败了
				for (int j = 0; j < n; j++)
					s[row][j] = 0;*/
				s[row][i] = 1;
				DFS(row + 1,s);
				s[row][i]=0;
			}
		}
	}
}
int main()
{
	static int a[8][8];
	DFS(0,a);
	printf("八皇后问题共有%d种方案\n", cnt);
	return 0;
}
