/*
����:������ͼ,n<=7.
����:http://poj.org/problem?id=2083
˼·:��Ҫ����ͼ�δ����ַ�������,������ȱ�����˳����
���Ͻǡ����Ͻǡ����м䡢���½ǡ����½�,ע���ǳ����ǵݹ��,
����ÿ���µ�ͼ�ζ��ǰ������˳�������,��Ϊ���ֻ�������
ͬһ�е�,�������һ��.
*/
#include<stdio.h>
char G[730][730];//n<=7,�������Ϊ3^6=729
int dis(int k)
{
	int res=1;
	for (int i = 1; i < k-1; i++)
		res *= 3;//��϶����3λ��λ������
    return res;
}
void solve(int k,int row,int col)
{
	if (k == 1)
		G[row][col] = 'X';
	else
	{
		int dist = dis(k);//�õ���ǰkֵ��ͼ��֮��ļ�϶
		solve(k - 1, row, col);//���Ͻ�
		solve(k - 1, row, col + 2 * dist);//���Ͻ�
		solve(k - 1, row + dist, col + dist);//���м�
		solve(k - 1, row + 2 * dist, col);//���½�
		solve(k - 1, row + 2 * dist, col + 2 * dist);//���½�
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
		dist = dis(k + 1);//������ΪҪ�õ��洢����ͼ�ε���������ֵ,���Բ�����k+1
		print(dist);//�������϶��ͼ��
	}
	return 0;
}
