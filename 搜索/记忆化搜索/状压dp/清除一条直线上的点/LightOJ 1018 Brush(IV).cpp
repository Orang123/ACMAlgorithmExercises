/*
����:ժ������
����ƽ������N���㣬������һ�ѿ������κη����ߵ�ˢ�ӿ���ˢȥ��Щ�㣬
��������Ҫˢ��������ֱ�߿��԰ѵ�ˢ�ꣿ
n<=16.
����:http://www.lightoj.com/volume_showproblem.php?problem=1018
˼·:����ö�ٳ���������ȷ����ֱ����������,Ȼ��������ʣ�಻�ڵ�ǰ
ֱ���ϵĵ㳢������,��Ϊn<=16,���Կ���δ������ֱ�ߵĵ�״̬�ı�ʶ��Ҫ�ö�����.
����ֱ��ö�����ӵ�Ĺ�����,ʣ��δ���ӵĵ������ظ���״̬.��˼��仯����.
s[i][j]��ʾi����j�����ӵ�ֱ�߲�������ֱ���ϵĵ�Ķ�����λ״̬.
dp[sta]=k��ʾsta�л�δ��ֱ�����ӵĵ� ������Ҫ�õ�ֱ������������ȫ�������еĵ�.
��Ҫע����� ��Ϊ���е㶼Ҫ��������,ʵ��Ӱ�����Ž������Ҫ��������ÿһ����ú�
������Щ��ϵĵ�����ֱ��,��ö�����ӵ��˳���޹�,��˼��仯����ʱֻ���ҵ���һ��
��δ���ӵĵ㼴��.���������û��Ҫ�����е㶼��������,����Ҫ����ö��ֱ�����ӵ�һ��
�����ӵ�˳��,���Ӱ����Ž�.��UVA11008 Antimatter Ray Clearcutting.
*/
//ac 135ms ���仯����+״ѹ
//s[i][j]��ʾi����j�����ӵ�ֱ�߲�������ֱ���ϵĵ�Ķ�����λ״̬.
//dp[sta]=k��ʾsta�л�δ��ֱ�����ӵĵ� ������Ҫ�õ�ֱ������������ȫ�������еĵ�.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define INF 0x3f3f3f3f
using namespace std;

int n,x[N],y[N],dp[1<<16],s[N][N];

int judge(int x1,int y1,int x2,int y2){
    return x1*y2 == x2*y1;
}

int bitCount(int val){
    int cnt=0;
    while(val){
        if(val & 1)
            cnt++;
        val>>=1;
    }
    return cnt;
}

int dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    int k=bitCount(sta);//��δ��ֱ�����ӵĵ�ĸ���
    if(!k)
        return dp[sta]=0;
    if(k<=2)//�п��ܸպ�ֻʣ��һ����,��Ҫ���� ��1��ֱ�� ��������,2����Ҳ��Ҫ1��ֱ������.
        return dp[sta]=1;
    for(int i=0;i<n;i++){//ֻ���ҵ���һ����δ���ӵĵ㼴��
        if(sta & 1<<i){
            for(int j=i+1;j<n;j++){
                if(sta & 1<<j)
                    dp[sta]=min(dp[sta],dfs(sta & s[i][j])+1);
            }
            //���ﲻ�����ᳬʱ,��Ϊ���е㶼��Ҫ��ֱ�����ӵ�,ʵ��Ӱ������ ��Ҫ����
            //����ÿһ����ú�������Щ��ϵĵ�����ֱ��,��ö�����ӵ��˳���޹�
            break;
        }
    }
    return dp[sta];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d%d",&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                s[i][j]=0;
                for(int k=0;k<n;k++){
                    if(!judge(x[i]-x[k],y[i]-y[k],x[j]-x[k],y[j]-y[k]))//�ж�(i,k) (j,k)��б���Ƿ���ͬ,����ͬ������һ��ֱ����
                        s[i][j]|=1<<k;
                }
            }
        }
        printf("Case %d: %d\n",cas,dfs((1<<n)-1));//��ʼ ���е㶼δ����
    }
    return 0;
}
