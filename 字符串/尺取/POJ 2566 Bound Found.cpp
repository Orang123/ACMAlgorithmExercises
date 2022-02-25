/*
题意:给你一个n长的序列，然后有k个询问，每个询问一个t,
问你在n长的序列中和的绝对值最接近t的为多少，并且输出此区间的左右边界。
n<=100000,0<=t<=10^9.
链接:http://poj.org/problem?id=2566
思路:尺取.可以统计出前缀和,按照前缀和从小到达排序,记录好前缀和的结束下标,
这样就能保证前缀和的单调性,就能应用尺取和作差和t做比较,好移动左右指针.
这里在排好序后,前缀和之差本身就已经是前缀和的绝对值了,无需再单独取绝对值.
*/
//ac 63ms
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

pair<int,int> pp[N];

int main(){
    int n,k,t;
    int left,right,l,r,res,ans,sum;
    while(scanf("%d%d",&n,&k)&&n+k){
        pp[0]=make_pair(0,0);
        for(int i=1;i<=n;i++){
            scanf("%d",&pp[i].first);
            pp[i].first+=pp[i-1].first;
            pp[i].second=i;
        }
        sort(pp,pp+n+1);
        while(k--){
            scanf("%d",&t);
            l=0,r=1,ans=INF;//t有可能为0,因此l和r初始化不能相等,必须l=0,r=1,否则会wa. 序列不能为空
            while(r<=n){
                res=pp[r].first-pp[l].first;
                if(abs(t-res)<ans){
                    ans=abs(t-res);
                    sum=res;
                    left=pp[l].second;
                    right=pp[r].second;
                }
                if(res>t)//比t大,l++可使得res更小 更接近t
                    l++;
                else if(res<t)//比t小,r++可使得res更大 更接近t
                    r++;
                else//res == t已经相等 就结束
                    break;
                if(l==r)//l,r作差前缀和不能相等,必须隔开 序列不能为空
                    r++;
            }
            if(left>right)//左端点下标要更小点
                swap(left,right);
            printf("%d %d %d\n",sum,left+1,right);//实际左端点因为前缀和作差,下标从left+1开始
        }
    }
    return 0;
}
