/*
����:ժ������
����n���ַ�������ӵ��ǰ׺a[0��l]���ַ�������x��������ַ������ȣ���������ֵ��
n<=50000,|s|<=50.
����:http://lightoj.com/volume_showproblem.php?problem=1224
˼·:�ֵ���.
*/
//ac 222ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2500010
using namespace std;

int n,tr[N][26],cnt,wordCnt[N],ans;
char s[60];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'A';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        wordCnt[rt]++;
        ans=max(ans,wordCnt[rt]*(i+1));
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        ans=0;
        cas++;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWord();
        }
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}
