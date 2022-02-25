/*
����:n*m������,�����ϵ�����ΪȨ��,Ҫ�������ߵ�һ������λ�õ�
���ұߵ�һ������λ��,����ʵ�������һ�к����һ�������ڵ�,��:
�ӵ�һ�������ߵ���0��,ʵ�����ߵ��˵�n��,�ӵ�n���ߵ���n+1��,ʵ��
���ߵ��˵�1��,���������߷�,�ֱ���б���ϡ���ǰ��б����,
�����С��Ȩ�ص�·��,���·���������к�(���ֵ���)����С·����Ȩֵ.
1<=n<=10,1<=m<=100.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1619
˼·:���仯����,��������yֵ������,���Ҳ����ظ�������,��������.
dp[x][y]��ʾ��(x,y)��������(?,m)(���һ������λ��)·������С��Ȩ�غ�,
ע��Ŀ��״̬����(n,m)����ֻҪy==m,�������һ�м���,���ҳ�ʼ״̬Ҳ����
(1,1),����Ҫö��(x,1),1<=x<=n,�����̵�·��Ȩֵ.
*/
//ac 0ms ���仯����
//dp[x][y]��ʾ��(x,y)��������(?,m)(���һ������λ��)·������С��Ȩ�غ�
#include<cstring>
#include<algorithm>
#define N 12
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dx[3]={-1,0,1},dp[N][M],mp[N][M],path[M],ans,p,l;

//������·��Ȩֵ
int dfs(int x,int y){
    if(dp[x][y]!=INF)
        return dp[x][y];
    if(y == m)
        return dp[x][y]=mp[x][y];
    int nx,ny;
    for(int i=0;i<3;i++){
        nx=x+dx[i];
        ny=y+1;//��������yֵ����1
        if(!nx)//�ӵ�һ���ߵ���n��
            nx=n;
        else if(nx == n+1)//�ӵ�n���ߵ���1��
            nx=1;
        dp[x][y]=min(dp[x][y],dfs(nx,ny)+mp[x][y]);
    }
    return dp[x][y];
}

//��¼���·�����к�
void findPath(int x,int y){
    path[++l]=x;//��ǰ·���к�Ϊx
    if(y == m)//�������һ�� m��ʱ ��ֹ����
        return;
    int nx;
    vector<int> a;
    for(int i=0;i<3;i++){
        nx=x+dx[i];
        if(!nx)
            nx=n;
        else if(nx == n+1)
            nx=1;
        a.push_back(nx);//���кż�¼���� ��С��������
    }
    sort(a.begin(),a.end());//��·����Ψһʱ,�����ֵ������
    for(int i=0;i<a.size();i++){
        if(dp[x][y] == dp[a[i]][y+1]+mp[x][y]){
            findPath(a[i],y+1);
            return;
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        ans=INF;
        l=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            if(ans>dfs(i,1)){
                ans=dp[i][1];//��¼����Ȩ��ans�ͳ������к�p
                p=i;
            }
        }
        findPath(p,1);//��¼��СȨ��·�����к�
        printf("%d",path[1]);
        for(int i=2;i<=l;i++)
            printf(" %d",path[i]);
        printf("\n%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms ����dp,�ɵ�һ�������һ��ת��
//dp[x][y]��ʾ��(?,1)��һ������λ�ó�������(x,y) ·������С��Ȩ�غ�
//ע��������� dp�Ľ׶�Ӧ�ö���Ϊ��,����������,��Ϊ���������ʼ״̬��
//�ڵ�һ�е�����λ�ó���,���Բ��ܽ���һ������Ϊ��ʼ״̬,������СȨֵ�����,
//��ʼȨֵ�����ǵ�һ������λ�ñ����Ȩֵ,ֻ���ɵ�һ��ת�ƶ���,���ҵ�������Ϊdp�Ľ׶�ʱ,��2��3..n�еĵ�һ�е�·��
//��û�г�ʼ״̬ Ҳ�޷�ת��
#include<cstring>
#include<algorithm>
#include<vector>
#define N 12
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dx[3]={-1,0,1},dp[N][M],mp[N][M],ans,p,pre[N][M];
vector<int> a;

void printPath(int x,int y){
    if(y == 1){
        printf("%d",x);
        return;
    }
    else{
        printPath(pre[x][y],y-1);//��һ��λ����(pre[x][y],y-1),�кű�Ȼ�Ǽ�1��
        printf(" %d",x);
    }
}

int main(){
    int nx;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        ans=INF;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++)
            dp[i][1]=mp[i][1];//��ʼ״̬ �ǵ�һ������λ�õ�Ȩֵ
        for(int j=1;j<m;j++){//������Ϊdp�Ľ׶�
            for(int i=1;i<=n;i++){//ö���� ��ת��
                a.clear();
                for(int k=0;k<3;k++){//��ת�Ƶ��а��մ�С�������� ����ת��
                    nx=i+dx[k];
                    if(!nx)
                        nx=n;
                    else if(nx == n+1)
                        nx=1;
                    a.push_back(nx);
                }
                sort(a.begin(),a.end());
                for(int k=0;k<a.size();k++){
                    if(dp[i][j]+mp[a[k]][j+1]<dp[a[k]][j+1]){
                        dp[a[k]][j+1]=dp[i][j]+mp[a[k]][j+1];
                        pre[a[k]][j+1]=i;//��¼����(a[k],j+1)λ�õ���һ״̬�� �к�,ǰһ״̬���к�һ����y-1 �����¼
                    }
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(ans>dp[i][m]){
                ans=dp[i][m];
                p=i;//��¼�����m�� ·��Ȩֵ��С���к�,�����Ŀ��λ���������ֱ����һ��Ϊֹ
            }
        }
        printPath(p,m);
        printf("\n%d\n",ans);
    }
    return 0;
}
*/
