/*
����:ժ������
��һ��n�����������У���n����������0,1,2,3...n-1��n����
(����һ�������˳�����)�������ȼ���һ�³�ʼ���е���������
Ȼ��ѵ�һ��Ԫ��a1�ŵ�an����ȥ���γ�������a2 a3 a4...an a1��
Ȼ������������е�������������ִ�����Ʋ���(һ��Ҫִ��n-1��)
ֱ����������an a1 a2...an-1Ϊֹ�����������������е��������������С��������
n<=5000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1394
˼·:�����������ʼ���е���������,ÿ�ν���λ���ַŵ�ĩβ��,�ᵼ��ԭ�Ⱥ���
����λ���ֹ��ɵ�������ٸ���Ϊa[i]-1,�����õ�ĩβ���ʹ��ԭ�ȱ�
a[i]���������a[i]ǰ�������µ��������Ϊn-a[i].
����µ���������Ϊsum-(a[i]-1)+n-a[i].
������Ϊ��״����ڵ��Ų���Ϊ0,���a[i]�����ֶ�����1.
*/
//ac 31ms ��״����
#include<cstdio>
#include<cstring>
#define N 5010

int n,c[N],a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    int sum,ans;
    while(scanf("%d",&n)!=EOF){
        sum=0;
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i]++;
        }
        for(int i=1;i<=n;i++){
            update(a[i],1);
            sum+=i-getsum(a[i]);
        }
        ans=sum;
        for(int i=1;i<n;i++){
            sum=sum-(a[i]-1)+(n-a[i]);
            if(sum<ans)
                ans=sum;
        }
        printf("%d\n",ans);
    }
    return 0;
}
