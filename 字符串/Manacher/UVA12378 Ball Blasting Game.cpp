/*
����:ժ������
����һ���ַ�������ĳ��λ�ò���һ���ַ�Cʹ�����������ַ�C���ڣ�
Ȼ��������Щ�ַ���������õ������������ַ����������������ַ�����
������Ӵ�������������ͬ���ַ�����ͬ�����������Դ�����.
�ַ�������<=100000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3800
˼·:manacher.��������ͬ���ַ���д��һ���ַ�,֮��
����manacher�����İ뾶,���� ���Ļ��İ뾶/2.
*/
//ac 10ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

char s1[N],s2[N<<1];
int p[N<<1],id,mx,len,ans;

void manacher(){
    len=strlen(s1);
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        if(s1[i] == s1[i+1])
            continue;
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';//���s2ĩβҪ����'\0',����ᵼ��,��ͬ���� �ڶԱ���������չ�Ա�ʱ �������鷶Χʱ,֮ǰs2�洢��ֵ��Ӱ����İ뾶�Ĵ�С.
    len=k;
    mx=0;
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
        if(p[i]>ans)
            ans=p[i];
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%s",s1);
        manacher();
        printf("%d\n",ans/2);
    }
    return 0;
}
