/*
题意:n个的串，求出它们的最长公共子串,这个子串可以正序也可以逆序.
n<=100,串长度<=100.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1238
思路:同POJ 3450,只是要考虑文本串正序、反序两个方向的匹配,正反序间
取最大长度,各个文本串间取最短公共子串的长度.
*/
//ac 46ms
//复杂度O(100*100*100)=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,plen,ans;
char s[N][M],g[N][M];

void getNext(char *p){
    plen=strlen(p);
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
            cnt=max(cnt,j);
        }
        else
            j=nxt[j];
    }
    return cnt;
}

int main(){
    int T,tp,k;
    scanf("%d",&T);
    while(T--){
        ans=0;
        len=INF;
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%s",s[i]);
            tp=strlen(s[i]);
            if(tp<len){
                len=tp;
                k=i;//记录最短串的下标 作为模式串
            }
            for(int j=0;j<tp;j++)//g表示其它串的反序
                g[i][j]=s[i][tp-j-1];
        }
        for(int i=0;i<len;i++){
            tp=INF;
            for(int j=0;j<n;j++){
                if(j == k) continue;
                tp=min(tp,max(kmp(s[j],s[k]+i),kmp(g[j],s[k]+i)));
            }
            if(tp>ans)
                ans=tp;
        }
        printf("%d\n",ans);
    }
    return 0;
}
