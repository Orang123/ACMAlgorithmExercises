/*
����:ժ������
����һ���ַ���һ���ַ�������ת�����ַ������ֵĵ�һ�������
�����кܶ���ͬ���ȣ������һ�������������ʼ�յ�λ�ã��Լ�ת
����Ļ��Ĵ���
�ַ�������<=200000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3294
˼·:manacher.��¼�������Ӵ�����ԭ���е���ʼλ��(i-p[i])/2.
����ʵ��ʼ�±���յ��±�Ϊ:(i-p[i])/2,(i-p[i])/2+maxLen-1.
������ת������ַ���.
*/
//ac 187ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;

char s1[N],s2[N<<1],mp[26];
int p[N<<1],id,mx,len,pos,maxLen;

void manacher(){
    len=strlen(s1);
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    mx=maxLen=0;
    for(int i=1;i<len;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        if(p[i]-1>maxLen){
            maxLen=p[i]-1;
            pos=(i-p[i])/2;
        }
    }
}

int main(){
    char x;
    mp[0]='z';
    for(int i=1;i<26;i++)
        mp[i]='a'+i-1;
    while(scanf("%c %s",&x,s1)!=EOF){
        getchar();
        manacher();
        if(maxLen<=1)
            printf("No solution!\n");
        else{
            int ed;
            ed=pos+maxLen-1;
            printf("%d %d\n",pos,ed);
            for(int i=pos;i<=ed;i++){
                int j=s1[i]-x;
                j++;
                j+=26;//��������±�Ϊ��,��26 �ٶ�26ȡ��
                j%=26;
                printf("%c",mp[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
