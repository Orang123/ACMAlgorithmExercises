#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
/*
����:http://poj.org/problem?id=3186
����:n�����ų�һ��,ÿ��ֻ��ȡ�ײ���β���������Ĺ���Ϊ��ȡ����ֵ*ȡ�ô���,��ȡ���������������.
˼·:����̰�Ĳ���,��ʹÿ�ζ�ȡ��С����,���ϴ�������ڴ����ϴ��ʱ��,����ȡ�߽�С�����µ��ײ�β��Ԫ��Ҳ�����,
��Ȼ̰�Ĳ���,�ٿ��Ǵ�ͳ�ı���,����һ�е���ÿ��ȡ������ѡ��,Ҫôȡ�ײ�Ҫôȡβ��,�ܹ�ȡn��,��ôʱ�临�Ӷ�O(2^n),
����n=2000,,2^(2000)��ȻҲ��ʱ.
����,˼·�϶����Ǳ���,ֻ�ǲ���ֱ�Ӱ�һ��ı�������ö�ٿ�����,���Բ�������ȥģ��ȡ�Ĺ���,ֻ������������ȡ,���Ž����������,����dp.
dp[i][j]����[i,j]��ȡ����ĩβ��ǰȡ�������������
*/
//ö�ٳ��� ��ʼ�˵������dp
int dp[2100][2100],a[2100];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int l=0;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            //��Ϊֻ��ȡ�ײ���β�� ���Բ�����ö�ٷָ��k
            //����a[i]��a[j]��Ϊ��(n-l)��ȡ������ ��ȡdp[i][j]���ֵ
            dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j]*(n-l));
            dp[i][j]=max(dp[i][j],dp[i+1][j]+a[i]*(n-l));
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}

/*
����Ӵ�������С����dp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[2100][2100],a[2100];
int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    //�Ӵ�������С����dp,dp[i][j]ֻ���������������ƹ��� �ֱ���dp[i-1][j]��dp[i][j+1],
    //������dp[i-1][j]����,˵������Ҫȡa[i-1]�����,��Ӧ����ȡ��(n-l-1)����
    //������dp[i][j+1]����,˵������Ҫȡa[j+1]�����,��Ӧ����ȡ��(n-l-1)����
    //���ȴ�n-1��ʼ,��Ϊ��һ��ȡ���,����ʱn-1,��l==0,��ֻʣ��һ����ʱ,�������ȡ��n-1����,����dp���ʣ�����һ����ûȡ
    //���Ҳ������ֵ�dp���޺�Ч��,����ļ������ֱ��ʹ���������������迼������������Ժ�������Ӱ��
    //��ĳ������[i,j]�����ȡ����ǰ��dp[i-1][j] do[i][j+1]û�й�ϵ,ֻ�Ƕ���dp[i][j]������ֵ���Ը���dp[i-1][j] do[i][j+1]�����
    for(int l=n-2;l>=0;l--){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            dp[i][j]=max(dp[i-1][j]+a[i-1]*(n-l-1),dp[i][j+1]+a[j+1]*(n-l-1));
        }
    }
    for(int i=1;i<=n;i++)//��ȡʣ�µ����һ����,��n��ȡ
        ans=max(ans,dp[i][i]+n*a[i]);
    printf("%d",ans);
	return 0;
}
*/

/*
ö���������Ҷ˵������dp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[2100][2100],a[2100];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n;i>=1;i--){
        for(int j=i;j<=n;j++){
            int l=j-i;
            dp[i][j]=max(dp[i][j],dp[i][j-1]+a[j]*(n-l));
            dp[i][j]=max(dp[i][j],dp[i+1][j]+a[i]*(n-l));
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
*/

/*
���仯���� [i,j]�ǳ�ʼ����,[i+1,j] [i,j-1]�������� �ɴ�����ֽ�С����
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[2100][2100],a[2100];

int dfs(int st,int ed,int num){
    if(st == ed) return dp[st][ed]=a[st]*num;
    if(dp[st][ed]) return dp[st][ed];
    //��ķ����Ͼ��Ǽٶ�[st+1,ed]��[st,ed-1]�����,Ȼ����ȡa[st]��a[ed],�ݹ�������ȡ������Ĺ���,ֱ��st==ed���һ��ȡ����С���������,��ʼ����.
    dp[st][ed]=max(dp[st][ed],dfs(st+1,ed,num+1)+a[st]*num);
    dp[st][ed]=max(dp[st][ed],dfs(st,ed-1,num+1)+a[ed]*num);
    return dp[st][ed];;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("%d",dfs(1,n,1));
	return 0;
}
*/

/*
���仯���� [i,j]�ǳ�ʼ����,[i-1,j] [i,j+1]�������� ��С����ֽ������
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,dp[2100][2100],a[2100];

int dfs(int i,int j){
    //��i==0��j==n+1��������߽�����[1,n]����״̬һ������ûȡ(j-i==n-1) ����0
    if(!i || j==n+1 || j-i==n-1) return 0;
    if(dp[i][j]) return dp[i][j];
    dp[i][j]=max(dfs(i-1,j)+a[i-1]*(n-j+i-1),dfs(i,j+1)+a[j+1]*(n-j-1+i));
    return dp[i][j];
}

int main(){
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)//��ȡʣ�µ����һ����,��n��ȡ
        ans=max(ans,dfs(i,i)+a[i]*n);
    printf("%d",ans);
	return 0;
}

*/

