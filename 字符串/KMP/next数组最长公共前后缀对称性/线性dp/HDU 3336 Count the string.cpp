/*
����:�ַ�����ÿ��ǰ׺��ԭ�ַ����г��ֵĴ�����.
����ǰ׺�����ص�����.
�ַ�������<=200000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3336
˼·:����������next����ȥdp.
dp[i]��ʾ��p[i-1]�ַ���β��ǰ׺�³��ֵĸ���.
ת�Ʒ��̾���dp[i]=dp[nxt[i]]+1.
�����dp[nxt[i]]��p[0~i-1]��p[nxt[i]~i]��׺����ǰ׺���
�³��ֵ�ǰ׺�ĸ���.
+1��p[0~i-1]�³��ֵĳ���Ϊi��ǰ׺,��һ�γ���,���Դ���+1.
��ʼ״̬dp[0]=0.
*/
/*
��������
abababa
"a", ��������ִ���4
"ab",��������ִ���3
"aba", ��������ִ���3
"abab", ��������ִ���2
"ababa", ��������ִ���2
"ababab", ��������ִ���1
"abababa", ��������ִ���1
4+3+3+2+2+1+1=16
*/
//ac 46ms
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 10007

int nxt[N],plen,ans,dp[N];
char p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&plen);
        scanf("%s",p);
        getNext();
        dp[0]=0;
        //ͬ��i,nxt[i]��������ͬ��
        for(int i=1;i<=plen;i++){
            dp[i]=dp[nxt[i]]+1;
            ans=(ans+dp[i])%mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 62ms ���仯����
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 10007

int nxt[N],plen,ans,dp[N];
char p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

//��ͬ��i,nxt[i]��������ͬ��,��˼��仯�����ȴ�iֵ�ϴ�ĵط�����
int dfs(int i){
	if(!i)
		return 0;
	if(dp[i])
		return dp[i];
	dp[i]=(dfs(nxt[i])+1)%mod;
	return dp[i];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(dp,0,sizeof(dp));
        scanf("%d",&plen);
        scanf("%s",p);
        getNext();
        for(int i=plen;i>=1;i--)
        	ans=(ans+dfs(i))%mod;
        printf("%d\n",ans);
    }
    return 0;
}
*/
