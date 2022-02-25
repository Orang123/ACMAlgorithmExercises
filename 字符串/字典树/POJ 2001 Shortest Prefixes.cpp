/*
����:ժ������
�������ɸ����ʵ��ֵ䣬���ֵ���ÿһ�����ʵ����Ψһǰ׺��
���Ψһǰ׺���ҳ���������е�һ��ǰ׺��Ҫ�����ǰ׺ֻ
����������г��ֹ�������Ҫ�����ǰ׺��̡�
���������Ψһǰ׺�����������ʱ���.
���ʸ���<=1000,ÿ�����ʳ���<=20.
����:http://poj.org/problem?id=2001
˼·:�����ֵ���,ͳ��ÿ���ڵ����浥�ʵ���Ŀ,����ʱ�����ֹ��
��һ���ڵ����浥�ʸ���Ϊ1���ַ�.�������Ψһǰ׺.
*/

//ac 547ms
#include<cstdio>
#include<cstring>
#define N 1100
#define M 20010

int tr[M][26],cnt,num[M],len[N];
char s[N][25];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    num[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son;
    len[id]=strlen(s[id]);
    for(int i=0;i<len[id];i++){
        son=s[id][i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        num[rt]++;
    }
}

void findWord(int id){
    printf("%s ",s[id]);
    int rt=0,son;
    for(int i=0;i<len[id];i++){
        son=s[id][i]-'a';
        rt=tr[rt][son];
        if(num[rt] == 1){
            for(int j=0;j<=i;j++)
                printf("%c",s[id][j]);
            printf("\n");
            return;
        }
    }
    printf("%s\n",s[id]);//������Ψһǰ׺,������ʱ���.
}

int main(){
    cnt=-1;
    newNode();
    int siz=0;
    while(scanf("%s",s[++siz])!=EOF)
        insertWord(siz);
    for(int i=1;i<=siz;i++)
        findWord(i);
    return 0;
}
