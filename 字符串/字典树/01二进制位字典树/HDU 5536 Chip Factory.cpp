/*
����:ժ������
��һ������a[], ����n��������n�������ҵ�������ʹ��
(a[i]+a[j])^a[k]���i,j,k��ͬ;
n<=1000,a[i]<=10^9.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5536
˼·:01�ֵ���,������a[i]�Ķ�����λ�����ֵ���.
ֻ��Ҫ��֤a[i]��a[j]��a[k]����������ͬ,��ô�ڿ���
a[i]+a[j]��������ֵʱ,����Ҫ���ֵ����е�a[i]��a[j]
ɾ��.�ڲ���ʱ��Ҫ�ۼ�ÿ��ǰ׺���ִ���,ɾ��ʵ���Ƕ�
ÿ���ַ�����ǰ׺num[rt]���м�һ,�ڲ���ʱ���ж�����
�ͱ�Ϊtr[rt][son^1] && num[tr[rt][son^1]],num�Ĵ�������Ϊ0.
*/
//ac 2667ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 31000
using namespace std;

int n,tr[N][2],cnt,num[N],a[1100],ans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    num[cnt]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        num[rt]++;//ǰ׺���ִ���+1
    }
}

void deletWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        rt=tr[rt][son];
        num[rt]--;//val���ʳ��ֵĴ���-1,��Ϊ���������Ҳ�������ǰ׺,����ֱ�ӽ�tr������Ϊ0
    }
}

int findWord(int val){
    int rt=0,son,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i &1;
        //trie���д��� ���λ,���ҵ�ǰλ��û�б�ɾ��
        if(tr[rt][son^1] && num[tr[rt][son^1]]){
            res|=1<<i;
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            insertWord(a[i]);
        }
        for(int i=1;i<=n;i++){
            deletWord(a[i]);//ɾ��a[i]
            for(int j=i+1;j<=n;j++){
                deletWord(a[j]);//ɾ��a[j]
                ans=max(ans,findWord(a[i]+a[j]));
                insertWord(a[j]);//�ָ�a[j]
            }
            insertWord(a[i]);//�ָ�a[i]
        }
        printf("%d\n",ans);
    }
    return 0;
}
