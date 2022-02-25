/*
����:ժ������
��������[n,m]��d��һ������ʹ��������С�ڵ���d�Ҵ���1���ȵ�����֮��Ϊ������
n,m<=1000,2<=d<=10.
����:http://poj.org/problem?id=2034
˼·:dfsö��ȫ����,��ö�ٵĹ�����,��ö�ٵ������Ѿ���2λʱ,
ûö��һ���� ���ж�2..d��Χ�ڵ������ǲ��Ƕ��Ǻ���,������ǺϷ����֦.
�жϺ�����Ҫɸ����Ԥ����,����ֱ�������жϻ�TLE.
*/
//ac 891ms ɸ����Ԥ����+dfsö��ȫ����+�жϺ�����֦
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1100
#define M 10000
using namespace std;

int n,m,d,len,a[N],b[N],vis[N],prim[M],sum[N];

void init(){
    int low=sqrt(M);
    for(int i=2;i<low;i++){
        if(prim[i]) continue;
        for(int j=i*i;j<M;j+=i)
            prim[j]=1;
    }
    /*
    for(int i=2;i<M/2;i++){
        if(prim[i]) continue;
        for(int j=i*2;j<M;j+=i)
            prim[j]=1;
    }
    */
}

int check(int k){
    for(int i=2;i<=min(k,d);i++){
        if(!prim[sum[k]-sum[k-i]])
            return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == len+1)
        return 1;
    for(int i=1;i<=len;i++){
        if(vis[i])
            continue;
        b[k]=a[i];
        sum[k]=sum[k-1]+b[k];
        if(k>=2 && !check(k))
            continue;
        vis[i]=1;
        if(dfs(k+1))
            return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    init();
    while(scanf("%d%d%d",&n,&m,&d) && n+m+d){
        len=0;
        memset(vis,0,sizeof(vis));
        for(int i=n;i<=m;i++)
            a[++len]=i;
        if(dfs(1)){
            for(int i=1;i<=len;i++){
                printf("%d",b[i]);
                if(i != len)
                    printf(",");
            }
            printf("\n");
        }
        else
            printf("No anti-prime sequence exists.\n");
    }
    return 0;
}

/*
//TLE dfs+�����жϺ���
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,d,len,a[N],b[N],vis[N];

int check(int k,int x){
    int low,flag;
    for(int i=k-1;i>k-d && i>=1;i--){
        x+=b[i];
        low=sqrt(x);
        flag=0;
        for(int i=2;i<=low;i++){
            if(x%i == 0){
                flag=1;
                break;
            }
        }
        if(!flag) return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == len+1)
        return 1;
    for(int i=1;i<=len;i++){
        if(vis[i])
            continue;
        if(k>=2 && !check(k,a[i]))
            continue;
        vis[i]=1;
        b[k]=a[i];
        if(dfs(k+1))
            return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    while(scanf("%d%d%d",&n,&m,&d) && n+m+d){
        len=0;
        memset(vis,0,sizeof(vis));
        for(int i=n;i<=m;i++)
            a[++len]=i;
        if(dfs(1)){
            for(int i=1;i<=len;i++){
                printf("%d",b[i]);
                if(i != len)
                    printf(",");
            }
            printf("\n");
        }
        else
            printf("No anti-prime sequence exists.\n");
    }
    return 0;
}
*/
