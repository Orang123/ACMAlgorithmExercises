#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 46ms 01���� �����ܶ��װ��+̰������
//dp��άѭ���½� j>=max(goods[i].p,goods[i].q)
/*
����:����n����Ʒ,������Ϊm�ı���,��i����Ʒ�����Ϊp[i],��ֵΪv[i],
�����뵱ǰ��������������q[i]�ſ��Է������Ʒ��,�����ļ�ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3466
˼·:����01��������ģ�ͻ�����,�����˵�ǰ����ʣ�������������q[i]����,
���ұ���ʣ������Ҳ��С��p[i],���ܽ�����Ʒװ�뱳��.��ôʵ��ÿ������װ��
��˳��ͬ����ʣ���ݻ��Ͳ�ͬ,��ô�ͻ�Ӱ�������Ʒ��װ�����.���Ҫ������
�ȷ���p-q�ϴ��,��Ȼ���˺��汳��ʣ���ݻ�ԽС,�ͿɷŲ���ȥ��,��˿��԰���
p-q��������,����q-p��������.

�ο�����:https://blog.csdn.net/the_love_story/article/details/52179575
����1:��ǰ��01������������,dp[j] = max(dp[j],dp[j-w[i]]+v[i])��������
��i����ƷҪ��Ҫ��,��ͬʱҲ���жϵ�i����ƷҪ��Ҫ����,�������ʣ�µĿռ�����,���Ƿ�õ��ļ�ֵ�����
A��Ʒp1,q1,v1;
B��Ʒp2,q2,v2
������A,������Ҫp1+q2 (p1 == q1����£�������B,������Ҫp2+q1;
��A<B,Ӧ����A,�� q1-p1 > q2-p2;����ֵ�������,���������Ӧ�ŵ�����

�ο�����:https://blog.csdn.net/qq_21057881/article/details/49976813
����2:��̬�滮�޺�Ч��,ĳ�׶ε�״̬һ��ȷ��,��˺���̵��ݱ䲻����
��ǰ����״̬�����ߵ�Ӱ��,�򵥵�˵,���ǡ�δ�����ȥ�޹ء�,��ǰ��״̬��
��ǰ��ʷ��һ�������ܽ�,��ǰ����ʷֻ��ͨ����ǰ��״̬ȥӰ�����δ�����ݱ�.
��ô��01������ԭʼ��״̬ת�Ʒ���dp[i][j]=max(dp[i-1][j],dp[i-1][j-c[i]]+w[i]);
��ôʲôʱ����ת����,j-c[i]�ǻ���,��ôʣ�µ�Ǯ����m-(j-c[i]),��m-(j-c[i])>q[i]ʱ
��ת��,����һ����j<m+p[i]-q[i],��ô�����̬�滮�����޺�Ч�ԵĻ�,��ÿһ�θ���ת�Ƶ�
��ΧӦ�ö�Ҫ��ǰһ��ҪС,�������ܸ���ʱ����ʧ״̬,��������һ��ʼ��֪���Ƶİ�p1-q1>p2-q2����Ȼ�󱳰�����
*/

int n,m,dp[M];

struct Goods{
    int p,q,v;
    bool operator < (const Goods &x)const{
        return p-q>x.p-x.q;//�ȼ���q-p<x.q-x.p
    }
}goods[N];

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&goods[i].p,&goods[i].q,&goods[i].v);
        sort(goods+1,goods+1+n);
        for(int i=1;i<=n;i++){
            //j>=max(goods[i].p,goods[i].q)��Ϊ�½� �ɱ�֤dp[j-goods[i].p]�����±겻Ϊ��
            for(int j=m;j>=max(goods[i].p,goods[i].q);j--)
                dp[j]=max(dp[j],dp[j-goods[i].p]+goods[i].v);
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 46ms 01���� �����ܶ��װ��+����
//dp��άѭ���½� j>=goods[i].q
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,m,dp[M];

struct Goods{
    int p,q,v;
    bool operator < (const Goods &x)const{
        return q-p<x.q-x.p;
    }
}goods[N];

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&goods[i].p,&goods[i].q,&goods[i].v);
        sort(goods+1,goods+1+n);
        for(int i=1;i<=n;i++){
            //j>=goods[i].q �п���q<p,,��j=qʱ,dp[j-p] �����±�j-pΪ����,
            //���ǲ���Ӱ����,��Ϊ�ϴ��p���ޱ����Ѿ���������
            for(int j=m;j>=goods[i].q;j--)
                dp[j]=max(dp[j],dp[j-goods[i].p]+goods[i].v);
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
̰������+����ö������ TLE
*/
