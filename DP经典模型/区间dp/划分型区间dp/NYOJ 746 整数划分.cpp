/*
����:http://nyoj.top/problem/746,http://acm.nyist.net/JudgeOnline/status.php?pid=746
��������
ʱ�����ƣ�1000 ms  |  �ڴ����ƣ�65535 KB
�Ѷȣ�3

����
������ˣ�hrdv ��Ҫ��ѧУ�ڲμ�ACM��ѵ�ˣ���ѵ������ǳ�Happy��ps���㶮�ã������������������һ�����⣬
������˼������⣬���ǳ����ơ��װ������ܰ������
���������Ǿ����������������֣������������� n , m ,Ҫ���� n �м���m - 1 ���˺ţ���n�ֳ�m�Σ������m�ε����˻�

����
��һ����һ������T����ʾ��T���������
������T�У�ÿ�������������� n��m ( 1<= n < 10^19, 0 < m <= n��λ��)��

���
���ÿ������������Ϊһ������ռһ��

��������
2
111 2
1111 2
�������
11
121
*/
/*
num[i][j]��¼s[i]~s[j]������ĵ�10������ֵ
dp[i][j] ����1��j������i���˺ź����˵������ֵ
˼·:���ȴ�ͳ�����ֱ���ö�� m-1���˺ų��ֵ�λ��,�������û����֦,���Ӷ�̫��,��TLE.
����dp����仯����.
�Ƽ��ü��仯���� д����Ҫ���׺ܶ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
char s[50];
int main(){
    int T,m,len;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){//��ʼ��num�����dp[0][i]��ֵ
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
            dp[0][i]=num[1][i];//[1,i]���ӳ˺ŵ���ֵ����num[1][i]
        }
        /*
        �����Ŀ,��Ϊ���ܼ��뼸���˺�,����ʱ�����������ֶ��������,����״̬��ת��,
        ��Ȼ������С���䵽������,Ӧ���������ڳ˺ŵĸ���ת�Ƶ��˺�+1����������,�Ҷ˵����䳤��
        ����ֻ��ת�ƹ�����һ��ά�ȵ�ö�ټ���,ת�Ƶ���Ҫ״̬��Ӧ�ǳ˺Ÿ���,��Ȼ��̫��дdp.
        ������Ϊ�������ͻ��漰��������������,��������ö�����䳤��,ֻ��ö��1~j,j����Ҷ˵�ȡ
        ������.
        */
        //��ʵ����m-1���˺�,���Ƿָ��m������,����dp������ȫ�ο� leetcode 813 ���ƽ��ֵ�͵ķ���
        //ʱ�临�Ӷ�O(len^3)
        for(int i=1;i<=m-1;i++){//��1��ʼö�ټ���˺ŵĸ���
            for(int j=i+1;j<=len;j++){//ö�������Ҷ˵�[1,j],��ʼ�Ҷ˵�Ϊi+1,��ΪҪ����i���˺�����Ҫ��i+1����
                //for(int k=i+1;k<=j;k++)//[k,j]��Ϊ��i���� ǰk-1������i-1����,������Ҫi���� ��:k-1>=i,k>=i+1,k���½�i+1
                    //dp[i][j]=max(dp[i][j],dp[i-1][k-1]*num[k][j]);
                for(int k=i;k<j;k++)//dp[i-1][k]ǰk��������i-1���˺�,������Ҫ��i����,k���½�Ϊi ��[k+1,j]�ֳɵ�i����
                    dp[i][j]=max(dp[i][j],dp[i-1][k]*num[k+1][j]);
            }
        }
        printf("%lld\n",dp[m-1][len]);//�������len�������м���m-1���˺����õ������ֵ
    }
	return 0;
}

/*
//���仯���� dp[st][k]��ʾ������[st,len]��Χ��,���k-1���˺ż�:�ֳ�k������,�������������۳˽��
//�ռ临�Ӷ�o(n*m) ʱ�临�Ӷ�O(n^2*m)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
int len,m;
char s[50];

ll dfs(int st,int k){
    if(k == 1)
        return num[st][len];
    if(st == len+1)//û�зֹ�k������ ���������Ѿ����� ���Ϸ�״̬
        return 0;
    ll &ans=dp[st][k];
    if(ans!=-1)//��ʼ״̬Ϊ-1
        return ans;
    for(int i=st;i<=len;i++)
        ans=max(ans,num[st][i]*dfs(i+1,k-1));
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
        }
        printf("%lld\n",dfs(1,m));
    }
	return 0;
}
*/

/*
//���仯���� dp[st][k]��ʾ������[st,len]��Χ��,���k-1���˺ż�:�ֳ�k������,�������������۳˽��
//�ռ临�Ӷ�o(n*m) ʱ�临�Ӷ�O(n^2*m)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
int len,m;
char s[50];

ll dfs(int st,int k){
    if(st == len+1){
        if(!k)
            return 1;//����״̬ ��Ϊ�۳�Ϊ1
        return 0;//���Ϸ�״̬Ϊ0 ������INF(-0x3f3f3f3f3f3f3f3f),���������
    }
    if(!k)//�Ѿ��ֳ�k������,��������û��Ϊ���Ϸ�״̬
        return 0;
    ll &ans=dp[st][k];
    if(ans!=-1)//��ʼ״̬Ϊ-1
        return ans;
    for(int i=st;i<=len;i++)
        ans=max(ans,num[st][i]*dfs(i+1,k-1));
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
        }
        printf("%lld\n",dfs(1,m));
    }
	return 0;
}
*/

