/*
����:����һ���ַ�������������������ٵ��ַ���ʹ���Ϊ���Ĵ���
�ַ�����<=10^5.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2470
˼·:���Խ�ԭ��s��ת��Ϊģʽ��p,��s��ȥƥ��p,�ҳ�ģʽ��p
��ƥ�䵽��λ��,��ôp���ʣ�µĺ�׺�ַ���������Ҫ��ӵ��ַ�,
����ʹ���Ϊ����.
*/
//ac 0ms ԭ��s��ת��pģʽ��ȥƥ��ԭ��s
#include<cstdio>
#include<cstring>
#define N 100010

int nxt[N],len;
char s[N],p[N];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(){
    getNext();
    int i=0,j=0;
    while(i<len){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=nxt[j];
    }
    return j;
}

int main(){
    while(scanf("%s",s)!=EOF){
        len=strlen(s);
        for(int i=0;i<len;i++)
            p[i]=s[len-i-1];
        p[len]='\0';
        printf("%s",s);
        printf("%s\n",p+kmp());
    }
    return 0;
}

/*
//ac 0ms ��ԭ����ת��p,�ٽ�ԭ��sƴ�ӵ�p�ĺ���,
//֮��nxt[2*len]�����ַ�����ǰ׺��ԭ�ַ����ĺ�׺�����ƥ�䳤��,Ҫ��ӵ��ַ������±���nxt[2*len]~len/2-1�ķ�Χ
#include<cstdio>
#include<cstring>
#define N 100010

int nxt[N<<1],len;
char s[N],p[N<<1];

void getNext(){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    while(scanf("%s",s)!=EOF){
        len=strlen(s);
        for(int i=0;i<len;i++)
            p[i]=s[len-i-1];
        p[len]='\0';
        strcat(p,s);
        len*=2;
        getNext();
        printf("%s",s);
        for(int i=nxt[len];i<len/2;i++)
        	printf("%c",p[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 20ms manacher
//manacher �����һ�����ɺ�׺�Ļ��Ĵ�,��:i+p[i] == len,��������Ӵ�ǰ��Ĳ��ֵ��������Ҫ����Ĳ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

char s1[N],s2[N<<1];
int p[N<<1],id,mx,len,ans;

void manacher(){
    len=strlen(s1);
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    mx=0;
    for(int i=1;i<len;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        if(i+p[i] == len){
            ans=(i-p[i])/2;
            break;
        }
    }
}

int main(){
    while(scanf("%s",s1)!=EOF){
        manacher();
        printf("%s",s1);
        for(int i=ans-1;i>=0;i--)
            printf("%c",s1[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
hash������
*/
