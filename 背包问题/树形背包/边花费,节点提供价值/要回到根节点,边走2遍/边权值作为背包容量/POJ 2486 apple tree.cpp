/*
����:һ��n���ڵ��ƻ����,ÿ���ڵ��϶���val[i]��ƻ��,���㾭�������ʱ���ܻ��
����ڵ������ƻ��,�ظ�����ͬ�ڵ�,����ڵ��ƻ��Ҳֻ��ȡһ��,������k��������
�ܵõ������ƻ����.�ӽڵ�1����.
n<=100,k<=200,val[i]<=1000.
����:http://poj.org/problem?id=2486
˼·:Ҫ��������ĵ�,�ȱ����ķ�֧��Ȼ�᷵��ȥ���ظ���һ��,ֻ�����һ����ֻ֧����һ��.
������Ҫö��ÿ��������Ƿ�ص�������벻�ᵽ���������.��������Ϊ��������k.
dp[i][j][0/1]��ʾ��iΪ���ڵ���������ڵ�i�����ڳ���j����������ܱ��������ڵ�Ȩֵ��.
dp[i][j][0]��ʾ������i��,dp[i][j][1]��ʾ����i��.
��Ϊ�����ܱ���С��k������,����Ҫ�����ܶ��װ������,��˳�ʼ״̬dp[i][0..k]=val[i].

dp[i][j][0/1]���ܱ�ʾ����iΪ���ڵ������i����������ڵ��Ȩֵ��ǡ��Ϊjʱ�����߹��ľ���.
Ϊÿ�����Ȩֵ���ɴ�1000,����Ȩֵ����Ϊ����������ը,ʱ�䡢�ռ临�ӶȻ�ը.
ʱ�临�Ӷ�O(n*M^2)=100*10^5*10^5=10^12
�ռ临�Ӷ�O(n*m)=100*10^5=10^7
*/
//ac 63ms
//ʱ�临�Ӷ�O(n*k^2)=100*200^2=4*10^6
//�ռ临�Ӷ�O(nk)=100*200=20000
//dp[i][j][0/1]��ʾ��iΪ���ڵ���������ڵ�i�����ڳ���j����������ܱ��������ڵ�Ȩֵ��.
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-1][1]+dp[v][t][0]);
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-2][0]+dp[v][t][1]);
//dp[u][j][1]=max(dp[u][j][1],dp[u][j-t-2][1]+dp[v][t][1]);
//�����ܶ��װ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=1;j--){
            for(int t=0;t<=j-1;t++){
                //dp�ľ�����
                //1.���ܱ����ڵ�����ͬ�������,����ѡ��·�������С�ķ�֧ȥ����
                //2.�Լ��������һ����ֻ֧��һ��·������,�������߾���϶�.�����֧ʵ�ʶ���������.
                //3.��ѡ�ڵ��Ȩֵ�����ܴ�
                //������k�����²��ܽ������ĵ��Ȩֵ�;����ܴ�
                //v����������v��,u�������ֵ�����Ҫ����u��,����u->v 1��
                dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-1][1]+dp[v][t][0]);
                if(j-t-2>=0)
                    //v��������v��,u�������ֵ�����Ҫ������u��,���ߵ�v����ÿ������������,���ߵ�u�������ֵ�����,����u->v v->u 2��
                    dp[u][j][0]=max(dp[u][j][0],dp[u][j-t-2][0]+dp[v][t][1]);
                if(j-t-2>=0)
                    //v��������v��,u�������ֵ�����Ҫ����u��,�����������ĸ�����,�������ĸ�ÿ���߶���������,����u->v v->u 2��
                    dp[u][j][1]=max(dp[u][j][1],dp[u][j-t-2][1]+dp[v][t][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        //ע�� ����ǻ�Ӱ��ʵ��k�������ڵĽ���� ��ĿҪ���1�ڵ����
        dfs(1,-1);
        //k�������ڲ����ػ�õ�Ȩֵ�Ϳ϶��ϴ� ֻ�����dp[1][k][0] �����ظ��ڵ�1�ļ��� ���迼�Ƿ��ظ��ڵ�1��dp[1][k][1]
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}

/*
//ac 63ms ��һ��ת�Ʒ�ʽ
//dp[i][j][0/1]��ʾ��iΪ���ڵ���������ڵ�i�����ڳ���j����������ܱ��������ڵ�Ȩֵ��.
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][1]+dp[v][t-1][0]);
//dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][0]+dp[v][t-2][1]);
//dp[u][j][1]=max(dp[u][j][1],dp[u][j-t][1]+dp[v][t-2][1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=1;j--){
            for(int t=1;t<=j;t++){
                dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][1]+dp[v][t-1][0]);
                if(t-2>=0)
                    dp[u][j][0]=max(dp[u][j][0],dp[u][j-t][0]+dp[v][t-2][1]);
                if(t-2>=0)
                    dp[u][j][1]=max(dp[u][j][1],dp[u][j-t][1]+dp[v][t-2][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}
*/

/*
//ac 79ms ��һ��ת�Ʒ�ʽ
//dp[i][j][0/1]��ʾ��iΪ���ڵ���������ڵ�i�����ڳ���j����������ܱ��������ڵ�Ȩֵ��.
//dp[u][j+t+1][0]=max(dp[u][j+t+1][0],dp[u][j][1]+dp[v][t][0]);
//dp[u][j+t+2][0]=max(dp[u][j+t+2][0],dp[u][j][0]+dp[v][t][1]);
//dp[u][j+t+2][1]=max(dp[u][j+t+2][1],dp[u][j][1]+dp[v][t][1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 210
using namespace std;

int cnt,head[N],n,k,val[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=0;i<=k;i++)
        dp[u][i][0]=dp[u][i][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=0;j--){
            for(int t=0;t+j+1<=k;t++){
                dp[u][j+t+1][0]=max(dp[u][j+t+1][0],dp[u][j][1]+dp[v][t][0]);
                if(t+j+2<=k)
                    dp[u][j+t+2][0]=max(dp[u][j+t+2][0],dp[u][j][0]+dp[v][t][1]);
                if(t+j+2<=k)
                    dp[u][j+t+2][1]=max(dp[u][j+t+2][1],dp[u][j][1]+dp[v][t][1]);
            }
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",dp[1][k][0]);
    }
    return 0;
}
*/

/*
//MLE TLE ��Ϊÿ�����Ȩֵ���ɴ�1000
//����Ȩֵ����Ϊ����������ը
//ʱ�临�Ӷ�O(n*M^2)=100*10^5*10^5=10^12
//�ռ临�Ӷ�O(n*m)=100*10^5=10^7
//siz[i]��ʾ��iΪ���ڵ���������нڵ��Ȩֵ��(����i��)
//dp[i][j][0/1]��ʾ����iΪ���ڵ������i����������Ľڵ��Ȩֵ��ǡ��Ϊjʱ(���ص�i���ص�i��)�����߹��ľ���.
//dp[i][j][0]��ʾ���ص�i��,dp[i][j][1]��ʾ�ص�i��.
//ǡ��װ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

int cnt,head[N],n,k,val[N],siz[N],dp[N][M][2];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
	dp[u][val[u]][0]=dp[u][val[u]][1]=0;
	siz[u]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //ʵ��������������ϵ,����v��Ȼ���Ѿ��ߵ�u����,�Ǳ��뱣֤������u���Ȩֵ,������v���Ȩֵ
		//���j����val[u],t����val[v]
        for(int j=siz[u];j>=val[u];j--){
            for(int t=val[v];t<=siz[v];t++){
                dp[u][j+t][0]=min(dp[u][j+t][0],dp[u][j][1]+dp[v][t][0]+1);
                dp[u][j+t][0]=min(dp[u][j+t][0],dp[u][j][0]+dp[v][t][1]+2);
                dp[u][j+t][1]=min(dp[u][j+t][1],dp[u][j][1]+dp[v][t][1]+2);
            }
        }
        siz[u]+=siz[v];
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        memset(dp,0x3f,sizeof(dp));
        dfs(1,-1);
        //1�ڵ�Ȩֵ�� ���� ֻҪ����������k���Ϸ� ������Ȩֵ��
        for(int i=siz[1];i>=0;i--){
            //�����صĲ����϶���С ֻ���ж�dp[1][i][0] �����ظ��ڵ�1��
        	if(dp[1][i][0]<=k){
        		printf("%d\n",i);
        		break;
			}
		}
    }
    return 0;
}
*/
