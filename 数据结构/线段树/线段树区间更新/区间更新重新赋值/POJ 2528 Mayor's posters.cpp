/*
����:ժ������
������Ҫ��ѡ�г���Ȼ����һ��ǽ�Ͽ���������Ϊ�Լ���Ʊ��
ÿ���˿�����������һ�����򣬺������Ŀ��Ը���ǰ��ģ���
�����һ�����Կ��������ź�����
n�ź���,n<=10^4,�������ĸ��ǵ��������䷶Χ<=10^7.
����:http://poj.org/problem?id=2528
˼·:���߶�������Ⱦɫ����,�������䷶ΧΪ10^7,ֱ�ӿ���MLE.
���Խ����䷶Χ��ɢ��,����ֱ����ɢ������������������,
������������:https://blog.csdn.net/zezzezzez/article/details/80230026
�����ź���Ϊ��1~10 1~4 6~10
��ɢ��ʱ X[ 1 ] = 1, X[ 2 ] = 4, X[ 3 ] = 6, X[ 4 ] = 10
��һ�ź���ʱ��ǽ��1~4��ȾΪ1��
�ڶ��ź���ʱ��ǽ��1~2��ȾΪ2��3~4��Ϊ1��
�����ź���ʱ��ǽ��3~4��ȾΪ3��1~2��Ϊ2��
���գ���һ�ź�������ʾ����ȫ�����ˣ��������2����ʵ�������Բ�����������ȷ���Ϊ3��
�µ���ɢ����Ϊ����������1�������һ����������������1 4 6 10�м��5
���㷨��ʵ����1��4֮�䣬6��10֮�䶼���������ģ�
X[ 1 ] = 1, X[ 2 ] = 4, X[ 3 ] = 5, X[ 4 ] = 6�� X[ 5 ] = 10
����֮�󣬵�һ����1~5��Ⱦ��1���ڶ���1~2��Ⱦ��2��������4~5��Ⱦ��3
���գ�1~2Ϊ2��3Ϊ1��4~5Ϊ3�����������ȷ���3��
*/
//ac 110ms �߶�������Ⱦɫ���� ��ɢ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//��ɢ�������������ΪN<<1,�߶���ʵ�ʽڵ���ΪN<<1<<2=N<<3,
//����ΪҪ�ڱ�������֮�������,ʵ���߶����������ұ߽������,
//����߶����ڵ��ſ���N<<4,tp����Ҳ��ͬ������,����ֻ��洢��������N<<1,����Ϊ�м�Ҫ����ֵ,���Կ���N<<2.
int n,sum[N<<4],vis[N],cnt,maxn,tp[N<<2];
struct Node{
    int l,r;
}node[N];

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])
        sum[rt]=sum[rt<<1];
    else
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=-1;
    }
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

void query(int rt,int l,int r){
    if(sum[rt]!=-1){
        if(!vis[sum[rt]]){
            cnt++;
            vis[sum[rt]]=1;
        }
        return;
    }
    if(l == r)//�п���Ҷ�ӽڵ� û��������
        return;
    int mid=(l+r)/2;
    if(l<=mid)
        query(rt<<1,l,mid);
    if(r>mid)
        query(rt<<1|1,mid+1,r);
}

int main(){
    int T,k;
    scanf("%d",&T);
    while(T--){
        k=cnt=0;
        memset(sum,-1,sizeof(sum));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&node[i].l,&node[i].r);
            tp[++k]=node[i].l;
            tp[++k]=node[i].r;
        }
        sort(tp+1,tp+1+k);
        maxn=unique(tp+1,tp+1+k)-(tp+1);
        int len=maxn;
        for(int i=2;i<=len;i++){
            if(tp[i]-tp[i-1]>1)//��������ֵ֮��������1��,���м����һ��ֵ,������ɢ���� rnk�պý���ֻ��1
                tp[++maxn]=tp[i-1]+1;
        }
        sort(tp+1,tp+1+maxn);//tp��������������ֵ,��������.
        for(int i=1;i<=n;i++){
            //lower_bound���ֲ��ҵ���<=node[i].l�ĵ�ַ,ֱ������ ʵ�ʵ�rnk��������һ,��˻�Ҫ���1
            node[i].l=lower_bound(tp+1,tp+1+maxn,node[i].l)-(tp+1)+1;
            node[i].r=lower_bound(tp+1,tp+1+maxn,node[i].r)-(tp+1)+1;
            update(node[i].l,node[i].r,1,1,maxn,i);
        }
        query(1,1,maxn);
        printf("%d\n",cnt);
    }
    return 0;
}
