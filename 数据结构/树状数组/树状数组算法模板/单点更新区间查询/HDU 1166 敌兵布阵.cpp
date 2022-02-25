/*
����:��һ��һ������T����ʾ��T�����ݡ�
ÿ�����ݵ�һ��һ��������N��N<=50000��,��ʾ������N������Ӫ�أ�
��������N��������,��i��������ai�����i������Ӫ���￪ʼʱ��ai���ˣ�1<=ai<=50����
������ÿ����һ�����������4����ʽ��
(1) Add i j,i��jΪ������,��ʾ��i��Ӫ������j���ˣ�j������30��
(2)Sub i j ,i��jΪ������,��ʾ��i��Ӫ�ؼ���j���ˣ�j������30��;
(3)Query i j ,i��jΪ������,i<=j����ʾѯ�ʵ�i����j��Ӫ�ص�������;
(4)End ��ʾ����������������ÿ������������;
ÿ�����������40000������
����:https://acm.hdu.edu.cn/showproblem.php?pid=1166
˼·:��״����,�����޸Ĳ�������ѯ����.
*/
//ac 218ms ��״����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50010
using namespace std;

int n,a[N],c[N];

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
    char str[20];
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(c,0,sizeof(c));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            update(i,a[i]);
        }
        printf("Case %d:\n",cas);
        int i,j;
        while(scanf("%s",str) && str[0]!='E'){
            scanf("%d%d",&i,&j);
            if(str[0] == 'A')
                update(i,j);
            else if(str[0] == 'S')
                update(i,-j);
            else{
                printf("%d\n",getsum(j)-getsum(i-1));
            }
        }
    }
    return 0;
}

/*
//ac 265ms �߶��������
#include<cstdio>
#include<cstring>
#define N 50010

int sum[N<<2];

void update(int pos, int change,int l,int r,int rt){//�����߶���
    if (l == r){//��Ҷ�ӽ�㿪ʼ����
        sum[rt] += change;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(pos,change,l,mid,rt<<1);
    else update(pos, change,mid+1,r,rt<<1|1);
    sum[rt]=sum[rt<<1]+sum[rt<<1 | 1];
}

int query(int cur_l, int cur_r, int l,int r,int rt){//��ѯ��������ĺ�
    if (cur_l <= l && r <= cur_r){//���������䱻�������������ʱ
        return sum[rt];
    }
    int mid = (l + r) >> 1,res=0;
    if (cur_l <= mid) res+=query(cur_l,cur_r,l,mid,rt << 1);//����������һ�����ڶ����е����,�ݹ�������
    if (cur_r > mid) res+=query(cur_l,cur_r,mid+1,r,rt << 1 | 1);//������һ���������ڶ����е��ұ�,�ݹ�������
    return res;
}

int main(){
    int T,n,pos,change,cur_l,cur_r,cnt=1,x;
    char cmd[6];
    scanf("%d", &T);
    while (T--){
        memset(sum,0,sizeof(sum));
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            update(i,x,1,n,1);
        }
        printf("Case %d:\n", cnt);
        cnt++;
        while (scanf("%s",cmd)&&*cmd!='E'){
            getchar();
            switch (*cmd){
            case 'A'://posλ�ýڵ�����change
                scanf("%d%d", &pos, &change);
                update(pos,change,1,n,1); break;
            case 'S'://posλ�ýڵ����change
                scanf("%d%d", &pos, &change);
                update(pos,-change,1,n,1); break;
            case 'Q'://��ѯ����[cur_l,cur_r]���ۼӺ�
                scanf("%d%d", &cur_l, &cur_r);
                printf("%d\n", query(cur_l,cur_r,1,n,1));
            }
        }
    }
    return 0;
}
*/
