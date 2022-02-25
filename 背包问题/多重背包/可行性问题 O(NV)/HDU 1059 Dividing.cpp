/*
题意:有价值为1~6的6种大理石各num[i]块,判断是否能将所有的大理石的对半分给两个人
使得两人大理石价值和相等.
思路:多重背包 价值和能否平分,价值和的一半作为背包容量.
*/
//ac 405ms 二进制优化01背包 复杂度O(∑log(num[i])*v)=6*log(20000)*60000=5*10^6
#include<bits/stdc++.h>
#define N 7
#define M 60000
using namespace std;

int cas,num[N],dp[M],sum;

int main(){
    int sum;
    while(scanf("%d%d%d%d%d%d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])){
        if(num[1]+num[2]+num[3]+num[4]+num[5]+num[6] == 0) break;
        cas++;
        sum=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=6;i++)
            sum+=i*num[i];
        printf("Collection #%d:\n",cas);
        if(sum%2){//不能被2整除 就不能平分
            printf("Can't be divided.\n\n");
            continue;
        }
        sum/=2;//它的一半若能装满,整体自然也就能平分
        int tw;
        for(int i=1;i<=6;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=i*k;
                for(int j=sum;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tw);
            }
        }
        if(dp[sum]==sum)
            printf("Can be divided.\n\n");
        else
            printf("Can't be divided.\n\n");
    }
    return 0;
}

/*
//ac 78ms 可行性 背包九讲做法
//不知为何 完全背包限制数量的做法会wa
#include<bits/stdc++.h>
#define N 7
#define M 60000
using namespace std;

int cas,num[N],dp[M],cnt[N],sum;

int main(){
    int sum,tp;
    while(scanf("%d%d%d%d%d%d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])){
        if(num[1]+num[2]+num[3]+num[4]+num[5]+num[6] == 0) break;
        cas++;
        sum=0;
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=6;i++)
            sum+=i*num[i];
        printf("Collection #%d:\n",cas);
        if(sum%2){//不能被2整除 就不能平分
            printf("Can't be divided.\n\n");
            continue;
        }
        tp=sum/2;//它的一半若能装满,整体自然也就能平分
        dp[0]=0;
        for(int i=1;i<=6;i++){
            for(int j=0;j<=tp;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=i)
                    dp[j]=max(dp[j],dp[j-i]-1);
            }
        }
        if(dp[tp] != -1)
            printf("Can be divided.\n\n");
        else
            printf("Can't be divided.\n\n");
    }
    return 0;
}
*/

/*
//TLE 朴素01背包做法 复杂度O(∑num[i]*v)=120000*60000=7.2*10^9
#include<bits/stdc++.h>
#define N 7
#define M 60000
using namespace std;

int cas,num[N],dp[M],sum;

int main(){
    int sum;
    while(scanf("%d%d%d%d%d%d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])){
        if(num[1]+num[2]+num[3]+num[4]+num[5]+num[6] == 0) break;
        cas++;
        sum=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=6;i++)
            sum+=i*num[i];
        printf("Collection #%d:\n",cas);
        if(sum%2){//不能被2整除 就不能平分
            printf("Can't be divided.\n\n");
            continue;
        }
        sum/=2;//它的一半若能装满,整体自然也就能平分
        for(int i=1;i<=6;i++){
            for(int j=sum;j>=i;j--){
                for(int k=1;k<=num[i]&&k*i<=j;k++)
                    dp[j]=max(dp[j],dp[j-k*i]+k*i);
            }
        }
        if(dp[sum]==sum)
            printf("Can be divided.\n\n");
        else
            printf("Can't be divided.\n\n");
    }
    return 0;
}
*/

/*
//TLE 朴素01背包做法 复杂度O(∑num[i]*v)=120000*60000=7.2*10^9
#include<bits/stdc++.h>
#define N 7
#define M 60000
using namespace std;

int cas,num[N],dp[M],sum;

int main(){
    int sum;
    while(scanf("%d%d%d%d%d%d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])){
        if(num[1]+num[2]+num[3]+num[4]+num[5]+num[6] == 0) break;
        cas++;
        sum=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=6;i++)
            sum+=i*num[i];
        printf("Collection #%d:\n",cas);
        if(sum%2){//不能被2整除 就不能平分
            printf("Can't be divided.\n\n");
            continue;
        }
        sum/=2;//它的一半若能装满,整体自然也就能平分
        int tw;
        for(int i=1;i<=6;i++){
            for(int k=1;num[i]>0;k++){
                num[i]-=k;
                tw=i*k;
                for(int j=sum;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tw);
            }
        }
        if(dp[sum]==sum)
            printf("Can be divided.\n\n");
        else
            printf("Can't be divided.\n\n");
    }
    return 0;
}
*/

