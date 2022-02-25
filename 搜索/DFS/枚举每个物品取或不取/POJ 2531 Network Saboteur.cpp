/*
����:ժ������
����һ��n��n�ľ���mp��mp[i][j]��ʾ��i����͵�j�����������
Ҫ����n�����Ϊ��������A��B������sumΪ ����A�и��㵽����
B�и���������ͣ�������sum��
n<=20.
����:http://poj.org/problem?id=2531
˼·:ö��ÿ��������A���ϻ���B����,vis[i]=1��ʾ i������A����,
vis[i]=0��ʾi������B����.����ʵʱ����������,һ����֦�����i
�����A���Ϻ�,��ǰ�����ͼ�����,��˵��������߽ϲ�,����������ȥ,
ת�����ǽ�i������B����.
*/
//ac 94ms dfs����+��֦
//����֦ 250ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
using namespace std;

int n,mp[N][N],vis[N],ans;

void dfs(int k,int sum){
    if(k == n+1){
        if(sum>ans)
            ans=sum;
        return;
    }
    int tp=sum;
    vis[k]=1;
    for(int i=1;i<=n;i++){
        if(i!=k && vis[i])//i�㱾�����A���� ��k����ͬһ����,��Ҫ��֮ǰ���������������,��Ϊ�Ѿ���ͬһ������
            tp-=mp[k][i];
        else//k i�ڲ�ͬ����
            tp+=mp[k][i];
    }
    if(tp>sum)//��֦:��k�����A���� �����ͼ�����,�Ͳ���k�����A����,ת�����Ƿ���ԭ�ȵ�B����
        dfs(k+1,tp);//k�����A����
    vis[k]=0;
    dfs(k+1,sum);
}

int main(){
    ans=0;
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}

/*
//TLE dfs+���� ����֦ ��������Ϊk == n+1ʱ Ҫ������ѭ����O(n^2)
//���Ӷ�O(2^20=10^6*400)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
using namespace std;

int n,mp[N][N],vis[N],ans;

void dfs(int k){
    if(k == n+1){
        int sum=0;
        for(int i=1;i<=n;i++){
        	for(int j=i+1;j<=n;j++){
        		if(vis[i] != vis[j])
        			sum+=mp[i][j];
			}
		}
		if(sum>ans)
            ans=sum;
        return;
    }
    vis[k]=1;
    dfs(k+1);//k�����A����
    vis[k]=0;
    dfs(k+1);
}

int main(){
    ans=0;
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    dfs(1);
    printf("%d",ans);
    return 0;
}
*/
