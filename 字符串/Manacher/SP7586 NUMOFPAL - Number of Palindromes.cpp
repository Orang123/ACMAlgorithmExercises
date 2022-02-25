/*
����:��һ�����а����������Ĵ�.
|s|<=1000.
˵��:���Ĵ������ظ�,����Ҫ���ʲ�ͬ,
���Ҫ���ʲ�ͬ�Ļ��Ĵ�,��Ҫ�û�����(PAM-�����Զ���)����.
����:https://www.luogu.com.cn/problem/SP7586
˼·:����ͳ�Ƴ�������Ӵ��ĳ���,������������Ӵ�,���ĳ���
��һ���������������л����Ӵ�,��˿�����manacher�㷨,�ۼ�
���İ뾶/2,��������л��Ĵ�����Ŀ.
���ﲻ�����������Ȼ��ĺ�ż�����Ȼ���.
ʵ���������Ȼ�����Ŀ=����/2+1
ż�����Ȼ�����Ŀ=����/2
��������ΪmanacherԤ����ʱ������'#'�ָ�,��������������û��İ뾶/2�����.

�������ͬ���������ַ���hash+���ֻ�����Զ��������.
*/
//ac 0ms manacher
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1111
using namespace std;
char str1[N],str2[N<<1];
int len,p[N<<1];

void init(){
    int n=strlen(str1),k=1;
    str2[0]='$';
    for(int i=0;i<n;i++){
        str2[k++]='#';
        str2[k++]=str1[i];
    }
    str2[k++]='#';
    str2[k]='\0';
    len=k;
}

int Manacher(){
    init();
    int id=0,mx=0,sum=0;
    //p[0]=0;
    for(int i=1;i<len;i++){
        if(i<mx) p[i]=min(mx-i,p[2*id-i]);
        else p[i]=1;
        while(str2[i-p[i]] == str2[i+p[i]]) p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        /*�����������p[i]/2����ǰ��չ���Ļ��Ĵ����±�iΪ�Գ����İ����Լ��������ж��ٻ����Ӵ�
        ������$#a#a#b#a#a# p[6]=6 6/2=3 ����b aba aabaa�⼸����b��Գ����ĵĻ����Ӵ�,������ö�ٳ�����
        �Գ����ľ�����չ���p[i]/2�ۼ�������������ַ����е����л��Ĵ�*/
        sum+=p[i]/2;
    }
    return sum;
}

int main(){
    scanf("%s",str1);
    printf("%d\n",Manacher());
    return 0;
}

/*
//ac PAM(�����Զ���)
#include<cstdio>
#include<cstring>
#define N 1010

struct PAM{
    int s[N];
    int n;
    int p;
    int last;
    int next[N][26];
    int fail[N];
    int len[N];
    int cnt[N];
    int num[N];
    int sum;

    int newNode(int l){
        for(int i=0;i<26;i++) next[p][i]=0;
        len[p]=l;
        cnt[p]=0;
        num[p]=0;
        return p++;
    }

    void init(){
        p=0;
        newNode(0);
        newNode(-1);
        n=0;
        last=0;
        s[0]=-1;
        fail[0]=1;
        fail[1]=0;
        sum=0;
    }

    int getFail(int x){
        while(s[n-len[x]-1] != s[n]) x=fail[x];
        return x;
    }

    void add(int c){
        c-='a';
        s[++n]=c;
        int cur=getFail(last);
        if(!next[cur][c]){
            int now=newNode(len[cur]+2);
            fail[now]=next[getFail(fail[cur])][c];
            next[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }

    void countAllNum(){
        for(int i=p-1;i>=2;i--){
            cnt[fail[i]]+=cnt[i];
                sum+=cnt[i];//�����º�����н�����ı��ʲ�ͬ�Ļ��Ĵ����ִ����ۼӽ��Ϊ���ַ������л��Ĵ��ĸ��� Ҫ�ų�0��1 ż�������
        }
    }

}pam;

int main(){
    char a[N];
    scanf("%s",a);
    int len=strlen(a);
    pam.init();
    for(int i=0;i<len;i++)
        pam.add(a[i]);
    pam.countAllNum();
    printf("%d\n",pam.sum);
    return 0;
}

*/
