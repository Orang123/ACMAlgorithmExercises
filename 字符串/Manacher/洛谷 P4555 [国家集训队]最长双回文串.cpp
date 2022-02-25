/*
题意:
顺序和逆序读起来完全一样的串叫做回文串。比如acbca是回文串，
而abc不是（abc的顺序为abc，逆序为cba，不相同）。
输入长度为n的串S，求S的最长双回文子串T,即可将T分为两部分
X，Y，（|X|,|Y|≥1∣X∣,∣Y∣≥1）且X和Y都是回文串。
2<=|S|<=10^5.
链接:https://www.luogu.com.cn/problem/P4555
思路:manacher.此题没太看懂题解,只是记录下来,其实没看懂,
主要对饱和回文和不饱和回文那里不太理解,当时看的洛谷题解
网友"蒟蒻初音ミク"写的比较好.
*/
//93分 78ms
//caaaacaa 这个样例 答案是8,我输出7,不知道哪错了
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

char s1[N],s2[N<<1];
//ed[i]表示以i结尾的最长回文串的长度
//st[i]表示以i开头的最长回文串的长度
int p[N<<1],id,mx,len,st[N<<1],ed[N<<1],ans;

void manacher(){
    len=strlen(s1);
    int k=0;
    s2[k++]='$';
    for(int i=1;i<=len;i++){
        s2[k++]='#';
        s2[k++]=s1[i];
    }
    s2[k++]='#';
    s2[l]='\0';
    len=k;
    mx=0;
    for(int i=1;i<len;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        ed[i+p[i]-1]=max(ed[i+p[i]-1],p[i]-1);
        st[i-p[i]+1]=max(st[i-p[i]+1],p[i]-1);
    }
}

int main(){
    scanf("%s",s1);
    manacher();
    //为什么从3开始
    for(int i=3;i<len;i+=2)
        st[i]=max(st[i],st[i-2]-2);
    for(int i=len-1;i>=3;i-=2)
        ed[i]=max(ed[i],ed[i+2]-2);
    for(int i=3;i<len;i+=2)
        if(st[i] && ed[i])
            ans=max(ans,st[i]+ed[i]);
    printf("%d",ans);
    return 0;
}

/*
//ac 摘自网友"蒟蒻初音ミク"
//因为每个双回文串中间不能交叉，所以只能枚举'#'来找答案
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int min(int a,int b){return a<b?a:b;}//手写min函数
inline int max(int a,int b){return a>b?a:b;}//手写max函数

#define re register
#define ll long long
#define N 100100

int n,len[(N<<1)+10],l[(N<<1)+10],r[(N<<1)+10];
//l[i]表示以i结尾的最长回文串的长度
//r[i]表示以i开头的最长回文串的长度
char ch[N+10],s[(N<<1)+10];
//ch：原数组，s：加了'#'的数组

void manache()//manacher求最长回文串的函数
{
	int id=0,maxx=0;
	for(re int i=1;i<=n;++i)
	{
		if(i<maxx)len[i]=min(maxx-i,len[id*2-i]);
		else len[i]=1;
		while(s[i+len[i]]==s[i-len[i]])++len[i];
		if(i+len[i]>maxx)
		{
			maxx=i+len[i];
			id=i;
		}
		l[i+len[i]-1]=max(l[i+len[i]-1],len[i]-1);//求出以i结尾的饱和回文串的最大长度
		r[i-len[i]+1]=max(r[i-len[i]+1],len[i]-1);//求出以i开头的饱和回文串的最大长度
	}
}

int main()
{
	scanf("%s",ch+1);
	int tlen=strlen(ch+1);
	s[0]='$';s[1]='#';n=1;
	for(re int i=1;i<=tlen;++i)
	{
		s[++n]=ch[i];
		s[++n]='#';
	}
	manache();
	for(re int i=3;i<=n;i+=2)r[i]=max(r[i],r[i-2]-2);//求出以i开头的饱和与不饱和回文串的最大长度
	for(re int i=n;i>=3;i-=2)l[i]=max(l[i],l[i+2]-2);//求出以i结尾的饱和与不饱和回文串的最大长度
	int ans=0;
	for(re int i=3;i<=n;i+=2)if(r[i]&&l[i])ans=max(ans,l[i]+r[i]);//一定要写r[i]&&l[i]，否则会wa
	printf("%d\n",ans);
	return 0;
}
*/
