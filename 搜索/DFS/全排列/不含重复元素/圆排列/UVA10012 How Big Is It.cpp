/*
����:����m��Բ�İ뾶������Բ�ų�һ�ţ�Ҫ�����ڵ��棬
��Ҫ�����ٳ�Ϊ���ٵĳ�������װ������.
m<=8.
����:https://www.luogu.com.cn/problem/UVA10012
˼·:��Ҫ����m��Բ�����п����ŷ�λ��,���ö��m��Բ
��ȫ����,��ÿ��������Բ�ľ��������˵ľ��벢����
����һ��Բ���е�λ��,��Ϊ�п���������Բ֮�����źܶ�
СԲ,����һ��Բ�����п��ܺ����ϸ�Բ�ཻ,��˵�ǰԲ��Բ��
λ���Ǿ����֮ǰ����Բ����ʱ��������ԲԲ������λ�õ����ֵ,
��Բ���е�ˮƽ������㹫ʽΪsqrt((r1+r2)^2-(r1-r2)^2)
*/
//ac 40ms ����ö��ȫ����
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 10
#define INF 1e40
using namespace std;

int m,vis[N];
//b[i]��ʾ���������е�i��ԲԲ�ľ��������˵�λ��
//a[i]��ʾ���������е�i��Բ�İ뾶
double r[N],a[N],b[N],ans;

double getDis(double r1,double r2){
    return 2*sqrt(r1*r2);//(r1+r2)^2-(r1-r2)^2 ƽ���ʽ����
}

void dfs(int k){
    if(k == m+1){
        b[1]=a[1];//��һ��Բ��Բ��λ�þ�����뾶
        for(int i=2;i<=m;i++){
            //���b[i]��ʼΪ0,�п��ܺ��ϸ�Բ����,���Ǻ�ǽ��ȴ�ཻ��Ȼ�ǲ��Ϸ���
            b[i]=a[i];//����Ҫ��ʼ��Ϊa[i],�п��ܵ�i��Բ�ǽ����������(��ʹ���ǵ�һ��Բ),��ʱ����뾶��������,��ǰ�涼�ǽ�С��Բ(��û�н���ǽ��)
            for(int j=1;j<i;j++)//ö�ٵ�i��Բ��ǰ��λ��Բ����ʱԲ�ĵ����λ�� ��֤��֮ǰ����Բ�����ཻ
                b[i]=max(b[i],b[j]+getDis(a[i],a[j]));
        }
        double res=0;
        //ͬ��;����Ҷ����е�ԲҲ��һ�������һ��Բ,���Ҫ���m��Բ�����������뾶��������,�����Ǹ�Բ���Ǻ;����Ҷ����е�
        for(int i=1;i<=m;i++){
            if(b[i]+a[i]>res)
                res=b[i]+a[i];
        }
        if(res<ans)//��¼��С�ľ��ε��ܳ���
            ans=res;
    }
    for(int i=1;i<=m;i++){
        if(!vis[i]){
            a[k]=r[i];
            vis[i]=1;
            dfs(k+1);
            vis[i]=0;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(vis,0,sizeof(vis));
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%lf",&r[i]);
        dfs(1);
        printf("%.3f\n",ans);
    }
    return 0;
}

/*
//ac 30ms stl next_permutation
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 10
#define INF 1e40
using namespace std;

int m;
double r[N],b[N],ans;

double getDis(double r1,double r2){
    return 2*sqrt(r1*r2);//(r1+r2)^2-(r1-r2)^2 ƽ���ʽ����
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%lf",&r[i]);
        sort(r+1,r+1+m);
        do{
            b[1]=r[1];
            for(int i=2;i<=m;i++){
                b[i]=r[i];
                for(int j=1;j<i;j++)
                    b[i]=max(b[i],b[j]+getDis(r[i],r[j]));
            }
            double res=0;
            for(int i=1;i<=m;i++){
                if(b[i]+r[i]>res)
                    res=b[i]+r[i];
            }
            if(res<ans)
                ans=res;
        }while(next_permutation(r+1,r+1+m));
        printf("%.3f\n",ans);
    }
    return 0;
}
*/
