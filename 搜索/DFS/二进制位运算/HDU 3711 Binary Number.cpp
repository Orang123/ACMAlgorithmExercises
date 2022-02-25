/*
����:����2���Ǹ�����x��y��f(x, y) ����Ϊx��y�Ķ����Ƹ�ʽ�в�ͬλ��������
���磬f(2, 3)=1,f(0, 3)=2, f(5, 10)=4�����ڸ���2��Ǹ�����A��B������B��
��ÿ������b����Ӧ����A���ҵ�һ������a��ʹ��f(a, b)��С��
������� A ���ж����������������ѡ����С��һ����
����:
2������A,B,����B�е�ÿһ����b[i]��A��������a[j]�ж�����λ��ͬ�����ٵ���Ŀ,
���ÿ��b[i]��Ӧ�Ķ�����λ���ٵĲ�ͬλ��Ӧ��A�е���a[j],���н����ͬ,���
��С��ea[j].
n,m<=100.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3711
˼·:��λ����,ͳ�ƶ�������1�ĸ���.
*/
#include<stdio.h>
int num_1(int x)
{
    int cnt=0;
    while(x)
    {
        if(x&1) cnt++;
        x>>=1;
    }
    return cnt;
}
void xor_(int *a,int m,int *b,int n)
{
    int temp1,temp2,temp3,result;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            temp1=b[i]^a[j];
            temp2=num_1(temp1);
            if(j==0)
            {
                temp3=temp2;
                result=a[j];
            }
            else
            {
                if(temp2<temp3)
                {
                    temp3=temp2;
                    result=a[j];
                }
                else if(temp2==temp3)
                    if(result>a[j])
                    result=a[j];
            }
        }
        printf("%d\n",result);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    int a[100],b[100];
    while(T--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        for(int i=0; i<m; i++)
            scanf("%d",a+i);
        for(int j=0; j<n; j++)
            scanf("%d",b+j);
        xor_(a,m,b,n);
    }
    return 0;
}
