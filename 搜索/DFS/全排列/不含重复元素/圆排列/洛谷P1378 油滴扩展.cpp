/*
����:��һ�������ο���������n������ĵ㣬�������κ�һ��
���Ϸ�һ����С���͵Σ���ô����͵λ�һֱ��չ��ֱ���Ӵ�����
���͵λ��߿��ӵı߽硣�����һ���͵���չ��ϲ��ܷ�����һ���͵Ρ�
��ôӦ�ð���������˳������n�����Ϸ����͵Σ�����ʹ������Ϻ���
���͵�ռ�ݵ����������أ�����ͬ���͵β����໥�ںϣ���
�����������κ���ʣ�����С�ռ䣨������������������
n<=6.
����:https://www.luogu.com.cn/problem/P1378
˼·:��Ҫö�ٷ����͵ε����п���˳��,��ȡ����˳�����͵�������չ���.
ÿ�ο�ʼ��չĳ���͵�ʱ��Ҫ����������չ�����뾶,������Ҫ�;����
���ԽǶ���Ƚ�,��ȡ��С��ǽ�����а뾶,��λ����֮ǰ�Ѿ���չ���͵�
��Բ����С���а뾶,���㷽ʽΪ������Բ�ľ���,��ȥ֮ǰ��չԲ�İ뾶,����
��ǰԲ����ʱ�İ뾶.
Ҫע��:�п���֮ǰ��չԲ��Բ�ľ���ҪС��֮ǰԲ�뾶,��ʱ��ǰԲ����ȫ��
������֮ǰ���Ѿ���չԲ�ڵ�,���Ե�ǰԲ�뾶Ϊ0.
*/
//ac 38ms dfsö��ȫ����
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 10
#define Pi 3.141592653
using namespace std;

//����Ϊx1,y1,x2,y2 ��Ⱦͻᱨint y1������������Ϊ��ͬ����ķ��� �������,��֪��ԭ��
int n,xx1,yy1,xx2,yy2,x[N],y[N],vis[N];
double r[N],ans;

double calR(int i){
    double R,d;
    R=min(fabs(xx1-x[i]),fabs(yy1-y[i]));
    R=min(R,min(fabs(xx2-x[i]),fabs(yy2-y[i])));
    for(int j=1;j<=n;j++){
        if(vis[j] && j!=i){
            d=sqrt(fabs(x[i]-x[j])*fabs(x[i]-x[j])+fabs(y[i]-y[j])*fabs(y[i]-y[j]));
            /*
            �п���֮ǰ��չԲ��Բ�ľ���ҪС��֮ǰԲ�뾶,��ʱ��ǰԲ����ȫ��
            ������֮ǰ���Ѿ���չԲ�ڵ�,���Ե�ǰԲ�뾶Ϊ0.
            */
            R=min(R,max(d-r[j],0.0));
        }
    }
    return R;
}

void dfs(int k){
    if(k == n+1){
        double sum=0;
        for(int i=1;i<=n;i++)
            sum+=Pi*r[i]*r[i];
        if(sum>ans)
            ans=sum;
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            r[i]=calR(i);//ע�����ﲻ��r[k]=calR(i),���Ǹ���ö�����е�˳�� ȷ����i���͵εİ뾶.����calR(i)ʱ ��֮ǰԲ�ԱȰ뾶
            dfs(k+1);
            vis[i]=0;
        }
    }
}

int main(){
    int s;
    scanf("%d",&n);
    scanf("%d%d",&xx1,&yy1);
    scanf("%d%d",&xx2,&yy2);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    dfs(1);
    s=abs(xx1-xx2)*abs(yy1-yy2);
    printf("%.0f",round(s-ans));
    return 0;
}

/*
һ���������
input
3
-98 5 30 30
-42 11
-51 17
-11 22

output
2547

�����ǰ��չԲ�뾶����0�Ա�,��ЩԲ����չ���˵�,R=min(R,max(d-r[j],0.0));
������Ϊ
2542(wa)
*/
