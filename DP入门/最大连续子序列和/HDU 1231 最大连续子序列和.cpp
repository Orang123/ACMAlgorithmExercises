/*
����:���������������к�,������ֵ���Լ������������˵��ֵ
����:http://acm.hdu.edu.cn/showproblem.php?pid=1231
˼·:һֱ�ۼ�,��������,res����Ϊ0,���Ҽ�¼�µ���˵�,
���ۼӺ��ܱ�֮ǰ����ʱ,��¼�µ����Ҷ˵���ۼӺ�.
*/
//ac 140ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[11000];
struct Node{
    int l,r,ans;
}node[11000];

int main(){
    int n,ans,sum,k;
    while(scanf("%d",&n)&&n){
        for(int i=1;i<11000;i++)//��ʼ��ans=-1,��������Ϊ0ʱ������Ҷ˵����
            node[i].l=node[i].r=0,node[i].ans=-1;
        k=1;
        sum=0;
        ans=-1;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        node[k].l=1,node[k].r=0;
        for(int i=1;i<=n;i++){
            sum+=a[i];
            if(sum>ans){
                ans=sum;//��¼���ֵ
                node[k].r=i;//�͸���ʱ�����Ҷ˵�
                node[k].ans=ans;//��¼�����ֵ,�𰸲�Ψһʱ���l��r��С�����
            }
            if(sum<=0){//sum<=0ʱ���¿�ʼ����,��ʼ����˵�
                sum=0;
                node[++k].l=i+1;
            }
        }
        if(!node[k].r && ans == -1){//rΪ0ʱ,˵��û��һ�����ʹ��ڵ���0,˵��ȫ�Ǹ���
            printf("0 %d %d\n",a[1],a[n]);
            continue;
        }
        for(int i=1;i<=k;i++){
            if(ans == node[i].ans){
                printf("%d %d %d\n",ans,a[node[i].l],a[node[i].r]);
                break;
            }
        }
    }
    return 0;
}
/*
����node���������,ֻ�и������ֵʱ,�ż�¼֮ǰ�µ����
//ac 109ms
#include<cstdio>
#define INF -0x3f3f3f3f
int main(){
    int n,a[10010];
    while(scanf("%d",&n)&&n){
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        int res=0,l,r,max_res=INF,l0;
        for(int i=0;i<n;i++){
            res+=a[i];
            if(res-a[i]==0)
                l=a[i];//lÿ��res��0 ��ʼ��¼��һ��a[i]
            if(res>max_res){
                max_res=res;
                l0=l;//��Ϊl��һֱ��,��˵� ��Ҫ������һ������l0�ټ�¼
                r=a[i];
            }
            if(res<0)
                res=0;
        }
        if(max_res<0)
            printf("0 %d %d\n",a[0],a[n-1]);
        else
            printf("%d %d %d\n",max_res,l0,r);
    }
    return 0;
}
*/


