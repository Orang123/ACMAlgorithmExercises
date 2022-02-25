/*
����:1��N(N<=10)��ȫ������,��������Ƿ�ʽ�ۼӺ�Ϊsum���ֵ�����С������.
eg:3 1 2 4 N=4
    4 3 6
     7 9
      16
����:http://poj.org/problem?id=3187
˼·:���ֵ�����ö�� ���ظ�Ԫ�ص�����
*/
//ac 79ms �����ظ�Ԫ��,��������л����ظ���
#include<stdio.h>
bool visit[10];
int temp[10],n,sum;
bool permutation(int *a,int k)
{
    if(k==n)
    {
        for(int i=0; i<n; i++) temp[i]=a[i];
        for(int i=0; i<n-1; i++)
            for(int j=0; j<n-i-1; j++) temp[j]+=temp[j+1];
        if(*temp==sum)
        {
            for(int i=0; i<n-1; i++) printf("%d ",a[i]);
            printf("%d\n",a[n-1]);
            return true;
        }
        return false;
    }
    else
        for(int i=0; i<n; i++)
            if(visit[i]==false)
            {
                a[k]=i+1;//����ǰλ��ֵ����һ����ջ��λ��ֵ����
                visit[i]=true;
                if(permutation(a,k+1)) return true;//ÿ�εݹ鶼�����λǰ���������ڵĽ�������������ǰ����
                visit[i]=false;//Ϊ�´εĻ�������׼��
            }
    return false;
}
int main()
{
    int a[10];
    int k;
    scanf("%d%d",&n,&sum);
    k=0;
    permutation(a,k);
    return 0;
}

/*
//ac 0ms ���������ܺͿ��Ա�ʾ��ԭ����������������һ��ϵ���ĳ˻��� ���м�֦
//�����һ�е���Ϊa,b,c,d,e,f
//��ôn=4ʱ ���һ�е��ۼӽ��sum���Ա�ʾ��a+3b+3c+d
//n=5 a+4b+6c+4d+e
//n=6 a+5b+10c+10d+5e+f
#include<cstdio>
int a[13],c[12][12],n,sum,vis[13];
int dfs(int num,int ans){
    if(ans>sum) return 0;//��֦�����ǰϵ���˻��Ѿ�����sum,���м�֦
    if(num == n+1){
        if(ans == sum) return 1;
        else return 0;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        a[num]=i;
        vis[i]=1;
        //i*c[n-1][num-1]��ʾsum�Ķ���ʽ�е�һ�������ֵ���� ��n-1����������е�num-1����*����(i)
        if(dfs(num+1,ans+i*c[n-1][num-1])) return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&sum);
    for(int i=0;i<12;i++)
        c[i][0]=1;//�������ά ���Ǵ�0��ʼ��ŵ�
    for(int i=1;i<12;i++)
        for(int j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    if(dfs(1,0)){
        printf("%d",a[1]);
        for(int i=2;i<=n;i++) printf(" %d",a[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 32ms stl�汾
//Ĭ��permutation ������ȫ����Ϊ���ֵ���˳�� �ǲ����ظ���ȫ����
//http://blog.csdn.net/desirepath/article/details/50447712
//http://blog.csdn.net/ac_gibson/article/details/45308645
#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
    int n,sum;
    int a[10],temp[10];
    while(scanf("%d%d",&n,&sum)!=EOF)
    {
        for(int i=0;i<n;i++) a[i]=i+1;
        do
        {
            for(int i=0;i<n;i++)
            temp[i]=a[i];
            for(int i=0;i<n-1;i++)
                for(int j=0;j<n-i-1;j++)
                temp[j]=temp[j]+temp[j+1];
            if(temp[0]==sum)
            {
                printf("%d",a[0]);
                for(int i=1;i<n;i++)
                    printf(" %d",a[i]);
                putchar('\n');
                break;
            }
        }while(next_permutation(a,a+n));
    }
    return 0;
}
*/
