/*
����:ժ������
����һ�ַ���S��Ҫ����S���ҵ�����Ӵ�E��ʹ��S�����ʽ��EAEBE����
����A��B����Ϊ�����S�Ӵ���Ҳ����˵�Ӵ�E����S��ǰ׺Ҳ��S�ĺ�׺��
ͬʱ����S�м���֣�������ǰ׺E���׺E�ص���
�ַ����̶�<=10^6.
˵��:��3��"E"���ǲ����ص���.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4763
˼·:2�ֽⷨ
�ⷨ1:ö��ԭ�������ǰ��׺i,���ı���Ϊs+i,����Ϊlen-2*i,ģʽ��Ϊs,
����Ϊi,kmp�ж��ı������Ƿ����ģʽ��
�ⷨ2:ö��ԭ�������ǰ��׺x,"EAEBE"�е�ǰ2/3,�ж�EAEB�����ǰ��׺
�Ƿ���ڵ���x,�����ڴ��ڵ���x�������ǰ��׺,��Զ���м�һ�����ڳ���Ϊx��E.
*/
//ac 46ms ö��ԭ�������ǰ��׺i,���ı���Ϊs+i,����Ϊlen-2*i,ģʽ��Ϊs,����Ϊi,kmp�ж��ı������Ƿ����ģʽ��
#include<cstdio>
#include<cstring>
#define N 1000100

int nxt[N],len;
char s[N];

void getNext(char *p){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,int slen,char *p,int plen){
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=nxt[j];
    }
    return j == plen;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        len=strlen(s);
        getNext(s);
        int i=len;
        while(i){
            i=nxt[i];
            if(i<=len/3 && kmp(s+i,len-2*i,s,i))//i>len/3�Ļ� �п����ص�
                break;//��һ������ ֱ�ӽ���,��Ϊ����Ӵ�E
        }
        printf("%d\n",i);
    }
    return 0;
}

/*
//ac 31ms ö��ԭ�������ǰ��׺x,"EAEBE"�е�ǰ2/3,
//�ж�EAEB�����ǰ��׺�Ƿ���ڵ���x,�����ڴ��ڵ���x�������ǰ��׺,��Զ���м�һ�����ڳ���Ϊx��E,�����
#include<cstdio>
#include<cstring>
#define N 1000100

int nxt[N],len;
char s[N];

void getNext(char *p){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<len){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int check(int x){
    //�ж�ǰ2/3���Ӵ���EAEB���������ǰ��׺�Ƿ���ڵ��� ֮ǰö�ٵ�ԭ���������ǰ��׺x�ĳ���,�����ڵ���,���м�һ������E
	for(int i=x*2;i<=len-x;i++){
		if(nxt[i]>=x)
			return 1;
	}
	return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        len=strlen(s);
        getNext(s);
        int i=len;
        while(i){
            i=nxt[i];
            if(i<=len/3 && check(i))
                break;
        }
        printf("%d\n",i);
    }
    return 0;
}
*/
