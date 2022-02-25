/*
题意:摘自网上
给定一个数n,和一个连续串str，要求将str拆分成若干段，并且要使这
若干段之和最接近于n，如果只有一种拆法，就输出这种拆法。
如果对于同一个最接近的和，有多种拆法，就输出rejected。
如果所有拆法得到的和都比n大，那么就输出error。
字符串长度最多6位.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1539
思路:dfs暴力枚举 在连续串str中的分隔符,记录最小差值.
一个剪枝,在分割过程中 如果 结果已经大于n了,就返回.
*/
//ac 0ms dfs暴力枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
#define INF 0x3f3f3f3f
using namespace std;

int n,len,ans,num,a[N],b[N],flag;
char str[N];

void dfs(int st,int k,int sum){
    if(sum>n)//如果结果已经大于n了, 就返回
        return;
    if(st == len){
        if(n-sum<ans){//刚好等于n时 也不能直接返回,还需判断是否有 别的分割情况使得差值为0
            ans=n-sum;
            flag=0;
            memcpy(b,a,sizeof(a));
            num=k;
        }
        else if(n-sum == ans)
            flag=1;
        return;
    }
    int tp=0;
    for(int i=st;i<len;i++){
        tp=tp*10+str[i]-'0';
        a[k]=tp;
        dfs(i+1,k+1,sum+tp);
    }
}

int main(){
    while(scanf("%d%s",&n,str)){
        if(!n && str[0] =='0')
            break;
        ans=INF;
        len=strlen(str);
        dfs(0,0,0);
        if(ans == INF)//不存在小于等于n的结果
            printf("error\n");
        else{
            if(!flag){//最小差值 只有一种情况
                printf("%d",n-ans);
                for(int i=0;i<num;i++)
                    printf(" %d",b[i]);
                printf("\n");
            }
            else//最小差值 有多种情况
                printf("rejected\n");
        }
    }
    return 0;
}

/*
//这个做法 为什么会RE,感觉6位数字 分割后求和的结果不会超过1000000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,len,res[M],ans,num,a[N],b[N];
char str[N];

void dfs(int st,int k,int sum){
    if(sum>n)
        return;
    if(st == len){
        if(sum<=n && n-sum<=ans){
            ans=n-sum;
            res[ans]++;
            memcpy(b,a,sizeof(a));
            num=k;
        }
        return;
    }
    int tp=0;
    for(int i=st;i<len;i++){
        tp=tp*10+str[i]-'0';
        a[k]=tp;
        dfs(i+1,k+1,sum+tp);
    }
}

int main(){
    while(scanf("%d%s",&n,str)){
        if(!n && str[0] =='0')
            break;
        memset(res,0,sizeof(res));
        ans=INF;
        len=strlen(str);
        dfs(0,0,0);
        if(ans == INF)
            printf("error\n");
        else{
            if(res[ans] == 1){
                printf("%d",n-ans);
                for(int i=0;i<num;i++)
                    printf(" %d",b[i]);
                printf("\n");
            }
            else
                printf("rejected\n");
        }
    }
    return 0;
}
*/
