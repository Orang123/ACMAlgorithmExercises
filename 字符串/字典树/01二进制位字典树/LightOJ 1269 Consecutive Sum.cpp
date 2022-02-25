/*
����:����һ�����У�ѡ��һ����������ͣ����������С��
����:http://lightoj.com/volume_showproblem.php?problem=1269
˼·:�������ǰ׺���ֵ��Ϊһ����ֵ����01�ֵ���.
���ڲ������,ÿ���Ҳ�ͬλ��ֵ��,������.��������С��ÿ��
����ͬλ��ֵͬ,������.��Ϊ����С���ǰ���ǰֵ��ͬ��λ����
�ߵ�,����һ��Ҫ�Ȳ����ٲ���,��Ȼ���ص���Сֵ��Զ��0.

���ժ�Բ���:https://blog.csdn.net/SSimpLe_Y/article/details/61618135
sum[1] = a[1];
sum[2] = a[1] ^  a[2];
sum[3] = a[1] ^ a[2] ^a[3];
������е���ѯsum[3]��ʱ��sum[3]���൱�ڸ������Ǹ�����sum[1],sum[2]���൱����ǰ����һ������
���sum[3]��sum[1]�����ֵ����ֵ����ô���൱��[2,3]�����������ֵ����ֵ��
��Ϊsum[3]^sum[1] = a[1] ^ a[2] ^a[3] ^ a[1] = a[2] ^a[3]��һ��������������Σ����൱��û�С�
*/
//ac 281ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1550010
#define INF 0x3f3f3f3f
using namespace std;

int n,tr[N][2],cnt,a[50010],maxans,minans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val,int mark){
    int rt=0,son,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^mark]){
            res|=mark<<i;
            rt=tr[rt][son^mark];
        }
        else{
            res|=(mark^1)<<i;
            rt=tr[rt][son^(mark^1)];
        }
    }
    return res;
}

int main(){
    int T,cas=0,val;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        insertWord(a[0]);//a[0]=0 �Ȳ���0, �п������ֵ��a[i]����
        maxans=0,minans=INF;
        for(int i=1;i<=n;i++){
            scanf("%d",&val);
            a[i]=a[i-1]^val;
            //maxans=max(maxans,a[i]);
            maxans=max(maxans,findWord(a[i],1));
            //minans=min(minans,a[i]);
            minans=min(minans,findWord(a[i],0));
            insertWord(a[i]);//��������С��,Ҫ�Ȳ����ٲ���, ���ⷵ��0
        }
        printf("Case %d: %d %d\n",cas,maxans,minans);
    }
    return 0;
}
