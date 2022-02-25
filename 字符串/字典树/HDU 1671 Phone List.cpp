/*
����:ժ������
����n�������������Ƿ���һ��������һ������ǰ׺��
����123����12345��ǰ׺�����������ʱ���NO����֮���YES.
n<=10000,ÿ�������ֳ���<=10
����:https://acm.hdu.edu.cn/showproblem.php?pid=1671
˼·:�ֵ���,���ڲ����Ȳ�϶̵ĺ��ϳ���,����ʱ�ж�ǰ׺�Ƿ�
�Ѿ����ڲ���ĵ�����,�����Ȳ�ϳ��ĺ��϶̵�,�жϽ϶̵ĵ���
β�ڵ�����Ƿ��ж���.
*/
//ac 78ms
#include<cstdio>
#include<cstring>
#define N 100010

int n,tr[N][10],cnt,word[N],flag;
char s[15];

int newNode(){
    ++cnt;
    for(int i=0;i<10;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,len=strlen(s),son;
    for(int i=0;i<len;i++){
        son=s[i]-'0';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        if(word[rt]){
            flag=1;
            return;
        }
    }
    word[rt]=1;
    if(!flag){
        for(int i=0;i<10;i++){
            if(tr[rt][i]){
                flag=1;
                return;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        flag=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            if(!flag)
                insertWord();
        }
        if(!flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
