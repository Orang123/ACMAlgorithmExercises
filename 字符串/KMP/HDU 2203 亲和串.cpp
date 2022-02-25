/*
����:ժ������
���������ַ���s1��s2,�����ͨ��s1ѭ����λ��ʹs2������s1�У���ô���Ǿ�˵s2��s1���׺ʹ���
s1,s2<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2203
˼·:ֱ��ö����λn��,ÿ����һ��kmp,���Ӷ�O(n^2),n<=10^5,��Ȼ����,
���Խ�s1ƴ��������β���,����2n,ֻ��һ��kmp�����O(s1len*2+s2len)ʱ��
������Ƿ����.
*/
//ac 15ms ��ͨnext����
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N<<1],p[N],tp[N];

void getNext(char *p){
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
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j == plen;
}

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);//ֱ����sƴ��s strcat(s,s)����ѭ��,���ȸ���һ������
        printf("%s\n",kmp()?"yes":"no");
    }
    return 0;
}

/*
//ac 15ms strstr����ʹ��,������Ӷ� һ���Ǳ�kmpҪ���
//strstr(str1,str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ���
//����ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��
#include<cstdio>
#include<cstring>
#define N 100100

char s[N<<1],p[N],tp[N];

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);
        printf("%s\n",strstr(s,p)?"yes":"no");
    }
    return 0;
}
*/

/*
strstr����ԭ��
����ԭ�� strstr��char *a�� char *b������a���Ƿ����b����ַ�����
�������ص�һ���Ӵ���λ�ã����򷵻�NULL��
˼·����ʵ����������Ӵ������⡣�����������bΪ�յ�ʱ��ֱ�ӷ���a��
��b��Ϊ�յ�ʱ��ָ��startָ�룬ͨ������ѭ������һ��strstr�е��Ӵ���b����ƥ�䣬
���b�ߵ�ĩβ����ʾ�ҵ���startָ��ָ��ʼλ�ã�����start������ǰ��
//���Ӷ�O(slen*plen) ���Ǹ���������
class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        if (!*needle)
            return haystack;
        char *start = haystack;
        char *temp1 = haystack, *temp2 = needle;
        while (*start){
            temp1 = start;
            temp2 = needle;
            while (*temp2 && temp1 && !(*temp2 - *temp1))
                temp2++, temp1++;
            if (!*temp2)
                return start;
            start++;
        }
        return NULL;
    }
};
*/

/*
//ac 0ms next�����Ż�
#include<cstdio>
#include<cstring>
#define N 100100

int slen,plen,next[N];
char s[N<<1],p[N],tp[N];

void getNext(char *p){
    plen=strlen(p);
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
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

int kmp(){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    return j == plen;
}

int main(){
    while(scanf("%s %s",s,p)!=EOF){
        strcpy(tp,s);
        strcat(s,tp);
        printf("%s\n",kmp()?"yes":"no");
    }
    return 0;
}
*/
