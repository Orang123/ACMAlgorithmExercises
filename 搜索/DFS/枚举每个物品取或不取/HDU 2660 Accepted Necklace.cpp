/*
����:ժ������
������ʯ����Ŀn���Ƴ���������ı�ʯ����k��Ȼ���ٸ���ÿ����ʯ�ļ�ֵa[i]������b[i]��
����ĸ�׻���ܵ��������w�������������������£������ļ�ֵ�����ܴ�
n<=20,k<=n,a[i],b[i]<=1000,w<=1000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2660
˼·:
���ֽⷨ:
1.dfs����ö�����б�ʯѡȡ�����.2^n
2.��ά���ñ���.O(n^2*w)
*/
//ac 0ms dfs
//ʱ�临�Ӷ�(2^n)=2^20=1048576 n̫��ͻ�TLE
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans;

void dfs(int i,int num,int suma,int sumb){
    if(num == k){
        if(suma>ans)
            ans=suma;
        return;
    }
    if(i == n+1)
        return;
    //num+n-i+1<k
    if(k-num>n-i+1)//��֦:�Ѻ������Ʒȫ��ѡ�� �������Ǵﲻ��k,�򷵻�
        return;
    if(sumb+b[i]<=w)
        dfs(i+1,num+1,suma+a[i],sumb+b[i]);
    dfs(i+1,num,suma,sumb);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        dfs(1,0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms dfs+ǿ��֦(�౳��) ��ӽ���̬�滮˼��ı�������
//dp[i][sumb]��ʾǰi����Ʒ������Ϊsumbʱ,����ܻ�õļ�ֵ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans,dp[N][21000];

void dfs(int i,int num,int suma,int sumb){
    if(suma<=dp[i][sumb])
    	return;
    dp[i][sumb]=suma;
    if(num == k){
    	if(suma>ans)
    		ans=suma;
    	return;
	}
    if(i == n+1)
        return;
    if(sumb+b[i]<=w)
        dfs(i+1,num+1,suma+a[i],sumb+b[i]);
    dfs(i+1,num,suma,sumb);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        dfs(1,0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 0ms ��ά����01����
//����ǡ��װ��,���������ܶ��װ��
//ʱ�临�Ӷ�O(n^2*w)=20*20*1000=400000
//�ռ临�Ӷ�O(n*w)=20*1000=20000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],dp[N][21000];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        for(int i=0;i<=w;i++)
        	dp[0][i]=0;//��Ʒ����ǡ��װ��,��Ʒ���������ܶ��װ��
        for(int i=1;i<=n;i++){
        	for(int j=k;j>=1;j--){
        		for(int t=b[i];t<=w;t++)
        			dp[j][t]=max(dp[j][t],dp[j-1][t-b[i]]+a[i]);
			}
		}
        printf("%d\n",dp[k][w]);
    }
    return 0;
}
*/

/*
//ac 0ms ��ά����01����
//���������������ܶ��װ��
//ʱ�临�Ӷ�O(n^2*w)=20*20*1000=400000
//�ռ临�Ӷ�O(n*w)=20*1000=20000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],dp[N][21000];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	//������Ʒ������Ϊһ����Ʒ�����Ծ�������1,ǡ��װ���;����ܶ��װ��������һ����
    	memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        for(int i=1;i<=n;i++){
        	for(int j=k;j>=1;j--){
        		for(int t=b[i];t<=w;t++)
        			dp[j][t]=max(dp[j][t],dp[j-1][t-b[i]]+a[i]);
			}
		}
        printf("%d\n",dp[k][w]);
    }
    return 0;
}
*/

/*
//ѭ��ģ��ö����Ʒ��Ϸ��� ժ�Բ���:https://www.cnblogs.com/neverchanje/p/3552463.html
//��Ϊstone������30�����Կ�������dfs������⣨ö�٣�

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=30;
const int maxc=1005;

int c,n,k,w,ans;
int a[maxn],b[maxn]; //a��ʾ��ֵ��b��ʾ����

//dfs���Ѿ�������stone��necklace�ϵ�stone��necklace��stone������������ǰ�ܼ�ֵ��
void dfs(int curt,int curn,int curw,int curv){

    if(curn>k || curt>n || curw>w )
        return;
    if(curv>ans)
        ans=curv;
    for(int i=curt+1;i<=n;i++)//curtǰ���һ���������
        dfs(i,curn+1,curw+b[i],curv+a[i]);
}

int main (){
    cin>>c;
    while(c--){

        cin>>n>>k;//nΪstone�ܸ�����kΪnecklace�������ɵĸ���
        for(int i=1;i<=n;i++)
            cin>>a[i]>>b[i];
        cin>>w;
        ans=0;
        dfs(0,0,0,0);
        cout<<ans<<endl;
    }
    return 0;
}
*/

/*
//ac 78ms ������ö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans;

int main(){
    int T,m,suma,sumb,id,cnt,flag,sta;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        m=(1<<n)-1;
        for(int i=0;i<=m;i++){
        	flag=cnt=id=suma=sumb=0;
        	sta=i;
        	while(sta){
        		if(sta & 1){
        			cnt++;
        			suma+=a[id];
        			sumb+=b[id];
        			if(cnt>k|| sumb>w){
        				flag=1;
        				break;
					}
				}
				sta>>=1;
				id++;
			}
			if(cnt!=k)
				flag=1;
			if(!flag)
				ans=max(ans,suma);
		}
        printf("%d\n",ans);
    }
    return 0;
}
*/
