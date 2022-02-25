#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
����:��һ��������ȵ��ַ���,ÿ�ο��Խ���ʼ��һ���������Ӵ�ˢ��ͬһ��ɫ,��ˢ����ɫ�Ḳ����ˢ����ɫ,
�ʽ���ʼ��ˢ��Ŀ�괮,��Ҫˢ�����ٵĴ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2476
˼·:dp[i][j]����[i,j]����δȾɫ�Ŀմ�ת��ΪĿ�괮s2��[i,j]������Ҫ��Ⱦɫ����
ʵ��ˢ��ʱ���������ˢ�������ˢС���� ����Ⱦɫ�����,��dp�Ǵ�С��״̬С����
��ʼת�Ƶ�,���ⲻӰ�������������.
ans[i]����ǰi���ַ���s1ת��s2��Ҫˢ�����ٴ���.
*/

char s1[110],s2[110];
int dp[110][110],ans[110],len;

int main(){
    while(scanf("%s",s1+1)!=EOF){
        scanf("%s",s2+1);
        memset(dp,0x3f,sizeof(dp));
        len=strlen(s2+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;//�����ַ�,ֻ��Ⱦһ��
        for(int l=1;l<len;l++){
            for(int i=1;i+l<=len;i++){
                int j=i+l;
                if(s2[i] == s2[j])//������˵����,�������һ��Ⱦ[i+1,j],[i,j-1]ʱһ��Ⱦ��s[i]��s[j]
                    dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
                else{//����ö��[i,j]�ָ��,�ֳ�2���ֱַ�Ⱦɫ,��[i,k] [k+1,j]2���ֵ�Ⱦɫ����֮����Сֵ
                    for(int k=i;k<j;k++)
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        for(int i=1;i<=len;i++)
            ans[i]=dp[1][i];//ans[i]��ʼ��Ϊ�ɿմ�ת��Ϊs2��״̬,�����������,��ans[i]�����ϵ����ֵ
        for(int i=1;i<=len;i++){
            if(s1[i] == s2[i])//�����ʼ����Ŀ�괮��ǰ�ַ���ͬ,��Ҫˢ�Ĵ�������ǰi-1��״̬Ҫˢ�Ĵ���
                ans[i]=ans[i-1];
            else{//�������,��ö�ٷָ��j,��ǰ����Ӵ�ans[j](��ʼ��s1)+[j+1,i](�ɿհ״�ת�Ƶ�s2�Ĵ���)
                for(int j=1;j<i;j++)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);//����ط������ݿ���̫��
            }
        }
        printf("%d\n",ans[len]);
    }
    return 0;
}
/*
һλ���ѡ�defKaeru������ans[j]+dp[j+1][i] s1ת�Ƶ�s2��ˢ���������
��ʼ������ȿմ�����
��ǰ׺���� [1, i] �У����Ա�֤����֮ǰ�����䶼ת�ƹ�������Ҫ��֮ǰ������Ϊ������չһλ
���ǰ����� [1, i] �ֳ����Σ�[1, j] �Ǳ�������ʼ���Դ���[j+1, i] �������հ״��Դ���
��ô������ȷ���������ֻ��һ����ǰ׺���� [j, k] ������ʼ������һ������Ȱ�һ��ǰ׺���� [1, j] ������ʼ����������
������Ĳ��� [j+1, i]����ȥ���ۺ�Ŀ�괮����ͬ���ֺ��鷳�����Բ��������հ״����������ͬ���֣�
����ö�ٵ�������Ķϵ�ʱ�����ǵ���
*/
/*
ö�����Ҷ˵������dp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s1[110],s2[110];
int dp[110][110],ans[110],len;

int main(){
    while(scanf("%s",s1+1)!=EOF){
        scanf("%s",s2+1);
        memset(dp,0,sizeof(dp));
        len=strlen(s2+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int i=len-1;i>=1;i--){
            for(int j=i+1;j<=len;j++){
                dp[i][j]=dp[i+1][j]+1;//�����ǳ�ʼ��dp[i][j]������,���s[i]��s[k]�����,�Ƕ�ˢһ��s2[i]����ɫ
                for(int k=i+1;k<=j;k++){
                    if(s2[i] == s2[k])//��s2[i]��s2[k]��� ����ָ��dp[i+1,k]+dp[k+1,j]��ˢ[i+1,k]��ʱ���˳��ˢs2[i],����û��Ҫ�ٵ�����ˢһ��s2[i]
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
                }
            }
        }
        for(int i=1;i<=len;i++)
            ans[i]=dp[1][i];
        for(int i=1;i<=len;i++){
            if(s1[i] == s2[i])
                ans[i]=ans[i-1];
            else{
                for(int j=1;j<i;j++)
                    ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
            }
        }
        printf("%d\n",ans[len]);
    }
    return 0;
}
*/


