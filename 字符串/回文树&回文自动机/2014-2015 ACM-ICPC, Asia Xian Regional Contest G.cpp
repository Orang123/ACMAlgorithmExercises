#include<cstdio>
#include<cstring>
#define N 200010
typedef long long ll;
ll res;
//��ĿԴ Codeforces Gym100548G
//�ж������ַ����й��ж����� �������Ĵ�
//���⣺�����������Ȳ�����20W���ַ���, ��ֻ����Сд��ĸ, ����ͬ�Ļ��Ĵ����� (S, T), ����S == T, S���Ե�һ���ַ���, T���Եڶ����ַ���, S��T���ǻ��Ĵ�
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
        }
    }

}pam1,pam2;

void dfs(int x,int y){
    int son1,son2;
    for(int i=0;i<26;i++){
        son1=pam1.next[x][i];//son1��son2�п��ܽ���Ų�ͬ,����ͬһ�����µĵ�ͬһ���͵Ķ��� ����Ļ��Ĵ���������ͬ��
        son2=pam2.next[y][i];
        if(son1&&son2){//ֻ�л��Ĵ���ͬ���ܼ�����ȱ�����������Ͳ���� ��������������������,��Ϊ����������ͬʱ����һ���ַ����ɸ���Ļ��Ĵ���
            res+=(ll)pam1.cnt[son1]*(ll)pam2.cnt[son2];//�˻��п��ܳ���int�����ֵ,���ǿ��ת��Ϊlong long ���ⶪʧ����
            dfs(son1,son2);
        }
    }
}

int main(){
    int T,len,index=1;
    char a[N],b[N];
    scanf("%d",&T);
    while(T--){
        res=0;
        scanf("%s",a);
        scanf("%s",b);
        len=strlen(a);
        pam1.init();
        for(int i=0;i<len;i++)
            pam1.add(a[i]);
        pam1.countAllNum();
        len=strlen(b);
        pam2.init();
        for(int i=0;i<len;i++)
            pam2.add(b[i]);
        pam2.countAllNum();
        dfs(0,0);//��ż����ʼ����
        dfs(1,1);//�������ʼ����
        printf("Case #%d: %lld\n",index,res);
        index++;
    }
    return 0;
}
