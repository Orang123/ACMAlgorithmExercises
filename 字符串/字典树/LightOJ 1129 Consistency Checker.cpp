/*
����:ժ������
����n�����ж��Ƿ����һ����Ϊ��һ������ǰ׺��
n<=10000,|s|<=10.
����:http://lightoj.com/volume_showproblem.php?problem=1129
˼·:�ֵ���.����ʱ�ж�,�п����Ȳ�϶̵�,Ҳ�п����Ȳ�ϳ���,
�����Ȳ�϶̵�,���ϳ���,�ڲ�ϳ���Ҫ�жϵ�ǰrtǰ׺�Ƿ��п���
�Ѿ�����һ������.�����Ȳ�ϳ���,���϶̵�,�ڲ�϶̵�ʱ,Ҫ�ж�
�϶̵��ʵĺ����Ƿ����ַ�.
*/
//ac 36ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,tr[N][10],cnt,word[N],flag;
char s[15];

int newNode(){
    cnt++;
    for(int i=0;i<10;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
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
    for(int i=0;i<10;i++){
        if(tr[rt][i]){
            flag=1;
            return;
        }
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        flag=0;
        cas++;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            if(!flag)
                insertWord();
        }
        printf("Case %d: %s\n",cas,flag?"NO":"YES");
    }
    return 0;
}
