/*
����:ժ������
����m��n��k����m�ֽ��n�ݣ�Ȼ������ÿ�ݵĸ����Ŷ��ֵ���
���һ���ʱҪ��a[i-1]<=a[i]������a[1]+a[2]+...+a[n]=m��
Ȼ������ֵ�������kλ�Ļ��ַ�����
1<=m<=220,1<=n<=10,k>=1
����:https://www.luogu.com.cn/problem/UVA10581
˼·:���仯����,��ΪҪ�����ֵ����kλ,���Դ�С����ö��
ÿһλ�ϵĿ���ȡֵ,����״̬�ǵ��ֵ�n��ʱ,m�Ѿ�������,ͳ�Ʒ�����.
dp[i][j][k]��ʾ��iλΪjʱ,ʣ��δ�ֵ���ֵΪkʱ�ķ�����.
*/
//ac 10ms ���仯����
//dp[i][j][k]��ʾ��iλΪjʱ,ʣ��δ�ֵ���ֵΪkʱ�ķ�����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 230
using namespace std;

int m,n,k,dp[N][M][M];

int dfs(int i,int j,int s){
    int &res=dp[i][j][s];
    if(res!=-1)
        return res;
    if(i == n){
        if(!s)//n�����������,�պ�ʹ��a[1]+a[2]+...+a[n]=m,�Ǻ���ķ���. ����1
            return res=1;
        else
            return res=0;
    }
    res=0;
    //����������ʣ�µ�(n-i)λ������t�Ѿ���s����,�ͼ�֦ ���Ϸ�
    for(int t=j;(n-i)*t<=s;t++)//ö�ٵ�i+1λ��t,ʣ��δ�������s-t
        res+=dfs(i+1,t,s-t);
    return res;
}

void print(){
    int t=1,s=m;
    for(int i=1;i<=n;i++){//�жϵ�iλ����ֵj
        for(int j=t;;j++){
            ll cnt=dp[i][j][s-j];
            if(k>cnt)//��ǰk��cnt��,˵��k�ڸ�����Ĵ���,k��ȥcnt,ͬʱj++���������ж�
                k-=cnt;
            else{//��ǰ����k ��cntС,˵����iλ����j
                printf("%d\n",j);
                s-=j;//ʣ��δ�������ֵΪs-j
                t=j;//��һλ�ĳ�ʼֵ�ǵ�ǰ��j
                break;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        scanf("%d%d%d",&m,&n,&k);
        for(int i=1;i*n<=m;i++)//ö�ٵ�1λ��ֵi,������n��λ����iǡ��n*i=m,�����С���ֵ���n*i>m,��ͳ���������ֵ�����
            dfs(1,i,m-i);
        print();
    }
    return 0;
}
