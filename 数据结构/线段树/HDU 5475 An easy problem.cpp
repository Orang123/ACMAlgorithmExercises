/*
����:ժ������
��X����ֵ1��Ȼ���Q��������ÿ��������Ӧһ������M�����������1��X���Զ�Ӧ��M��
�����2����Ե�M�β�����Ӧ��M'�������X��ֵ�Ը���ֵȡ���Ľ����
Q<=10^5,M<=10^9.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5475
˼·:�߶������㵥���޸� ���ǰ׺�˻�ֵ,���Ⱪ��Ҳ�ܹ�,
�о���״����Ҳ����,����û���ò�֪��Ϊɶ,���ܺ�ȡģ�йذ�.
*/
//ac 1154ms �߶������㵥���޸� ���ǰ׺�˻�ֵ
#include<cstdio>
#include<cstring>
#define N 100010
typedef long long ll;

ll sum[N<<2],q,m;

void update(int pos,int rt,int curl,int curr,int c){
    if(curl == curr){
        sum[rt]=c;
        return;
    }
    int mid=(curl+curr)/2;
    if(pos<=mid)
        update(pos,rt<<1,curl,mid,c);
    else
        update(pos,rt<<1|1,mid+1,curr,c);
    sum[rt]=sum[rt<<1]*sum[rt<<1|1]%m;
}

int main(){
    int T,x,y;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        scanf("%d%d",&q,&m);
        for(int i=1;i<=(q<<2);i++)
            sum[i]=1;
        printf("Case #%d:\n",cas);
        for(int i=1;i<=q;i++){
            scanf("%d%d",&x,&y);
            if(x == 1){
                update(i,1,1,q,y);
                printf("%lld\n",sum[1]);
            }
            else{
                update(y,1,1,q,1);
                printf("%lld\n",sum[1]);
            }
        }
    }
    return 0;
}

/*
//ac 4040ms ������������
//�о������޸Ŀ���ֱ����ǰ׺�ͳ���,�Ѻ���Ĳ��ִ�����,ֱ���۳� ������һ��һ���������۳�
//ժ�Բ���:https://blog.csdn.net/h1021456873/article/details/48765565
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+100;
__int64 a[maxn];

int main()
{
	int t,n,mod,x,i,j;
	__int64 temp,temp2,y;
	scanf("%d",&t);
	for(int _=1;_<=t;_++) {
		scanf("%d%d",&n,&mod);
		temp=1;
		for(i=1;i<=n;i++) {
			scanf("%d%I64d",&x,&y);
			if(i==1) printf("Case #%d:\n",_);
			if(x==1) {
				a[i]=y;
				temp=temp*y%mod;
				printf("%I64d\n",temp);
			}
			else {
				temp=1;
				a[y]=1;
				a[i]=1;
				for(j=1;j<i;j++) {
					 temp= temp*a[j]%mod;
				}
				printf("%I64d\n",temp);
			}
		}
	}
	return 0;
}
*/
