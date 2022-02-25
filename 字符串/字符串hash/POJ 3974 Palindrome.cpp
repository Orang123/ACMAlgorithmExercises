/*
����:��������Ӵ��ĳ���
����:http://poj.org/problem?id=3974
˼·:manacher����,���ַ���hash.
*/
//ac 594ms ����Ĵ������������ӻ��İ뾶 �Ƕ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007Ҳ��
#define N 1000100
using namespace std;
typedef unsigned long long ull;
ull h1[N*2],h2[N*2],powr[N];
char s[N],str[2*N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    int index=1;
    while(scanf("%s",s+1) && strcmp(s+1,"END")){
        len=strlen(s+1);
        int j=0;
        for(int i=1;i<=len;i++){
            str[++j]='#';
            str[++j]=s[i];
        }
        str[++j]='#';
        h1[0]=0;
        for(int i=1;i<=j;i++)
            h1[i]=h1[i-1]*p+(str[i]-'a'+1);
        h2[j+1]=0;
        for(int i=j;i>=1;i--)
            h2[i]=h2[i+1]*p+(str[i]-'a'+1);
        int l=0;
        for(int i=1;i<=j;i++){//ö�ٻ��ĶԳ����ĵ�
            if(i-l<1 || i+l>j) break;//���ĳ�����ĵ� ���Ե�ǰ����İ뾶Խ��,����ĵ�ֻ������Գ�,���İ뾶�㲻��������,������
            while(h1[i-1]-h1[i-l-1]*powr[l] == h2[i+1]-h2[i+l+1]*powr[l] && i-l>=1 && i+l<=j) l++;//�������Ӵ��ԳƵ�hashֵ��Ⱦ������������ӻ��İ뾶
        }
        printf("Case %d: %d\n",index,l-1);//��Ϊstr�����#Ԥ����֮��Ļ��İ뾶����������Ĵ��ĳ���
        index++;
    }
    return 0;
}
