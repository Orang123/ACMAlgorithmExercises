/*
题意:长度为n的子序列,输出其前p个不下降的子序列.
注意:子序列不能有重复.
1<n<=1000, 1<p<=10000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2610
思路:dfs枚举[1,n]中长度为len的子序列.
注意重复子序列只枚举一次,需要判断[st,i)内是否有和当前
序列第i位相等的,如有相等的就是重复子序列,因为前面的已经
枚举过了.
一个剪枝是如果当前长度为i的子序列不存在,长度为i+1,i+2...n-1
的子序列也是不存在的
*/
//ac 78ms dfs枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,p,a[N],b[N],ok,cnt;

void dfs(int k,int st,int len){
    if(cnt>=p)//当已经枚举够前p个时,就直接返回
        return;
    if(k == len+1){
        ok=1;
        cnt++;
        printf("%d",b[1]);
        for(int i=2;i<k;i++)
            printf(" %d",b[i]);
        printf("\n");
        return;
    }
    int flag;
    for(int i=st;i<=n;i++){
        if(a[i]<b[k-1]) continue;//相比上一个位置b[k-1],下一个元素a[i]不能下降,必须是a[i]>=b[k-1]
        flag=0;
        for(int j=st;j<i;j++){//判断子序列之前[st,i)位置已经枚举过的元素是否有和a[i]相同的,如有相同的,不再重复枚举
            if(a[j] == a[i]){
                flag=1;
                break;
            }
        }
        if(flag) continue;
        b[k]=a[i];
        dfs(k+1,i+1,len);//判断子序列第k+1个位置
    }
}

int main(){
    while(scanf("%d%d",&n,&p)!=EOF){
        cnt=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<n;i++){
            ok=0;
            dfs(1,1,i);
            if(!ok) break;//如果长度为i的子序列不存在,i+1,i+2..n-1自然也不存在,不加这个剪枝  会TLE
            if(cnt == p) break;//已经枚举完前p个时,结束.
        }
        printf("\n");
    }
    return 0;
}
