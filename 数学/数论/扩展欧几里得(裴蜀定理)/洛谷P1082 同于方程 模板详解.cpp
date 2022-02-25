#include<cstdio>
typedef long long ll;
void ext_gcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        /*
        再根据欧几里得 辗转相除法求解最大公约数转移时,最终b肯定会等于0,
        此时gcd(a,b)==gcd(a,0)=ax+b(b=0)y=a,
        那么此时的x一定等于1,y的值可以随意取,不过一般默认取0 好计算.
        之后就回溯依次迭代计算出最先开始的x0,y0
        扩展欧几里得所求出的解只是某一组,可能有多组解.
        */
        x=1,y=0;
        return;
    }
    ext_gcd(b,a%b,x,y);//gcd(a,b)=gcd(b,a%b)
    ll tmp=y;
    y=x-a/b*y;//y1=x2-a/b*y2; 迭代转移
    x=tmp;//x1=y2
}
//ax mod b=1 ax=by+1 实质是ax+by=1 这里y是个负数,在ext_gcd转移时可能会变成正数 然后就扩展欧几里得迭代(裴蜀定理)
int main(){
    ll a,b,x,y;
    scanf("%lld%lld",&a,&b);
    ext_gcd(a,b,x,y);
    x=(x%b+b)%b;
    printf("%lld\n",x);
    return 0;
}
