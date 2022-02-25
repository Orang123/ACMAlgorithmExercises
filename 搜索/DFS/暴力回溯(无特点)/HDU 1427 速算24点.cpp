/*
题意:
速算24点相信绝大多数人都玩过。就是随机给你四张牌，包括A(1),2,3,4,5,6,7,8,9,10,J(11),Q(12),K(13)。
要求只用'+','-','*','/'运算符以及括号改变运算顺序，使得最终运算结果为24(每个数必须且仅能用一次)。
游戏很简单，但遇到无解的情况往往让人很郁闷。你的任务就是针对每一组随机产生的四张牌，判断是否有解。
我们另外规定，整个计算过程中都不能出现小数。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1427
思路:因为只有4个数,所有考虑左边项结合还是右边项结合,枚举全排列
使用stl中的next_permutation.
*/
//ac 109ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4
using namespace std;

char str[N];
int a[N],flag;

void dfs(int k,int res1,int res2){
    if(flag)
        return;
    if(k == 4){
        if(res1+res2 == 24 || res1-res2 == 24 || res1*res2 == 24 || (res2 && res1%res2 == 0 && res1/res2 == 24))
            flag=1;
        return;
    }
    dfs(k+1,res1+res2,a[k]);
    dfs(k+1,res1-res2,a[k]);
    dfs(k+1,res1*res2,a[k]);
    if(res2 && res1%res2 == 0)
        dfs(k+1,res1/res2,a[k]);
    dfs(k+1,res1,res2+a[k]);
    dfs(k+1,res1,res2-a[k]);
    dfs(k+1,res1,res2*a[k]);
    if(a[k] && res2%a[k] == 0)
        dfs(k+1,res1,res2/a[k]);

}

int main(){
    while(scanf("%s",str)!=EOF){
        for(int i=0;i<4;i++){
            if(i)
                scanf("%s",str);
            if(strlen(str) == 2)
                a[i]=10;
            else if(str[0] == 'A')
                a[i]=1;
            else if(str[0] == 'J')
                a[i]=11;
            else if(str[0] == 'Q')
                a[i]=12;
            else if(str[0] == 'K')
                a[i]=13;
            else
                a[i]=str[0]-'0';
        }
        sort(a,a+4);
        flag=0;
        do{
            dfs(2,a[0],a[1]);
            if(flag){
                printf("Yes\n");
                break;
            }
        }while(next_permutation(a,a+4));
        if(!flag)
            printf("No\n");
    }
    return 0;
}
