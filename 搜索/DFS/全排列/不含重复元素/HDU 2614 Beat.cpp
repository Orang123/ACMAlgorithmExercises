/*
����:ժ������
СAϲ����ս���⣬����һ��n*n�ľ��� ��a[i][j]����ʾ��������i���ȥ��j�⣬
������a[i][j]��ʱ�䣬ÿ����ѡ��j��Ŀ����ʱ��>=i�Ļ���ʱ�䡣
���СA�ܽ�������������.
n<15.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2614
˼·:dfs��������
*/
//ac 46ms dfs����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,a[N][N],vis[N],ans;

void dfs(int k,int num,int time){
    if(num>ans)
        ans=num;
    for(int i=0;i<n;i++){
        if(vis[i] || a[k][i]<time)
            continue;
        vis[i]=1;
        dfs(i,num+1,a[k][i]);
        vis[i]=0;
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        }
        vis[0]=1;
        dfs(0,1,0);
        vis[0]=0;
        printf("%d\n",ans);
    }
    return 0;
}
