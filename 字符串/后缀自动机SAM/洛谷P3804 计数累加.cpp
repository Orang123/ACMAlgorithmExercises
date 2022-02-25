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
char s[N];
int last=1,tot=1,cnt[N<<1],sa[N<<1],len[N<<1];

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

int main(){
    int res=-1,siz;
    scanf("%s",s);
    siz=strlen(s);
    for(int i=0;i<siz;i++)
        SAM(s[i]-'a');
    /*计数累加 sa[i]=j记录长度排名为i的 结点 其对应的结点下标为j */
    for(int i=1;i<=tot;i++) cnt[t[i].len]++;
    for(int i=1;i<=tot;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=tot;i++) sa[cnt[t[i].len]--]=i;
    for(int i=tot;i>=1;i--){//从叶子节点 长度最长的点开始统计计算遍历
        len[t[sa[i]].fa]+=len[sa[i]];
        if(len[sa[i]]>1) res=max(res,len[sa[i]]*t[sa[i]].len);/* i>=2 只要判断的len值包括源点即可 if(len[t[sa[i]].fa]>1) res=max(res,len[t[sa[i]].fa]*t[t[sa[i]].fa].len);*/
    }
    printf("%d\n",res);
    return 0;
}
