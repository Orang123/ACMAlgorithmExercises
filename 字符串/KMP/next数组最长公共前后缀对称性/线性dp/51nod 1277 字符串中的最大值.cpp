/*
����:ժ������
����һ���ַ��������ֵֵΪ��
���ַ�������ǰ׺���ֵĴ������Ӧǰ׺�ĳ��ȵĳ˻������ֵ��
����һ���ַ���������ַ��������ֵ��
plen<=10^5.
˵��:ǰ׺���ִ�������ʱ,�Ӵ�֮������ص�.
����:https://www.51nod.com/Challenge/Problem.html#problemId=1277
˼·:��Ȼ��next����ĶԳ���,��ʼÿ��ǰ׺���ִ�������1,��Ҫ����
1~plen�����µ�nxt����������ǰ��׺�Գ���,�ۼӳ��ֵĴ���,
��:cnt[nxt[i]]+=cnt[i].
����Ϊi��ǰ׺,��nxt[i]��ʾ���Ӧ��ͬ��ǰ׺,�������Ϊi��ǰ׺�ĺ�׺��
���� ��Ӧ�ĳ���Ϊnxt[i]��ǰ׺,���cnt[nxt[i]]+=cnt[i],��ͬi��Ӧ��nxt[i]
��������ͬ��.
*/
//ac 31ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
typedef long long ll;

int plen,nxt[N];
ll cnt[N],ans;
char p[N];

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    scanf("%s",p);
    getNext();
    for(int i=plen;i>=1;i--){
        cnt[i]++;//����Ϊi��ǰ׺�������һ�� ����ֱ�Ӹ�ֵ,cnt[i]���ܱ��������ֵ,ֵ���ȸ�����ǰ׺�ĺ�׺�г��ֹ�
        cnt[nxt[i]]+=cnt[i];
    }
    for(ll i=1;i<=plen;i++){
        //printf("cnt[%lld]=%lld\n",i,cnt[i]);
        ans=max(ans,i*cnt[i]);
    }
    printf("%lld",ans);
    return 0;
}
