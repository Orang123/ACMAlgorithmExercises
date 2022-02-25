/*
����:����һ��n�����n��Χ�ں���13�����ܱ�13�����ĸ���
n<=10^9.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3652
˼·:������λdp.����һ��ǰk-1λȡģ��������Ϊdp��ά��.
dp[k][mod][pre]��ʾn����λ��len��k-1λ��13ȡģΪmod(�������������λ�±�)
�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ����㲻����"13"�Ĳ����ܱ�13���������ִ��ĸ���
*/
//ac 0ms ���仯����
//dp[k][mod][pre]��ʾn����λ��len��k-1λ��13ȡģΪmod(�������������λ�±�)�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ����㲻����"13"�Ĳ����ܱ�13���������ִ��ĸ���
//pre == 0��ʾ��һλ����1
//pre == 1��ʾ��һλ��1
//pre == 2��ʾǰ����λ���ֹ�13
//�ռ临�Ӷ�O(10*13*3)=390
//ʱ�临�Ӷ�O(10*10*13*3)=3900
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
using namespace std;

int n,len,dp[N][13][3],a[N];

int dfs(int k,int mod,int pre,int limit){
    if(!k)
        return pre == 2 && !mod;
    if(!limit && dp[k][mod][pre]!=-1)
        return dp[k][mod][pre];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++){
        int val=(mod*10+i)%13;
        if(!pre || (pre == 1 && i!=3))
            ans+=dfs(k-1,val,i == 1,limit && i == last);
        else
            ans+=dfs(k-1,val,2,limit && i == last);
    }
    if(!limit)
        dp[k][mod][pre]=ans;
    return ans;
}

int main(){
    memset(dp,-1,sizeof(dp));//dp����ֻ�ó�ʼ��һ��,�����������Թ���֮ǰ�����dpֵ
    while(scanf("%d",&n)!=EOF){
        len=0;
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        printf("%d\n",dfs(len,0,0,1));
    }
    return 0;
}

/*
//ac 0ms ������� û��
//ժ�Բ���:https://blog.csdn.net/with_passion/article/details/50605223
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int (i) = 0;i < (n);i++)
int f[15][3][13];
int bit[12];
void init()
{
    memset(f,0,sizeof(f));
    bit[1] = 1;
    for(int i = 2;i < 11;i++) bit[i] = bit[i-1]*10%13;
    f[0][0][0] = 1;
    for(int i = 0;i <= 10;i++)
    for(int k = 0;k < 13;k++){//ֱ�Ӱ�����Ҫ����������
        for(int j = 0;j <= 9;j++)
            f[i+1][0][(k+j*bit[i+1])%13] += f[i][0][k];
        f[i+1][0][(k+bit[i+1])%13] -= f[i][1][k];
        f[i+1][1][(k+bit[i+1]*3)%13] += f[i][0][k];//ָ������~~;
        f[i+1][2][(k+bit[i+1])%13] += f[i][1][k];
        for(int j = 0;j <= 9;j++)
            f[i+1][2][(k+bit[i+1]*j)%13] += f[i][2][k];
    }
}
int query(int n)
{
    int d[15]={},tot = 0;
    while(n){
        d[++tot] = n % 10;
        n /= 10;
    }
    int ans = 0,mod = 0,flag = 0;
    for(int i = tot;i > 0;mod = (mod + d[i]*bit[i])%13,i--){
        for(int j = 0;j < d[i];j++)
            ans += f[i-1][2][(13 - (mod + j*bit[i])%13)%13];
        if(flag){
            for(int k = 0;k < d[i];k++){
                ans += f[i-1][0][(13 - (mod + k * bit[i])%13)%13];
            }
            continue;
        }
        if(d[i] > 1) ans += f[i-1][1][(13 - (mod + bit[i])%13)%13];
        if(d[i+1] == 1 && d[i] > 3) ans += f[i][1][(13-mod)%13];
        if(d[i+1] == 1 && d[i] == 3) flag = 1;
    }
    return ans;
}
int main()
{
    init();
    int n;
    while(scanf("%d",&n) == 1){
        printf("%d\n",query(n+1));
    }
}
*/
