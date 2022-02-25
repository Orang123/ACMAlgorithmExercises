/*
题意:求解最大连续子序列和,输出最大值和以及该子序列两端点的值
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1231
思路:一直累加,遇到负数,res重置为0,并且记录新的左端点,
当累加和能比之前更大时,记录新的左右端点和累加和.
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
        for(int i=1;i<11000;i++)//初始化ans=-1,避免最大和为0时输出左右端点错误
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
                ans=sum;//记录最大值
                node[k].r=i;//和更大时更新右端点
                node[k].ans=ans;//记录该最大值,答案不唯一时输出l、r较小的情况
            }
            if(sum<=0){//sum<=0时从新开始计算,初始化左端点
                sum=0;
                node[++k].l=i+1;
            }
        }
        if(!node[k].r && ans == -1){//r为0时,说明没有一个最大和大于等于0,说明全是负数
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
不用node数组的做法,只有更新最大值时,才记录之前新的起点
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
                l=a[i];//l每次res从0 开始记录第一个a[i]
            if(res>max_res){
                max_res=res;
                l0=l;//因为l会一直变,左端点 需要单独用一个变量l0再记录
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


