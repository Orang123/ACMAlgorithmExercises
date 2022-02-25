/*
����:ժ������
����n����������˳�򣩣�����ѡ��6��������ӡ���е���Ϸ�����
k=0��ʾ�����������ӡʱÿ������֮����пո񣬲���ÿ������֮����һ�����С�
6<n<13.
����:http://poj.org/problem?id=2245
˼·:ʵ�ʸ�����n����������������,Ҫ��ѡȡ��6����Ҳ����������,
��������������,�˻�����һ���������,ʵ�ʾ���ÿ����ѡȡ���,dfs����ö��.
һ����֦:�����ǰѡȡ��������ʣ�໹δѡȡ�����е�������С��6�򷵻�.
*/
//ac 32ms dfsÿ����ѡȡ���
//���Ӷ�O(2^13)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int n,a[N],vis[N];

void dfs(int k,int num){
    if(num == 6){
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    flag=1;
                    printf("%d",a[i]);
                }
                else
                    printf(" %d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    if(num+n-k+1<6)
        return;
    vis[k]=1;
    dfs(k+1,num+1);
    vis[k]=0;
    dfs(k+1,num);
}

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dfs(1,0);
        printf("\n");
    }
    return 0;
}

/*
//ac 32ms dfsѭ������ö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int n,a[N],vis[N];

void dfs(int k,int num){
    if(num == 6){
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    flag=1;
                    printf("%d",a[i]);
                }
                else
                    printf(" %d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    if(num+n-k+1<6)
        return;
    for(int i=k;i<=n;i++){
    	vis[i]=1;
    	dfs(i+1,num+1);
    	vis[i]=0;
	}
}

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dfs(1,0);
        printf("\n");
    }
    return 0;
}
*/
