/*
����:���������ַ�������������Ӵ��ĳ��ȡ�
�����ַ�������<=10^5
����:http://poj.org/problem?id=2774
˼·:��׺����,�������ַ����м���'$'ƴ������,
����height���������,ֻҪsa[i]��sa[i-1]���±�
�ڷָ���'$'�����߾Ϳ��Ժ����ʾ�����ַ�����
������Ӵ�,�����ᳬ��'$'�������ַ����ص����ཻ
�����,��Ϊ�ָ���'$'��֤�� lcp��ֹ��'$'��λ��.
*/
//ac 516ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

int n,sa[N],id[N],cnt[N],rk[N],oldrk[N],height[N];
char s[N],tp[N];

void SA(){
    int m;
    m=max(n,300);
    for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
    for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;
    for(int w=1;w<n;w<<=1){
        int p=0;
        for(int i=n;i>n-w;i--) id[++p]=i;
        for(int i=1;i<=n;i++){
            if(sa[i]>w)
                id[++p]=sa[i]-w;
        }
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) cnt[rk[i]]++;
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldrk,rk,sizeof(rk));
        int k=0;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=(oldrk[sa[i-1]] == oldrk[sa[i]] && oldrk[sa[i-1]+w] == oldrk[sa[i]+w])?k:++k;
        if(k == n) return;
        m=k;
    }
}

/*
//ac
void initHeight(){
    int j,k;
    for(int i=1;i<=n;i++){
        if(rk[i] == 1) continue;
        j=sa[rk[i]-1];
        k=max(0,height[rk[i-1]]-1);
        while(s[i+k] == s[j+k]) k++;
        height[rk[i]]=k;
    }
}
*/

void initHeight(){
    int j,k=0;
    for(int i=1;i<=n;i++){
        if(rk[i] == 1) continue;
        j=sa[rk[i]-1];
        if(k) k--;
        while(s[i+k] == s[j+k]) k++;
        height[rk[i]]=k;
    }
}

int main(){
    int len,ans=0;
    scanf("%s",s+1);
    scanf("%s",tp+1);
    n=strlen(s+1);
    s[n+1]='$';
    len=n+1;
    s[n+2]='\0';
    strcat(s+1,tp+1);
    n=strlen(s+1);
    SA();
    initHeight();
    for(int i=2;i<=n;i++){
        if(height[i]>ans){
            if(sa[i]<len && sa[i-1]>len)//ֻҪ����Ϊi��i-1�ĺ�׺ �ֱ�ֲ��ڷָ���'$'������,���ܱ�֤lcp����Խ���ָ���
                ans=height[i];
            if(sa[i]>len && sa[i-1]<len)
                ans=height[i];
        }
    }
    printf("%d",ans);
    return 0;
}
