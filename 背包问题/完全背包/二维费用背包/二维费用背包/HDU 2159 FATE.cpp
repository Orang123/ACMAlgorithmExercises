//ac 15ms ��ά��ȫ����
//dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t])
/*
����:���xhd������һ�����FATE����Ϸ,Ϊ�˵õ���Ʒװ��,xhd�ڲ�ͣ��ɱ��������.
�ö���֮xhd��ʼ��ɱ�ֲ���������,���ֲ��ò�ͨ��ɱ�������������һ��.���ڵ�������,
xhd�������һ������n�ľ���ֵ,xhd������m�����Ͷ�,ÿɱһ����xhd��õ���Ӧ�ľ���a[i],��������Ӧ�����Ͷ�b[i].
�����ͶȽ���0����0����ʱ,xhd�Ͳ���������Ϸ.xhd��˵�������ֻɱsֻ��,�����������������һ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=2159
˼·:ÿ�ֹ������ɱ���,��Ȼ��ȫ����,������������ά�ȵ�����һ����ɱ���������һ�������Ͷ�,
������ֵ��ΪҪ��������ֵ.��ʼ״̬,ǡ��װ�������򾡿��ܶ��װ���������ɽ�.
dp[t][i][j]��ʾǰt�ֹ����������ɱi�����������Ͷ�Ϊjʱ�ܻ�õ������ֵ
dp[t][i+1][j+b[t]]=max(dp[t-1][i+1][j+b[t]],dp[t][i][j]+a[t]);
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;//��Ϊ�����ɱs������,�������ٵ����Ͷ���ǡ��װ����,���Գ�ʼ״̬��dp[0..s][0]=0
        for(int t=1;t<=k;t++){
            for(int i=0;i<s;i++){//i+1���ֻ��ɱs������,���i���Ͻ���s-1
                for(int j=0;j+b[t]<=m;j++){//�ܼ��ٵ����Ͷ������m
                    if(dp[i][j]<0) continue;
                    dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){//�����������򶼿�,ֻ������Ҫ�жϵ����m=1��ʱ��Ž���
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 686ms ����ö��dfs����+��֦
//������dp[N][N]״̬�����ž��߻�tle
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k������ɱ����Ϊi,���ٵ����Ͷ�Ϊjʱ����ܻ�þ���ֵΪk.
//�����dp[i][j]=k��ʾΪ��þ���ֵi,�������Ͷ�jʱ������ɱ����Ϊk,���������ͻ�tle.��Ϊ��֦���ܴ�dp��2��ά��ȥ��֦
int n,m,k,s,a[N],b[N],dp[N][N],ans;

void dfs(int num,int sumb,int suma){
    //n m ���Ҳֻ��100,��ÿ�ֹ���Ľ��ٵ����Ͷ���߿ɴ�20,�����֦�ͱȽϸ�Ч
    if(num>s || sumb>m)//��֦1
        return;
    //�����ǰ��״̬��þ���ֵ���ܱ�֮ǰ������ͬ��״̬�µ�����ֵ���� �򲻱��ظ�������ȥ
    if(suma<=dp[num][sumb])//��֦2(����Ҫ,Ҫ����tle)
        return;
    dp[num][sumb]=suma;
    if(suma>=n)
        ans=max(ans,m-sumb);
    for(int i=1;i<=k;i++)
        dfs(num+1,sumb+b[i],suma+a[i]);
}

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        ans=-1;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=-1;
        dfs(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 327ms bfs�������ö��״̬
//bfsҲ���������Ƶ�,��֦��dfs����ͬ��,�����ǰ״̬���ܱ�֮ǰ�ĸ��žͲ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
using namespace std;

//dp[i][j]=k������ɱ����Ϊi,���ٵ����Ͷ�Ϊjʱ����ܻ�þ���ֵΪk.
//�����dp[i][j]=k��ʾΪ��þ���ֵi,�������Ͷ�jʱ������ɱ����Ϊk,���������ͻ�tle.��Ϊ��֦���ܴ�dp��2��ά��ȥ��֦
int n,m,k,s,a[N],b[N],dp[N][N],ans;

struct State{
    int num,sumb,suma;
    State(int num=0,int sumb=0,int suma=0):num(num),sumb(sumb),suma(suma){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.suma>=n)
            ans=max(ans,m-tp.sumb);
        Q.pop();
        for(int i=1;i<=k;i++){
            if(tp.num+1>s || tp.sumb+b[i]>m)
                continue;
            if(tp.suma+a[i]<=dp[tp.num+1][tp.sumb+b[i]])
                continue;
            Q.push(State(tp.num+1,tp.sumb+b[i],tp.suma+a[i]));
            dp[tp.num+1][tp.sumb+b[i]]=tp.suma+a[i];
        }
    }
}

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        ans=-1;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=-1;
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms
//dp[t][i][j]��ʾǰt�ֹ��ﲻ����ÿ��ɱ�ĸ����������ɱi����ʣ���Ͷ�Ϊjʱ�ܻ�õ������ֵ
//dp[i+1][j-b[t]]=max(dp[i+1][j-b[t]],dp[i][j]+a[t]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][m]=0;
        for(int t=1;t<=k;t++){
            for(int i=0;i<s;i++){
                for(int j=m;j>=b[t];j--){
                    if(dp[i][j]<0) continue;
                    dp[i+1][j-b[t]]=max(dp[i+1][j-b[t]],dp[i][j]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=m-1;i>=0;i--){
            if(dp[s][i]>=n){
                ans=i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 46ms
//dp[t][i][j]��ʾ��ǰt�ֹ�����ɱ�����þ���Ϊi,���������Ͷ�Ϊjʱ����ɱ�����ٵĹ������
//dp[t][i+a[t]][j+b[t]]=min(dp[t-1][i+a[t]][j+b[t]],dp[t][i][j]+1);
//���������״̬ת�Ʒ������д������dp[t][i][j]]=min(dp[t-1][i][j],dp[t][i-a[t]][j-b[t]]+1)
//�Ͳ���ȷ��ʵ�ʻ�ü�ֵ����n,�����˶���,��Ȼ���Զ���n���Ͻ�Ϊn+30,��Ϊ�������������ǳ���20
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 2100//ɱ������ܻ�õľ���ֵ�� ����ÿ��������ٵ����Ͷȶ���1,100�ֹ���ÿ������ľ���ֵ����20,��ôʵ����ɱ100������ֵΪ20�Ĺ���,��:100*20=2000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[M][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        dp[0][0]=0;//ֻ��һ������û��ɱ ����ֵ�����Ͷ�û����ʱ���ǺϷ�״̬
        for(int t=1;t<=k;t++){
        	//ɱ�ֻ�þ���ֵ���Գ���n,����dp״̬�ڸճ�����,�Ͳ��ټ���ɱ��,
			//��Ϊ����ɱ�����Ͷ�ֻ�᲻���½�,����ʱ��õľ���ֵ�Ѿ��ﵽ��Ҫ��.
			//���i���Ͻ�����Ѿ��ﵽ��n,�Ͳ��ٴ�n����ת��ʹ�þ���ֵ������.
            for(int i=0;i<n;i++){
                for(int j=0;j+b[t]<=m;j++){
                    if(dp[i][j] == INF) continue;
                    //�����ɱ��i�ֹ���,��ôɱ�ָ�������dp[t-1][i+a[t]][j+b[t]] ǰt-1�ֹ���ʱ��ɱ����
					//���ɱ��i�ֹ���,ɱ�ָ�������dp[t][i][j]+1,������ǰt�ֹ���ɱ�ֻ�������ɱһ����t�ֹ���,���߷��������㾭��ֵ�����Ͷȵ���Сɱ����.
                    dp[i+a[t]][j+b[t]]=min(dp[i+a[t]][j+b[t]],dp[i][j]+1);
                }
            }
        }
        int flag=0,ans=-1;
        for(int i=n;i<M;i++){//ʵ������ܱ��������Ͷ� ���ܻ�þ���ֵ����n �����Ҫ����������� ��ȡ��������Ͷ�
            for(int j=1;j<=m;j++){
                if(dp[i][j]!=INF && dp[i][j]<=s)
                    ans=max(ans,m-j);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms ��ά��ȫ����
//dp[t][i][j]��ʾǰt�ֹ����������ɱi�����������Ͷ�Ϊjʱ�ܻ�õ������ֵ
//dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int t=1;t<=k;t++){
            for(int i=1;i<=s;i++){//���ɱs������ i���Ͻ���s
                for(int j=b[t];j<=m;j++){//�Ե�i�ֹ����ܼ��ٵ����Ͷ�������b[t],j���½���b[t]
                    if(dp[i-1][j-b[t]]<0) continue;
                    dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t]);
                }
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 46ms dpʱ s��j��ǰ����ѭ�� ��Ʒ�����ڵ�����ѭ��
//dp[t][i][j]��ʾǰt�ֹ����������ɱi�����������Ͷ�Ϊjʱ�ܻ�õ������ֵ
//dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int i=1;i<=s;i++){
            for(int j=0;j<=m;j++){
                for(int t=1;t<=k;t++){
                    if(j<b[t] ||dp[i-1][j-b[t]]<0) continue;
                    dp[i][j]=max(dp[i][j],dp[i-1][j-b[t]]+a[t]);
				}
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms dpʱ s��j��ǰ����ѭ�� ��Ʒ�����ڵ�����ѭ��
//dp[t][i][j]��ʾǰt�ֹ����������ɱi�����������Ͷ�Ϊjʱ�ܻ�õ������ֵ
//dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t])
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,s,a[N],b[N],dp[N][N];

int main(){
    while(scanf("%d%d%d%d",&n,&m,&k,&s)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d",&a[i],&b[i]);
        for(int i=0;i<=s;i++)
            dp[i][0]=0;
        for(int i=0;i<s;i++){
            for(int j=0;j<=m;j++){
                for(int t=1;t<=k;t++){
                    if(j+b[t]>m ||dp[i][j]<0) continue;
                    dp[i+1][j+b[t]]=max(dp[i+1][j+b[t]],dp[i][j]+a[t]);
				}
            }
        }
        int ans=-1;
        for(int i=1;i<=m;i++){
            if(dp[s][i]>=n){
                ans=m-i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
