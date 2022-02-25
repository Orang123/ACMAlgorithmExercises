/*
����:ժ������
��������ʮ����������n��m���������[n ,m]���ж��ٸ�Round number
��ν��Round Number���ǰ�һ��ʮ������ת��Ϊһ���޷��Ŷ���������
���ö���������0�ĸ������ڵ���1�ĸ�������������һ��Round Number
n<=2*10^9.
����:http://poj.org/problem?id=3252
˼·:��λdp.ֻ����λ�Ƕ�����λ01.״̬��ʶ,
Ҫ��ע������λ��0��1�ĸ���,ע��ǰ��0������0�ĸ���.
00110,��������0��1��,���������ʵ��Ӧ����110.
��Ȼ����dp[k][zero][one]��˵ ����ǰ�����Ӱ�����
���仯����,�������dfsֻ�������ȿ�ʼ����� ����ѡ��i=0,�ѵ�ȫ0�����.
������ǰ��0��û��ǰ��0,��zero oneһ���ǲ�ͬ��,��ǰ��0 oneһ����Ϊ0,
����ǰ��0 one��zeroһ����Ϊ0,������������ص�,���dp������Բ���¼ǰ��0.
��㲻ͬ�����P2602 [ZJOI2010]���ּ���.
*/
//ac 16ms ���仯����
//dp[k][zero][one]��ʾn�Ķ�������λ��len��k-1λ0����ĿΪzero,1����ĿΪone(�������������λ�±�)
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn�Ķ����ƴ�����0�ĸ�����С��1�ĸ����Ķ����ƴ��ĸ���
//�ռ临�Ӷ�O(2*32*32)=1800
//ʱ�临�Ӷ�O(2*2*32*32)=3600
#include<cstdio>
#include<cstring>
#define N 32

int n,m,len,dp[N][N][N],a[N];

int dfs(int k,int flag,int zero,int one,int limit){
    if(!k)
        return zero>=one;
    if(!limit && dp[k][zero][one]!=-1)
        return dp[k][zero][one];
    int last=limit?a[k]:1;
    int ans=0;
    for(int i=0;i<=last;i++){
        if(flag){//û��ǰ��0,ǰ���Ѿ���1��
            if(!i)//ȡ0 zero+1
                ans+=dfs(k-1,flag,zero+1,one,limit && i == last);
            else//ȡ1 one+1
                ans+=dfs(k-1,flag,zero,one+1,limit && i == last);
        }
        else{//ǰ��û��һ��1,����ǰ��0,��Щ�㲢������0�ĸ�����
            if(i)//��ǰλȡ1 �Ͳ�����ǰ��0��,flag����Ϊ1,one+1
                ans+=dfs(k-1,1,zero,one+1,limit && i == last);
            else//��ǰλȡ0 ��Ȼ��ǰ��0 ������0�ĸ���,flag,zero,one����0
                ans+=dfs(k-1,0,0,0,limit && i == last);
        }
    }
    if(!limit)
        dp[k][zero][one]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%2;
        val/=2;
    }
    return dfs(len,0,0,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&n,&m);
    printf("%d",solve(m)-solve(n-1));
    return 0;
}

/*
//ac 0ms ���仯����
//dp[N][N][N][2] ��ǰ��0Ҳ���� dp����
#include<cstdio>
#include<cstring>
#define N 32

int n,m,len,dp[N][N][N][2],a[N];

int dfs(int k,int flag,int zero,int one,int limit){
    if(!k)
        return zero>=one;
    if(!limit && dp[k][zero][one][flag]!=-1)
        return dp[k][zero][one][flag];
    int last=limit?a[k]:1;
    int ans=0;
    for(int i=0;i<=last;i++){
        if(flag){//û��ǰ��0,ǰ���Ѿ���1��
            if(!i)//ȡ0 zero+1
                ans+=dfs(k-1,flag,zero+1,one,limit && i == last);
            else//ȡ1 one+1
                ans+=dfs(k-1,flag,zero,one+1,limit && i == last);
        }
        else{//ǰ��û��һ��1,����ǰ��0,��Щ�㲢������0�ĸ�����
            if(i)//��ǰλȡ1 �Ͳ�����ǰ��0��,flag����Ϊ1,one+1
                ans+=dfs(k-1,1,zero,one+1,limit && i == last);
            else//��ǰλȡ0 ��Ȼ��ǰ��0 ������0�ĸ���,flag,zero,one����0
                ans+=dfs(k-1,0,0,0,limit && i == last);
        }
    }
    if(!limit)
        dp[k][zero][one][flag]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%2;
        val/=2;
    }
    return dfs(len,0,0,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&n,&m);
    printf("%d",solve(m)-solve(n-1));
    return 0;
}
*/
