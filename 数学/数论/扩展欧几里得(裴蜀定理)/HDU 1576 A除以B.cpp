#include<cstdio>
#define mod 9973
typedef long long ll;
void ext_gcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1,y=0;
        return;
    }
    ext_gcd(b,a%b,x,y);
    ll tmp=y;
    y=x-a/b*y;
    x=tmp;
}
/*
思路:设(A/B)%9973 = k,则A/B = k + 9973x(x未知),因此A = kB + 9973xB,又A%9973 = n,
所以kB%9973 = n,,故kB = n + 9973y(y未知),故(k/n)B +(-y/n)*9973 = gcd(B,9973) = 1扩展欧几里得求出k/n,
再乘以个n,记得取模,因为k/n (-y/n)只是其中的一组解,并不一定是之前定义的(A/B)%9973,所以要取模.
*/
int main(){
    int T;
    ll B,n,x,y;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&n,&B);
        ext_gcd(B,mod,x,y);
        x=(x+mod)%mod;
        printf("%lld\n",x*n%mod);
    }
    return 0;
}
/*
https://blog.csdn.net/tigerisland45/article/details/51239640
暴力试探法
根据题意，输入的n=A%9973（没有输入A）,A%B=0（A必能被B整除），B与9973互素（GCD(B,9973)=1）。

　　解题过程首先是建立方程，然后才能编写程序。

　　设x=(A/B)%9973（x是最终想计算的值，满足0<=x<=9972），则9973k+x=A/B（k为整数），得A=9973Bk+xB。

　　因为n=A%9973与A=9973Bk+xB，所以xB%9973=n，得xB=n+9973y，亦得xB-n=9973y。

　　故：(xB-n)%9973=0
————————————————

int main(void)
{
    int t, i, j;
    long long n, b, a=9973;

    scanf("%d", &t);
    for(i=0; i<t; i++) {
        scanf("%lld%lld", &n, &b);
        for(j=0; j<a; j++)
            if((j * b - n) % a == 0) {
                printf("%d\n", j);
                break;
            }
    }

    return 0;
}
*/
