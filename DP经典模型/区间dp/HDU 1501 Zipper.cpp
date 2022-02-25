/*
����:�������ַ����жϵ������ַ����ܷ���ǰ�������մ������,���Խ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1501
˼·:�����ӽṹ����Ҫö�ٵ������ַ����еĵ�ǰ�ַ��͵�һ���ַ�����
��ǰλ��ƥ�仹�ǵڶ����ַ����ĵ�ǰλ��ƥ��.
���仯����
dp[l1][l2] ������s�������ַ�����s1ƥ����l1��,s2ƥ����l2��.
�ص���������,��ǰ���״̬s1ƥ����l1,s2ƥ����l2ʧ�ܺ�,���ݻ���ͨ��
����s1��s2��sƥ���λ��,�п��ܻ������s1ƥ����l1,s2ƥ����l2�������,
�����Ҫ��¼�����ƥ��Ľ��,ֱ�ӷ���0,�����ظ�����.
*/
//ac 31ms ���仯����
//dp[l1][l2]=1 �����ڵ������ַ�����s1ƥ����l1��,s2ƥ����l2����������ѱ������,�����Ƴ�s1 s2�����s3
//ʱ�临�Ӷ�O(len1*len2) ��Ϊdp[l1][l2]ֻ�����һ��
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[250][250],len1,len2,len0;
char s1[250],s2[250],s[500];
int dfs(int l1,int l2,int len){

    if(len == len0+1) return 1;//s�ַ���ƥ����� ����

    if(dp[l1][l2]) return 0;//������������Ѿ����Թ�,ƥ��ʧ��,ֱ�ӷ���0
    dp[l1][l2]=1;
    if(s1[l1]==s[len]){//����ƥ��s1�е��ַ�,��ƥ��,��s1��s���±�+1
        if(dfs(l1+1,l2,len+1)) return 1;
    }
    if(s2[l2]==s[len]){//ƥ��s2���е��ַ�,��ƥ��,��s2��s���±�+1
        if(dfs(l1,l2+1,len+1)) return 1;
    }
    return 0;//ƥ��ʧ��
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s",s1+1);
        scanf("%s",s2+1);
        scanf("%s",s+1);
        len0=strlen(s+1);
        if(dfs(1,1,1)) printf("Data set %d: yes\n",cas);
        else printf("Data set %d: no\n",cas);
    }
    return 0;
}

/*
//ac 31ms ����dp
//dp[i][j]=1/0��ʾ��s3��Ա�,s1����˳��ƥ����i���ַ�,s2����˳��ƥ��j���ַ�Ϊ��(1)���(0)
//�����������ȷ�����ڶ���s1�е�ÿһλƥ���,s3�е���һλ��ƥ��ʱ �ῼ������s2�е�����λj,
//ͬ��s2�еĵ�jλҲ�ῼ��s1�е����е�iλ �Ӷ���֤��Ͻ������ȷ��.
//���������������Ϊ����,���������Ϊÿ��i,j����ͬ,���Լ������о���s1��s2��ƥ��˳������п������,���Բ������ص������������
#include<cstdio>
#include<cstring>
#define N 210
using namespace std;

char s1[N],s2[N],s3[N<<1];
int cas,dp[N][N];

int main(){
    int T,len1,len2;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%s%s%s",s1+1,s2+1,s3+1);
        len1=strlen(s1+1);
        len2=strlen(s2+1);
        dp[0][0]=1;//��ʼ״̬,s1,s2��һ���ַ���δƥ��Ϊ��
        for(int i=0;i<=len1;i++){//ö��s1�еĵ�iλ
            for(int j=0;j<=len2;j++){//ö��s2�еĵ�jλ
                //����s1�е�i���ַ��Ƿ��s3��i+j���ַ�ƥ��,�����һ״̬dp[i-1][j]ƥ��,��һ��ƥ��
                if(i>0 && dp[i-1][j] && s1[i] == s3[i+j])
                    dp[i][j]=1;
                //����s2�е�j���ַ��Ƿ��s3��i+j���ַ�ƥ��,�����һ״̬dp[i][j-1]ƥ��,��һ��ƥ��
                if(j>0 && dp[i][j-1] && s2[j] == s3[i+j])
                    dp[i][j]=1;
            }
        }
        if(dp[len1][len2])
            printf("Data set %d: yes\n",cas);
        else
            printf("Data set %d: no\n",cas);
    }
    return 0;
}
*/
