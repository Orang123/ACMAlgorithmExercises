/*
题意:摘自网上
给你n和m要求找出这样的m位数，从第n位到第m位都满足前i位是可以被i整除，
如果没有这样的数，输出-1.有多个就输出字典序最小的那个。
0<n<m<30.
链接:https://www.luogu.com.cn/problem/UVA10624
思路:枚举每一位的取值,因为最大可以有29位,超过了longlong的范畴,
为避免累乘的过程中溢出,在累乘的过程边取余边累乘,
对于前k位,判断是否能取余的过程中,将前i-1位的余数乘10加上第i位的数字
再对k取余.
for(int i=1;i<=k;i++)
    sum=(sum*10+a[i])%k;
*/
//ac 1.70s dfs回溯
//最坏时间界10^29,实际数据可能偏向于 存在这样的数,可以直接避免过多回溯.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,a[N],flag;

int check(int k){
    int sum=0;
    for(int i=1;i<=k;i++)
        sum=(sum*10+a[i])%k;
    return sum;
}

void dfs(int k){
    if(k == m+1){
        flag=1;
        return;
    }
    for(int i=0;i<=9;i++){
        if(!i && k==1) continue;
        a[k]=i;
        if(k>=n){
            if(!check(k))
                dfs(k+1);
        }
        else
            dfs(k+1);
        if(flag)
            return;
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        flag=0;
        cas++;
        scanf("%d%d",&n,&m);
        dfs(1);
        printf("Case %d: ",cas);
        if(flag){
            for(int i=1;i<=m;i++)
                printf("%d",a[i]);
        }
        else
            printf("-1");
        printf("\n");
    }
    return 0;
}
