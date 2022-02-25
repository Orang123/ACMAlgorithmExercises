/*
����:ժ������
һ���ַ��� ͨ��ɾ������һЩ�ַ��� �ܹ�ʹ�⴮�ַ���ɻ��Ĵ���
���ڸ���һ���ַ������ܹ��õ������ֲ�ͬ�Ļ��Ĵ���
ע�⣺�ַ���"abba", ���Եõ�9�����Ĵ����ֱ�Ϊ'a', 'a', 'b', 'b', 'aa', 'bb', 'aba', 'aba', 'abba'.
�ַ�������<=60.
����:http://www.lightoj.com/volume_showproblem.php?problem=1025
˼·:ժ��https://www.cnblogs.com/aiterator/p/5875206.html
����dp[i][j]Ϊ�ַ���[i,j]������ͨ��ɾ�����Եõ���ͬ���Ĵ�������
��ô���������������
1����str[i] != str[j]ʱ�� dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
��֮���Լ�ȥdp[i+1][j-1] ��ǰ����������һ��dp[i+1][j-1]��,�ǹ����ص�����
2����str[i] == str[j]ʱ�� dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]) + (dp[i+1][j-1] + 1);
��ǰ��һ����ָstr[i]��str[j]����Ӧʱ�ܹ���ɻ��Ĵ��ķ��������ڶ�����ָstr[i]��str[j]��Ӧʱ�ܹ���ɻ��Ĵ��ķ�������
ʵ�ʲ�����Ҫ���ɾȥ�ַ�,ʵ�ʾ���ͨ���ж��������˵������ܹ��ɵĻ����Ӵ�����Ŀ.
*/
//ac 5ms ���仯����(����dp)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
typedef long long ll;
using namespace std;

ll dp[N][N];
char str[N];

ll dfs(int l,int r){
    ll &res=dp[l][r];
    if(res!=-1)
        return res;
    if(l == r)
        return res=1;
    if(l>r)
        return res=0;
    if(str[l]!=str[r])
        res=dfs(l+1,r)+dfs(l,r-1)-dfs(l+1,r-1);
    else
        res=dfs(l+1,r)+dfs(l,r-1)+1;
    return res;
}

int main(){
    int T,len;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        printf("Case %d: %lld\n",i,dfs(1,len));
    }
    return 0;
}

/*
//ac 4ms ��������dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
typedef long long ll;
using namespace std;

ll dp[N][N];
char str[N];

int main(){
    int T,len;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        for(int i=1;i<=len;i++)
            dp[i][i]=1;
        for(int l=1;l<len;l++){
            for(int i=1;i<len;i++){
                int j=i+l;
                if(str[i]!=str[j])
                    dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
                else
                    dp[i][j]=dp[i+1][j]+dp[i][j-1]+1;
            }
        }
        printf("Case %d: %lld\n",i,dp[1][len]);
    }
    return 0;
}
*/
