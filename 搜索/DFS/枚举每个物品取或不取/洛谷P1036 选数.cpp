/*
����:��֪n������x1,x2,...,xn,�Լ�1������k(k<n).
��n����������ѡk��������ӣ��ɷֱ�õ�һϵ�еĺ͡�
���ڣ�Ҫ����������Ϊ�������ж����֡�
n<=20,k<n.
����:https://www.luogu.com.cn/problem/P1036
˼·:dfs
*/
//ac 13ms �����ж�����+dfs
#include<cstdio>
#include<cmath>
#define N 5000100
bool flag[N];
int a[N],n,k,cnt;

int check(int x){
    int low=sqrt(x);
    for(int i=2;i<=low;i++){
        if(x%i == 0)
            return 0;
    }
    return 1;
}

void dfs(int sum,int p,int j){
    if(j == k && check(sum)){
        cnt++;
        return;
    }
    if(p == n)
        return;
    dfs(sum+a[p],p+1,j+1);
    dfs(sum,p+1,j);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    dfs(0,0,0);
    printf("%d\n",cnt);
    return 0;
}

/*
//ac 301ms ɸ����+dfs
#include<cstdio>
#include<cmath>
#define N 5000100
bool flag[N];
int a[N],n,k,cnt;

void prim(){
    for(int i=0;i<N;i++)
        flag[i]=true;
    flag[0]=flag[1]=false;
    int h=sqrt(N);
    for(int i=2;i<=h;i++){
        if(flag[i])
            for(int j=i*i;j<N;j+=i) flag[j]=false;
    }
}

void dfs(int sum,int p,int j){
    if(j == k && flag[sum]){
        cnt++;
        return;
    }
    for(int i=p;i<n;i++)
        dfs(sum+a[i],i+1,j+1);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    prim();
    dfs(0,0,0);
    printf("%d\n",cnt);
    return 0;
}
*/
