#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
����:�۵��Ķ������£�
һ���ַ������Կ�����������۵�������S = S
X(S)��X(X>1)��S������һ��Ĵ����۵�������X(S) = SSSS��S(X��S)��
���A = A��, B = B������AB = A��B�� ���磬��Ϊ3(A) = AAA, 2(B) = BB��
����3(A)C2(B) = AAACBB����2(3(A)C)2(B) = AAACAAACBB
��һ���ַ���������������۵�������AAAAAAAAAABABABCCD������۵�Ϊ��9(A)3(AB)CCD��
����:https://www.luogu.com.cn/problem/P4302
˼·:dp[i][j]����i~j�ڵ��ַ����۵��������ַ���
digit[i]��¼����i��λ��,�����ж��۵��ַ���ǰ�����ֵĳ���
�о������ֱ���������۵����ַ�����̫����
*/
int dp[110][110],digit[110];

int judge(int n,int len,char *s){
    for(int k=len;k<n;k++)
        //s[k]��ʵ��[i,j]�е��ַ�,s[k%len]Ϊ[i,k]�е��ַ�
        if(s[k] != s[k%len]) return 0;
    return 1;
}

int main(){
    char s[110];
    int n;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<110;i++){
        if(i<10) digit[i]=1;
        else if(i<100) digit[i]=2;
        else digit[i]=3;
    }
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        dp[i][i]=1;//�����ַ��޷��۵�,��̳��Ⱦ���1
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                //ö�ٷָ���������ŷָ��ַ�������
                //��[i,j]�ָ������[i,k] [k+1,j] ���,�۵�δ��һ���Ȳ��۵��ĺ�,��aa�۵���2(a)����Ϊ4,ԭ��Ϊ����2
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                int len=k-i+1;//[i,k]�Ӵ��ĳ���
                /*
                ��[i,k]�ĳ��Ȳ��ܱ�[i,j]�ĳ�������,[i,k]���޷�ͨ��ѭ����ƴ�ӳ�[i,j],
                ����ʵ�������ж�[i,k]ѭ������[i,j]ֻ�е�l+1Ϊlen����������ʱ ����,
                һ����n�����Ӳ����log(n)��,�����if�ж�ʵ�ʿ��Ժ���Ϊ����ʱ��
                */
                if((l+1)%len) continue;
                //�ж�[i,k]�Ƿ�����Ϊѭ���ڹ���[i,j]�Ա��һ���۵�
                if(judge(l+1,len,s+i))
                    //digit[(l+1)/len]������[i,k]�ܹ���[i,j]�۵�ǰ�������,2Ϊ2������,dp[i][k]Ϊԭ��[i,k]�۵��������ַ���
                    dp[i][j]=min(dp[i][j],digit[(l+1)/len]+2+dp[i][k]);
            }
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],digit[110];

int judge(int i,int j,int len){
    //�ж�[i,k]�е�ÿһλ����ÿ������len�ж�[i,j]�е��Ƿ����
    for(int k=i;k<i+len;k++)
        for(int t=k+len;t<=j;t+=len)
            if(s[k] != s[t]) return 0;
    return 1;
}

int main(){
    int n;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<110;i++){
        if(i<10) digit[i]=1;
        else if(i<100) digit[i]=2;
        else digit[i]=3;
    }
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        dp[i][i]=1;
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                int len=k-i+1;
                if((l+1)%len) continue;
                if(judge(i,j,len))
                    dp[i][j]=min(dp[i][j],digit[(l+1)/len]+2+dp[i][k]);
            }
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
*/
