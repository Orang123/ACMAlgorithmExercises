/*
����:ժ������
����һ��n���������У��� a Ϊ��������ǰ׺�����ͣ�b Ϊ���������׺�����ͣ�
�� a ��� b �����ֵ��ǰ׺�ͺ�׺����Ϊ�ա�
n<=10^5,ÿ����ֵ<=10^12.
����:http://codeforces.com/problemset/problem/282/E
˼·:��ǰ׺���Ͳ���01�ֵ���,�ú�׺�������ֵ,ע��Ҫ
������ֵ0,�п��ܲ��Һ�׺���� �������ֵ,��Ҫע����λʱ,
1Ҫǿ��ת��ΪLL,�������ֵ���,Ĭ�ϵ�1��int.
*/
//ac 248ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6000010
#define M 100010
using namespace std;
typedef long long ll;

int n,tr[N][2],cnt;
ll a[M],prefix[M],suffix[M],ans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(ll val){
    int rt=0,son;
    for(int i=60;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

ll findWord(ll val){
    int rt=0,son;
    ll res=0;
    for(int i=60;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){
            res|=1LL<<i;//1Ҫǿ��ת��ΪLL,�������ֵ���,Ĭ�ϵ�1��int.
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

int main(){
    cnt=-1;
    newNode();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    insertWord(0);//���ֻ��һ����,����������䱾��,���˱�����1ʱ,����0,������0,�ֵ�����û��1,���յ����ֵǡ�þ��Ǳ���
    for(int i=1;i<=n;i++){
        prefix[i]=prefix[i-1]^a[i];
        insertWord(prefix[i]);
    }
    for(int i=n;i>=1;i--){
        suffix[i]=suffix[i+1]^a[i];
        ans=max(ans,findWord(suffix[i]));
    }
    printf("%lld",ans);
    return 0;
}
