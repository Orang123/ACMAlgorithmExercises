/*
����:��8��8��Ĺ��������ϰڷ�8���ʺ�ʹ�䲻�ܻ��๥����
�����������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб���ϣ����ж����ְڷ���
*/
#include<cstdio>//һλ����Ч�ʽϸ�,�ռ任ʱ��O(1)�ж�ì��
#define N 8
//�˻ʺ���NPC(Non-deterministic Polynomial Complete)������ʽ���ӳ̶ȵķ�ȷ��������,NP��ȫ��
//����ʱ�临�Ӷ�O(N^N)
/*
lr:������ϵ����������ҵ����Խ���,���Խ����ϵĸ����к��еĲ�Ϊ��ֵ.
y-x�������õ����±���Ψһ��,��Ϊ�����±겻��Ϊ��,����Ҫ�ڲ�ֵ�Ļ����ϼ�n.1<=y-x+n<=n*n-1
rl:������ϵ�����������ĸ��Խ���,���Խ����ϵĸ����к��еĺ�Ϊ��ֵ.
x+y���ӷ��õ����±���Ψһ��.2<=x+y<=2*n
col[i]:����ǰ�е�֮һ����û�з��ù��ʺ�
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
		//for(i=1;i<=n;i++) printf("%d ",a[i]);ÿһ�����ִ�����һ�лʺ�����ڵڼ���
		//printf("\n\n");
	}
    for(i=1;i<=n;i++){
        if(!col[i] && !lr[i-k+n] && !rl[k+i]){//�ж��� ���Խ��� ���Խ�������û�лʺ� O(1)�ж�������ѭ�������������
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
int a[8], n = 8, cnt;//֮������a[8],��Ϊʵ����λ�õķ�����ԶҲֻ����8��ֵ��ĳһ��λ����ԶҲֻ�ܸ�һ��ֵ���ᱻ���ǵ�
void DFS(int row)
{
	if (row == n)
	{
		cnt++;
		printf("��%d�ְڷŷ���:\n", cnt);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n;j++)
			if (a[i] == j) printf("1 ");//��������лʺ�
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
			a[row] = i;//�����row��,��i��
			flag = true;
			for (int j = 0; j < row; j++)//ֻ��Ҫ����row��֮ǰ�����Ƿ��ͻ,row��֮��ٶ���û���ûʺ�,��Ϊǰ���һ�η�����row��֮����ܻ��в���Ҫ�ĳ�ͻ
			if (a[row] == a[j] || row - j == a[row] - a[j] || row - j == a[j] - a[row])//�ֱ�Ϊͬһ���Ƿ��ͻ,���Խ����Ƿ��ͻ,�ζԽ����Ƿ��ͻ
			{
				flag = false;//˵���г�ͻ,�ñ��Ϊ0,�����жϱ���ж���������һ�е�dfs
				break;
			}
			if (flag) DFS(row + 1);
		}
	}
}
int main()
{
	DFS(0);
	printf("�˻ʺ������ܹ���%d�ְڷŷ���\n", cnt);
	return 0;
}
*/
