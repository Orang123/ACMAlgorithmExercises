/*
����:����������n��������n��������꣬ÿ����֮��ľ��������ǵ������������16��
���ҳ�һ�����������·����ʹ��ÿ���㾭���ҽ�����1�Ρ�������·�������
�����ʽ����������
2<=n<=8.
����:https://www.luogu.com.cn/problem/UVA216
˼·:ö�ٳ�����·������������,�����·�����ȱȽϼ�¼��С����.
*/
//ac 10ms stl next_permutationö��ȫ����
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 10
#define INF 1e40
using namespace std;

int n,a[N],b[N],x[N],y[N];
double ans,dis[N][N];

double getDis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+16;
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        ans=INF;
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++)
                dis[i][j]=dis[j][i]=getDis(i,j);
        }
        for(int i=1;i<=n;i++)
            a[i]=i;
        do{
            double res=0;
            for(int i=1;i<n;i++)
                //res+=dis[a[i]][a[i+1]];
                res+=getDis(a[i],a[i+1]);
            if(res<ans){
                ans=res;
                memcpy(b,a,sizeof(a));
            }
        }while(next_permutation(a+1,a+1+n));
        printf("**********************************************************\n");
        printf("Network #%d\n",cas);
        for(int i=1;i<n;i++)
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",x[b[i]],y[b[i]],x[b[i+1]],y[b[i+1]],getDis(b[i],b[i+1]));
        printf("Number of feet of cable required is %.2f.\n",ans);
    }
    return 0;
}
