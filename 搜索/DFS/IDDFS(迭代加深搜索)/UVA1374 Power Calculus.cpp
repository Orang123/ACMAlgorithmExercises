/*
����:����ժ������
����������n����������Ҫ���γ˳������Դ�x�õ�x^n��
ÿ�γ˳��õ����µĴ���,�������´μ���ʱʹ�á�
�ڼ��������x��ָ��Ӧ��������������
n<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4120
˼·:ö�ٵ�ǰ����a[k]��ǰ���a[1..k-1]������˷������,
������������ö��ÿ�����������,������ʱ ֱ�ӷ��������С��������.
һ����֦���õ�ǰa[1..k]�е�������maxn���˷����,��maxn+maxn
��������,��ʣ���dep-k�ν��������ܻ�õ���������maxn<<(dep-k)
������ֵ��n��С,��˵����ǰ�����õ��Ĵ�����С,����.
*/
//ac 490ms IDA*
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,a[N];

int dfs(int k,int dep){
    if(a[k] == n)
        return 1;
    int maxn=0;
    for(int i=0;i<=k;i++)
        maxn=max(maxn,a[i]);
    if(maxn << (dep-k) < n)//û�������֦��TLE
        return 0;
    //ÿ�μ��㶼����һ�ε�a[k]��֮ǰ�õ����ݴ� �����
    for(int i=k;i>=0;i--){//���� ����˷� �����׾���ʹ���ݴε���n
        a[k+1]=a[k]+a[i];//�˷� �������
        if(a[k+1]>n)
            continue;
        if(dfs(k+1,dep))
            return 1;
        a[k+1]=a[k]-a[i];//�����������
        if(a[k+1]<=0)
            continue;
        if(dfs(k+1,dep))
            return 1;
    }
    return 0;
}

int main(){
    a[0]=1;
    while(scanf("%d",&n) && n){
        for(int i=0;;i++){
            if(dfs(0,i)){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}

/*
����bfs����ģ��״̬,���ö�״̬��������
*/

/*
//TLE dfs+��֦����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],ans,vis[N];

void dfs(int k){
    if(a[k] == n){
    	if(k<ans)
    		ans=k;
        return;
	}
	if(k>=ans)
		return;
	if(ans!=INF){
    	int maxn=0;
    	for(int i=0;i<=k;i++)
        	maxn=max(maxn,a[i]);
    	if(maxn << (ans-k) < n)
        	return;
	}
    vis[a[k]]=1;
    for(int i=k;i>=0;i--){
        a[k+1]=a[k]+a[i];
        if(a[k+1]>n)
            continue;
        dfs(k+1);
        a[k+1]=a[k]-a[i];
        //֮����Ҫ�Դ�����vis���,����Ϊû��IDA*���������,�����᲻�ϵصõ��ظ���֮ǰ���ֹ��Ĵ���,����dfs��ѭ��.
        if(a[k+1]<=0 || vis[a[k+1]])
            continue;
        dfs(k+1);
    }
    vis[a[k]]=0;
}

int main(){
    a[0]=1;
    while(scanf("%d",&n) && n){
    	ans=INF;
    	dfs(0);
    	printf("%d\n",ans);
    }
    return 0;
}
*/
