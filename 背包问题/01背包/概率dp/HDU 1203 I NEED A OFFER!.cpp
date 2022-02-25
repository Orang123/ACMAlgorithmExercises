#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;
//ac 0ms һά����dp �����ܶ�װ,��Ҫ��ǡ��װ��
/*
ǰ��֪ʶ:��ѧ�еĶ����¼�����.
eg:�������,��������Ϊ����֮һ,��������Ϊ����֮һ,��������Ϊ�ķ�֮һ.
(1)���˶����еĸ��ʣ�(2)������������һ�˻��еĸ��ʣ�
(1).(1/2)*(1/3)*(1/4)=1/24
(2).��������:
һ���Ǵ����濼��,����һ������,��Ϊ1������,2������,3������,
���������.
1������:
������:(1/2)*(1-1/3)*(1-1/4)=1/4
������:(1-1/2)*(1/3)*(1-1/4)=1/8
������:(1-1/2)*(1-1/3)*(1/4)=1/12
1�����и���=1/4+1/8+1/12=11/24

2������:
�ұ�����:(1-1/2)*(1/3)*(1/4)=1/24
�ױ�����:(1/2)*(1-1/3)*(1/4)=1/12
��������:(1/2)*(1/3)*(1-1/4)=1/8
2�����и���:1/24+1/12+1/8=6/24

��������:(1/2)*(1/3)*(1/4)=1/24

������������һ�����и���=P(1������)+P(2������)+P(3������)=11/24+6/24+1/24=3/4

��һ�ַ����Ǵӷ��濼��:"����1������"�Ķ����¼�Ϊ"�����˶�δ����",�������¼�����
����,P(����1������)=1-P(�����˶�δ����)=1-(1-1/2)*(1-1/3)*(1-1/4)=1-1/4=3/4
*/

/*
����:V(V<=10^4)ԪǮ,N(N<=10^4)��ѧУ,ÿ��ѧУ�������Ϊw[i],
ͨ��������val[i],ÿ��ѧУ�����¼����໥������,����������յ�
����һ��offer��������.
ע��:0<=v<=10^4,0<=n<=10^4,v��n��Ϊ0,w[i]Ҳ����Ϊ0,Ҳ���Ǵ���
����Ǯ����ѧУ�����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1203
˼·:ÿ��ѧУֻ�������벻����2��״̬,��ֻ��������һ��,����
�ʵ���"���ٻ��һ��offer��������",ֱ�ӿ��ǵ÷ֺܶ����һ��ѧУͨ��,
2��ѧУͨ��,3��ѧУͨ��,...,n��ѧУͨ��,��������ԭ�������һ����
����n����Ʒ��ѡȡָ����Ŀ��Ʒ�ı���ö������,���Ҹ��ӶȽϸ�,����
"���ٻ��һ��offer��������"�Ķ����¼�Ϊ��һ��offerҲ���ܻ�õ���С���ʡ�,
������ѧУ����ͨ������С����(1-val[i]),��������������VԪǮ��Ȼ��Ҫ
С������ѧУ����������ܺ͵�,���ݳ˷�ԭ������ת�����˾����ܶ��ѡ��ѧУ֮��
��ͨ������˽����С�ĸ��ʻ�,��ȻVԪǮ��������²����������е�ѧУ,��ô����
ÿ��ѧУ����������Ҫ����ȡ��,��ô������ȡ��С��û��offer����С���ʾ͹�����
һ��01��������,���ұ�������Ӧ���Ǿ����ܶ��װ������ǡ��װ�����������,
���Գ�ʼ��dp��Ϊ1.0,��Ϊ���ʶ����¼�֮���ǳ˷�ԭ���۳˸���,V�п����ǻ���ʣ���,
��ʣ�µ�ǮҲ��������ʣ�µ��κ�һ��ѧУ.ֻ����Ծ����01���������ۼӵ�����ֵ,
�����ǰ��ճ˷�ԭ���۳���ȡ��Сû��offer�ĸ���,״̬ת�Ʒ���Ϊdp[j]=min(dp[j],dp[j-w[i]]*(1-val[i])),
��ʼ��dp[v]=1.0,����Խ�۳˽����ԽС,���ϱ�����ȡѡ���˼��.
*/
int w[N],n,v;
double dp[N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=0;i<=v;i++)
            dp[i]=1.0;//��Ϊ���۳�,���Գ�ʼ��Ϊ1.0
        for(int i=1;i<=n;i++){
            for(int j=v;j>=w[i];j--)
                dp[j]=min(dp[j],dp[j-w[i]]*(1-val[i]));//Խ�۳˽��ԽС���ϱ���ȡ����Ʒ��ԭ��
        }
        printf("%.1f%%\n",(1-dp[v])*100);//���ԭ����Ҫȡ��,�����ٻ��һ��offer��������
    }
    return 0;
}

/*
//ac 15ms һά����dp ǡ��װ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define INF 1e18
using namespace std;

int w[N],n,v;
double dp[N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=0;i<=v;i++)
            dp[i]=INF;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        dp[0]=1.0;
        for(int i=1;i<=n;i++){
            for(int j=v;j>=w[i];j--)
                dp[j]=min(dp[j],dp[j-w[i]]*(1-val[i]));//Խ�۳˽��ԽС���ϱ���ȡ����Ʒ��ԭ��
        }
        double ans=1.0;//��������Ǯv���������κ�һ��ѧУ,��dp[0..v]>1,��Ҫ��ʼ��ans=1.0,���ٻ��offer�ĸ���Ϊ1-ans=0
        //��������:v=0,n=1 w[1]=0,val[1]=1,ʵ�ʿ��Բ���Ǯ���뵽offer,ͨ����ʵ��Ϊ1,����ֻ��dp[0]=0<1.0,����i������Ҫ��0
        for(int i=v;i>=0;i--){
            if(dp[i]<1.0)
            //��һ������ǮԽ��,û�л��offer�ĸ��ʾ�ԽС,��Ȼ�˻���Խ��ԽС,
            //������ֻ��1��2��ѧУ�Ļ��Ѻܸ�,��ʵ�ʲ�ͨ���ʱ���ͺܴ�,
            //��ʵ������Ǯ��С��,�����Ǻܶ��ѧУ�Ĳ�ͨ���ʳ˻� Ҳ���ܸ�С,����Ҫ�����������
                ans=min(ans,dp[i]);
        }
        printf("%.1f%%\n",(1-ans)*100);//���ԭ����Ҫȡ��,�����ٻ��һ��offer��������
    }
    return 0;
}
*/

/*
//TLE ����ö������+��֦
#include<cstdio>
#include<algorithm>
#define N 11000
#define INF 0x3f3f3f3f
using namespace std;

//sufxv[i]��ʾi~n��׺ѧУ����С���������
//sufxval[i]��ʾi~n��׺����ѧУ�����벻ͨ���ʵĻ�
int w[N],n,v,sufxv[N];
double ans,val[N],sufxval[N];

//numΪ�Ѿ������ѧУ����,VΪʣ��Ǯ,resΪ��ǰ����ѧУ�����ܻ��offer�ĸ���
int dfs(int k,int num,int V,double res){
    if(res<ans)
        ans=res;
    //��֦1 ������ѧУ������ʱ,���ܻ��offer�ĸ���һ������С��(С���˻�,Խ��ԽС),�����ٱȽ�,ֱ�ӷ���1,�˳�����
    if(num == n) return 1;
    if(V<sufxv[k]) return 0;//��֦2 ǰʣ��Ǯ�ȱ��Ϊk~n��ѧУ�����������С�Ļ���ʱ,�Ͳ���������,����0,ֹͣ��ǰ����,������һ��
    if(res*sufxval[k]>=ans) return 0;//��֦3 ����ǰ����res�˱��Ϊk~n����ѧУ�����벻ͨ����֮���Ļ�����ansСʱ,ֹͣ��ǰ����,���ݵ���һ��
    if(k == n+1) return 0;//ö��������Ʒ����,����,���ݵ���һ��
    if(V>=w[k])//ֻ�е�ʣ��Ǯ�㹻֧����k��ѧУ�������ʱ ������
        if(dfs(k+1,num+1,V-w[k],res*(1-val[k]))) return 1;
    if(dfs(k+1,num,V,res)) return 1;//�������k��ѧУ
    return 0;
}

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        sufxv[n+1]=INF;
        sufxval[n+1]=1.0;
        ans=1.0;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=n;i>=1;i--)
            sufxv[i]=min(sufxv[i+1],w[i]);
        for(int i=n;i>=1;i--)
            sufxval[i]=sufxval[i+1]*(1-val[i]);
        dfs(1,0,v,1.0);
        printf("%.1f%%\n",(1-ans)*100);
    }
    return 0;
}
*/

/*
//MLE ��ά����dp
//N<=10^4 N*N<=10^8,�ռ䳬��
#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;

int w[N],n,v;
double dp[N][N],val[N];

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        for(int i=0;i<=v;i++)
            dp[0][i]=1.0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
                if(j>=w[i])
                    dp[i][j]=min(dp[i-1][j],dp[i-1][j-w[i]]*(1-val[i]));
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%.1f%%\n",(1-dp[n][v])*100);
    }
    return 0;
}
*/

/*
//MLE ��ά������仯����
//N<=10^4 N*N<=10^8,�ռ䳬��
#include<cstdio>
#include<algorithm>
#define N 11000
using namespace std;

int w[N],n,v;
double dp[N][N],val[N];

double dfs(int i,int j){
    if(!i) return 1.0;
    if(dp[i][j]) return dp[i][j];
    if(j>=w[i])
        dp[i][j]=min(dfs(i-1,j),dfs(i-1,j-w[i])*(1-val[i]));
    else
        dp[i][j]=dfs(i-1,j);
    return dp[i][j];
}

int main(){
    while(scanf("%d%d",&v,&n) && v+n){
        for(int i=1;i<=n;i++)
            for(int j=0;j<=v;j++)
                dp[i][j]=0;
        for(int i=1;i<=n;i++)
            scanf("%d%lf",&w[i],&val[i]);
        printf("%.1f%%\n",(1-dfs(n,v))*100);
    }
    return 0;
}
*/

/*
//л����ʦ08������̽.pptx�ϵı�̲�������״̬ת�Ʒ���
//dp[j] = MAX(dp[j],w[i]+(1.0-w[i])*dp[j-c[i]]) ΪɶҪ�ټ�w[i],Ӧ����д����
#define V 11111
#define N 1111
#define MAX(x,y) ((x)>(y)?(x):(y))
double dp[V];
int c[N];
double w[N];
void solve(int n,int v){
	int i,j;
	memset(dp,0,sizeof(double)*(v+1));
	for(i=0;i<n;i++){
		for(j=v;j>=c[i];j--) dp[j] = MAX(dp[j],w[i]+(1.0-w[i])*dp[j-c[i]]);
	}
}
*/

