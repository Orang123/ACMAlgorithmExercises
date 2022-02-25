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
       /* for(int i=2;i<p;i++)
            sum+=cnt[i];*/
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
