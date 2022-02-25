/*
����:���ر���ģ����.n<=1000,v<=1000
���ö������Ż���TLE.
����:https://www.acwing.com/problem/content/description/5/
˼·:������ö�ٵ�i����Ʒ��Ϸ���.
*/
//ac 238ms �ر����������Ż�01��������
//���Ӷ�O(��log(num[i])*v) 1000*log(2000)*2000=11000*2000=2.2*10^7
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k<<=1){//ö�ٵ�i����Ʒ���ܵĶ��������
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}

/*
//ac 124ms �������Ż� �ȱ����Ž��汾���ŵ����� �����ر���ת��Ϊ �������Ż���01����+��ȫ���������
//���ｫ�����Ž��ж�����ȫ�������ж���չΪ����������,��:v-num[i]*w[i]<w[i],��i����Ʒ�ܾ����ܶ�
//��װ�뵽����Ϊv�ı���,ֱ��������װ��һ��Ϊֹ.
//���Ƕ��ر������Ż����⸴�ӶȽ����ڵ��������Ż��İ汾 �����汳���Ž��汾�ĸ��Ӷȸ���
//���Ӷȱȱ�׼�Ķ������Ż����ʱ���O(��log(num[i])*v) ����Ҫ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        if(v-num[i]*w[i]<w[i]){//��i����Ʒ������Ʒ����Ͳ�С�ڱ����ݻ�vʱ ��ȫ����
            for(int j=w[i];j<=v;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        else{//���� �������Ż� 01����
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//ac 170ms �������Ż� �����Ž��汾 �����ر���ת��Ϊ �������Ż���01����+��ȫ���������
//���Ƕ��ر������Ż����⸴�ӶȽ����ڵ��������Ż��İ汾
//���Ӷȱȱ�׼�Ķ������Ż����ʱ���O(��log(num[i])*v) ����Ҫ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        if(num[i]*w[i]>=v){//��i����Ʒ������Ʒ����Ͳ�С�ڱ����ݻ�vʱ ��ȫ����
            for(int j=w[i];j<=v;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        else{//���� �������Ż� 01����
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//ac 735ms ���ر���ת��01�������� ����������Ϸ��� ������Ʒ������ö�ٴ���
//��ǰ������i����Ʒ�����������ٷ������һ����Ŀ��1����Ʒ����,���һ�������ʣ��,�������Ʒ��������
//���Ӷ��ڶ������Ż�O(��log(num[i])*v)������01����O(��num[i]*v)֮��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k++){
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/

/*
//TLE ���ر�������01�������� ��ÿ�����ܱ�������j������ö��[1,num[i]]����Ʒ�����µ���Ʒ���뱳��
//���Ӷ�O(��num[i]*v) ���ǰ�������Ʒ������һ����Ʒ01�����ĸ��Ӷ�,��������ĸ��ӶȻ��Ǳ����ҪСһ���
//���Ӷ�O(��num[i]*v) 1000*2000*2000=4*10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int tw,tv;
    //���Ӷ�O(��num[i]*v)
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--){
            for(int k=1;k<=num[i];k++){
                tw=w[i]*k;
                if(j<tw) break;//�����ǰ�����Ѿ�װ���������Ŀ�µ���Ʒ �ͽ���
                tv=val[i]*k;
                dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/

/*
//TLE ���ر�������01�������� ֱ��ת���ɡ�num[i]����Ʒ����01����
//���Ӷ�O(��num[i]*v) 1000*2000*2000=4*10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 2000100
#define M 2100
using namespace std;

int n,v,w[N],val[N],dp[M];

int main(){
    int a,b,m,id;
    id=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
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
    return 0;
}
*/


