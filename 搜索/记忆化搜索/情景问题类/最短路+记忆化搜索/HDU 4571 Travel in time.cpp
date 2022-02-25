/*
����:ժ������
n�����У�m��·����ʱ��t����ʼ����st���յ����ed
�����������������е����ʱ��c[i]��������������������̶�s[i]��
Ȼ����m��·����Ϣ��Ҫ��һ�����˳��ʹ���ܵ�����̶����
Ȼ�󾭹�һ�����п���ѡ��ȥ�������ǰ������е������һ��Ҫ
��ǰһ��������е�����ȸߣ���������Ҫ�ص�����e��
1<n<100,0<M<1000,0<t<=300,0<=c[i]<=t,0<=s[i]<=100.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4571
˼·:����һ�����п��Ծ����������,������Ͳ���������̶�,��ô
����̶���Ȼ��ǰһ������ĳ��е������,����floydԤ��������г���
��ͨ�л��ѵ�ʱ��,ʵ��Ҫ����������,����Ҫ�����ܶ���������,��
������еĽ���״̬��
1.������Ȳ��ܼ�������
2.��ǰ����ĳ�����ʣ��ʱ��k���޷��ص��յ�ed
���ҵ��ﵱǰ��Ӱ����������������� ��һ�����е�����Ⱥ�ʣ���ʱ��.
��˼��仯����,dp[i][j][k]��ʾ����i������������Ϊj,ʣ��ʱ��Ϊkʱ
����������в����ܻص�ed���ܻ�õ���������.
*/
//ac 780ms floyd+���仯����
//dp[i][j][k]��ʾ����i������������Ϊj,ʣ��ʱ��Ϊkʱ����������в����ܻص�ed���ܻ�õ���������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 310
#define INF -0x3f3f3f3f
using namespace std;

int n,m,t,st,ed,c[N],s[N],dp[N][N][M],dis[N][N];

void floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    }
}

int dfs(int i,int j,int k){
    int &ans=dp[i][j][k];
    if(ans!=-1)
        return ans;
    if(dis[i][ed]>k)//ʣ�µ�ʱ��t�޷���i��ص�ed ���ز��Ϸ�״̬
        return ans=INF;
    ans=0;
    for(int v=0;v<n;v++){//ö��Ҫ�����v������ ��ȡ�������
        if(s[v]<=j)//����Ȳ�����
            continue;
        int res=dfs(v,s[v],k-dis[i][v]-c[v]);//dis[i][v]�����м仹�����˱�ĵ㵫�� ����� ������ȡ�������
        if(res!=INF)
            ans=max(ans,res+s[v]);
    }
    //��ans=0ʱ �����޷��ټ��������ȥ����״̬��,����������Ȳ�������,������Ҫ����ĳ���ʣ��ʱ�䶼�޷��ص�ed��
    return ans;
}

int main(){
    int w,u,v,d;
    scanf("%d",&w);
    for(int cas=1;cas<=w;cas++){
        scanf("%d%d%d%d%d",&n,&m,&t,&st,&ed);
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<n;i++)
            scanf("%d",&c[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&s[i]);
        memset(dis,0x3f,sizeof(dis));
        for(int i=0;i<n;i++)
            dis[i][i]=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&d);
            dis[u][v]=dis[v][u]=min(dis[u][v],d);
        }
        floyd();
        printf("Case #%d:\n",cas);
        if(dfs(st,0,t)!=INF)
            printf("%d\n",dp[st][0][t]);
        else
            printf("0\n");
    }
    return 0;
}
