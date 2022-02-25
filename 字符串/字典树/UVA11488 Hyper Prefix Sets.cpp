/*
����:ժ������
�������ɸ�01��������P(S)Ϊ������ļ��ϵ�ĳ������ǰ׺�ĳ���
�����������ǰ׺���ַ���������������P(S)��
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2483
˼·:�ֵ���.
*/
//ac 80ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10000010
using namespace std;

int n,tr[N][2],wordCnt[N],cnt,ans;
char s[200];

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'0';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        wordCnt[rt]++;
        ans=max(ans,wordCnt[rt]*(i+1));
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        ans=0;
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWord();
        }
        printf("%d\n",ans);
    }
    return 0;
}
