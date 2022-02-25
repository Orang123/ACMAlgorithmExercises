/*
����:ժ������
�������ַ���p��s, �����p��ǰ׺����s�ĺ�׺������ַ���
plen,slen<=50000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2594
˼·:����POJ 2752,���Խ�sƴ�ӵ�p�ĺ���,Ȼ�����next����
�ĶԳ���,�ҵ���õ�ǰ��׺,��Ҫע�ⳤ�Ȳ��ܴ���ԭ��s��p
��ԭʼ���ĳ���,��Ȼ�Ͳ���ԭ����ǰ׺���׺��.
*/
//ac 15ms
#include<cstdio>
#include<cstring>
#define N 50010

int plen,nxt[N<<1];
char p[N<<1],s[N];

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int len1,len2;
    while(scanf("%s %s",p,s)!=EOF){
        len1=strlen(p);
        len2=strlen(s);
        strcat(p,s);
        getNext();
        if(!nxt[plen]){
            printf("0\n");
            continue;
        }
        int i=plen;
        while(nxt[i]>len1 || nxt[i]>len2)//����ͬʱ����nxt[i]<=len1 && nxt[i]<=len2����󳤶�
            i=nxt[i];
        p[nxt[i]]='\0';
        printf("%s %d\n",p,nxt[i]);
    }
    return 0;
}
