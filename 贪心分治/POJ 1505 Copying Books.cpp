//二分 最大值最小化 做法 94ms
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

