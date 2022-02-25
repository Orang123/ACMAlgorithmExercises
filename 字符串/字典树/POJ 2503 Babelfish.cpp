/*
����:ժ������
����һ���ֵ䣬�ֵ��ʽΪ��Ӣ�� -> �����һһӳ���ϵ
Ȼ���������ɸ����ﵥ�ʣ�������ǵ� Ӣ�﷭�뵥�ʣ����
�ֵ��в�����������ʣ��������eh��
��������<=100000,ÿ�����ʳ���<=10
����:http://poj.org/problem?id=2503
˼·:�����ｨ���ֵ���,��Ӣ�ﵥ��������һ����Ӧ�ڵ���ַ�������,
���Ҽ���.
ע������ �����������Ի��з���Ϊ��������.
*/
//ac 516ms
#include<cstdio>
#include<cstring>
#define N 100010
#define M 1000010

int cnt,word[M];
char s1[15],s2[15],tp[15];
struct S{
    int son[26];
    char str[15];
}tr[M];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt].son[i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        if(!tr[rt].son[child])
            tr[rt].son[child]=newNode();
        rt=tr[rt].son[child];
    }
    word[rt]=1;
    strcpy(tr[rt].str,s1);
}

void findWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        rt=tr[rt].son[child];
        if(!rt){
            printf("eh\n");
            return;
        }
    }
    if(word[rt])
        printf("%s\n",tr[rt].str);
    else
        printf("eh\n");
}

int main(){
    char x;
    cnt=-1;
    newNode();
    while(gets(tp) && tp[0]){//���� ���з���ֹ,gets��ѻ��з� ת��Ϊ'\0'������
        sscanf(tp,"%s %s",s1,s2);
        insertWord();
    }
    while(scanf("%s",s2)!=EOF)
        findWord();
    return 0;
}

/*
//ac 547ms
#include<cstdio>
#include<cstring>
#define N 100010
#define M 1000010

int tr[M][26],cnt,word[M];
char str[M][15],s1[15],s2[15],tp[15];

int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        if(!tr[rt][child])
            tr[rt][child]=newNode();
        rt=tr[rt][child];
    }
    word[rt]=1;
    strcpy(str[rt],s1);
}

void findWord(){
    int rt=0,child,len=strlen(s2);
    for(int i=0;i<len;i++){
        child=s2[i]-'a';
        rt=tr[rt][child];
        if(!rt){
            printf("eh\n");
            return;
        }
    }
    if(word[rt])
        printf("%s\n",str[rt]);
    else
        printf("eh\n");
}

int main(){
    char x;
    cnt=-1;
    newNode();
    while(gets(tp) && tp[0]){
        sscanf(tp,"%s %s",s1,s2);
        insertWord();
    }
    while(scanf("%s",s2)!=EOF)
        findWord();
    return 0;
}
*/
