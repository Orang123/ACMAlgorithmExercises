/*
题意:对于2个非负整数x和y，f(x, y) 定义为x和y的二进制格式中不同位的数量。
例如，f(2, 3)=1,f(0, 3)=2, f(5, 10)=4。现在给定2组非负整数A和B，对于B中
的每个整数b，您应该在A中找到一个整数a，使得f(a, b)最小。
如果集合 A 中有多个这样的整数，则选择最小的一个。
释义:
2个集合A,B,对于B中的每一个数b[i]和A中所有数a[j]中二进制位不同的最少的数目,
输出每个b[i]对应的二进制位最少的不同位对应的A中的数a[j],如有结果相同,输出
最小的ea[j].
n,m<=100.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3711
思路:按位异或后,统计二进制中1的个数.
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
