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
        sum+=t[i].len-t[t[i].fa].len;//这个fa与son的差值 感觉所代表的就是某条特定的有后缀关联的路径上的边数 进行累加恰好就会所有不重复子串的个数具体 性质证明尚未知
    printf("%lld\n", sum);
    return 0;
}
