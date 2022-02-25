/*
����:ժ������
һ��n*m�ĳ��У���С͵��͵���У�С͵͵����t���Ӻ󣬳��лᱻȫ��������
Ȼ�����q���Ų飬ÿ���Ų�ķ�Χ��һ�����Σ��������Ͻ����꣨a,b)����
�½�����(c,d)����ʽΪt a,b,c,d����ʾ�����Χ��ʱ��С͵���٣��������
С͵�����ڵ�λ�ú�ʱ��.
����һ��ʼû��������˼.
����:https://www.luogu.com.cn/problem/UVA707
˼·:ժ������
һ�������������ȷ��С͵���ڵ�λ�ú�ʱ�䣬С͵������У�һ������
Ҫ����һ��״̬������Ҫ����������(x,y,t),��Ϊ��֪��С͵���ģ�����Ҫ����
t=1��ʱ��С͵���п��ܵ�λ�ã�-1��ʾ��״̬��δȷ����0��ʾ���ڣ�1��ʾ�����ڣ�
��ô�ӿ�ʼ�Ѿ�����,���һ��״̬�ĺ��״̬��ȫ���ڲ���������˵���������ڸ�λ�ã�
��¼ÿ��ʱ����ܵ����꣬���һ��ʱ����ܵ�����ֻ��һ������ô��ȷ����С͵��λ��.
���仪����,dp[x][y][t]��ʾ��tʱ��x��yʱ��û�п��ܴ��ڵ���
*/
//ac 10ms ���仯����
//dp[x][y][t]��ʾ��tʱ��x��yʱ��û�п��ܴ��ڵ���
//���Ӷ�O(10^6)
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

//ע��С͵����ͣ����ԭ�ز���
int w,h,t,q,dp[N][N][N],dir[5][2]={{-1,0},{1,0},{0,-1},{0,1},{0,0}},cnt;
vector<pair<int,int>> ans[N];

int dfs(int x,int y,int tt){
    int &res=dp[x][y][tt];
    if(res!=-1)
        return res;
    if(tt>=t){//����tʱ�� ���оͻᱻ����
        cnt++;
        ans[tt].push_back(make_pair(x,y));
        return res=1;
    }
    res=0;
    int nx,ny;
    for(int i=0;i<5;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>w || ny<1 || ny>h)
            continue;
        if(dfs(nx,ny,tt+1))
            res=1;
    }
    if(res)
        ans[tt].push_back(make_pair(x,y));
    return res;
}

int main(){
    int cas=0,tt,x1,y1,x2,y2;
    while(scanf("%d%d%d",&w,&h,&t) && w+h+t){
        cas++;
        cnt=0;
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=t;i++)
            ans[i].clear();
        scanf("%d",&q);
        while(q--){
            scanf("%d%d%d%d%d",&tt,&x1,&y1,&x2,&y2);
            for(int i=x1;i<=x2;i++){
                for(int j=y1;j<=y2;j++)
                    dp[i][j][tt]=0;//���η�Χ��ttʱ�� ������С͵
            }
        }
        for(int i=1;i<=w;i++){//ö��С͵�ĳ�ʼ��,ʱ���Ǵ�1��ʼ��
            for(int j=1;j<=h;j++){
                if(dp[i][j][1])
                    dfs(i,j,1);
            }
        }
        printf("Robbery #%d:\n",cas);
        if(!cnt)
            printf("The robber has escaped.\n");
        else{
            int k=0;
            for(int i=1;i<=t;i++){
                if(ans[i].size() == 1){//iʱ��ֻ��һ��λ�� ����ȷ��
                    k=1;
                    printf("Time step %d: The robber has been at %d,%d.\n",i,ans[i][0].first,ans[i][0].second);
                }
            }
            if(!k)//�ж��λ�ò���ȷ��
                printf("Nothing known.\n");
        }
        printf("\n");
    }
    return 0;
}
