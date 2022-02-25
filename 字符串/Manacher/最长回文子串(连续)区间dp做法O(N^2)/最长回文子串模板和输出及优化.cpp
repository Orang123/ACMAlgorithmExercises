/*
��Ӧ����:leetcode 5 ������Ӵ�
����һ���ַ��� s���ҵ� s ����Ļ����Ӵ���
https://leetcode-cn.com/problems/longest-palindromic-substring/
*/

//��Щ������O(n^2)������,ʵ��������Ӵ�������manacher�㷨��O(n)����ʱ���ڽ��
#include<cstdio>//������Ӵ�
#include<cstring>
#include<algorithm>
using namespace std;
int vis[1100][1100];
char a[1100];
//ʱ�临�Ӷȶ�O(N^2) �ռ�O(N^2) 1s���� n>1000����ܾͻ�TLE,2000���ϵ����� �о�ֻ����Manacher(ʱ��:O(N)�ռ�:O(N))�㷨,����4000vis����Ҳ��TLE
int main(){
    int lt=1,rt=1,len;//���������,�ַ�����ÿ���ַ�������ͬ,��Ĭ�������һ���ַ���Ϊ����Ϊ1�Ļ����Ӵ�
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        vis[i][i]=1;
    //��ͳ�ƽ�С������Ļ����Ӵ�,�ٸ����������Ҷ˵�ͳ�ƽϴ������Ƿ�Ϊ���Ĵ�
    for(int l=1;l<len;l++){//O(N^2)
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            //ǰ����[i,j] �м��[i+1,j-1]����Ϊ���Ĵ�,[i,j]�ſ����� ���䳤��Ϊ2ʱ�������м��Ӵ�
            if(a[i]==a[j] && (l==1 || vis[i+1][j-1])){//�������䳤������,��¼���󳤶ȵĻ����Ӵ�
                lt=i,rt=j;
                vis[i][j]=1;
            }
        }
    }
    printf("%d\n",rt-lt+1);
    for(int i=lt;i<=rt;i++)//���������Ψһ  ��������±����нϿ����������Ӵ�
        printf("%c",a[i]);
    return 0;
}

/*
ͬ���ɲ���ö�����Ҷ˵�dpʹ�ù��������Ż��ռ�
*/

/*
O(N^3) ��ԭʼ�ı�������,ö��ÿһ�����,��ö����㿪ʼ�Ŀ��ܳ��ȵ��Ӵ�,��ÿ���Ӵ����������Ա��ж�,���ϸ�����󳤶�
*/

/*
����dp�����������������ѯ,dp[i][j]��ʾ[i,j]��������Ӵ��ĳ���
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],vis[110][110];//vis[i][j]����[i,j]���ַ����Ƿ��ǻ��Ĵ�,����Ϊ1
char a[110];
//ʱ�临�Ӷ�O(N^2) 1s���������Ϊ1000
int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        vis[i][i]=dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            //[i,j]Ϊ���Ĵ���ǰ��������[i+1,j-1]����Ϊ���Ĵ�
            if(a[i] == a[j] && (l==1 || vis[i+1][j-1])){//[i,j]����Ϊ2ʱû���м���ַ��������ж� ��l==1
                dp[i][j]=dp[i+1][j-1]+2;//[i,j]��[i+1,j-1]�Ļ���������2
                vis[i][j]=1;//��Ǹ���Ļ��Ĵ�����
            }
            //��a[i]!=a[j]��[i+1,j-1]���ǻ���,��ô[i,j]������ļ̳�֮ǰС����[i,j-1]��[i+1,j]�ϴ�ĳ���
            else dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
        }
    }
    printf("%d",dp[1][len]);//dp[i][j]������������[i,j]֮���������Ӵ��ĳ��� ���ڸ���һ���ַ��� ���벻ͬ���Ҷ˵� �����������������
    return 0;
}
*/

/*
//���仯���� ������Ӵ�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],vis[110][110];
char a[110];

int dfs(int i,int j){
    if(i>j) return 0;
    if(dp[i][j]) return dp[i][j];
    dfs(i+1,j-1);//Ҫ����a[i]��a[j]��ϵ�ж�[i,j]�Ƿ�Ϊ���Ĵ�,�ȵ��ж�[i+1,j-1]�Ƿ�Ϊ���Ĵ�
    if(a[i] == a[j] && (j-i==1 || vis[i+1][j-1])){//����Ϊ2ʱû���м��Ӵ�
        dp[i][j]=dp[i+1][j-1]+2;
        vis[i][j]=1;
    }
    else
        dp[i][j]=max(dfs(i,j-1),dfs(i+1,j));
    return dp[i][j];
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=vis[i][i]=1;
    printf("%d",dfs(1,len));
    return 0;
}
*/

/*
leetcode 647 ͳ�ƻ����Ӵ�����Ŀ
����:https://leetcode-cn.com/problems/palindromic-substrings/
//����dp
//ʱ�临�Ӷ�O(n^2) �ռ临�Ӷ�O(n^2)
class Solution {
public:
    int dp[1100][1100];
    int countSubstrings(string s) {
        int ans=0;
        for(int l=0;l<s.size();l++){
            for(int i=0;i+l<s.size();i++){
                int j=i+l;
                if(s[i] == s[j] && (i+1>=j-1 || dp[i+1][j-1])){
                    dp[i][j]=1;
                    ans++;
                }
            }
        }
        return ans;
    }
};

//������չ�� ˫ָ��
//ʱ�临�Ӷ�O(n^2) �ռ临�Ӷ�O(1)
class Solution {
public:
    int ans;

    void cal(string &s,int l,int r){
        while(l>=0 && r<s.size() && s[l] == s[r]){
            l--;
            r++;
            ans++;
        }
    }

    int countSubstrings(string s) {
        for(int i=0;i<s.size();i++){
            cal(s,i,i+1);//����Ϊż�� ��s[i] == s[i+1]��ʼ������չ
            cal(s,i,i);//����Ϊ���� �Գ�����λs[i]
        }
        return ans;
    }
};
*/

