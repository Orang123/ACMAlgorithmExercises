/*
����:ժ������
��ӵ����⣬ÿ����������n��������n����ӵģ�ÿ������pos,val��
��˼�Ǵ���Ϊval����ǰ����pos���ˣ������Ķ��������?
n<=200000
����:http://poj.org/problem?id=2828
˼·:�߶����������.
��Ϊ���һ����ѡ����λ��һ���ǲ��ᱻ�ı��,���Ҫ���Ų���ڵ�.
ע�����ʱposֵҪ��1,��Ϊǰ����pos����,ʵ��Ҫ����pos+1��λ��.
*/
//ac 3594ms �߶����������
#include<cstdio>
#define N 200010

//sum[rt]��ʾ�߶�����ǰλ��֮ǰ���ж��ٿ�λ
int n,sum[N<<2],ans[N],pos[N],val[N];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int p,int rt,int l,int r,int c){
    if(l == r){
        sum[rt]=0;
        ans[l]=c;
        return;
    }
    int mid=(l+r)/2;
    if(p<=sum[rt<<1])//��λ����������������p��,����������
        update(p,rt<<1,l,mid,c);
    else//��λ��������������p��,����������,����ʵ��ȷ���Ŀ�λ��Ϊp-sum[rt<<1]
        update(p-sum[rt<<1],rt<<1|1,mid+1,r,c);
    pushup(rt);
}

int main(){
    while(scanf("%d",&n)!=EOF){
        build(1,1,n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&pos[i],&val[i]);
            //����ʱposֵҪ��1,��Ϊǰ����pos����,ʵ��Ҫ����pos+1��λ��.
            pos[i]++;
        }
        for(int i=n;i>=1;i--)
            update(pos[i],1,1,n,val[i]);
        for(int i=1;i<n;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[n]);
    }
    return 0;
}
