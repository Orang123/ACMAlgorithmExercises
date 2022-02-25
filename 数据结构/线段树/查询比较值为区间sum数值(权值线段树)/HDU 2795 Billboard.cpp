/*
����:ժ������
һ��h*w�Ĺ���������棬ÿ������Ϊ1*wi��
����������������λ�ã����ڼ��У�λ�þ������ϣ����󣩣��������-1.
h,w<=10^9,n<=2*10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2795
˼·:��h��Ϊ�߶�����������,w�����ֵ��Ϊ��������ֵ,�����߶���,
��ѯʱ��ΪҪ���������ڿ��ϵ�λ��,������ȱȽ���������������Ƿ��ܷ���,
���ܷ����ٵݹ����������.
*/
//ac 2230ms �߶��������ѯ
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;

int h,w,n,sum[N<<2];

void pushup(int rt){
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=w;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

int query(int rt,int l,int r,int c){
    if(l == r){
        sum[rt]-=c;
        return l;
    }
    int mid=(l+r)/2,res;
    if(c<=sum[rt<<1])
        res=query(rt<<1,l,mid,c);
    else
        res=query(rt<<1|1,mid+1,r,c);
    pushup(rt);
    return res;
}

int main(){
    int x;
    while(scanf("%d%d%d",&h,&w,&n)!=EOF){
        if(h>n)
            h=n;
        build(1,1,h);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            if(x>sum[1])
                printf("-1\n");
            else
                printf("%d\n",query(1,1,h,x));
        }
    }
    return 0;
}
