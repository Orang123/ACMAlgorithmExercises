#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
����:��������һ������Ϊ5��ľ�壬��ʼʱû��Ϳ���κ���ɫ����ϣ��������5����λ���ȷֱ�Ϳ
�Ϻ졢�̡������̡���ɫ����һ������Ϊ5���ַ�����ʾ���Ŀ�꣺RGBGR��ÿ������԰�һ������
��ľ��Ϳ��һ����������ɫ����Ϳ����ɫ������Ϳ����ɫ�������һ�ΰ�ľ��Ϳ��RRRRR���ڶ���Ϳ��RGGGR��
������Ϳ��RGBGR���ﵽĿ�ꡣ�þ����ٵ�Ϳɫ�����ﵽĿ�ꡣ
����:https://www.luogu.com.cn/problem/P4170
˼·:dp[i][j]����[i,j]����δȾɫ�Ŀմ�ת��ΪĿ�괮��[i,j]������Ҫ��Ⱦɫ����
ʵ��ˢ��ʱ���������ˢ�������ˢС���� ����Ⱦɫ�����,��dp�Ǵ�С��״̬С���俪ʼת�Ƶ�,
���ⲻӰ�������������.
����GBG�ķֽ�GBG=min(GB,BG)=2,ʵ�ʵ�Ⱦ�����Ȱ�������Ⱦ��G,����м��Ⱦ��B,�ܹ�2��
*/

char s[110];
int dp[110][110],len;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;//�����ַ�,ֻ��Ⱦһ��
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(s[i] == s[j])//������˵����,�������һ��Ⱦ[i+1,j],[i,j-1]ʱһ��Ⱦ��s[i]��s[j]
                dp[i][j]=min(dp[i+1][j],dp[i][j-1]);//dp[i+1][j]��dp[i][j-1]���ܲ�ͬ��Ϊs[i+1]��s[j]�Լ�s[i]��s[j-1]���Ƿ���ȵ������ͬ
            else{//����ö��[i,j]�ָ��,�ֳ�2���ֱַ�Ⱦɫ,��[i,k] [k+1,j]2���ֵ�Ⱦɫ����֮����Сֵ
                for(int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);//��Ϊs[i] s[j]�����,����2���ָ�����ֱ𶼰���s[i] s[j]��Ⱦɫ����,s[i] s[j]��Ҫ����Ⱦһ��ɫ
            }
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int l=0;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            /*
            dp[i][j]=dp[i+1][j]+1,��Ϊ�˱�������ָ�����û��һ��s[k]��s[i]���ʱ,
            dp[i][j]���һ�����,����s[i]������ˢһ��ɫ��dp[i+1][j]+1,
            ��Ȼdp[i][j]Ҳ���Գ�ʼ��Ϊdp[i][j-1],ֻ�������ö�ٷָ��s[k]�Ǻ�s[j]�Ƚ�
            */
            /*
            ��������s[i]��s[k]�Ƚ�,����Ͳ��ܳ�ʼ��dp[i][j-1],
            ��Ϊ��ʹû��һ��s[i]��s[k]���,��Ҳ�п���s[j]��i~j-1�е�ĳһ����ɫ��ͬ,
            �������и��ŵķָ���,�����ʼ��������������ֵ.
            */
            /*
            dp[i][j]=dp[i+1][j]+1;
            for(int k=i+1;k<=j;k++)
                if(s[i] == s[k])*/
                    /*
                    ������ö�ٷָ��������s[i]��s[k]�Ƚ�,�ָ������оͲ�Ӧ����i,
                    ��Ϊs[i]��s[k]��ͬһ��ɫ,��ˢs[k]ʱ˳��Ϳ���ˢ��s[i].
                    ����ʵ�ʵ�ˢ��,Ӧ������[i+1,k]ˢs[k]ʱ˳��ˢ��s[i],��������ת��dp[i+1][k]+dp[k+1][j]
                    ������ʵ�ʲ���,������Ϊ����ֻ���������ˢ�Ĵ���,������ô�ָ�,s[i]��s[k]ʼ��ֻ����ˢs[k]����һ��,
                    ����dp[i+1][k-1]+dp[k][j],s[k]Ҳ��������ˢ[k,j]������Ĵ���,ͬ������ֻ������һ��.
                    */
                    /*
                    dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
                    //dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
dp[i][j]=dp[i][j-1]+1 ö��s[j]��s[k]�Ĺ�ϵ
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int l=0;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            dp[i][j]=dp[i][j-1]+1;
            for(int k=i;k<j;k++)
                if(s[j] == s[k])//�ж�s[j]��s[k]���Ƿ������ʹ��s[k] s[j]����ɫֻˢһ��
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
                    //dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j-1]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
ö���������Ҷ˵� dp[i][j]=dp[i][j-1]+1;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=len;i>=1;i--){
        for(int j=i;j<=len;j++){
            dp[i][j]=dp[i][j-1]+1;
            for(int k=i;k<j;k++)
                if(s[j] == s[k])
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
ö���������Ҷ˵� dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],len;

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%s",s+1);
    len=strlen(s+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int i=len-1;i>=1;i--){
        for(int j=i+1;j<=len;j++){
            if(s[i] == s[j])
                dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
            else{
                for(int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

*/


