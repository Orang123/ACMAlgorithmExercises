/*
����:
˳��������������ȫһ���Ĵ��������Ĵ�������acbca�ǻ��Ĵ���
��abc���ǣ�abc��˳��Ϊabc������Ϊcba������ͬ����
���볤��Ϊn�Ĵ�S����S���˫�����Ӵ�T,���ɽ�T��Ϊ������
X��Y����|X|,|Y|��1�OX�O,�OY�O��1����X��Y���ǻ��Ĵ���
2<=|S|<=10^5.
����:https://www.luogu.com.cn/problem/P4555
˼·:manacher.����û̫�������,ֻ�Ǽ�¼����,��ʵû����,
��Ҫ�Ա��ͻ��ĺͲ����ͻ������ﲻ̫���,��ʱ����������
����"�X�m�����ߥ�"д�ıȽϺ�.
*/
//93�� 78ms
//caaaacaa ������� ����8,�����7,��֪���Ĵ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

char s1[N],s2[N<<1];
//ed[i]��ʾ��i��β������Ĵ��ĳ���
//st[i]��ʾ��i��ͷ������Ĵ��ĳ���
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
    //Ϊʲô��3��ʼ
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
//ac ժ������"�X�m�����ߥ�"
//��Ϊÿ��˫���Ĵ��м䲻�ܽ��棬����ֻ��ö��'#'���Ҵ�
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int min(int a,int b){return a<b?a:b;}//��дmin����
inline int max(int a,int b){return a>b?a:b;}//��дmax����

#define re register
#define ll long long
#define N 100100

int n,len[(N<<1)+10],l[(N<<1)+10],r[(N<<1)+10];
//l[i]��ʾ��i��β������Ĵ��ĳ���
//r[i]��ʾ��i��ͷ������Ĵ��ĳ���
char ch[N+10],s[(N<<1)+10];
//ch��ԭ���飬s������'#'������

void manache()//manacher������Ĵ��ĺ���
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
		l[i+len[i]-1]=max(l[i+len[i]-1],len[i]-1);//�����i��β�ı��ͻ��Ĵ�����󳤶�
		r[i-len[i]+1]=max(r[i-len[i]+1],len[i]-1);//�����i��ͷ�ı��ͻ��Ĵ�����󳤶�
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
	for(re int i=3;i<=n;i+=2)r[i]=max(r[i],r[i-2]-2);//�����i��ͷ�ı����벻���ͻ��Ĵ�����󳤶�
	for(re int i=n;i>=3;i-=2)l[i]=max(l[i],l[i+2]-2);//�����i��β�ı����벻���ͻ��Ĵ�����󳤶�
	int ans=0;
	for(re int i=3;i<=n;i+=2)if(r[i]&&l[i])ans=max(ans,l[i]+r[i]);//һ��Ҫдr[i]&&l[i]�������wa
	printf("%d\n",ans);
	return 0;
}
*/
