/*
����:ժ������
��һ��1-n�����У���i����֪������ǰ���ұ���С�����ĸ�����������С�
n<=8000.
����:http://poj.org/problem?id=2182
˼·:��POJ 2828һ��,sum[rt]��ʾ��ǰ����Ŀ�λ.
��n��������߶���,��a[i]��a[i+1]Сʱ,a[i]�ı��
�϶���С,�ῼ���߶�������������λ�ĸ���,��a[i]��
a[i+1]��ʱ,a[i+1]֮ǰ����ʱ�϶������˿�λ����,����
a[i]ʱ��Ȼ�ͻ������ұߵ���������,ʵ�ʷ��õ�λ�þ�ƫ��
������.
*/
//ac 94ms
#include<cstdio>
#define N 8100

int n,sum[N<<2],a[N],ans[N];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int rt,int l,int r,int val,int pos){
    if(l == r){
        sum[rt]=0;
        ans[pos]=l;
        return;
    }
    int mid=(l+r)/2;
    if(val<=sum[rt<<1])
        update(rt<<1,l,mid,val,pos);
    else
        update(rt<<1|1,mid+1,r,val-sum[rt<<1],pos);
    pushup(rt);
}

int main(){
    scanf("%d",&n);
    build(1,1,n);
    a[1]=0;
    for(int i=2;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n;i>=1;i--)
        update(1,1,n,a[i]+1,i);//a[i]+1����Ϊ ʵ��Ҫ���õ�λ����a[i]+1
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}

/*
//ac 375ms ����
//ժ�Բ���:https://blog.csdn.net/qq_34374664/article/details/62216201
//�������������û��ô����
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int main()
{
    int n , j,cow[8005] ={0}, book[8005] = {0} ,  b[8005] = {0};
    cin >> n;
    for(int i = 2 ; i <= n; i++)  cin >> cow[i];
    b[n] = cow[n] + 1;
    book[b[n]] = 1;
    for(int i = n - 1; i >= 1 ; i--)
    {
        int count = 0 ;
        for(j = 1 ; j <= n - 1 ; j++)
        {
            if(book[j] == 0)  count++;
            if(count == cow[i] + 1)  break;
        }
        b[i] = j;
        book[j]  =1;
    }
    for(int i = 1; i <= n ;i++)
        cout << b[i] <<endl;
    return 0;
}
*/
