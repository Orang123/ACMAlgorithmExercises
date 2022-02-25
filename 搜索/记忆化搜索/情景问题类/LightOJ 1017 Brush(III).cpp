/*
����:ժ������
n����,����ˢ�ӵĿ�w������ɨ����k,�ʱ�ɨ�����ĵ��Ƕ��ٸ�.
1<=n<=100,1<=w<=10000,1<=k<=100.
˵��:ˮƽ����ɨ���ǿ�������ɨ��,����yֵ��ͬ�ĵ� һ������һ����ɨ��.
����:http://www.lightoj.com/volume_showproblem.php?problem=1017
˼·:ʵ��ֻ�͵��yֵ�й�,���԰���y���꽫������,�����Ϳ����������±����
��ͬyֵ�����е��������.Ȼ����Ҫö����ˢ�ӿ�Ϊwʱ����ɨ����һ��Χ��yֵ
�ĵ�.��Ȼ�����ֿ���,��w��Χ��yֵɨ���ǲ�ɨ,��Ȼ���������ʱ�����ص�������.
��˼��仯����,dp[i][j]����ˢ���±߽�Ϊiʣ��j�κ�ɨ����ʱ��ɨ���ĵ��������.
����Ϊɨ��������

����:LightOJ 1016 Brush(II)���Ǵ���if(y[t]-y[i]<=w)��̰����ⲿ��
*/
//ac 5ms ���仯����
//dp[i][j]����ˢ���±߽�Ϊiʣ��j�κ�ɨ����ʱ��ɨ���ĵ��������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int n,w,k,y[N],dp[N][N];

int dfs(int i,int j){
    int &ans=dp[i][j];
    if(ans)
        return ans;
    if(i == n+1 || j<=0)//����������n���㶼������ϻ� ��ɨ�����պ�����
        return ans=0;
    int t,cnt,res1,res2;
    for(t=i;t<=n;t++){
        if(y[t]-y[i]<=w)
            cnt=t-i+1;
        else
            break;
    }
    //ɨ����ǰw��Χ�ĵ� ɨ������j-1
    res1=cnt+dfs(t,j-1);//t�ǵ�һ��������y[t]-t[i]<=w�ĵ�,��δ�����¼��cnt��
    //��ɨ����ǰw��Χ�ڵĵ� ���´�i+1��ʼ�ж� ɨ����������j
    res2=dfs(i+1,j);
    ans=max(res1,res2);//��ȡ���ߵ����ֵ
    return ans;
}

int main(){
    int T,x;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(dp,0,sizeof(dp));
        scanf("%d%d%d",&n,&w,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x,&y[i]);
        sort(y+1,y+1+n);
        printf("Case %d: %d\n",cas,dfs(1,k));
    }
    return 0;
}
