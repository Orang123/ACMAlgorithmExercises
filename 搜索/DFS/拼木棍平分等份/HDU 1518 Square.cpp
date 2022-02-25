/*
题意:摘自网上
n个棍子，要求将所有的棍子都用上，拼成一个正方形。
n<=20.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1518
思路:需要枚举每条边用哪些棍子拼凑,对这个问题来说,同一条
边上的棍子 和选取顺序无关,只在于具体选的哪些棍子,因此对于
不同的边与边上的棍子是排列问题,而对于同一条边上的棍子是
类背包选取与否的问题,所以对于新的边(长度为0时)枚举的下界
是从第一根棍子开始,而对于一条边上往后枚举的棍子应该是紧跟上一个
枚举的棍子的.
有4个剪枝:
1.当棍子总长不能整除4时,不能构成正方形.
2.当最长的棍子大于边长时,不能构成正方形.
3.对于同一位置枚举相同长度的棍子时 对于重复排列要去重.
当前长度和前一个一样且前一个不使用，当前也不使用
4.当能凑出三条合法边时,剩下一条边一定能凑出来.

还有2个剪枝同UVA 307 Sticks
1.!len 初始从0开始失败 直接返回0
2.a[i]+len == b 凑整失败 直接返回0
*/
//ac 483ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int pos,int k){
    if(k == 3)//当能凑出三条合法边时,剩下一条边一定能凑出来.
        return 1;
    for(int i=pos;i<=n;i++){
        if(!vis[i]){
            //当前长度和前一个一样且前一个不使用，当前也不使用
            if(a[i] == a[i-1] && !vis[i-1])//第i-1个棍子必须未使用,是在当前dfs循环层,如果是前一个父dfs里i-1是使用的 则是可以的.
                continue;
            if(len+a[i]>b)//棍子长度是升序的,如果当前第i个加上大于边长,剩下的也必然大于边长,直接返回
                break;
            vis[i]=1;
            if(len+a[i]<b){//同一条边上继续 按接下来的棍子i+1序号 累加
                if(dfs(len+a[i],i+1,k))
                    return 1;
            }
            else if(len+a[i] == b){//当前边已经凑出来,要凑新的边,枚举棍子的顺序从第一个棍子开始
                if(dfs(0,1,k+1))
                    return 1;
            }
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}

/*
//ac 343ms dfs+4剪枝
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int pos,int k){
    //剪枝1
    if(k == 3)//当能凑出三条合法边时,剩下一条边一定能凑出来.
        return 1;
    for(int i=pos;i<=n;i++){
        if(vis[i]) continue;
        vis[i]=1;
        if(a[i]+len<b){//同一条边上继续 按接下来的棍子i+1序号 累加
            if(dfs(len+a[i],i+1,k))
                return 1;
        }
        else if(a[i]+len  == b){//当前边已经凑出来,要凑新的边,枚举棍子的顺序从第一个棍子开始
            if(dfs(0,1,k+1))
                return 1;
        }
        vis[i]=0;
        //剪枝2、3
        if(!len || a[i]+len == b)
            return 0;
        //剪枝4
        while(i+1<=n && a[i] == a[i+1])
            i++;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
*/

/*
//ac 608ms dfs+4剪枝
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int i,int k){
    //剪枝1
    if(k == 3)//当能凑出三条合法边时,剩下一条边一定能凑出来.
        return 1;
    if(i == n+1)
        return 0;
    if(!vis[i]){
        vis[i]=1;
        if(a[i]+len<b){//同一条边上继续 按接下来的棍子i+1序号 累加
            if(dfs(len+a[i],i+1,k))
                return 1;
        }
        else if(a[i]+len  == b){//当前边已经凑出来,要凑新的边,枚举棍子的顺序从第一个棍子开始
            if(dfs(0,1,k+1))
                return 1;
        }
        vis[i]=0;
        //剪枝2、3
        if(!len || a[i]+len == b)
            return 0;
        //剪枝4
        while(i+1<=n && a[i] == a[i+1])
            i++;
    }
    if(dfs(len,i+1,k))
        return 1;
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
*/
