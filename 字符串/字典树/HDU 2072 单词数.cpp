/*
����:ժ������
ͳ��һƪ�����ﲻͬ���ʵ�������
����:https://acm.hdu.edu.cn/showproblem.php?pid=2072
˼·:ֱ��ÿ���ַ�����ǰ��ıȽ��Ƿ���ͬ���Ӷ���Ƕ��n^3,����ֵ���.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#define N 1000100

int tr[N][26],word[N],cnt,ans;
char str[N],s[150];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    if(!word[rt]){
        ans++;
        word[rt]=1;
    }
}

int main(){
    int len;
    while(gets(str) && str[0]!='#'){
        cnt=-1;
        newNode();
        ans=0;
        len=strlen(str);
        int j=0;
        for(int i=0;i<=len;i++){
            if(str[i]>='a' && str[i]<='z')
                s[j++]=str[i];
            else{
                if(!j)//��2���ո�,���ܲ���,�ᵼ��rt=0 ���������һ��
                    continue;
                s[j]='\0';
                insertWord();
                j=0;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
