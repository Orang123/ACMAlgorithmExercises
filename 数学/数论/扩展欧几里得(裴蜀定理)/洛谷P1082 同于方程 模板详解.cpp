#include<cstdio>
typedef long long ll;
void ext_gcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        /*
        �ٸ���ŷ����� շת�����������Լ��ת��ʱ,����b�϶������0,
        ��ʱgcd(a,b)==gcd(a,0)=ax+b(b=0)y=a,
        ��ô��ʱ��xһ������1,y��ֵ��������ȡ,����һ��Ĭ��ȡ0 �ü���.
        ֮��ͻ������ε�����������ȿ�ʼ��x0,y0
        ��չŷ�����������Ľ�ֻ��ĳһ��,�����ж����.
        */
        x=1,y=0;
        return;
    }
    ext_gcd(b,a%b,x,y);//gcd(a,b)=gcd(b,a%b)
    ll tmp=y;
    y=x-a/b*y;//y1=x2-a/b*y2; ����ת��
    x=tmp;//x1=y2
}
//ax mod b=1 ax=by+1 ʵ����ax+by=1 ����y�Ǹ�����,��ext_gcdת��ʱ���ܻ������� Ȼ�����չŷ����õ���(������)
int main(){
    ll a,b,x,y;
    scanf("%lld%lld",&a,&b);
    ext_gcd(a,b,x,y);
    x=(x%b+b)%b;
    printf("%lld\n",x);
    return 0;
}
