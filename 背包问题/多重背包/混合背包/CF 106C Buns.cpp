/*
����:����n�˵����m����,���ֻ���������,����c0�˵���,��һ����ֵΪd0����ͷ.
������m����ÿ�ֶ���a��b��c��d������,a��ʾ���ж��ٿ�,bΪ��һ�����и��ڵ����
������ڵ���,c�������и��ڵ��������������,dΪ������������еļ�ֵ,��n����
m���������������ܵõ����ټ�ֵ.
1<=a,b,c,d<=100 n<=1000,m<=10
����:http://codeforces.com/problemset/problem/106/C
˼·:��������Ƿ�����,Ҫ���������һ��Ҫ���.������ۿ���Ϊ���������һ������.
���������������������n��.
��ʱ����Ҫ�����������������ֻ����������������+������,�������+�ڵ�������m��,
ֻ����۵�ֻ��1��,����ʵ�ʾ�������m+1����������,������������ʹ�û�õļ�ֵ���.
������ֻ����������������һ����ȫ����,��Ϊ��n�������Ϊ��������������,��Щ��ۿ���
�����ܶ�ص���ȫ�������Ƴ�ֻ����۵����,�������ʣ��,���ʵ����Ʒ��������������.
ʵ���ж���ȫ���������پ�������Ʒ��������,ʵ��ֻҪ����������Ʒ�����ܶ��װ��������,
��:װ���,������ʣ���ݻ�����������Ʒ�����.
���������+�ڹ��� ÿ����Ʒʵ�ʵ���Ʒ������a/b.��һ�����ر�������,��ʵ��
O(nv)=(10*100+1)*1000=10^6.1sʱ�޿���ֱ����01�������.
*/
//ac 60ms ��ϱ���(��ȫ����+���ر���)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,c0,d0,a,b,c,d,num,dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d%d",&n,&m,&c0,&d0);
    /*
    //̰��
    for(int j=c0;j<=n;j++)
        dp[j]=j/c0*d0;
    */
    for(int i=c0;i<=n;i++)
        dp[i]=max(dp[i],dp[i-c0]+d0);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        num=a/b;
        for(int k=1;k<=num;k++){
            for(int j=n;j>=c;j--)
                dp[j]=max(dp[j],dp[j-c]+d);
        }
    }
    printf("%d",dp[n]);
    return 0;
}

/*
//ac 62ms ��ȫ����+�����Ʋ�ֵ�01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,c0,d0,a,b,c,d,num,dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d%d",&n,&m,&c0,&d0);
    for(int i=c0;i<=n;i++)
        dp[i]=max(dp[i],dp[i-c0]+d0);
    int tw,tv;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        num=a/b;
        for(int k=1;num>0;k<<=1){
            num-=k;
            if(num<0) k+=num;
            tw=c*k;
            tv=d*k;
            for(int j=n;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d",dp[n]);
    return 0;
}
*/
