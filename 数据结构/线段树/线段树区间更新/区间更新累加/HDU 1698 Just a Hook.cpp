/*
����:���ǽ����ӵ�������������Ŵ�1��n��
����ÿ�β�����Pudge ���Խ���Ŵ�X��Y����������������Ϊͭ��������������
���ӵ���ֵ����Ϊn����������ֵ֮�͡���׼ȷ��˵��ÿ�ֹ��ӵ�ֵ�������£�
����ÿ��ͭ������ֵΪ 1��
����ÿ����������ֵΪ 2��
����ÿ���������ֵΪ 3��
������֪��ִ�в������ӵ���ֵ��
�����ܻ���Ϊԭʼ��������ͭ���Ƴɵġ�
n<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1698
˼·:�߶����������������.
*/
//ac 826ms �߶����������������
#include<cstdio>
#include<cstring>
#define N 100010

int n,q,sum[N<<2],lazy[N<<2];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void pushdown(int rt,int l,int r){
    if(lazy[rt]!=-1){
        int mid=(l+r)/2;
        lazy[rt<<1]=lazy[rt<<1|1]=lazy[rt];
        sum[rt<<1]=(mid-l+1)*lazy[rt];
        sum[rt<<1|1]=(r-mid)*lazy[rt];
        lazy[rt]=-1;
    }
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=(curr-curl+1)*c;
        lazy[rt]=c;
        return;
    }
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

int main(){
    int T,x,y,z;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(lazy,-1,sizeof(lazy));
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++)
            update(i,i,1,1,n,1);
        while(q--){
            scanf("%d%d%d",&x,&y,&z);
            update(x,y,1,1,n,z);
        }
        printf("Case %d: The total value of the hook is %d.\n",cas,sum[1]);//[1,n]������;���sum[1]
    }
    return 0;
}
