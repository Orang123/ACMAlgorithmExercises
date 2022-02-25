/*
题意:埃及分数
给定一个分数a/b,然后给定k个数q[i],要求把a/b分为几个不同的分子为1的最简分数,
要求分成的分数的分母中不能出现q[i].若有多种情况，输出拆分出分数最少的一种.
如果还有多种情况,应使第一大的分母最小,如果还不行,第二大最小,以此类推.
注意:埃及分数中的分母是单调递增的.
2<=a<b<=876,gcd(a,b)=1,2<=q[i]<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4003
思路:首先对于枚举的分母数字是没有明确上界的,因此无法使用bfs去枚举每一步的
所有可能状态 会MLE,因为分母必须是严格递增的,所以bfs的状态是不会重复的.
所以迭代加深搜索依次增加分数个数,枚举每一位上的分母.为了方便剪枝估价函数,
dfs时 表示的是剩余分数的值,所以要减去当前分数.
*/
//ac 2.25s IDA*
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 1100
typedef long long ll;
using namespace std;

ll res[N],ans[N];
//因为dfs中用的是剩余分数的值,回去判断当前分数分子是否为1,
//以及分母是否是 k个不能用的,而分母的值可能很大,用vis数组会数组越界.
set<ll> vis;

ll gcd(ll a,ll b){
    return !b?a:gcd(b,a%b);
}

int check(int d){
    for(int i=d;i>=0;i--){//当分数个数相同时,从后往前判断,如果不相等时,如果当前分母值更小 则更新.
        if(res[i]!=ans[i])//这个条件不能丢
            return ans[i] == -1 || res[i]<ans[i];
    }
    return 0;//原则上 是不会出现和之前完全相等的 情况的
}

int dfs(int d,int dep,ll a,ll b,ll st){
    if(d == dep){
        if(a == 1 && !vis.count(b)){//剩余的分数 分子刚好为1,分母不在不可使用范围内即可
            res[d]=b;//第d+1个分数是1/b
            if(check(d)){//判断是否比之前分母更小
                for(int j=0;j<=d;j++)//实际有d+1个分数 因为下标0..d
                    ans[j]=res[j];
                return 1;
            }
        }
        return 0;
    }
    int ok=0;
    st=max(st,b/a+1);//st要取分母递增的下一个 但要和实际剩余分数a/b b/a+1取最大值,有可能1/(i+1)要大于b/a
    for(ll i=st;;i++){
        if(vis.count(i))//i 不能使用
            continue;
        //剪枝:如果后面dep+1-d个数全部用1/i 小于等于剩下的a/b则返回,等于是因为实际分母必须是递增的
        //1/i * (dep-d+1)<=a/b
        if(b*(dep-d+1)<=a*i)//因为实际分数个数是dep+1个数,因为分数小标是从0..d
            break;
        ll bb=b*i;//分母通分
        ll aa=a*i-b;//分子要减去b,表示加上1/i还剩下的分数
        ll g=gcd(aa,bb);
        res[d]=i;
        //分数要化简除g,分母单调递增因此i+1
        if(dfs(d+1,dep,aa/g,bb/g,i+1))//因为 分数个数一致时,要输出从后往前分母较大的解,因此这里不能直接结束
            ok=1;
    }
    return ok;
}

int main(){
    int T,k,cas=0;
    ll a,b,x;
    scanf("%d",&T);
    while(T--){
        cas++;
        vis.clear();
        memset(ans,-1,sizeof(ans));
        scanf("%lld%lld%d",&a,&b,&k);
        while(k--){
            scanf("%lld",&x);
            vis.insert(x);
        }
        for(int i=1;;i++){
            //b/a+1表示 a/b的分数和 中起始所能取的最小分母的下界
            if(dfs(0,i,a,b,b/a+1)){
                printf("Case %d: %lld/%lld=",cas,a,b);
                for(int j=0;j<=i;j++){
                    printf("1/%lld",ans[j]);
                    if(j!=i)
                        printf("+");
                }
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
//RE TLE 暴力dfs
//RE 是因为实际先搜索到的方案,分数个数很多,没有明确上界,TLE 也是肯定的,首先样例输出就比较慢了
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 1100000
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int num;
ll res[N],ans[N];
set<ll> vis;

ll gcd(ll a,ll b){
    return !b?a:gcd(b,a%b);
}

int check(int d){
    for(int i=d;i>=0;i--){
        if(res[i]!=ans[i])
            return res[i]<ans[i];
    }
}

void dfs(int d,ll a,ll b,ll st){
    if(a == 1 && !vis.count(b) && d<=num){
        res[d]=b;
        if(d<num || (d==num && check(d))){
        	num=d;
            for(int j=0;j<=d;j++)
                ans[j]=res[j];
		}
        return;
    }
    st=max(st,b/a+1);
    for(ll i=st;;i++){
        if(vis.count(i))
            continue;
        if(b*(num-d+1)<=a*i)
            break;
        ll bb=b*i;
        ll aa=a*i-b;
        ll g=gcd(aa,bb);
        res[d]=i;
        dfs(d+1,aa/g,bb/g,i+1);
    }
}

int main(){
    int T,k,cas=0;
    ll a,b,x;
    scanf("%d",&T);
    while(T--){
        cas++;
        vis.clear();
        num=INF;
        scanf("%lld%lld%d",&a,&b,&k);
        while(k--){
            scanf("%lld",&x);
            vis.insert(x);
        }
        dfs(0,a,b,b/a+1);
        printf("Case %d: %lld/%lld=",cas,a,b);
        for(int j=0;j<=num;j++){
            printf("1/%lld",ans[j]);
            if(j!=num)
                printf("+");
        }
        printf("\n");
    }
    return 0;
}
*/
