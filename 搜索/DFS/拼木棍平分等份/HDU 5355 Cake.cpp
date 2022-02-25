/*
题意:摘自网上
给定 n，m，让你把 1 ~ n 分成 m 部分，而且每部分和是一样大的。
1<=n<=100000,2<=m<=10.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5355
思路:类似拼木棍那题,但是n<=100000,直接暴力会超时,因为
n个数是连续的,因此可以按照连续2m个数为一单位,按照最大的和最小的,
次大的和次小的..最小的和最大的分别分配到第1,2,..,m组中,这样每组
必须是相等的.直到剩下不够2m个数的组 用dfs暴力枚举出m个相等的组,
只是对于剩下不够2m个数的情况,一定要加上2m,这样相等与原先预处理时
实际少处理了一组连续2m数.
dfs每个组的长度为n个数和分成m组的平均长度减去预处理的每组的长度.
对于dfs如果升序枚举会TLE,必须降序才可.dfs的最大区段是[1,4m).
实际对于dfs low>20的情况是会超时的,官方的题解是对于low>20时 会再减去m,没看太懂.

一个初始不可分m份的判断,如果n个数的和不能被m整除 则不可分,或者n个数分成m份,
每份的和比n小,也不可分,这样第n个数数值为n是必定不可分的.
*/
//ac 234ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 50
typedef long long ll;
using namespace std;

int m,low,vis[N],sum,len,cake[N];
vector<int> ans[11];
ll n;

int dfs(int pos,int num,int val){
    if(num == m+1)
        return 1;
    for(int i=low;i>=pos;i--){//这个输入数据降序 比较能较早地搜索出m份方案,否则升序会TLE
        if(vis[i] || val+i>len) continue;
        vis[i]=1;
        cake[i]=num;
        if(val+i<len){
            if(dfs(pos+1,num,val+i))
                return 1;
        }
        else if(val+i == len){
            if(dfs(0,num+1,0))
                return 1;
        }
        vis[i]=0;
        //对于刚好构成一个长度len,和初始从0开始的情况,如果之前不可分,再去枚举更小的值也仍然是不可分成m份的
        if(val+i == len)
            return 0;
        if(!val)
            return 0;
        //因为i都是不同的,因此不必判重 while(a[i] == a[i+1]) i++;
    }
    return 0;
}

int main(){
    int T;
    ll t;
    scanf("%d",&T);
    while(T--){
        sum=0;
        for(int i=1;i<=10;i++)
            ans[i].clear();
        memset(vis,0,sizeof(vis));
        scanf("%lld%d",&n,&m);
        t=n*(n+1)/2;//t是ll 否则n*(n+1)会溢出
        if(t%m || t/m<n){
            printf("NO\n");
            continue;
        }
        low=n%(2*m);
        if(low){
            low+=2*m;
            low=min(low,(int)n);
        }
        int x,y;
        for(int i=n;i>low;i-=2*m){
            for(int j=1;j<=m;j++){
                x=i-j+1;
                y=i-2*m+j;
                ans[j].push_back(x);
                ans[j].push_back(y);
                if(j==1)
                    sum+=x+y;
            }
        }
        int avg=t/m;
        len=avg-sum;
        dfs(1,1,0);//这个地方if(!dfs(1,1,0)) 会输出NO
        printf("YES\n");
        for(int i=1;i<=low;i++)
            ans[cake[i]].push_back(i);
        for(int i=1;i<=m;i++){
            printf("%d",ans[i].size());
            for(int &j : ans[i])
                printf(" %d",j);
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 202ms 类官方题解 判断了n>20的情况
//摘自博客:https://www.cnblogs.com/dwtfukgv/p/8974806.html
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <set>
#include <queue>
#include <algorithm>
#include <vector>
#include <map>
#include <cctype>
#include <cmath>
#include <stack>
#include <sstream>
#include <list>
#include <assert.h>
#include <bitset>
#include <numeric>
#define debug() puts("++++")
#define gcd(a, b) __gcd(a, b)
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define fi first
#define se second
#define pb push_back
#define sqr(x) ((x)*(x))
#define ms(a,b) memset(a, b, sizeof a)
#define sz size()
#define be begin()
#define ed end()
#define pu push_up
#define pd push_down
#define cl clear()
#define lowbit(x) -x&x
//#define all 1,n,1
#define FOR(i,n,x)  for(int i = (x); i < (n); ++i)
#define freopenr freopen("in.in", "r", stdin)
#define freopenw freopen("out.out", "w", stdout)
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> P;
const int INF = 0x3f3f3f3f;
const LL LNF = 1e17;
const double inf = 1e20;
const double PI = acos(-1.0);
const double eps = 1e-8;
const int maxn = 1e5 + 20;
const int maxm = 1e6 + 10;
const LL mod = 1000000000000000LL;
const int dr[] = {-1, 1, 0, 0, 1, 1, -1, -1};
const int dc[] = {0, 0, 1, -1, 1, -1, 1, -1};
const char *de[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
int n, m;
const int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int monn[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
inline bool is_in(int r, int c) {
  return r >= 0 && r < n && c >= 0 && c < m;
}
inline int readInt(){ int x;  scanf("%d", &x);  return x; }

int a[50][50];
int b[50];

bool dfs(int cur){
  if(cur == 0)  return true;
  for(int i = 0; i < m; ++i)  if(a[i][40] + cur <= b[i]){
    a[i][40] += cur;
    a[i][++a[i][0]] = cur;
    if(dfs(cur-1))  return true;
    a[i][40] -= cur;
    --a[i][0];
  }
  return false;
}

int main(){
  int T;  cin >> T;
  while(T--){
    scanf("%d %d", &n, &m);
    vector<int> ans[20];
    LL sum = (LL)n * (n+1) / 2;
    LL p = sum / m;
    if(sum % m || sum < (LL)n * m){ puts("NO");  continue; }
    puts("YES");
    int t = n % (m<<1);
    if(t)  t += m<<1;
    t = min(t, n);
    for(int i = t+1; i < n; i += (m<<1)){
      for(int j = 0; j < m; ++j)  ans[j].pb(i+j);
      for(int j = 0; j < m; ++j)  ans[j].pb(i+(m<<1)-j-1);
    }
    sum = t * (t+1) / 2 / m;
    for(int i = 0; i < m; ++i)  b[i] = sum;
    if(t > 20){
      for(int i = t, j = 0; j < m; ++j, --i)  b[j] -= i, ans[j].pb(i);
      t -= m;
    }
    ms(a, 0);
    dfs(t);
    for(int i = 0; i < m; ++i){
      printf("%d", ans[i].sz + a[i][0]);
      for(int j = 0; j < ans[i].sz; ++j)  printf(" %d", ans[i][j]);
      for(int j = 1; j <= a[i][0]; ++j)  printf(" %d", a[i][j]);
      printf("\n");
    }
  }
  return 0;
}
*/

/*
//ac 202ms dfs 降序
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 50
typedef long long ll;
using namespace std;

int m,low,vis[N],sum,len,cake[N];
vector<int> ans[11];
ll n;

int dfs(int i,int num,int val){
    if(num == m+1)
        return 1;
    if(!i)
    	return 0;
    if(!vis[i] && val+i<=len){
    	vis[i]=1;
    	cake[i]=num;
    	if(val+i<len){
    		if(dfs(i-1,num,val+i))
    			return 1;
		}
		else if(val+i == len){
			if(dfs(low,num+1,0))
				return 1;
		}
		vis[i]=0;
		if(val+i == len)
			return 0;
		if(!val)
			return 0;
	}
	if(dfs(i-1,num,val))
		return 1;
    return 0;
}

int main(){
    int T;
    ll t;
    scanf("%d",&T);
    while(T--){
        sum=0;
        for(int i=1;i<=10;i++)
            ans[i].clear();
        memset(vis,0,sizeof(vis));
        scanf("%lld%d",&n,&m);
        t=n*(n+1)/2;
        if(t%m || t/m<n){
            printf("NO\n");
            continue;
        }
        low=n%(2*m);
        if(low){
            low+=2*m;
            low=min(low,(int)n);
        }
        int x,y;
        for(int i=n;i>low;i-=2*m){
            for(int j=1;j<=m;j++){
                x=i-j+1;
                y=i-2*m+j;
                ans[j].push_back(x);
                ans[j].push_back(y);
                if(j==1)
                    sum+=x+y;
            }
        }
        int avg=t/m;
        len=avg-sum;
        dfs(low,1,0);//这个地方if(!dfs(1,1,0)) 会输出NO
        printf("YES\n");
        for(int i=1;i<=low;i++)
            ans[cake[i]].push_back(i);
        for(int i=1;i<=m;i++){
            printf("%d",ans[i].size());
            for(int &j : ans[i])
                printf(" %d",j);
            printf("\n");
        }
    }
    return 0;
}
*/

/*
//TLE dfs 升序
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 50
typedef long long ll;
using namespace std;

int m,low,vis[N],sum,len,cake[N];
vector<int> ans[11];
ll n;

int dfs(int i,int num,int val){
    if(num == m+1)
        return 1;
    if(i == low+1)
    	return 0;
    if(!vis[i] && val+i<=len){
    	vis[i]=1;
    	cake[i]=num;
    	if(val+i<len){
    		if(dfs(i+1,num,val+i))
    			return 1;
		}
		else if(val+i == len){
			if(dfs(1,num+1,0))
				return 1;
		}
		vis[i]=0;
		if(val+i == len)
			return 0;
		if(!val)
			return 0;
	}
	if(dfs(i+1,num,val))
		return 1;
    return 0;
}

int main(){
    int T;
    ll t;
    scanf("%d",&T);
    while(T--){
        sum=0;
        for(int i=1;i<=10;i++)
            ans[i].clear();
        memset(vis,0,sizeof(vis));
        scanf("%lld%d",&n,&m);
        t=n*(n+1)/2;
        if(t%m || t/m<n){
            printf("NO\n");
            continue;
        }
        low=n%(2*m);
        if(low){
            low+=2*m;
            low=min(low,(int)n);
        }
        int x,y;
        for(int i=n;i>low;i-=2*m){
            for(int j=1;j<=m;j++){
                x=i-j+1;
                y=i-2*m+j;
                ans[j].push_back(x);
                ans[j].push_back(y);
                if(j==1)
                    sum+=x+y;
            }
        }
        int avg=t/m;
        len=avg-sum;
        dfs(1,1,0);//这个地方if(!dfs(1,1,0)) 会输出NO
        printf("YES\n");
        for(int i=1;i<=low;i++)
            ans[cake[i]].push_back(i);
        for(int i=1;i<=m;i++){
            printf("%d",ans[i].size());
            for(int &j : ans[i])
                printf(" %d",j);
            printf("\n");
        }
    }
    return 0;
}
*/
