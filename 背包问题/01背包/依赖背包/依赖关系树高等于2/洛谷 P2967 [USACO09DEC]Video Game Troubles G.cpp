/*
����:ũ��Լ������ţ�Ǵ���Ϸ����ˣ�����Լ������Ҫ���յ����޵�����������ȥ�������,
�ɺ�����������ţ������Ϸ֮���ԭ�Ȳ��������.������,������Ϊ�����ţ����������.
����,��ţ�������Ϊ��õ���Ϸ���������ò��ɿ���.Լ����Ҫ�ڸ�����Ԥ���ڹ���һЩ��Ϸ
ƽ̨��һЩ��Ϸ,ʹ������ţ������������ţ����������Сţ.Լ��������n����Ϸ����,
��i�������ļ۸���p,��������g����ռ��Ϸ.������,��ţ���������һ����Ϸ����,���������
�������������е���Ϸ.��ÿ��������,��Ϸk�ļ۸�Ϊw[k],ÿͷ��ţ�����˸���Ϸ���ţ�̲���
Ϊval[k].ũ��Լ����Ԥ��Ϊv.�������ȷ��Ӧ����ʲô��Ϸ��������Ϸ,ʹ�����ܹ���õĲ���ֵ�ĺ����.
����:https://www.luogu.com.cn/problem/P2967
˼·:��HDU 3449 һģһ��10���У,Ӧ��˵HDU 3449��ȫ��Ϯ��[USACO09DEC]Video Game Troubles G,
Ҫ����Ϸ�ͱ����������Ϸ��Ӧ������,�������������ô��������ϵ���Ϸ�Ͷ�������.
dp[i][j]ǰį�������Ӧ��Ϸ����ܻ�õĲ���ֵ.
�ȶ������ڵ���Ϸ��dp[i-1][j]�����ϼ���01����,�������������л����޼�ֵ����Ʒ,Ҳ������Ϸ01����
����״̬�ϼ���01����,ֻ�Ƕ��ڲ����������ĵ���һ״̬��ǰi-1̨���������Ž�dp[i-1][j],��Ϊ����
��������ǰ��������Ϸ��һ����������.
*/
//ac 898ms �������� һά����ʵ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
#define M 100010
using namespace std;

int n,v,tp[M],dp[M];

int main(){
    int p,g,w,val;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&g);
        for(int j=0;j<=v;j++)
            tp[j]=dp[j];
        for(int k=1;k<=g;k++){
            scanf("%d%d",&w,&val);
            for(int j=v-p;j>=w;j--)
                tp[j]=max(tp[j],tp[j-w]+val);
        }
        for(int j=v;j>=p;j--)
            dp[j]=max(dp[j],tp[j-p]);
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 100�� 2.04s ���鱳����ǰ������ȡһ��(�����ά����)�͵�ǰ��һ��Ҳ��ѡ ������ֵ
//���Ӷ�O(nvmax(num[i]))=50*10^5*10=5*10^7
//��ʼ��-INF �����ж���һ״̬�Ƿ�Ϸ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    scanf("%d%d",&n,&v);
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<=v;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&num);
        for(int k=1;k<=num;k++){
            scanf("%d%d",&w,&val);
            for(int j=v;j>=w;j--){
                //ע��:�����Ŀ������Ʒ��Ǯ����Ϊ0,�ж�ת��˳�� �������� ����HDU 3449���� ����˳���ǻ�wa,�о��������������Ծɴ������Ϊ0�����
                //��i���е���Ʒ��ǰi-1����Ʒ���������ٷ�һ��,��Ҫ�����Ӻ���Ʒ�ļ�Ǯ ���Ӳ�������ֵ
                if(j>=p+w && dp[i-1][j-p-w]!=-1)
                    dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                //��i���е���Ʒ��Ʒ�Ѿ�ѡ����������ѡ�����Ʒ 01����,���ӵ�Ǯ�Ѿ����� �����ٸ�
                if(dp[i][j-w]!=-1)
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
            }
        }
        //�Ƚ�����ѡһ����i����Ʒ�͵�i����Ʒһ��Ҳ��ѡ(ǰi-1����Ʒ���Ž�dp[i-1][j])�ĸ���ֵ����
        for(int j=0;j<=v;j++)
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
    }
    printf("%d\n",dp[n][v]);
    return 0;
}
*/

/*
���������Ż� ��������dp[M]��tp[M]
���鱳����ǰ������ȡһ��(�����ά����)�͵�ǰ��һ��Ҳ��ѡ ������ֵ
�ȿ��ǹ�������,�����ѹ������������Ϲ����Ӧ����Ϸ
�����μ�HDU 3449
*/

/*
//TLE 78�� ���鱳�� ÿ����Ʒ����ѡһ��,ÿ����Ʒ����ѡȡ��� dfs����ö��+��֦
//���Ӷ� 50*10^5*1024=5*10^9 ����������ϻή��һ�� ������TLE��
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 55
#define M 100010
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

void dfs(int i,int k,int tw,int tv){
    if(k == num+1){
        //��֦ �����i��֮ǰѡȡ����Ϸ������ ������Ե�ǰ���,����������ڵ�ǰ������
        //��ֵҲ�������ڵ�ǰ���,�Ǿ�û��Ҫѡȡ��ǰ�������,��û�б�֮ǰ������������
        //�����֮������������ֵС����϶������Ž����ȡû�а���
        for(Node & x : a[i]){
            if(x.w<=tw && x.val>=tv)
                return;
        }
        a[i].push_back(Node(tw,tv));
        return;
    }
    if(tw+w[k]<=v)
        dfs(i,k+1,tw+w[k],tv+val[k]);
    dfs(i,k+1,tw,tv);
}

int main(){
    scanf("%d%d",&n,&v);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++)
        a[i].clear();
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&num);
        for(int k=1;k<=num;k++)
            scanf("%d%d",&w[k],&val[k]);
        //����������i�������ĳ�����Ϸ����ѡȡ���
        dfs(i,1,p,0);//��i������Ҫ�� ������������,��������Ϸ,������������ֵ
    }
    //ÿ����Ʒ����ѡȡһ��
    for(int i=1;i<=n;i++){
        for(int j=v;j>=1;j--){
            for(Node & k :  a[i]){
                if(j>=k.w)
                    dp[j]=max(dp[j],dp[j-k.w]+k.val);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//TLE 62�� ���鱳������
//���Խ�ÿ�������������ܳ�����Ϸ������������������Ϊһ��,�������ܱ�֤������Ϸһ���ȹ���������.
//��Ϊÿ���������ֻ��10����Ϸ���Զ�����ö���Ӽ������������Ϲ��ɵĵ�����Ʒ���������ֵ,�����鱳��.
//��������Ӷ��е�� 50*10^5*1024=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
#define M 100010
using namespace std;

int n,v,gp[11],pv[11],w[N][1050],val[N][1050],num[N],dp[M];

int main(){
    int p,g;
    memset(num,0,sizeof(num));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&g);
        for(int j=1;j<=g;j++)
            scanf("%d%d",&gp[j],&pv[j]);
        int k=(1<<g)-1;
        //ö�� ����+2^g�ֿ��ܵ���Ϸ��� ������Ϊ��i���ڵ���Ʒ
        for(int j=1;j<=k;j++){
            int tp=j,t=1;
            num[i]++;
            while(tp){
                if(tp & 1){
                    w[i][num[i]]+=gp[t];
                    val[i][num[i]]+=pv[t];
                }
                tp>>=1;
                t++;
            }
            w[i][num[i]]+=p;//��ǰ��Ϸ��ϼ��������ļ�Ǯ
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=v;j>=1;j--){
            for(int k=1;k<=num[i];k++){
                if(j>=w[i][k])
                    dp[j]=max(dp[j],dp[j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/
