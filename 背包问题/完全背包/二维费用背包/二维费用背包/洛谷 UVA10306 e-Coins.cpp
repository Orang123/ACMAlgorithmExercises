/*
����:ժ������
�ֱ��ʾ��n��Ӳ��,����һ����s,����ÿһ��Ӳ����������ֵ,
�ֱ����x[i],y[i],Ҫ�����ѡ��һЩӲ��,ʹ������s*s=X*X+Y*Y,
����X��ѡ����Ӳ�ҵ�����x��ֵ�ĺ�,Y������ѡ����Ӳ�ҵ�y��ֵ�ĺ�,
Ӳ�����������,����Ҫ�����,��������Ҫ��ʹ�õ����ٵ�Ӳ����.
����:https://www.luogu.com.cn/problem/UVA10306
˼·:ÿ��Ӳ�ҿ���ѡ�ö��,ÿ��Ӳ�Ҷ�����������,��ά������ȫ����.
dp[k][i][j]����ǰk��Ӳ�ҹ��ɵ�x����֮��Ϊi,y����֮��Ϊj��ѡ�õ�����Ӳ����.
ע��x��ֵ��y��ֵ֮�͵�������s.��Ϊ����s��,ƽ���϶���s��ƽ����,��û������.
*/
//ac 0ms
//dp[i][j]=min(dp[i][j],dp[i-x[k]][j-y[k]]+1);
//dp[k][i][j]����ǰk��Ӳ�ҹ��ɵ�x����֮��Ϊi,y����֮��Ϊj��ѡ�õ�����Ӳ����.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

int n,s,x[N],y[N],dp[M][M];

int main(){
    int T,ans;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dp[0][0]=0;
        for(int k=1;k<=n;k++){
            for(int i=x[k];i<=s;i++){
                for(int j=y[k];j<=s;j++){
                    if(dp[i-x[k]][j-y[k]]!=INF){
                        dp[i][j]=min(dp[i][j],dp[i-x[k]][j-y[k]]+1);
                        if(i*i+j*j == s*s)//ÿ����������Ľ� ����СӲ����
                            ans=min(ans,dp[i][j]);
                    }
                }
            }
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}

/*
//ac 0ms
//dp[i+x[k]][j+y[k]]=min(dp[i+x[k]][j+y[k]],dp[i][j]+1);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

int n,s,x[N],y[N],dp[M][M];

int main(){
    int T,ans;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dp[0][0]=0;
        for(int k=1;k<=n;k++){
            for(int i=0;i+x[k]<=s;i++){
                for(int j=0;j+y[k]<=s;j++){
                    if(dp[i][j]!=INF){
                        dp[i+x[k]][j+y[k]]=min(dp[i+x[k]][j+y[k]],dp[i][j]+1);
                        if((i+x[k])*(i+x[k])+(j+y[k])*(j+y[k]) == s*s)//ÿ����������Ľ� ����СӲ����
                            ans=min(ans,dp[i+x[k]][j+y[k]]);
                    }
                }
            }
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/

/*
//ac 200ms ����ö��dfs���� ���ݱȽ����� n<=40
//O(n^(s/min(x[i]))
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k ����x��ֵ֮��Ϊi,y��ֵ֮��Ϊjʱ����ʹ����k��Ӳ��
int n,s,x[N],y[N],dp[M][M],ans;

//O(n^(s/min(x[i]))
void dfs(int sumx,int sumy,int num){
    //��֦1:x��ֵ֮�� �� y��ֵ֮�Ͷ����ܳ���s,�����ʽsumx*sumx+sumy*sumy == s*s�Ͳ�����
    if(sumx>s || sumy>s)
        return;
    //��֦2:�����ǰ��ѡӲ��x��ֵ֮��Ϊsumx,y��ֵ֮��Ϊsumyʱ,
    //��ʹ�õ�Ӳ�������ܱ�֮ǰ��¼ͬ����ͬ�µ�Ӳ����С,��û��Ҫ��������ȥ
    if(num>=dp[sumx][sumy])//Ҳ�������Ϊ���仯����,ʵ������dp��״̬ת�Ʒ��̵�����������ž���
        return;
    dp[sumx][sumy]=num;
    if(sumx*sumx+sumy*sumy == s*s)
        ans=min(ans,num);
    for(int i=1;i<=n;i++)
        dfs(sumx+x[i],sumy+y[i],num+1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dfs(0,0,0);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/

/*
//ac 0ms bfs�������ö��״̬+��֦
//bfsҲ���������Ƶ�,��֦���������ͬ��,�����ǰ״̬���ܱ�֮ǰ�ĸ��žͲ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k ����x��ֵ֮��Ϊi,y��ֵ֮��Ϊjʱ����ʹ����k��Ӳ��
int n,s,x[N],y[N],dp[M][M],ans;
struct State{
    int sumx,sumy,num;
    //��������ʼ���Ǹ���:sumy(x),num(num),sumx(y)��ʼ������,State(int ..)����βο�����������
    //���豣֤ʵ�ʹ���ĸ��������sumx,sumy,num�໥ƥ��
    State(int y=0,int x=0,int num=0):sumy(x),num(num),sumx(y){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sumx*tp.sumx+tp.sumy*tp.sumy == s*s)
            ans=min(ans,tp.num);
        Q.pop();
        for(int i=1;i<=n;i++){
            if(tp.sumx+x[i]>s || tp.sumy+y[i]>s)
                continue;
            if(tp.num+1>=dp[tp.sumx+x[i]][tp.sumy+y[i]])//���������֦��TLE
                continue;
            Q.push(State(tp.sumx+x[i],tp.sumy+y[i],tp.num+1));
            dp[tp.sumx+x[i]][tp.sumy+y[i]]=tp.num+1;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        bfs();
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/
