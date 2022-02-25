/*
����:ժ������
����1���ַ���a����a����ɾ��������ʹ��ʣ�µ��Ӵ��ǻ����ַ�����
�������ַ��������ж����ͬ���ȵľ�����ֵ�����С�ġ�
�ַ�������<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2399
˼·:���������LCS������������������,����ע�Ȿ��Ҫ���ڳ�����ͬ
�������ֵ�����С,��Ҫ����dpʱ���dp�������,���յ�ǰ����ַ������ֵ���
ȥ����,������Ϊ�������Ŷ��ͷ��Ŷ�һ��,ǰ����֮һ���ֵ�����С�ͺ����֮һ
���ֵ�����С�����п�����������֮һ�Ļ��ĺ�ǰ����֮һ�Ͳ�һ����.���
���ʱֱ�����ǰ����֮һ,Ȼ���ٴ��е��������ǰ����֮һ,�������ܰ�����
���Ĵ����,����Ҫ���ֳ���Ϊ������ż��.
*/
//ac 1280ms LCS����dp ���ֳ�������ż���������
//dp[i][j].len��ʾ�����е�ǰi��Ԫ�غ������е�ǰj��Ԫ�ص�LCS����
//dp[i][j].s��ʾ�����е�ǰi��Ԫ�غ������е�ǰj��Ԫ�ص�LCS
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#define N 1100
using namespace std;

int n;
char a[N],b[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    for(int i=1;i<N;i++)
        dp[0][i].len=0;
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
        for(int i=1;i<=n;i++)
            b[i]=a[n-i+1];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i] == b[j]){
                    dp[i][j].len=dp[i-1][j-1].len+1;
                    dp[i][j].s=dp[i-1][j-1].s+a[i];
                }
                else{
                    if(dp[i-1][j].len>dp[i][j-1].len)
                        dp[i][j]=dp[i-1][j];
                    else if(dp[i-1][j].len<dp[i][j-1].len)
                        dp[i][j]=dp[i][j-1];
                    else{
                        //ǰ����֮һ���ֵ�����С�ͺ����֮һ
                        //���ֵ�����С�����п�����������֮һ�Ļ��ĺ�ǰ����֮һ�Ͳ�һ����.
                        if(dp[i-1][j].s<dp[i][j-1].s)
                            dp[i][j]=dp[i-1][j];
                        else
                            dp[i][j]=dp[i][j-1];
                    }
                }
            }
        }
        if(dp[n][n].len & 1){
            for(int i=0;i<dp[n][n].len/2;i++)
                printf("%c",dp[n][n].s[i]);
            for(int i=dp[n][n].len/2;i>=0;i--)
                printf("%c",dp[n][n].s[i]);
        }
        else{
            for(int i=0;i<dp[n][n].len/2;i++)
                printf("%c",dp[n][n].s[i]);
            for(int i=dp[n][n].len/2-1;i>=0;i--)
                printf("%c",dp[n][n].s[i]);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 620ms ����dp ö�����䳤��
//dp[i][j].len��ʾ�±�����[i,j]�ڵ���������Ļ��������еĳ���
//dp[i][j].s��ʾ�±�����[i,j]�ڵ���������Ļ���������
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int l=1;l<n;l++){
        	for(int i=1;i+l<=n;i++){
        		int j=i+l;
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/

/*
//ac 540ms ����dp ����ö��������˵㡢�Ҷ˵�
//dp[i][j].len��ʾ�±�����[i,j]�ڵ���������Ļ��������еĳ���
//dp[i][j].s��ʾ�±�����[i,j]�ڵ���������Ļ���������
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int i=n-1;i>=1;i--){
        	for(int j=i+1;j<=n;j++){
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/

/*
//ac 770ms ����dp ����ö�������Ҷ˵㡢��˵�
//dp[i][j].len��ʾ�±�����[i,j]�ڵ���������Ļ��������еĳ���
//dp[i][j].s��ʾ�±�����[i,j]�ڵ���������Ļ���������
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define N 1100
using namespace std;

int n;
char a[N];
struct DP{
    int len;
    string s;
}dp[N][N];

int main(){
    while(scanf("%s",a+1)!=EOF){
        n=strlen(a+1);
		for(int i=1;i<=n;i++){
			dp[i][i].len=1;
			dp[i][i].s=a[i];
		}
        for(int j=2;j<=n;j++){
        	for(int i=j-1;i>=1;i--){
        		if(a[i] == a[j]){
        			dp[i][j].len=dp[i+1][j-1].len+2;
        			dp[i][j].s=a[i]+dp[i+1][j-1].s+a[j];
				}
        		else{
        			if(dp[i+1][j].len>dp[i][j-1].len)
						dp[i][j]=dp[i+1][j];
					else if(dp[i+1][j].len<dp[i][j-1].len)
						dp[i][j]=dp[i][j-1];
					else{
						if(dp[i+1][j].s<dp[i][j-1].s)
							dp[i][j]=dp[i+1][j];
						else
							dp[i][j]=dp[i][j-1];
					}
				}

			}
		}
		cout << dp[1][n].s << endl;
    }
    return 0;
}
*/
