/*
����:n���Ĵ���������ǵ�������Ӵ�,����Ӵ���������Ҳ��������.
n<=100,������<=100.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1238
˼·:ͬPOJ 3450,ֻ��Ҫ�����ı������򡢷������������ƥ��,�������
ȡ��󳤶�,�����ı�����ȡ��̹����Ӵ��ĳ���.
*/
//ac 46ms
//���Ӷ�O(100*100*100)=10^6
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
                k=i;//��¼��̴����±� ��Ϊģʽ��
            }
            for(int j=0;j<tp;j++)//g��ʾ�������ķ���
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
