#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000100
using namespace std;
struct node{
    int ch[26],fa,len;
    node(){
        memset(ch,0,sizeof(ch));
        len=0;
    }
}t[N<<1];
struct edge0{
    int to,next;
}ver[N<<1];
char s[N];
int last=1,tot=1,len[N<<1],head[N<<1],index0=0,res=-1;

void add(int fa,int son){
    ver[index0].to=son;
    ver[index0].next=head[fa];
    head[fa]=index0++;
}

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
    len[np]=1;
}

void dfs(int x){//这里深搜是从叶子节点 也就是len长度最长的节点开始统计计算的
    for(int i=head[x];i!=-1;i=ver[i].next){
        int v=ver[i].to;
        dfs(v);
        len[x]+=len[v];
    }
    if(len[x]>1)//根据SAM的后缀性质 得知出现重复子串
        res=max(res,len[x]*t[x].len);
}

int main(){
    int siz;
    scanf("%s",s);
    siz=strlen(s);
    for(int i=0;i<siz;i++)
        SAM(s[i]-'a');
    memset(head,-1,sizeof(head));
    for(int i=2;i<=tot;i++)
        add(t[i].fa,i);
    dfs(1);
    printf("%d\n",res);
    return 0;
}
