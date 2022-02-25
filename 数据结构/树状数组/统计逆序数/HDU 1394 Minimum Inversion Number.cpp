/*
题意:摘自网上
有一个n个整数的排列，这n个整数就是0,1,2,3...n-1这n个数
(但不一定按这个顺序给出)。现在先计算一下初始排列的逆序数，
然后把第一个元素a1放到an后面去，形成新排列a2 a3 a4...an a1，
然后再求这个排列的逆序数。继续执行类似操作(一共要执行n-1次)
直到产生排列an a1 a2...an-1为止。计算上述所有排列的逆序数，输出最小逆序数。
n<=5000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1394
思路:可以先求出初始序列的总逆序数,每次将首位数字放到末尾后,会导致原先后面
比首位数字构成的逆序减少个数为a[i]-1,而放置到末尾后会使得原先比
a[i]大的数字在a[i]前面增加新的逆序个数为n-a[i].
因此新的序列逆序为sum-(a[i]-1)+n-a[i].
这里因为树状数组节点编号不能为0,因此a[i]的数字都加了1.
*/
//ac 31ms 树状数组
#include<cstdio>
#include<cstring>
#define N 5010

int n,c[N],a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    int sum,ans;
    while(scanf("%d",&n)!=EOF){
        sum=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i]++;
        }
        for(int i=1;i<=n;i++){
            update(a[i],1);
            sum+=i-getsum(a[i]);
        }
        ans=sum;
        for(int i=1;i<n;i++){
            sum=sum-(a[i]-1)+(n-a[i]);
            if(sum<ans)
                ans=sum;
        }
        printf("%d\n",ans);
    }
    return 0;
}
