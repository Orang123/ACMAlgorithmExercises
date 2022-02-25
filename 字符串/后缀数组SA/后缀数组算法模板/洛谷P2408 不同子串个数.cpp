/*
����:����һ����Ϊn���ַ�������ͬ���Ӵ��ĸ�����
���Ƕ��������Ӵ���ͬ�����ҽ������������Ӵ����Ȳ�һ��
���߳���һ����������һλ��һ����
�Ӵ��Ķ��壺ԭ�ַ�����������һ���ַ���ɵ��ַ�����
�����һ�����Ӵ�������
n<=10^5
����:https://www.luogu.com.cn/problem/P2408
˼·:��׺����.����height���������.
ͨ�����п��ܵĺ�׺��ȥ �ֵ������ڵĺ�׺�������ǰ׺,��Ϊ�ֵ������ڵ�ƥ��̶ȿ϶����,
�����Ӵ��ĸ�����ͨ��ÿ����׺��ǰ׺ȥö�ٵ�,��ǰ����ֵ�����ܳ��ֹ�ĳ��ǰ׺���Ҫȥ��,��˼�ȥheight[i]
n-sa[i]+1������Ϊi�ĺ�׺������ǰ׺�ĸ�����Ϊsa[i]���±�,����+1���Ǻ�׺�ĳ���,,����������Ϊi�ĺ�׺��ǰ׺
һ����ǰ׺�Ѿ�������Ϊi-1�ĺ�׺�ۼӹ���,���Ҫ��ȥ�ظ��Ĺ���ǰ׺,����ȥheight[i](����Ϊi�ĺ�׺������Ϊi-1
�ĺ�׺�������ǰ׺,Ҳ����ʵ���ظ��ۼӵ�����ǰ׺�ĸ���)
*/

/*
lcp(i,j):��ʾ��׺�±��i��ʼ�ͺ�׺�±��j��ʼ��2����׺�������ǰ׺�ĳ���.
lcp:Longest Common Prefix.
height[i]=lcp(sa[i],sa[i-1])
height[i]��ʾ������i�ĺ�׺��������i-1�ĺ�׺�������ǰ׺�ĳ���.(i>=2,i==1ʱ������ ����Ϊ0�ĺ�׺,������)
height[1]��������0.
height[rk[i]]>=height[rk[i-1]]-1  iΪ��׺����ʼ�±�,height[rk[i]]ǰ׺����ƥ����height[rk[i-1]]-1
����ͨ�����������O(n)ʱ���ڿ������height����.
*/

//ac 145ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000100
char s[N];
int sa[N],rk[N],oldRk[N],cnt[N],id[N],height[N];

//ʱ�临�Ӷ� O(5nlog(n))=O(nlog(n))
void SA(int n){
    int p,k=max(n,126);
    for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
    for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;

    for(int w=1;w<n;w<<=1){//O(log(n))
        p=1;
        for(int i=n;i>n-w;i--) id[p++]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>w) id[p++]=sa[i]-w;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) ++cnt[rk[i]];//O(n)
        for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldRk,rk,sizeof(rk));
        k=0;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=(oldRk[sa[i-1]]==oldRk[sa[i]] && oldRk[sa[i-1]+w]==oldRk[sa[i]+w])?k:++k;
        if(k==n) return;
    }
}

/*
void initHeight(int n){
    for(int i=1,j,k=0;i<=n;i++){
        if(rk[i]==1) continue;
        //����������rk[i]=1,��Ϊheight[rk[i]]>=height[rk[i-1]]-1,ʵ��kֵ����ƥ�����󹫹�ǰ׺����Ŀ�ǿ��Խ���֮ǰ����Ե�
        if(k) k--;
        j=sa[rk[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
}
*/

//O(n)
void initHeight(int n){//֤���õ��� lcp=min(height)��������
    for(int i=1,j,k;i<=n;i++){
        if(rk[i]==1) continue;//ֻ��height[1]�ǲ������,��Ϊ����Ϊ1������Ϊ0�ĺ�׺�������ǰ׺������,����������Ϊ0�ĺ�׺
        j=sa[rk[i]-1];
        //height[rk[i]]>=height[rk[i-1]]-1  iΪ��׺����ʼ�±�,height[rk[i]]ǰ׺����ƥ����height[rk[i-1]]-1,
        //���Լ��ٲ���Ҫ�ıȽ�,���󲽳�,height[rk[i-1]]�п��ܱ����Ϊ0,height[rk[i-1]]-1Ϊ-1,��ʱkȡ0
        //����height[rk[i-1]=1]�����,��Ϊheight[1]���������,û������Ϊ0�ĺ�׺,��ʱk�Ǵ�0��ʼ�Աȵ�
        k=max(0,height[rk[i-1]]-1);
        //���е�n��ѭ�������while k���Ϊn,Ҳ����˵n��ѭ�� whileֻ�ж���O(n),
        //����жϵ���ʼ�±��������ϸ�rk[i-1]�����ۼ��жϵ�,�����ܹ�ֻ���ж�n���ַ�
        //�����������height��ʱ�临�Ӷ�ΪO(n)���while�Ŀ�����Ϊ��������
        while(s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
}

int main(){
    int n;
    long long sum=0;
    scanf("%d",&n);
    scanf("%s",s+1);
    SA(n);
    initHeight(n);
    for(int i=1;i<=n;i++)
        //ͨ�����п��ܵĺ�׺��ȥ �ֵ������ڵĺ�׺�������ǰ׺,��Ϊ�ֵ������ڵ�ƥ��̶ȿ϶����,
        //�����Ӵ��ĸ�����ͨ��ÿ����׺��ǰ׺ȥö�ٵ�,��ǰ����ֵ�����ܳ��ֹ�ĳ��ǰ׺���Ҫȥ��,��˼�ȥheight[i]
        //n-sa[i]+1������Ϊi�ĺ�׺������ǰ׺�ĸ�����Ϊsa[i]���±�,����+1���Ǻ�׺�ĳ���,,����������Ϊi�ĺ�׺��ǰ׺
        //һ����ǰ׺�Ѿ�������Ϊi-1�ĺ�׺�ۼӹ���,���Ҫ��ȥ�ظ��Ĺ���ǰ׺,����ȥheight[i](����Ϊi�ĺ�׺������Ϊi-1
        //�ĺ�׺�������ǰ׺,Ҳ����ʵ���ظ��ۼӵ�����ǰ׺�ĸ���)
        sum+=n-sa[i]+1-height[i];
    printf("%lld\n",sum);
    return 0;
}

/*
//ac sam 162ms
#include<cstdio>
#include<cstring>
#define N 100100
struct node{
    int ch[26],fa,len;
    node(){
        memset(ch,0,sizeof(ch));
        len=0;
    }
}t[N<<1];
char s[N];
int last=1,tot=1;
long long dp[N<<1];

void SAM(int c){
    int p=last,np=last=++tot;
    t[np].len=t[p].len+1;
    for(;p&&!t[p].ch[c];p=t[p].fa) t[p].ch[c]=np;
    if(!p) t[np].fa=1;
    else{
        int q=t[p].ch[c];
        if(t[q].len==t[p].len+1) t[np].fa=q;
        else{
            int nq=++tot;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].fa=t[np].fa=nq;
            for(;p&&t[p].ch[c]==q;p=t[p].fa) t[p].ch[c]=nq;
        }
    }
}

int main(){
    int n;
    long long sum=0;
    scanf("%d",&n);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        SAM(s[i]-'a');
    for(int i=2;i<=tot;i++)
        sum+=t[i].len-t[t[i].fa].len;
    printf("%lld\n", sum);
    return 0;
}
*/
