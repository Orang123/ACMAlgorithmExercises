/*
����:��n����Ʒ��һ������Ϊv�ı���.��i����Ʒ�����num[i]������,
ÿ���ķѵĿռ���w[i],��ֵ��val[i].��⽫��Щ��Ʒװ�뱳����ʹ��
Щ��Ʒ�ĺķѵĿռ��ܺͲ�������������,�Ҽ�ֵ�ܺ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2191
˼·:
*/

//ac 0ms ���ر����������Ż�01��������
//���Ӷ�O(��log(num[i])*v)
/*
�������Ż�����:
����i����Ʒ�ֳ����ɼ�01�����е���Ʒ,����ÿ����Ʒ��һ��ϵ��.
�����Ʒ�ķ��úͼ�ֵ����ԭ���ķ��úͼ�ֵ�������ϵ������Щϵ���ֱ�Ϊ
2^0=1,2^1,2^2 ,2^(k-1);nmu[i]-2^k+1,��k������num[i]-2^k+1>0���������.
num[i]=13,����Ӧ��k = 3,�������ȡ13������ƷӦ���ֳ�ϵ���ֱ�Ϊ1,2,4,6��
�ļ���Ʒ.
�ֳɵ��⼸����Ʒ��ϵ����Ϊnum[i],����������ȡ����num[i]���ĵ�i����Ʒ.����
���ַ���Ҳ�ܱ�֤����[0,num[i]]���ÿһ������,�����������ɸ�ϵ���ĺͱ�ʾ.
�����㷨��ȷ�Ե�֤�����Է�[0,2^(k-1)]��[2^k,num[i]]�������ֱ����۵ó�.
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int m,tw,tv;
        //���Ӷ�O(��log(num[i])*v)
        for(int i=1;i<=n;i++){
            m=num[i];
            //����ȫ����һ�������i����Ʒ���������ڵڶ���ѭ�������������ڵ�����ѭ��
            //ֻ���������ܱ�֤�϶���Ŀ�ĵ�i����Ʒ���������ڽϵ���Ŀ�ĵ�i����Ʒ�������ۼ�
            //���ܴﵽ��i����Ʒ�������޵���Ʒ�������뱳��,����ߵ�ѭ��˳��ʵ��װ��ĵ�i����Ʒ�������ܲ��ﲻ����Ʒ����
            for(int k=1;m>0;k<<=1){//ö�ٵ�i����Ʒ���ܵĶ��������
                //������Ǵ���ϵĽǶȼӵ�,��֮����1��2��4��8..��������
                //������������п��ܵļ��� ֱ�������Ʒ�ļ����ﵽ����Ϊֹ
                //��֤֮��01�������ڵ�i����Ʒ�ļ�������ۼ�Ҳ���ᳬ����i����Ʒԭ����������
                m-=k;
                //�����ǵ�k���ƵĽ������m��,ֻȡm����ʣ�µĲ�����Ϊ����
                if(m<0) k+=m;
                tw=w[i]*k;
                tv=val[i]*k;
                //��i����Ʒ�����Ƽ�����ϵ�����Ϊһ����Ʒ����01����
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}

/*
//ac 0ms �������Ż� �����Ž��汾 �����ر���ת��Ϊ �������Ż���01����+��ȫ����
//���Ƕ��ر������Ż����⸴�ӶȽ����ڵ��������Ż��İ汾
//���Ӷȱȱ�׼�Ķ������Ż����ʱ���O(��log(num[i])*v) ����Ҫ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

void ZeroOnePack(int tw,int tv){
    for(int j=v;j>=tw;j--)
        dp[j]=max(dp[j],dp[j-tw]+tv);
}

void CompletePack(int tw,int tv){
    for(int j=tw;j<=v;j++)
        dp[j]=max(dp[j],dp[j-tw]+tv);
}

void MultiplePack(int i){
    //����i����Ʒ ������Ʒ������ܺͲ����ڱ���������ʱ,
    //������Ϊ�ڱ�������v��ǰ����,��i����Ʒ���Է������޸�,��:��i����Ʒ����������.
    //����ת��Ϊ��ȫ��������,����num[i]*w[i]<v,���i����Ʒ��������������������������v,��Ҫ����������������
    //ʵ���������������չ�ظ�Ϊ��Ϊ:v-num[i]*w[i]<w[i],Ҳ���ǽ���i����Ʒȫ����������Ϊv�ı���,������ʣ��
    //�������ȵ�i����Ʒ�����С,Ҳ���ǿ��Ծ����ܶ��װ��i����Ʒ,װ��������װΪֹ.������ȷ�Ծ����ڵ�ʹ�ñ���
    //��������ת��ʱ�������װ��ĵ�i����Ʒ�����϶����ᳬ����i����Ʒ����������.
    if(num[i]*w[i]>=v)//v-num[i]*w[i]<w[i]�������Ҳ�ǿ��Ե�
        CompletePack(w[i],val[i]);
    else{//����Ͳ��ö������Ż���01����ȥ���
        int tw,tv;
        for(int k=1;num[i]>0;k<<=1){
            num[i]-=k;
            if(num[i]<0)
                k+=num[i];
            tw=k*w[i];
            tv=k*val[i];
            ZeroOnePack(tw,tv);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        for(int i=1;i<=n;i++)//�ж�ÿ����Ʒ ���ö��ر�������01�������
            MultiplePack(i);
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms ���ر�������01�������� ��ÿ�����ܱ�������j������ö��[1,num[i]]����Ʒ�����µ���Ʒ���뱳��
//���Ӷ�O(��num[i]*v) ���ǰ�������Ʒ������һ����Ʒ01�����ĸ��Ӷ�,��������ĸ��ӶȻ��Ǳ����ҪСһ���
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int tw,tv;
        //���Ӷ�O(��num[i]*v)
        for(int i=1;i<=n;i++){
            //���ﱳ�����������ڵڶ���ѭ��,��Ʒ���������ڵ�����ѭ��,
            //ö��ÿ�����������³��Է������п��ܵĵ�i����Ʒ�ĸ���,ע���ʱdp[j-tw]��Զ��ǰi-1����Ʒ�����Ž�,��û�е�i����Ʒ��
            //��������������ڵ�����ѭ��,��Ʒ���������ڵڶ���ѭ��,��ô�������Ʒ������Ͼͻ��ۼ���ǰ����Ʒ���������
            //��������Ʒ������num[i]����,��������ʵ�ʵ�i����Ʒ���˳���num[i]������,��wa
            for(int j=v;j>=w[i];j--){
                for(int k=1;k<=num[i];k++){//k<=num[i] && k*w[i]<=j
                    tw=w[i]*k;
                    if(j<tw) break;//�����ǰ�����Ѿ�װ���������Ŀ�µ���Ʒ �ͽ���
                    tv=val[i]*k;
                    dp[j]=max(dp[j],dp[j-tw]+tv);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms ���ر���ת��01�������� ����������Ϸ��� ������Ʒ������ö�ٴ���
//��ǰ������i����Ʒ�����������ٷ������һ����Ŀ��1����Ʒ����,���һ�������ʣ��,�������Ʒ��������
//���Ӷ��ڶ������Ż�O(��log(num[i])*v)������01����O(��num[i]*v)֮��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int m,tw,tv;
        //���Ӷ��ڶ������Ż�O(��log(num[i])*v)������01����O(��num[i]*v)֮��
        for(int i=1;i<=n;i++){
            m=num[i];
            //ÿ���µ���Ʒֻ����һ����Ʒ������1��,
            for(int k=1;m>0;k++){
                m-=k;
                //���һ����ʣ��,��˴η�����Ʒ��������һ��
                if(m<0) k+=m;
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms ���ر�������01�������� ֱ��ת���ɡ�num[i]����Ʒ����01����
//���Ӷ�O(��num[i]*v)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 110
using namespace std;

int n,v,w[N],val[N],dp[M];

int main(){
    int T,a,b,m,id;
    scanf("%d",&T);
    while(T--){
        id=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&a,&b,&m);
            while(m--){
                w[++id]=a;
                val[id]=b;
            }
        }
        //ʵ����Ʒ������id,�Ѿ�ת��Ϊһ����׼��01������
        for(int i=1;i<=id;i++){
            for(int j=v;j>=w[i];j--)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms ���ر�������01�������� ֱ��ת���ɡ�num[i]����Ʒ����01����
//���Ӷ�O(��num[i]*v)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        //ʵ����Ʒ������id,�Ѿ�ת��Ϊһ����׼��01������
        for(int i=1;i<=n;i++){
            for(int k=1;k<=num[i];k++)//����k����Ʒ���ǵ�i����Ʒ ��01����
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
ע��:����������O(nv)���ܽ���������Ʒ��������������ͼ�ֵ�����Ż���ֵ�Ķ��ر�������
*/

/*
����dfs������������ת��Ϊ01��������,���б���ö�� O(2^n)
��Ȼ����Ӧ�ö����Ʋ�ּ���ͬ����Ʒ����Ʒ��ϸ���.
*/
