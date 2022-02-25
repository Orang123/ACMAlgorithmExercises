//ac 0ms 2����ȫ����
/*
����:6��ŷԪ����,��С����ֵ��Զ��1,�����ٵĻ��������1~100��ֵ�����е�Ǯ,
ֻ�ǻ��Ҳ���������ֵ���1~100��Ǯ,�����Ը�ֵ���,��:3=1+1+1=2+1=3,������3=5-2=4-1,
��Ҫ����1~100����ֵ��Ǯƽ��ʹ�ö��ٻ���,��Щ��ֵ�е�Ǯ���ʹ�õĻ������Ƕ���.
����:http://poj.org/problem?id=1252
˼·:ÿ�ֻ��ҿ�������ʹ��,��Ϊ�����ֵ��Ǯ����������ֵ���,���Ը�ֵ���,���
������ȫ����,1����ֵ,1�θ�ֵ,ֻ�Ǹ�ֵ��������Ҫ����,�������ܱ�֤ÿ�ָ�ֵ�����ܹ�
����ʹ��.
*/
//ע����ȫ�����޷�����ƽ���������ƽ��ȥ��,��Ϊ�����͸�������һ���ǵ�ǰ��Ʒֻ��ȡһ��,��������ȡ,
//ֻ��01�������� ���������� �ö�ά�����¼��һ״̬,�պ���ÿ����Ʒ2�ַ��� �պ�ֻȡһ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define M 150
#define INF 0x3f3f3f3f
using namespace std;

int w[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++)
            scanf("%d",&w[i]);
        dp[0]=0;
        //��ֵ
        for(int i=1;i<=6;i++){
            for(int j=w[i];j<=M-1;j++)
                dp[j]=min(dp[j],dp[j-w[i]]+1);
        }
        //��ֵ
        for(int i=1;i<=6;i++){
            /*
            //��һ��ת�� ac 0ms
            for(int j=M-1;j>=w[i]+1;j--)
                dp[j-w[i]]=min(dp[j-w[i]],dp[j]+1);
            */
            //��Ϊÿ�ָ�ֵ���ҵ���һ״̬��dp[j+w[i]],����j���뽵��,
            //����ʹ�õ�i�ָ�ֵ��������ʹ��
            for(int j=M-1-w[i];j>=1;j--)//�Ͻ���100-w[i],��Ϊj+w[i]��һ״̬�����100,�Ͻ綨��Ϊ100,j+w[i]�ʹ��ڱ���������
                dp[j]=min(dp[j],dp[j+w[i]]+1);
        }
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];//��Ϊ��һ�ֻ�����ֵ��Զ��1,����dp[i]��Զ�ǺϷ���
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}

/*
//ac 47ms �������+��֦ ����6�ֻ����ܹ�12�ֻ�������
//M���ó�2100 �ͻ�TLE,������������̫����.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define M 210
#define INF 0x3f3f3f3f
using namespace std;
//dp[i]=j����12�ֻ������������ֵΪiʱ��ʹ�õ����ٻ�����
int w[N],dp[M];

void dfs(int num,int sum){
    if(sum>M || sum<0)
        return;
    if(num>=dp[sum])
        return;
    dp[sum]=num;
    for(int i=1;i<=12;i++)
        dfs(num+1,sum+w[i]);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++){
            scanf("%d",&w[i]);
            w[i+6]=-w[i];
        }
        dfs(0,0);
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}
*/

/*
//ac 0ms bfs�������ö��״̬+��֦ ����6�ֻ����ܹ�12�ֻ�������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 13
#define M 210
#define INF 0x3f3f3f3f
using namespace std;
//dp[i]=j����12�ֻ������������ֵΪiʱ��ʹ�õ����ٻ�����
int w[N],dp[M];

struct State{
    int num,sum;
    State(int num=0,int sum=0):num(num),sum(sum){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0));
    while(!Q.empty()){
        State tp=Q.front();
        Q.pop();
        for(int i=1;i<=12;i++){
            if(tp.sum+w[i]>M-1 || tp.sum+w[i]<=0) continue;
            if(tp.num+1>=dp[tp.sum+w[i]]) continue;
            Q.push(State(tp.num+1,tp.sum+w[i]));
            dp[tp.sum+w[i]]=tp.num+1;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=6;i++){
            scanf("%d",&w[i]);
            w[i+6]=-w[i];
        }
        bfs();
        int sum=0,ans=0;
        for(int i=1;i<=100;i++){
            sum+=dp[i];
            ans=max(ans,dp[i]);
        }
        printf("%.2f %d\n",1.0*sum/100,ans);
    }
    return 0;
}
*/
