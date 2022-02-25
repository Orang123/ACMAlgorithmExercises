/*
����:ժ������
����һt,n,�ٸ�����n�����У�������еĿ���ʹ�������ĺ͵���t
ע�ⲻ������ظ����,��Ŀ����������Ĭ���ǽ������е�.
n<=12,t<=1000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1258
˼·:dfs����ö�� ÿ����ȡ�벻ȡ,ע����һ��������һ������ͬʱ,
�����ظ�ѡȡ,�����ظ����.
*/
//ac 0ms dfs+����ö��ÿ������ѡ�벻ѡ,ȥ���ظ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int t,n,a[N],vis[N],ok;

void dfs(int k,int sum){
    if(sum>t)
        return;
    if(sum == t){
        ok=1;
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",a[i]);
                    flag=1;
                }
                else
                    printf("+%d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    vis[k]=1;
    //�����k-1�����͵�k��������,�������ж�
    //�����k-1�����͵�k�������,������ǵ�k-1����ѡȡ������ѡȡ��k����,
    //���������k-1������ѡȡ,��k����ѡȡ,�����Ȼ��͵�k-1����ѡȡ,��k������ѡȡ �ظ�
    if(a[k]!=a[k-1] || (a[k] == a[k-1] && vis[k-1]))
        dfs(k+1,sum+a[k]);
    vis[k]=0;
    dfs(k+1,sum);
}

int main(){
    while(scanf("%d%d",&t,&n) && t+n){
        ok=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("Sums of %d:\n",t);
        dfs(1,0);
        if(!ok)
            printf("NONE\n");
    }
    return 0;
}

/*
//ac 0ms dfsѭ������ö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int t,n,a[N],vis[N],ok;

void dfs(int k,int sum){
    if(sum>t)
        return;
    if(sum == t){
        ok=1;
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",a[i]);
                    flag=1;
                }
                else
                    printf("+%d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    //������� ʵ�ʵ�n���� �ǿ϶���ȡ����,���dfs��������������k == n+1,ֱ�Ӿ�����k������ʱ�����ж��Ƿ�sum == t����,��ʱ���ܻ�δ�ۼӵ�n����
    for(int i=k;i<=n;i++){
    	if(i-1>=k && a[i] == a[i-1])//ö����һλ���ܺ�֮ǰ��һλ��ͬ,����������ظ� ���
    		continue;
    	vis[i]=1;
    	dfs(i+1,sum+a[i]);
    	vis[i]=0;
	}
}

int main(){
    while(scanf("%d%d",&t,&n) && t+n){
        ok=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("Sums of %d:\n",t);
        dfs(1,0);
        if(!ok)
            printf("NONE\n");
    }
    return 0;
}
*/
