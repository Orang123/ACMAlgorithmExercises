/*
����:ժ������
����n���ַ���, ���������ȽϵĴ���. ÿ�αȽ϶���Ҫ�Ƚ�
(str1[i] == str2[i])�� (str1[i] == '\0'��һ��).
n<=4000,�ַ�������<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2832
˼·:�ֵ���.
˼·�ο��Բ���:https://www.cnblogs.com/TheRoadToTheGold/p/6958455.html
ÿ�����ַ�����Ҫôȫ��ƥ�䣬Ҫô�м�ֹͣƥ��
���ȫ��ƥ�䣬�Ƚϴ���Ϊ 2*len+2����\0������ƥ�䣩
����м�ֹͣƥ�䣬�Ƚϴ���Ϊ 2*��ͬǰ׺����+1 ��1��ʧ��ƥ����˳���
����
1�����ڵ�i���ַ������ȼ���i-1��������ȫ�� �м�ֹͣƥ��
��������ټ���ȫ��ƥ����
2��ƥ��һ����+sum*2
*/
//ac 730ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4000010
#define M 1100
using namespace std;
typedef long long ll;

//end0��ʾ�ַ�����β��'\0'�����.
int n,tr[N][62],end0[N],sum[N],cnt;
char s[M];
ll ans;//�����ǳ���,Ҫ��ll,��������wa

int newNode(){
    cnt++;
    for(int i=0;i<62;i++)
        tr[cnt][i]=0;
    sum[cnt]=end0[cnt]=0;
    return cnt;
}

int check(char x){
    if(x>='0' && x<='9')
        return x-'0';
    if(x>='a' && x<='z')
        return x-'a'+10;
    if(x>='A' && x<='Z')
        return x-'A'+36;
}

void insertWord(int num){
    ans+=num;//�����Ǽ����ǰ��i-1����û����ȫ���,�����ֻ��ԱȽ�һ��
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=check(s[i]);
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        ans+=sum[rt]*2;//��ǰ�ַ�����ǰ��������ַ���ǰ׺���,��Ϊÿ�� ����2��
        sum[rt]++;
    }
    ans+=end0[rt];//�����Ǽ���ĩβ'\0' ��ȫ���,�������ܰ�ǰ�� ans+=num�� i-1�ַ�������û����ȫ��ԵĲ�����ԵĴ���
    end0[rt]++;
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        cnt=-1;
        newNode();
        ans=0;
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            insertWord(i-1);
        }
        printf("Case %d: %lld\n",cas,ans);
    }
    return 0;
}
