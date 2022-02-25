#include<cstdio>
#include<cstring>
#define N 200010
typedef long long ll;
ll res;
//题目源 Codeforces Gym100548G
//判断两个字符串中共有多少组 公共回文串
//题意：给你两个长度不超过20W的字符串, 都只包含小写字母, 求相同的回文串对数 (S, T), 其中S == T, S来自第一个字符串, T来自第二个字符串, S和T都是回文串
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
        son1=pam1.next[x][i];//son1和son2有可能结点编号不同,但是同一个跟下的的同一类型的儿子 代表的回文串本质是相同的
        son2=pam2.next[y][i];
        if(son1&&son2){//只有回文串相同才能继续深度遍历，否则本身就不相等 继续深度搜索更不会相等,因为是在其两边同时加上一个字符构成更大的回文串的
            res+=(ll)pam1.cnt[son1]*(ll)pam2.cnt[son2];//乘积有可能超过int的最大值,因此强制转化为long long 避免丢失精度
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
        dfs(0,0);//从偶根开始遍历
        dfs(1,1);//从奇根开始遍历
        printf("Case #%d: %lld\n",index,res);
        index++;
    }
    return 0;
}
