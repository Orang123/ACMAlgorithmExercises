/*
����:ժ������
��һ���ַ����ָ�����ٵ��ַ�����ʹ�÷ָ����ÿ���ַ������ǻ��Ĵ��������С�ķָ�����
�ַ�������<=1000s.
����:http://lightoj.com/volume_showproblem.php?problem=1044
˼·:����[l,r]�ڵ��ַ���,ö������ָ�ķ�ʽ,��ôʵ�ʷָ�Ļ��Ĵ���
�����ӽṹΪ[l,r]=[l,i]+[i+1,r],���dp[l][r]Ϊ����[l,r]�ڿ��Էָ��
���ٵĻ��Ĵ�����Ŀ.
״̬ת�Ʒ���Ϊif(check(l,i))([l,i]�ǻ��Ĵ�)
dp[l][r]=min(dp[l][r],1+dfs(i+1,r));
*/
//ac 151ms ���仯���� ����dp
//dp[l][r]Ϊ����[l,r]�ڿ��Էָ�����ٵĻ��Ĵ�����Ŀ.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int dp[N][N],len;
char str[N];

int check(int l,int r){//�ж�[l,r]�Ƿ�Ϊ���Ĵ�
    while(l<r){
        if(str[l] == str[r]){
            l++;
            r--;
        }
        else
            return 0;
    }
    return 1;
}

int dfs(int l,int r){
    int &res=dp[l][r];
    if(res!=INF)
        return res;
    if(l>r)//����
        return res=0;
    for(int i=l;i<=r;i++){
        if(check(l,i))//[l,i]�ǻ��Ĵ� ���Ĵ���Ŀ+1
            res=min(res,1+dfs(i+1,r));
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0x3f,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        printf("Case %d: %d\n",i,dfs(1,len));
    }
    return 0;
}

/*
//ac ����dp
//ժ�Բ���:https://blog.csdn.net/u011026037/article/details/23872821
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int dp[1005];
char str[1005];
bool find(int k,int r)
{
    while(k < r)
    {
        if(str[k] == str[r])  k++,r--;
        else  return false;
    }
    return true;
}
int main()
{
    int n,Case = 1;;
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        scanf("%s",str);
        int l = strlen(str);
        for(int i = 0; i < l; i++)
        {
            dp[i] = i + 1;
            for(int j = 0; j <= i; j++)
            {
                if(find(j,i))
                {
                    if(j == 0)
                        dp[i] = 1;
                    else
                        dp[i] = min(dp[i],dp[j - 1] + 1);
                }
            }
        }
        printf("Case %d: %d\n",Case++,dp[l-1]);
    }
}
*/

/*
//TLE dp[l][r]=min(dp[l][r],dfs(l,i)+dfs(i+1,r))
//֮����TLE������ ��������ӽṹ ��2��dfs,��������ص�������,��len���ɴ�1000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int dp[N][N],vis[N][N],len;
char str[N];

int dfs(int l,int r){
    int &res=dp[l][r];
    if(res!=INF)
        return res;
    if(vis[l][r])
        return res=1;
    if(l>r)
        return res=0;
    for(int i=l;i<=r;i++)
        res=min(res,dfs(l,i)+dfs(i+1,r));
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(vis,0,sizeof(vis));
        memset(dp,0x3f,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        for(int i=1;i<=len;i++){
            vis[i][i]=1;
            for(int l=i,r=i+1;l>=1 && r<=len;l--,r++){//�ж�ż�����Ȼ��Ĵ�
                if(str[l] == str[r])
                    vis[l][r]=1;
                else
                    break;
            }
            for(int l=i-1,r=i+1;l>=1 && r<=len;l--,r++){//�ж��������Ȼ��Ĵ�
                if(str[l] == str[r])
                    vis[l][r]=1;
                else
                    break;
            }
        }
        printf("Case %d: %d\n",i,dfs(1,len));
    }
    return 0;
}
*/
