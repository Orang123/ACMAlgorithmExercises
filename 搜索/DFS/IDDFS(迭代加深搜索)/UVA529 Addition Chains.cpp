/*
题意:
a[0]=1 a[m]=n,a序列为严格递增序列, 对于任意的下标k在[1，m]内，
都存在1<=j<=i<=k-1使得 a[i]+a[j]=a[k],找出m最小的符合条件的序列，
即长度最小的序列。
n<=10000.
链接:https://www.luogu.com.cn/problem/UVA529
思路:同UVA1374 Power Calculus,不同点是枚举下一个数a[k+1]的时候,是从[1,k]中
选出任意两个数,因此是嵌套两层循环.
*/
//ac 0ms IDA*
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
using namespace std;

int n,a[N];

int dfs(int k,int dep){
    if(a[k] == n)
        return 1;
    if(a[k] << (dep-k) < n)
        return 0;
    for(int i=k;i>=1;i--){
        for(int j=i;j>=1;j--){
            a[k+1]=a[i]+a[j];
            if(a[k+1]<=a[k] || a[k]>n)
                continue;
            if(dfs(k+1,dep))
                return 1;
        }
    }
    return 0;
}

int main(){
    a[1]=1;
    while(scanf("%d",&n) && n){
        for(int i=1;;i++){
            if(dfs(1,i)){
                for(int j=1;j<=i;j++){
                    if(j == 1)
                        printf("%d",a[j]);
                    else
                        printf(" %d",a[j]);
                }
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
此题bfs不好模拟状态,不好对状态进行判重
*/

/*
//ac 230ms dfs搜索+剪枝
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],b[N],ans;

void dfs(int k){
    if(a[k] == n){
    	if(k<ans){
    		ans=k;
    		for(int i=1;i<=k;i++)
    			b[i]=a[i];
		}
        return;
	}
	//当前的a[k] 后面(ans-k)个数都累加末尾两个相同的a[k]  得到的结果比n还小就 返回
	if(a[k] << (ans-k) < n)//这个剪枝有很大不确定性,如果先行搜索到的长度较大 这个剪枝的高效性也无法保证
		return;
    for(int i=k;i>=1;i--){
        for(int j=i;j>=1;j--){
            a[k+1]=a[i]+a[j];
            if(a[k+1]<=a[k] || a[k]>n)
                continue;
            dfs(k+1);
        }
    }
}

int main(){
    a[1]=1;
    while(scanf("%d",&n) && n){
    	ans=INF;
    	dfs(1);
    	for(int i=1;i<=ans;i++){
        	if(i == 1)
                printf("%d",b[i]);
            else
                printf(" %d",b[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
