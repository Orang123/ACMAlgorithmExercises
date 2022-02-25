/*
����:����Ϊn��������,�����ǰp�����½���������.
ע��:�����в������ظ�.
1<n<=1000, 1<p<=10000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2610
˼·:dfsö��[1,n]�г���Ϊlen��������.
ע���ظ�������ֻö��һ��,��Ҫ�ж�[st,i)���Ƿ��к͵�ǰ
���е�iλ��ȵ�,������ȵľ����ظ�������,��Ϊǰ����Ѿ�
ö�ٹ���.
һ����֦�������ǰ����Ϊi�������в�����,����Ϊi+1,i+2...n-1
��������Ҳ�ǲ����ڵ�
*/
//ac 78ms dfsö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,p,a[N],b[N],ok,cnt;

void dfs(int k,int st,int len){
    if(cnt>=p)//���Ѿ�ö�ٹ�ǰp��ʱ,��ֱ�ӷ���
        return;
    if(k == len+1){
        ok=1;
        cnt++;
        printf("%d",b[1]);
        for(int i=2;i<k;i++)
            printf(" %d",b[i]);
        printf("\n");
        return;
    }
    int flag;
    for(int i=st;i<=n;i++){
        if(a[i]<b[k-1]) continue;//�����һ��λ��b[k-1],��һ��Ԫ��a[i]�����½�,������a[i]>=b[k-1]
        flag=0;
        for(int j=st;j<i;j++){//�ж�������֮ǰ[st,i)λ���Ѿ�ö�ٹ���Ԫ���Ƿ��к�a[i]��ͬ��,������ͬ��,�����ظ�ö��
            if(a[j] == a[i]){
                flag=1;
                break;
            }
        }
        if(flag) continue;
        b[k]=a[i];
        dfs(k+1,i+1,len);//�ж������е�k+1��λ��
    }
}

int main(){
    while(scanf("%d%d",&n,&p)!=EOF){
        cnt=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<n;i++){
            ok=0;
            dfs(1,1,i);
            if(!ok) break;//�������Ϊi�������в�����,i+1,i+2..n-1��ȻҲ������,���������֦  ��TLE
            if(cnt == p) break;//�Ѿ�ö����ǰp��ʱ,����.
        }
        printf("\n");
    }
    return 0;
}
