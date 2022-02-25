#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;
//ac 234ms �������� ��ά01����ʵ��
//�����ά����������ǰ������ Ҫ�����i��ĸ���,�ͱ����Ȱ�������Ǯ�ڳ���,�����Ѿ�����pԪ��������,��ȥ�򸽼���
//����д�Ķ�ά�����ǰ�����Ҳ��ȫ����һ����ֵΪ0����Ʒ,���򸽼���������,�ۺ�������д�İ汾���������
/*
���Լ���˼·:һάdp�������������
//˼·���ǰ�������Ʒ��������һ������Ʒ,ֻ�Ƕ�������ֻ�м�Ǯû�ж�Ӧ��ֵ,Ȼ��������Ʒ01����
//��˳��Ҫ���պ����������Ӧ���ȷŸ���,������,ֻ�������ڽ���01����ʱ,���ڲ�ѡȡ��������һ��
//״̬������dp[i-1][j],��Ϊ��ѡ�������и������Ͷ�����ѡ,����һ��״̬�ǳ�����������num���Ӽ�֮ǰ
//��ǰi-num����Ʒ��״̬,��˴������������Ѿ���ÿ���������������ֿ�,����ÿ���ڶ�ÿ����Ʒ����01
//����֮ǰ��ǰһ��������������״̬Ӧ�ñ���һ������dp,���µ�����tp���и��鸽������01����,�ȶԸ���
//��Ʒ�ĸ��������г����01����,֮��Ը������������01����ʱ,��ǰһ״̬��dp[j],��ǰ����������״̬
//��tp[j-p]+0,��Ϊ���ֵΪ0.
*/
/*
����:n����Ʒ,ÿ����Ʒ��Ӧһ������,���ӵļ۸�Ϊp,ÿ����Ʒ��num����Ʒ,
Ҫ������Ʒ���빺�������Ʒ��Ӧ�ĺ��Ӳ��ܽ���Ʒ�������,ÿ����Ʒ�ļ۸�
Ϊw,��ֵΪval,���ڳ�ʼ��vԪǮ,������Ʒ����ܻ�ö��ټ�ֵ.
ע��:������Ӳ������ü�ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3449
˼·:����� P2967 [USACO09DEC]Video Game Troubles G ��ͬһ����
���ϱ������˼·��Ҫ����Ʒ��ü�ֵ,�ͱ����������,ÿ���ڶ���Ʒ����
01����֮ǰ,�ȼ�����������,�����������ڿճ�pԪ,��ȥ����Ʒ��,����ٺ�
Ҫ������Ʒ�����ȹ��������Ʒ��Ӧ�ĺ���,�����ӱ���û�м�ֵ.Ȼ���ٱȽ�
����dp[i-1][j]��dp[i][j]�����Ž�,ע��dp[i][j]����dp[i-1][j-p]�����Ͻ���01������,
���ԱȽϵķ�Χ��[0,v]
���������ͱ���������01������ģ��.ǰi-1�������ֵ�ȳ�ȥ��i����ӻ���p
�ټ̳�ǰi-1���Ǯ��p�������ֵ,���ҳ�ʼ״̬����j<p��״̬����Ϊ-1��ʾ���Ϸ�.
֮�����ڵ�i����Ʒ�н����ڳ�ȥpԪ���ǰi-1����Ʒ����ֵ�����Ͻ���01����,
֮���ٱȽ�������ǰi������ֵdp[i][j]��ǰi-1������ֵdp[i-1][j]����dp[i][j].

���������Ž���ѡ�˵�һ����Ʒ�е�3����Ʒ ��ֵ80,����300+25=325
��������Ʒ�еĵ�2��3����Ʒ ��ֵ��70+60=130,����400+40+35=475.
�ܼ�ֵ=80+130=210,�ܻ���=325+475=800.
*/
//dp[i][j]��ʾ��jԪ����ǰi����Ʒ���ܻ�õ�����ֵ
int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        //��ÿ����Ʒ�ĺ��ӽ���01����
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //��i����Ʒ ����Ҫ�����,��j<pʱ�޷�������� ���޷���������е���Ʒ,���Ϊ-1(�Ƿ�״̬)
            for(int j=0;j<p;j++)//ע����<p,��Ϊ����p�Ѿ��������µ�i��ĺ���,�ǺϷ�״̬
                dp[i][j]=-1;//���Ϸ�״̬��ʼ��Ϊ-1,���ܳ�ʼ��Ϊ0,��Ϊdp[i][p]=0�ǺϷ�״̬��������
            //��i����Ʒ�����Ž�̳�ǰi-1����Ʒ������ֵ,��ΪҪ���i��ĵĺ���,
            //����ֻ�̳м�ǮΪj-p�µ����Ž�,��ΪҪ��ǰi-1��״̬�����Ž��ڳ�һ����Ǯ�������i��ĺ���
            //�������ܹ����i���ڵ���Ʒ
            //ʵ�ʾ����������ֻ�������Ӽ۸�Ϊp,��ֵ0
            for(int j=p;j<=v;j++)
                dp[i][j]=dp[i-1][j-p]+0;
            //�Ե�i����Ʒ�ڵ���Ʒ����01����(��Ȼ��ǰi-1����Ʒ������)
            //ע������dp[i][j]������ǹ��������Ż������,�����i��ǰi��,
            //dp[i-1][j]��ǰi-1���״̬,���������ڵ�i���ڽ���01����,����ֻ�еڶ�άj�����õ�
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                //dp[i][j]��ʾ��jԪ������ǰi����Ʒ�������жԵ�i��ǰk����Ʒ�ܻ�õ�����ֵ
                for(int j=v;j>=w;j--){
                    if(dp[i][j-w]!=-1)//j-w����>=p,���������ܹ����¸�����Ʒ��Ӧ�ĺ��Ӳ���������ڵ���Ʒ
                        dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                }
            }
            //�����ǱȽ� ǰi-1��(dp[i-1][j])���ڷ����i����Ʒdp[i][j]������ֵ,
            //������01����ת�Ʒ�����ֻ�ǱȽϵ�i����ǰk����Ʒ��ǰk-1����Ʒ��ֵ.
            //ע��ǰi-1��,����dp[i-1][j]�е�j ��û�м�ȥ��i����ӵķ���p,����ֵ��û�е�i�����Ʒ,
            //��dp[i][j]������ֵ����dp[i-1][j-p]���������ڳ����ӵ�pԪ����dp��,dp[i][j]���п��ܻ�����
            //ǰi-1�����Ʒ�͵�i�����Ʒ,����ֻ�ǱȽ���ȡdp[i][j]������ֵ
            //���j�õ����½�Ϊ[0,v]
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i-1][j],dp[i][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
/*
//ac 249ms ��ά���� 01���� ���Լ����İ汾
//��д�Ķ�ά�����ǰ�����Ҳ��ȫ����һ����ֵΪ0����Ʒ,���򸽼���������
//����һ���״̬����Ϊdp[i-1][j],�ȶԸ�������01����dp[i][j]���������Ż�,
//�ٶ���������01����,�����ڿ��ǲ����븽��ʱ,����һ��״̬����dp[i-1][j]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //dp[i][j]�̳���һ��״̬dp[i-1][j]
            for(int j=0;j<=v;j++)
                dp[i][j]=dp[i-1][j];
            //�ڸ�����Ʒ�ڶԸ�������01���� ���ù��������Ż�
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v-p;j>=w;j--){//j���Ͻ���Ż�Ϊv-p,��Ϊ�ڷ�������ʱ,�����۸�Ϊp,dp[i][j-p],j-p���ֻ����v-p
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                }
            }
            //�ڸ���dp[i][j]�����Ϸ�������,��Ӧ��״̬Ϊdp[i][j-p]+0
            //������������,�����еĸ��������ܷ���,��Ӧ����һ״̬����һ���״̬Ϊdp[i-1][j]
            //���µ�ǰi����Ʒ������ֵ��ֵ��dp[i][j],����j���뽵����ܱ�֤dp[i][j-p]��û��������֮ǰ��״̬
            for(int j=v;j>=0;j--){//����j���½���0,��Ϊdp[i][j]�жԸ�������01����ʱ,j<p�����Ž�Ҳ��������,��ʵ��j<p�ǲ��ܷ��븽����,����Ҫ���¼̳���һ״̬dp[i-1][j]
                if(j>=p)
                    dp[i][j]=max(dp[i-1][j],dp[i][j-p]);
                else//������ܷ�������,��̳���һ��dp[i-1][j]��״̬
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 171me �������� ���������Ż�01����ʵ��
//���������Ż� ǰi���ά��,��2������ʵ��,tp������е�i���ڵ�01����
//dp�����¼ǰi-1�������ֵ,��
//���ܼ�Ǯvֱ���ȳ�ȥ��i��ĺ���Ǯ,�Ƚ������01����
//֮�󽫵�i��״̬tp[j-p]��ǰi-1��״̬dp[j]�Ƚ�����ֵ,��Ϊ�ڹ����i����Ʒ��Ҫ��
//�����i��ĺ���,������p+1,С�ڵ���p��ֱ�Ӱ�����ǰi-1���״̬����,��Ϊ�������˵�i�����Ʒ.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //��ǰi-1���״ֱ̬�Ӹ�ֵ����i��״̬
            memcpy(tp,dp,sizeof(dp));
            //��i������Ʒ��ȥ���ӷ���p�������01����
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v-p;j>=w;j--)//��ΪpԪ�������������,�����������v-pԪ����Ʒ
                    tp[j]=max(tp[j],tp[j-w]+val);
            }
            //j<=p �����������i����Ʒ,ע��<p���˺���,=pֻ�������,������Ʒ,Ҳ������
            //����Ҫ������ԭ��tp[j]����ֵ�����ϳ�ȥ����ӵ�Ǯ,��ֻ�ܱ���tp[j-p]
            //��ǰi����Ʒ״̬tp[j-p]��ǰi-1����Ʒdp[j]״̬(��������i�����Ʒ��ֵ)�Ƚ���ȡ����ֵ
            //�µ�ǰi����Ʒ����ֵ��ֵ��dp[j]
            for(int j=p+1;j<=v;j++)
                dp[j]=max(tp[j-p],dp[j]);//��Ϊ���ڵ�i����Ʒ��˵,Ҫ����pԪ���������,����ǰi��״̬tp,֧ȡtp[j-p]
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 171ms ���Լ��뵽����򵥵�01����
//˼·���ǰ�������Ʒ��������һ������Ʒ,ֻ�Ƕ�������ֻ�м�Ǯû�ж�Ӧ��ֵ,Ȼ��������Ʒ01����
//��˳��Ҫ���պ����������Ӧ���ȷ��Ӽ�,������,ֻ�������ڽ���01����ʱ,���ڲ�ѡȡ��������һ��
//״̬������dp[i-1][j],��Ϊ��ѡ���������Ӽ��Ͷ�����ѡ,����һ��״̬�ǳ�����������num���Ӽ�֮ǰ
//��ǰi-num����Ʒ��״̬,��˴������������Ѿ���ÿ���������Ӽ����ֿ�,����ÿ���ڶ�ÿ����Ʒ����01
//����֮ǰ��ǰһ���������Ӽ���״̬Ӧ�ñ���һ������dp,���µ�����tp���и����Ӽ���01����,�ȶԸ���
//��Ʒ���Ӽ����г����01����,֮��Ը������������01����ʱ,��ǰһ״̬��dp[j],��ǰ����������״̬
//��tp[j-p]+0,��Ϊ���ֵΪ0.
//���Ӷ�O(nvmax(num[i]))=50*10^5*10=5*10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //����һ����Ʒ״̬��ֵ��tp,��tp���и�����Ʒ��01����
            //dp��Ϊ��һ����Ʒ��״̬
            memcpy(tp,dp,sizeof(dp));
            //�ȶԸ�����Ʒ���Ӽ�����01����
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)//������ʵj>=v-p�Ĳ��� tp[j],�ڷ��������������õ�,���Կ��Կ����Ż��Ͻ�Ϊj=v-p.
                    tp[j]=max(tp[j],tp[j-w]+val);
            }
            //�ٶԸ�����Ʒ����������01����
            //ע�ⲻѡ������ô�������Ӽ�������ѡ,��:ǰ��һ״̬��ǰһ����Ʒ��״̬dp[j]
            for(int j=v;j>=p;j--)//����j�������� ��Ӱ���
                dp[j]=max(dp[j],tp[j-p]);
            //j<pʱ,����Ͳ��ܷ��µ�i����Ʒ������,����dp[j]������һ����Ʒ��dp[j],���dp[j]���������Ϊ�µ�ǰi����Ʒ�����Ž�
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//��ΪN*M<=5.6*10^7 MLE dfs��������������� ����01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 560
#define M 100100
using namespace std;

//����i�ڵ���dfs���������õ�����Ϊk
//dp[i][j] ����dfs��������ǰk���������Ʒ��jԪǮ���������ܻ�õ�����ֵ
int cnt,head[N];
int n,m,p,num,k,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        for(int j=0;j<=m;j++)
            dp[v][j]=dp[u][j];
        dfs(v);
        for(int j=m;j>=w[v];j--)
            //����ѡȡ����,��ôʵ��dp[v][j]������ֵֻ��ѡ��dp[v][j-w[v]]ʱ������ֵ,��Ϊ��Ҫ�ڳ�w[v]�����,�����򸽼�
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);//ʵ�ʺ��ӵ�val[v]Ϊ0,���Ⲣ��Ӱ������ֵ
    }
}

int main(){
    int rt;
    while(scanf("%d%d",&n,&m)!=EOF){
        k=0;
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            k++;
            scanf("%d%d",&w[k],&num);
            rt=k;
            addEdge(0,rt);
            while(num--){
                k++;
                scanf("%d%d",&w[k],&val[k]);
                addEdge(rt,k);
            }
        }
        dfs(0);
        printf("%d\n",dp[0][m]);
    }
    return 0;
}
*/

/*
//ac 343ms ���鱳����ǰ������ȡһ��(��������������)�͵�ǰ��һ��Ҳ��ѡ ������ֵ
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
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=0;i<=v;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--){
                    //ע��:��Ȼ�����Ŀ������Ʒ��Ǯ����Ϊ0,�����ж�˳���ǲ��ܴ�dp[i-1][j-p-w]ת�� �����wa �ݲ����ԭ��
                    //��i���е���Ʒ��Ʒ�Ѿ�ѡ����������ѡ�����Ʒ 01����,���ӵ�Ǯ�Ѿ����� �����ٸ�
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                    //��i���е���Ʒ��ǰi-1����Ʒ���������ٷ�һ��,��Ҫ�����Ӻ���Ʒ�ļ�Ǯ ���Ӳ�������ֵ
                    if(j>=p+w)
                        dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                }
            }
            //�Ƚ�����ѡһ����i����Ʒ�͵�i����Ʒһ��Ҳ��ѡ(ǰi-1����Ʒ���Ž�dp[i-1][j])�ĸ���ֵ����
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 390ms ���鱳��ÿ������ȡһ���͵�ǰ��һ��Ҳ��ѡ ������ֵ
//��ʼ��Ϊ0 ���ж���һ״̬�Ƿ�Ϸ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--){
                    if(dp[i][j-w])//���ж� �ᵼ��ֱ�Ӵ�dp[i][j-w]=0��ʼ�ۼ�,���²�û���� ��i���������ӵ�Ǯ,���½��ƫ�� ��wa
                        dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                    //dp[i-1][j-p-w]�������>=0��,��: ���ǵ���0��������˱�����������Ϊ0��,�������0��״̬��ʵ�ǲ��Ϸ���,������Ҳ����Ӱ����
                    //��Ϊ���Ϸ�״̬�ۼӼ�ֵ����Ҳ�Ͳ������ŵ�
                    //ʵ�������ʼ��Ϊ0������ �ϸ��������������
                    //������memset(dp,-1,sizeof(dp)) dp[0][0..v]=0,�ж�dp[i][j-w]!=-1��dp[i-1][j-p-w]!=-1
                    if(j>=p+w)//dp[i-1][j-p-w]>=0���Բ��ж� ��Ϊ�������dp[i-1][j-p-w]���Ϸ��ۼ� ��ֵ��ȻҲ��������
                        dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                }
            }
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 249ms ���鱳����ǰ������ȡһ����Ʒ�뵱ǰ��һ����ƷҲ��ѡ �Ƚ���ȡ����ֵ
//�����ӷ���,ÿ�����ƷΪ���ӡ���Ʒ1����Ʒ2��..��Ʒ10
//�ȿ��ǹ�������,�ٿ����������ѹ����״̬�� ��ʣ�µ���Ʒ�������01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=0;i<=v;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //�������� ��ǮΪp,��ֵΪ0
            for(int j=v;j>=p;j--)
                dp[i][j]=max(dp[i][j],dp[i-1][j-p]);
            //���������ӵĻ����� �����ʣ�µ���Ʒ 01����
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
            }
            //�Ƚ�ǰi�����Ž� ��ѡȡ��i����Ʒ(dp[i][j])�Ͳ�ѡȡ��i����Ʒ(ǰi-1����Ʒdp[i-1][j])״̬�Ƚ� ѡȡ����ֵ
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 171ms ���鱳����ǰ������ȡһ����Ʒ�뵱ǰ��һ����ƷҲ��ѡ �Ƚ���ȡ����ֵ
//���ù��������Ż� 2������һ������ֻ��¼ǰi-1��״̬tp,��һ�������¼ǰi��״̬dp
//�����ӷ���,ÿ�����ƷΪ���ӡ���Ʒ1����Ʒ2��..��Ʒ10
//�ȿ��ǹ�������,�ٿ����������ѹ����״̬�� ��ʣ�µ���Ʒ�������01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

//tp[j]����ǰi-1���״̬
//dp[j]����ǰi���״̬
int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //��ǰi-1������Ž⸳ֵ��tp
            for(int j=0;j<=v;j++)
                tp[j]=dp[j];
            //ǰi���״̬��ʼ��Ϊ-INF
            memset(dp,-0x3f,sizeof(dp));
            //��������
            for(int j=v;j>=p;j--)
                dp[j]=max(dp[j],tp[j-p]);
            //���������ӵĻ����� �����ʣ�µ���Ʒ 01����
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)
                    dp[j]=max(dp[j],dp[j-w]+val);
            }
            //�Ƚ�ǰi�����Ž� ��ѡȡ��i����Ʒ(dp[j])�Ͳ�ѡȡ��i����Ʒ(ǰi-1����Ʒtp[j])״̬�Ƚ� ѡȡ����ֵ
            for(int j=0;j<=v;j++)
                dp[j]=max(dp[j],tp[j]);
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 561ms ���鱳�� ÿ����Ʒ����ѡһ��,ÿ����Ʒ����ѡȡ��� dfs����ö��+��֦
//����֦�϶���TLE,��Ϊÿ����Ʒ�������ĸ��Ӷ����ɴ� 2^10=1024 ���鱳�����Ӷ�ΪO(nv*1024)=5*10^6*10^3=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

void dfs(int i,int k,int tw,int tv){
    if(k == num+1){
        //��֦ �����i��֮ǰѡȡ����Ʒ������ ������Ե�ǰ���,����������ڵ�ǰ������
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
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            a[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++)
                scanf("%d%d",&w[k],&val[k]);
            //����������i����Ʒ�Ŀ���ѡȡ���
            dfs(i,1,p,0);//��i������Ҫ�� ��Ʒ������������,���Ӳ�������ֵ
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
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//TLE ���鱳�� ÿ����Ʒ����ѡһ��,������ö��ÿ����Ʒѡȡ�Ŀ��ܵ�����Ϊ��ǰ���������Ʒ ����+(���ܵĵ�ǰ����Ʒ)
//ÿ����Ʒ�������ĸ��Ӷ����ɴ� 2^10=1024 ���鱳�����Ӷ�ΪO(nv*1024)=5*10^6*10^3=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            a[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++)
                scanf("%d%d",&w[k],&val[k]);
            int k=(1<<num)-1;
            for(int j=1;j<=k;j++){
                int tp=j,cnt=1;
                Node goods=Node(0,0);
                while(tp){
                    if(tp & 1){
                        goods.w+=w[cnt];
                        goods.val+=val[cnt];
                    }
                    cnt++;
                    tp>>=1;
                }
                goods.w+=p;
                a[i].push_back(goods);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=v;j>=1;j--){
                for(Node & k :  a[i]){
                    if(j>=k.w)
                        dp[j]=max(dp[j],dp[j-k.w]+k.val);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/
