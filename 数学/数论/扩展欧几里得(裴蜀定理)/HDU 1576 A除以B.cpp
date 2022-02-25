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
˼·:��(A/B)%9973 = k,��A/B = k + 9973x(xδ֪),���A = kB + 9973xB,��A%9973 = n,
����kB%9973 = n,,��kB = n + 9973y(yδ֪),��(k/n)B +(-y/n)*9973 = gcd(B,9973) = 1��չŷ��������k/n,
�ٳ��Ը�n,�ǵ�ȡģ,��Ϊk/n (-y/n)ֻ�����е�һ���,����һ����֮ǰ�����(A/B)%9973,����Ҫȡģ.
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
������̽��
�������⣬�����n=A%9973��û������A��,A%B=0��A���ܱ�B��������B��9973���أ�GCD(B,9973)=1����

����������������ǽ������̣�Ȼ����ܱ�д����

������x=(A/B)%9973��x������������ֵ������0<=x<=9972������9973k+x=A/B��kΪ����������A=9973Bk+xB��

������Ϊn=A%9973��A=9973Bk+xB������xB%9973=n����xB=n+9973y�����xB-n=9973y��

�����ʣ�(xB-n)%9973=0
��������������������������������

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
