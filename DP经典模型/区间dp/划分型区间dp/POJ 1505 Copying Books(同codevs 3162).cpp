#include<cstdio>//dp做法 534ms
#include<cstring>
#include<algorithm>
using namespace std;

int dp[550][550],m,k,a[550],sum[550],pos[550];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&m,&k);
        for(int i=1;i<=m;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=m;i++)
            sum[i]=sum[i-1]+a[i];
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=m;i++)
            dp[i][1]=sum[i];
        for(int t=2;t<=k;t++){
            for(int i=t;i<=m;i++){
                for(int j=t-1;j<i;j++)
                    dp[i][t]=min(dp[i][t],max(dp[j][t-1],sum[i]-sum[j]));
            }
        }
        int tmp=0,p=k-1;
        for(int i=m;i>=1;i--){
            tmp+=a[i];
            if(tmp>dp[m][k] || i<=p){//i<=p 当tmp<=dp[m][k]时尽可能让前面人少朝,因此前面的书尽可能多地平均分给前面的人
                tmp=a[i];
                pos[p--]=i+1;
            }
        }
        for(int i=1,j=1;i<=m;i++){
            if(i>1)
                printf(" ");
            if(j<k && pos[j] == i){//j<k应该避免最后一个人抄的书 加上多余的'/'
                printf("/ ");
                j++;
            }
            printf("%d",a[i]);
        }
        printf("\n");
    }
    return 0;
}

/*
二分 最大值最小化 做法 94ms
#include<cstdio>
#include<cstring>
using namespace std;
int book[505];
bool flag[505];
int m,k;
int cnt;
int copy(long long x)
{
    cnt=1;
    long long sum=0;
    memset(flag,false,sizeof(flag));
    for(int i=m-1;i>=0;i--)
    {
        sum+=book[i];
        if(sum>x)
        {
            cnt++;
            sum=book[i];
            flag[i]=true;
        }

    }
    return cnt;
}
void print()
{
    printf("%d",book[0]);
    for(int i=1;i<m;i++)
    {
        if(flag[i-1])   printf(" /");
        printf(" %d",book[i]);
    }
    printf("\n");

}
int main()
{
        int T;
        long long l,r;
        scanf("%d",&T);
        while(T--)
        {
            scanf("%d%d",&m,&k);
            l=r=0;
            for(int i=0;i<m;i++)
            {
                scanf("%d",&book[i]);
                if(book[i]>l)    l=book[i];
                r+=book[i];

            }
            long long mid;
            while(l<r)
            {
                mid=(l+r)/2;
                if(copy(mid)<=k)    r=mid;
                else l=mid+1;
            }
            int cnt=copy(r);
            for(int i=0;i<m&&cnt<k;i++)
            {
                if(!flag[i])   flag[i]=true,cnt++;


            }
          print();

        }
    return 0;
}
*/
