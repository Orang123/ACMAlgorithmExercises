/*
����:ժ������
���������ַ���s,p����������������û��ǰ��˳��Ҫ���ǳ���������ȣ�
������ֵ�����С��
plen,slen<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1867
˼·:��kmp ��s��ƥ��p,����p��ƥ��s,���ƥ�䳤�Ƚϴ�����,
�������һ��,����ֵ����С�ļ���.
*/
//ac 46ms ��ͨnext����
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N],p[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    //��Ϊģʽ�����ı����м�ƥ�����˺�,�����ܽ���Ҫ����next[plen]����ƥ��,����j<plen
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    //ƥ������������ı�������ĩβ,������ģʽ��ƥ�����,��Ϊ��Ҫ���ǵ���ģʽ����ǰ׺���ı����ĺ�׺ƥ�����󳤶�
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j;
}

int main(){
    int len1,len2;
    while(scanf("%s %s",s,p)!=EOF){
        len1=kmp(s,p);
        len2=kmp(p,s);
        if(len1 == len2){
            if(strcmp(s,p)<0){
                printf("%s",s);
                printf("%s",p+len1);
            }
            else{
                printf("%s",p);
                printf("%s",s+len2);
            }
        }
        else if(len1>len2){
            printf("%s",s);
            printf("%s",p+len1);
        }
        else if(len1<len2){
            printf("%s",p);
            printf("%s",s+len2);
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 46ms next�����Ż�
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N],p[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen){//��Ϊ���õ�next[plen],����j<plen
        if(i == -1 || p[i] == p[j]){
        	if(p[++i] != p[++j])
        		next[j]=i;
        	else
        		next[j]=next[i];
		}
        else
            i=next[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j;
}

int main(){
    int len1,len2;
    while(scanf("%s %s",s,p)!=EOF){
        len1=kmp(s,p);
        len2=kmp(p,s);
        if(len1 == len2){
            if(strcmp(s,p)<0){
                printf("%s",s);
                printf("%s",p+len1);
            }
            else{
                printf("%s",p);
                printf("%s",s+len2);
            }
        }
        else if(len1>len2){
            printf("%s",s);
            printf("%s",p+len1);
        }
        else if(len1<len2){
            printf("%s",p);
            printf("%s",s+len2);
        }
        printf("\n");
    }
    return 0;
}
*/
