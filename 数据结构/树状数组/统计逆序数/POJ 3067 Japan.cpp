/*
����:ժ������
�ձ����Ķ��������������ֱ���N��M�����У�����Щ��������K�����ٹ�·��
ÿ����·�����Ŷ�����һ�����к���������һ�����У����ܹ���Щ��·�ж��ٽ����
N,M<=1000.
����:http://poj.org/problem?id=3067
˼·:��·(u1,v1),(u2,v2)����ֽ�������Ϊu1<u2,v1>v2��
u1>u2,v1<v2 ��������Ż���ֽ���.��ʵ���ǹ̶�һ���˵��
��С��ϵ����һ���˵㹹�ɵ�����Ե��ܸ���,������״�����Ż�ʱ��.
2������:
1.����u��һ�ؼ���,v�ڶ��ؼ��ִ�С��������,���˵�v��Ϊ��״�����еĽڵ���.
��ô��״����ڵ�洢�ľ���û�й��ɽ���Ĺ�·����,��ôʵ������Ծ���
i-getsum(a[i].v),iΪ��ǰ���µĹ�·����.
2.����u��һ�ؼ���,v�ڶ��ؼ��ִӴ�С����,���˵�v��Ϊ��״�����еĽڵ���.
��ô��״����ڵ�洢�ľ��ǹ��ɽ���Ĺ�·����,��ôʵ������Ծ���
getsum(a[i].v-1),����Ҫע���Ҷ��н������������빹�ɽ�������,��˲�ѯʱ
��ż�1,���Ǹ��±�Ų���1
*/
//ac 407ms
//��С�������� ans+=i-getsum(a[i].v) �ȸ��º��ѯ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000000
typedef long long ll;
using namespace std;

int n,m,k,maxn,c[N];
struct Ele{
    int u,v;
    bool operator < (const Ele &x)const{
        if(u!=x.u)
            return u<x.u;
        else
            return v<x.v;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=maxn){
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
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        maxn=-1;
        memset(c,0,sizeof(c));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&a[i].u,&a[i].v);
            maxn=max(maxn,a[i].v);//v�ڵ�������� ��Ϊ��״�����������Ƚڵ�
        }
        sort(a+1,a+1+k);
        ll ans=0;
        for(int i=1;i<=k;i++){
            update(a[i].v,1);//�ȸ��º��ѯ
            ans+=i-getsum(a[i].v);//��������Ҷ�v�ڵ��غϵ�������� �������벻���ɽ��������ᱻ����
        }
        printf("Test case %d: %lld\n",cas,ans);
    }
    return 0;
}

/*
//ac 391ms
//�Ӵ�С���� ans+=getsum(a[i].v-1) �Ȳ�ѯ�����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000000
typedef long long ll;
using namespace std;

int n,m,k,maxn,c[N];
struct Ele{
    int u,v;
    bool operator < (const Ele &x)const{
        if(u!=x.u)
            return u>x.u;
        else
            return v>x.v;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=maxn){
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
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        maxn=-1;
        memset(c,0,sizeof(c));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++){
            scanf("%d%d",&a[i].u,&a[i].v);
            maxn=max(maxn,a[i].v);
        }
        sort(a+1,a+1+k);
        ll ans=0;
        for(int i=1;i<=k;i++){//�Ȳ�ѯ �����
            ans+=getsum(a[i].v-1);//v�Ҷ��н���ʱ��������뽻��,���Բ�ѯ���Ҫ��1
            update(a[i].v,1);//���±��������a[i].v
        }
        printf("Test case %d: %lld\n",cas,ans);
    }
    return 0;
}

*/
