/*
����:����n*n������,ÿ������������һЩ����,һֻ�����(1,1)�����,
����ˮƽ��ֱ��һ�����������k��,����ÿ���ߵ���λ������Ӧ�ñȵ�
ǰλ�����Ҹ������,����ֻ�����ߵ���������Ϊֹ����ܳԵ����������Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1078
˼·:dp[x][y]��ʾ��(x,y)������ߵ��������ߵ�λ�����ܻ�ȡ����������
���仯���� �ݹ�ش�Ŀ��״̬(�����ߵ�״̬)���ʼ״̬(1,1)ת��,�Ѿ�����
�����ص�������ֱ�ӷ���dp[x][y]����������.
֮���Դ���ֹ״̬����ʽ�����ʼ״̬��������Ϊ��ֹ״̬�Ѿ�ֹͣ��,�����������
��ȥ,������ӳ�ʼ״̬���㵽�ﵱǰ���ߵ�״̬�����Ž�,�����ǻ����������ȥ��,
���һ��޷���֤��ǰ���������ľ�һ�������Ž�,������֦�����������ᴥ��.
������仯����dp�ļ�֦�Ǵ���ֹ״̬�������ʼ״̬��������֦��.
*/
//ac 62ms ���仯���� �ݹ�ش�Ŀ��״̬(�����ߵ�״̬)���ʼ״̬(1,1)ת��
//dp[x][y]��ʾ��(x,y)������ߵ��������ߵ�λ�����ܻ�ȡ����������
//���仯���������Ѿ���������·��û��Ҫ�ظ�����,��֦��������·����������,���õ�����·��Ӧ����
//ʱ�临�Ӷ�O(n*n)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int dfs(int x,int y){
    if(dp[x][y])//��Ϊ�Ǽ��仯����,���dp[x][y]��Ϊ0�������㿪ʼ��ö�ٵ�·���Ǳ���������,�����ص�������,��Ҫȥ�ظ�����,�Ǿ�ֱ����֮ǰ��������ֵ�ͺ�
        return dp[x][y];
    int nx,ny,res=0;
    for(int i=1;i<=k;i++){//ö��ÿ�����ߵĲ���
        for(int j=0;j<4;j++){//ö�ٷ���
            nx=x+dir[j][0]*i;
            ny=y+dir[j][1]*i;
            if(nx<1 || nx>n || ny<1 || ny>n)
                continue;
            if(mp[nx][ny]<=mp[x][y])
                continue;
            res=max(res,dfs(nx,ny));//����dp�е�״̬ת�Ʒ��̣�ȡmax�ľ��߷���
        }
    }
    return dp[x][y]=mp[x][y]+res;
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        printf("%d\n",dfs(1,1));
    }
    return 0;
}

/*
//dfs�������� �౳��dp�׶��Լ�֦ TLE 1000ms
//dp[x][y]��ʾ��(1,1)��������(x,y)���ܻ�õ��������
//��֦1 �����ǰ��(1,1)����������Ҳ���֮ǰ��õĶ� �Ͳ�����������ȥ
//���������ʱ����Ҫԭ���������֦�ĸ�Ч���޷���֤,�п���������,
//����������·����ȡ�����������Ƚ�С,���廹�������˺ܶ��ظ���·��.
//�����������ļ��仯���� �Ǵ���ֹ״̬ת�Ƶ�,���ܱ�֤��ǰ�׶��Ѿ���¼��dp[x][y]һ�������Ž�,
//�����Ҫ����(x,y),��dp[x][y]�Ѿ�������,ֱ�ӷ�������������,��һ��ȷ�еļ�֦.

//Ϊɶһ��Ҫ �ӽ���״̬���ʼ״̬�����Ž���Ҫԭ����:
//����ӳ�ʼ״̬ �����ߵ�״̬�����Ž�,����� ���ǻ����¼���������,�������������Ļ���һ��������,
//��֦�ĸ�Ч�Ծ��޷���֤,����ֹ״̬ȥ����,��Ϊ�Ѿ�ͣ����,���������¼���������,�Ͳ����ظ�����,
//�������Ǳ�֤�˶����ӽ׶ε�״̬�Ѿ��������ŵ���,���ԲŸ���Ч��.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;

void dfs(int x,int y,int sum){
    if(sum<=dp[x][y])//��֦1 �����ǰ��(1,1)����������Ҳ���֮ǰ��õĶ� �Ͳ�����������ȥ
        return;
    dp[x][y]=sum;
    ans=max(ans,sum);
    int nx,ny;
    for(int i=1;i<=k;i++){
        for(int j=0;j<4;j++){
            nx=x+dir[j][0]*i;
            ny=y+dir[j][1]*i;
            if(nx<1 || nx>n || ny<1 || ny>n)
                continue;
            if(mp[nx][ny]<=mp[x][y])
                continue;
            dfs(nx,ny,sum+mp[nx][ny]);
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        dfs(1,1,mp[1][1]);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//bfs�������� �౳��dp�׶��Լ�֦ MLE 390ms
//dp[x][y]��ʾ��(1,1)��������(x,y)���ܻ�õ��������
//MLE TLE��ԭ���dfs��һ����.
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;
struct State{
    int x,y,sum;
    State(int x=0,int y=0,int sum=0):x(x),y(y),sum(sum){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(1,1,mp[1][1]));
    dp[1][1]=mp[1][1];
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        ans=max(ans,tp.sum);
        Q.pop();
        for(int i=1;i<=k;i++){
            for(int j=0;j<4;j++){
                nx=tp.x+dir[j][0]*i;
                ny=tp.y+dir[j][1]*i;
                if(nx<1 || nx>n || ny<1 || ny>n)
                    continue;
                if(mp[nx][ny]<=mp[tp.x][tp.y])
                    continue;
                //��֦1 �����ǰ��(1,1)����������Ҳ���֮ǰ��õĶ� �Ͳ�����������ȥ
                if(tp.sum+mp[nx][ny]<=dp[nx][ny])
                    continue;
                Q.push(State(nx,ny,tp.sum+mp[nx][ny]));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/
