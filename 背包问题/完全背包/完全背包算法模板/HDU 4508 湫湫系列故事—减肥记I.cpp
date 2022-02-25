/*
����:���ڳԻ���˵,�������Ҹ����¾��ǳ���,û��֮һ��
���Ƕ���Ů����˵,��·�����������а���������Ů����
���ϡ�������ɽ��,��ȥ���˿���ĵ���,������ϣ�����ܰ�æ��
��һ��ʳ��,��ʹ���Եÿ��ĵ�ͬʱ,��������̫������.
��Ȼ,Ϊ�˷���������ʳ��,���и�����ÿ��ʳ���嵥,��������
�˵�������Ե�ÿ��ʳ���ܴ��������Ҹ��̶�a[i],�Լ������ӵĿ�·����b[i].
��������㿨·����������ͬʱ,���пɻ�õ�����Ҹ�ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4508
˼·:�������ȫ����
*/
//ac 46ms һά����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
            for(int j=b[i];j<=m;j++)
                dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 140ms һά���� dp��һ�׶�����ö�ٱ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int j=0;j<=m;j++){
            for(int i=1;i<=n;i++){
                if(j>=b[i])
                    dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 171ms ����01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(tb=b[i],ta=a[i];tb<=m;tb+=b[i],ta+=a[i]){
                for(int j=m;j>=tb;j--)
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 187ms ����01���� ���������ڵڶ������Ʒ��������ڵ�����ѭ��,˳��ߵ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=b[i];j--){
                for(tb=b[i],ta=a[i];tb<=j;tb+=b[i],ta+=a[i])
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 93ms 01���� �������Ż�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(tb=b[i],ta=a[i];tb<=m;tb<<=1,ta<<=1){
                for(int j=m;j>=tb;j--)
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        //����������ǰ,��Ʒ�����ں� �ͻ����,��Ϊ�ڶ������������ֵ����m��ǡ�õ���m�����ʱ
        //�޷������ڱ�������=m���ʱ,���뱳������������ ��������ĵ�i����Ʒ�Ŀ���,
        //for(int i=1;i<=n;i++){
            //for(int j=m;j>=b[i];j--)
                //for(tb=b[i],ta=a[i];tb<=j;tb<<=1,ta<<=1)
                    //dp[j]=max(dp[j],dp[j-tb]+ta);
        //}
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//MLE ��ά���� �ռ俪��10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[N][M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(j>=b[i])
                    dp[i][j]=max(dp[i-1][j],dp[i][j-b[i]]+a[i]);
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/

/*
//ac 717ms bfs���ѱ���ö��״̬����ת��
//����if(tp.a+a[i]>dp[tp.b+b[i]]) ��֦��MLE,ö�ٵ�״̬��̫��ѹ�����,��ȻҲ��tle
//ÿ��״̬����n�ֿ��ܵ�ת��,������,ÿ����Ʒ���Ϊ1,�ʱ�临�Ӷ� �о�Ҳ���Ǹ�����ʽʱ��
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
//dp[i]=j,����ǰ��ѡ��Ʒ��ռ���Ϊiʱ����õ�����ֵΪj.
int n,m,a[N],b[N],dp[M],ans;

struct State{
    int a,b;
    State(int a=0,int b=0):a(a),b(b){}
};

//ÿ��״̬����n�ֿ��ܵ�ת��,������,ÿ����Ʒ���Ϊ1,�ʱ�临�Ӷ� �о�Ҳ���Ǹ�����ʽʱ��
void bfs(){
    queue<State> Q;
    Q.push(State(0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(ans<tp.a)
            ans=tp.a;
        for(int i=1;i<=n;i++){
            //���������������m Ҳ�������
            if(tp.b+b[i]>m) continue;
            //��֦ �����ǰ״̬��tp��ѡ��Ʒռ���Ϊtp.b+b[i]���ܻ�õļ�ֵ��֮ǰ��¼��dp[tp.b+b[i]]����ֵ��С�Ͳ������.
            if(tp.a+a[i]>dp[tp.b+b[i]]){
                dp[tp.b+b[i]]=tp.a+a[i];
                Q.push(State(tp.a+a[i],tp.b+b[i]));
            }
        }
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/
