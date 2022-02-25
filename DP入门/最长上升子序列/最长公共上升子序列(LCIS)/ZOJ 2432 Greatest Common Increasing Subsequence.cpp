/*
����:��a�����b��������������������(LCIS).
���鳤��<=500.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365931
˼·:O(n^2)��ȡLCIS�����
dp[i][j]Ϊ����aȡǰi��Ԫ��ʱ(��Ϊa[1 ~ i]),�ҵ���b����������j��βʱ,���ǵ�����������г���.
dp[i][j]>=dp[i-1][j].
path[i][j].i path[i][j].j �ֱ��¼��aȡǰi��Ԫ��ʱ,��b����������j��βʱ,��LCIS��һ״̬��¼��
��a��ǰpath[i][j].i��Ԫ��,b������path[i][j].j��β
���������ΪҪ�������,����ֻ�ܶ�ά����O(n^2)ʵ��.
*/
//ac 38ms LCIS ��ά����ʵ�� O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;
struct Node{
    int i,j;
}path[N][N];
vector<int> res;

int main(){
    int T,mx,ti,tj,id;
    scanf("%d",&T);
    while(T--){
        res.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;
            ti=tj=0;//����Ҫ��ʼ��Ϊ0,�п��ܲ�������������,��һ״̬����dp[0][0] �����������ʱ��ѭ��
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                path[i][j].i=i-1;//��ʼ״ֱ̬�Ӽ̳���һ״̬
                path[i][j].j=j;
                if(a[i]>b[j] && mx<dp[i-1][j]){
                    mx=dp[i-1][j];
                    ti=i-1,tj=j;
                }
                else if(a[i] == b[j]){
                    dp[i][j]=mx+1;
                    path[i][j].i=ti;
                    path[i][j].j=tj;
                }
            }
        }
        ans=0;
        for(int i=1;i<=m;i++){
            if(ans<dp[n][i]){
                ans=dp[n][i];
                id=i;
            }
        }
        printf("%d\n",ans);
        int ni=n,nj=id;
        while(dp[ni][nj]!=0){
            int tpi,tpj;
            tpi=path[ni][nj].i,tpj=path[ni][nj].j;
            if(dp[ni][nj]!=dp[tpi][tpj])//�п���i����,��ʵ�� LCIS�����ǲ����,��ʱ��û���µ�Ԫ�ؼ���
                res.push_back(nj);
            ni=tpi,nj=tpj;
        }
        for(int i=res.size()-1;i>=0;i--)
            printf("%d ",b[res[i]]);
        if(T)
            printf("\n");
    }
    return 0;
}
