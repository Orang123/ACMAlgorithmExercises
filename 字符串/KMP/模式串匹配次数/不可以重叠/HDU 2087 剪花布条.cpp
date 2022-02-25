/*
����:���������ַ���s��p����s�а����˼������ص���p����
slen,plen<=1000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2087
˼·:��POJ 3461����,ֻ���ǵ�������ص�,����ⲻ���ص�,
��ô��ƥ��ʱ,��ģʽ��pƥ�����,����+1,p���±�j��Ҫ��0
��ͷ��ʼƥ��.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#define N 1010

int slen,plen,next[N];
char s[N],p[N];

void getNext(){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(){
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
        if(j == plen){
            cnt++;
            j=0;
        }
    }
    return cnt;
}

int main(){
    while(scanf("%s",s) && s[0]!='#'){
        scanf("%s",p);
        getNext();
        printf("%d\n",kmp());
    }
    return 0;
}
