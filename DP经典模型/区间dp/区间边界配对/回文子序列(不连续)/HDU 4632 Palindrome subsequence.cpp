#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];
/*
����:���һ���ַ����ﺬ�ж��ٻ���������.
��ʾ:�����в�һ��Ҫ����,�±���Էָ�.
��:aaa ����7������������,a(3��) aa(2��([12][23])+1��([13])) aaa([123])
����:http://acm.hdu.edu.cn/showproblem.php?pid=4632
��ͳ�ı�����֪�������.����ֻ�ܴ�С��״̬ת�Ƶ����״̬,���ܽ��������.
˼·:������ĵ�����,��״̬ת�Ƶ�ʱ��,ֻ�ǵ�����ָ������������Ĳ��������Ž�,
��[1,6]=[1,3]+[4,6]����ֻ�����[1,3]��[4,6]2������Ļ��������еĸ����ܺ�,
����[1,3]��[4,6]�������ַ������໥��Ϲ����µĻ���������.
���aaa�������ֻ����������Ž�max([1,1]+[2,3],[1,2]+[3,3])=4
ֻ������һ��aa,����[1,1][2,3]����[2,3]��aa��,s���޷�����[1,2]���aa,�ڶ��ַָ��ͬ��.
���Կ��Բ�ȡ�ݳ�ԭ��dp[i][j]=max(dp[i][j],dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]);,�����м佻���Ĳ��־Ͷ��ܼ����ȥ.
*/
//ö�����䳤����ʼ��
int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                /*
                �ݳ�ԭ�� ����պû���м�Ĳ��ֶ����һ��,����Ҫ����.
                dp[i][j-1]��dp[i+1][j]��dp[i+1][j-1]�Ѿ���ȡģ��Ľ����,
                ���Դ�С�������ȷ��,��ȥdp[i+1][j-1]�п��ܽ��Ϊ��,
                ����Ҫ�ټ���mod����ȡģ.
                */
                dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
                if(a[i] == a[j])
                /*
                �������������Ҷ˵���ͬ,��a[i]a[j]�ɹ���һ������������+1,
                ���������ɺ��м��a[i+1][j-1]�Ļ����������ٶ���Ϲ����µĻ���������,
                ���Ҫ�ټ���dp[i+1][j-1].
                */
                    dp[i][j]=(dp[i][j]+dp[i+1][j-1]+1)%mod;
            }
        }
        printf("Case %d: %d\n",cas,dp[1][len]);
    }
	return 0;
}
/*
ö������2�˵�dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];

int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int i=len-1;i>=1;i--){
            for(int j=i+1;j<=len;j++){
                dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
                if(a[i] == a[j])
                    dp[i][j]=(dp[i][j]+dp[i+1][j-1]+1)%mod;
            }
        }
        printf("Case %d: %d\n",cas,dp[1][len]);
    }
	return 0;
}
*/
/*
���仯����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100];
char a[1100];

int dfs(int st,int ed){
    if(st == ed) return dp[st][ed]=1;
    if(st>ed) return 0;
    if(dp[st][ed]) return dp[st][ed];
    //һ��Ҫ�ȼ����ݳ��ⲿ�ֵĴ�,����dp[st+1][ed-1]����ֱ���ý��
    //�����ȼ���dfs(st+1,ed-1),dp[st+1][ed] dp[st][ed-1]����Ҫ���µݹ����.
    dp[st][ed]=(dfs(st,ed-1)+dfs(st+1,ed)-dp[st+1][ed-1]+mod)%mod;
    if(a[st] == a[ed])
        dp[st][ed]=(dp[st][ed]+dp[st+1][ed-1]+1)%mod;
    return dp[st][ed];
}

int main(){
    int T,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",a+1);
        len=strlen(a+1);
        printf("Case %d: %d\n",cas,dfs(1,len));
    }
	return 0;
}
*/
