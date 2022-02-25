#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//2016-2017 ACM-ICPC, NEERC, Southern Subregional Contest (Online Mirror, ACM-ICPC Rules)
//ac 156ms ��ά01���� װ��ָ����Ʒ����������ֵ
//��������������е㲻̫���
/*
����:��nƿˮ��iƿˮ��ˮ��Ϊa[i],����Ϊb[i].��1��λˮ
��һ��ƿ��ת�Ƶ���һ��ƿ��������ʱ��Ϊ1��,�ҿ��Խ���
���޴�ת��.�󴢴�����ˮ������Сƿ����num�Լ��������������Сʱ��t.
����:http://codeforces.com/contest/730/problem/J
˼·:����װ����ˮ��Ҫ����Сƿ��������ͨ��̰�İ��ձ��������Ӵ�С����,
�ӵ�һ�����Ŀ�ʼװˮ,ֱ����ˮװ��,���ܼ����num,tʵ���Ͼ����ƶ��˵�
���ֵ��������,t��С����ζ��û���ƶ��Ĳ���������.
�ܵĵ���ʱ��=ˮ�������-ѡ�����Ҫ�����ƿ�ӵ�û���ƶ���ˮ�������.ˮ����
�����һ����ֵ,��������Ҫ������Ҫ�����ƿ�ӵ�û���ƶ���ˮ�������.
"���Ҫ�����ƿ�ӵ�û���ƶ���ˮ�������"����ͨ����άָ����Ʒ������01�������,
���ұ�����ǡ��װ������,��Ϊ���ӵ��ݻ���ԭ��������װ��ˮ �Ǳ����û���ƶ���,�̶���,
һ���ǵȼ� ��ȶ�Ӧ��,�����ܶ������.
*/
//dp[i][j]��ʾѡ��i��ƿ��,һ�����ݻ�Ϊj��ʱ��,��i��ƿ���ﱾ��û���ƶ�ˮ�����ֵ.
int n,num,dp[N][M],sum1,sum2;
struct Bottle{
    int a,b;
    bool operator < (const Bottle &x)const{
        return b>x.b;
    }
}bot[N];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].a);
        sum1+=bot[i].a;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].b);
        sum2+=bot[i].b;
    }
    sort(bot+1,bot+1+n);
    int sum=0;
    while(sum<sum1) sum+=bot[++num].b;
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int k=num;k>=1;k--){
            for(int j=sum2;j>=bot[i].b;j--)
                dp[k][j]=max(dp[k][j],dp[k-1][j-bot[i].b]+bot[i].a);
        }
    }
    int ans=0;
    //�����е㲻���,Ϊʲô���������sum2��ʼ ��һ���Ϸ�״̬���������ֵ��,�������������wa
    for(int i=sum1;<=sum2;i++)
        ans=max(ans,dp[num][i]);
    printf("%d %d",num,sum1-ans);
    return 0;
}

/*
//ac 156ms ���������ŵڶ��㽵��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,num,dp[N][M],sum1,sum2;
struct Bottle{
    int a,b;
    bool operator < (const Bottle &x)const{
        return b>x.b;
    }
}bot[N];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].a);
        sum1+=bot[i].a;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].b);
        sum2+=bot[i].b;
    }
    sort(bot+1,bot+1+n);
    int sum=0;
    while(sum<sum1) sum+=bot[++num].b;
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=sum2;j>=bot[i].b;j--){
            for(int k=1;k<=num;k++)
                dp[k][j]=max(dp[k][j],dp[k-1][j-bot[i].b]+bot[i].a);
        }
    }
    int ans=0;
    for(int i=sum1;i<=sum2;i++)
        ans=max(ans,dp[num][i]);
    printf("%d %d",num,sum1-ans);
    return 0;
}
*/

/*
//�ο�����:https://blog.csdn.net/stay_accept/article/details/53464425
//ac 124ms ���ӵ��ݻ���Ϊ��ֵ,�����б���װ��ˮ��Ϊ����
//dp[i][j]��ʾѡ��i��ƿ��,�Ѿ�װ��j���,i��ƿ�ӵ��������.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
int dp[105][10005];
struct node{
    int le,val;
    friend bool operator<(node a,node b){
        if(a.val==b.val)
        return a.le>b.le;
        return a.val>b.val;
    }
}s[105];
int main(){
    int n,i,j,k,ans1,ans2,tmp,sum;
    while(scanf("%d",&n)!=EOF){
        sum=0;
        for(i=1;i<=n;i++){
            scanf("%d",&s[i].le);
            sum+=s[i].le;
        }
        for(i=1;i<=n;i++)
        scanf("%d",&s[i].val);
        sort(s+1,s+n+1);                        //��ΪҪ��ƿ����Ŀ��С������
        tmp=0;                                  //ֱ��������ǰ׺�������С��
        for(i=1;i<=n;i++){                      //ƿ����Ŀ�����ǲ�һ��������
            tmp+=s[i].val;                      //����ƿ�ӣ������dp�ж�
            if(tmp>=sum){
                ans1=i;
                break;
            }
        }
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;                             //dp[i][j]��ʾѡ��i��ƿ�ӣ��Ѿ�
        for(i=1;i<=n;i++){                      //װ��j�����i��ƿ�ӵ��������
            for(j=sum;j>=0;j--){
                for(k=1;k<=i;k++){
                    if(j>=s[i].le&&dp[k-1][j-s[i].le]!=-1)
                    dp[k][j]=max(dp[k][j],dp[k-1][j-s[i].le]+s[i].val);
                }
            }
        }
        for(i=sum;i>=0;i--){                    //�ҳ�ans1��ƿ����װ����ˮʱ�����Сֵ
            if(dp[ans1][i]>=sum){
                ans2=sum-i;
                break;
            }
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/
