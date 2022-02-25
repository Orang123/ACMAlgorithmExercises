/*
����:ժ������
����p����Ʒ����,Ȼ������q���ַ�����ѯ,
��ÿ����ѯ������в�ѯ��Ϊ�Ӵ�����Ʒ����.
p<=10000,q<=100000. |s|<=20.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2846
˼·:�ֵ���,��Ϊ���ڶ���ı������ж��Ƿ����ģʽ��.
ac�Զ�����1���ı���ƥ����ģʽ��.
���Կ��ǽ�ÿ���ַ����ĺ�׺�Ӵ������ֵ���,����ÿ����׺�Ӵ�
��ǰ׺�͹�����������������Ӵ�,Ȼ�����,ֻ��Ҫ�ж϶���ͬһ��
������ͬ�Ӵ� �����ظ�����,��:abab"��"ab".
*/
//ac 187ms
#include<cstdio>
#include<cstring>
#define N 4000010//20*20*10000

int p,q,tr[N][26],cnt,wordCnt[N],id[N];
char s[25];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=id[cnt]=0;
    return cnt;
}

void insertWord(char *s,int k){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        if(id[rt]!=k){//ͬ�����Ӵ� ͬһ����ֻͳ��һ��
            wordCnt[rt]++;
            id[rt]=k;
        }
    }
}

int findWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            return 0;
        rt=tr[rt][son];
    }
    return wordCnt[rt];
}

int main(){
    int len;
    cnt=-1;
    newNode();
    scanf("%d",&p);
    for(int i=1;i<=p;i++){
        scanf("%s",s);
        len=strlen(s);
        for(int j=0;j<len;j++)
            insertWord(s+j,i);
    }
    scanf("%d",&q);
    while(q--){
        scanf("%s",s);
        printf("%d\n",findWord());
    }
    return 0;
}
