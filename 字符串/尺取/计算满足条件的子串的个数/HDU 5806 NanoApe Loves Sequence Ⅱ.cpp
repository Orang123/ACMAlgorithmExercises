/*
题意:摘自网上
给你n，m，k，并且给你n个数列，问有多少个区间满足第k大的数不小于m？
2<=n<=200000,1<=m<=10^9,1<=k<=100000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5806
思路:尺取.只要保证连续子串中不小于m的数的个数为k,就能保证区间
第k大的数不小于m.
*/
//ac 546ms
//当时 复制粘贴leetcode时 把之前写的 覆盖了...
//这是csdn重新找的
#include <iostream>
#include <cstdio>
#include<vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N=2e5+10;
int a[N];
int s,e,cnt;
int n,m,k;

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);

        LL ans=0;
        cnt=e=0;

        for(s=1;s<=n;s++)
        {
            while(cnt<k&&e<=n)
            {
                if(a[++e]>=m)
                    cnt++;
            }
            if(cnt>=k)
                ans+=n-e+1;
            if(a[s]>=m)
                --cnt;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
//这时粘贴错误的leetcode 904水果成蓝
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;
typedef long long ll;

int n,m,k,a[N],num;
ll ans;

int main(){
        unordered_map<int,int> mp;
        int l=0,r=0,ans=0,n=fruits.size();
        while(r<n){
            while(r<n && mp.size()<=2)
                mp[fruits[r++]]++;
            if(r == n && mp.size()>2)
                break;
            ans=max(ans,r-l);
            if(!--mp[fruits[l]])
                mp.erase(fruits[l]);
            l++;
        }
    return 0;
}

/*
//ac 546ms 乘法原理
//摘自博客:https://tigerisland.blog.csdn.net/article/details/77394544
#include <iostream>
#include <stdio.h>

using namespace std;

const int N = 200000;
int a[N];
long long d[N];

int main()
{
    int t, n, m, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &k);

        int j=0;
        long long sum=0;
        for(int i=0; i<n; i++) {
            scanf("%d", &a[i]);

            if(a[i] >= m) {
                d[j++] = i + 1;
                if(j == k)
                    sum += d[0] * (n - i);
                else if(j > k)
                    sum += (d[j - k] - d[j - k - 1]) * (n - i);
            }
        }

        printf("%lld\n", sum);
    }
    return 0;
}
*/
