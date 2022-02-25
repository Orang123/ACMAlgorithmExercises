/*
题意:给你一个数n，询问有多少种连续自然数的平方和等于这个数，输出所有可能
n<=10^14.
链接:http://poj.org/problem?id=2100
思路:尺取,数的上界设置为 sqrt(n)+1.
*/
//ac 3875ms
//len=sqrt(n)+1;r<len;
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

ll n,l,r,len,sum;
vector<pair<ll,ll> > ans;

int main(){
    scanf("%lld",&n);
    len=sqrt(n)+1;
    l=r=1;
    while(1){
        while(r<len && sum<n){
            sum+=r*r;
            r++;
        }
        if(sum<n)
            break;
        if(sum == n)
            ans.push_back(make_pair(l,r-1));
        sum-=l*l;
        l++;
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++){
        printf("%d",ans[i].second-ans[i].first+1);
        for(ll j=ans[i].first;j<=ans[i].second;j++)
            printf(" %lld",j);
        printf("\n");
    }
    return 0;
}

/*
//ac 3797ms
//len=sqrt(n);r<=len;
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

ll n,l,r,len,sum;
vector<pair<ll,ll> > ans;

int main(){
    scanf("%lld",&n);
    len=sqrt(n);
    l=r=1;
    while(1){
        while(r<=len && sum<n){
            sum+=r*r;
            r++;
        }
        if(sum<n)
            break;
        if(sum == n)
            ans.push_back(make_pair(l,r-1));
        sum-=l*l;
        l++;
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++){
        printf("%d",ans[i].second-ans[i].first+1);
        for(ll j=ans[i].first;j<=ans[i].second;j++)
            printf(" %lld",j);
        printf("\n");
    }
    return 0;
}
*/

/*
//wa l,r 双循环 不知何原因wa
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

ll n,l,r,len,sum;
vector<pair<ll,ll> > ans;

int main(){
    scanf("%lld",&n);
    len=sqrt(n)+1;
    l=r=1;
    while(1){
        while(r<len && sum<n){
            sum+=r*r;
            r++;
        }
        if(sum<n)
            break;
        while(sum>=n){
            sum-=l*l;
            l++;
            if(sum == n)
                ans.push_back(make_pair(l,r-1));
        }
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++){
        printf("%d",ans[i].second-ans[i].first+1);
        for(ll j=ans[i].first;j<=ans[i].second;j++)
            printf(" %lld",j);
        printf("\n");
    }
    return 0;
}
*/
