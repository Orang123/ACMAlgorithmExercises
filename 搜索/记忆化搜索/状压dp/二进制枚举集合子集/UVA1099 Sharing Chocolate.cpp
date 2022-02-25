/*
����:
����һ�鳤Ϊx,��Ϊy�ľ����ɿ�����ÿ�β���������һ��ֱ�߰�һ���ɿ���
�и�����鳤���Ϊ�������ɿ�����һ�β���ͬʱ�и����ɿ�������
��:�Ƿ���Ծ������ɴβ����õ�n������ֱ�Ϊ a1, a2,...,an���ɿ�����
n<=15.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3540
˼·:nֻ��15,״ѹdp.��Ҫ�õ�������ö�ټ���״̬���Ӽ�.
��Ҫ���ǽ���ʼ��r*c�ľ��ηָ�,��������ָܷ��a[1..n]�е�����һ��,�����ַָ���ǿ��е�.
�����ٷָ�����б�Ȼ�����ظ���״̬,�����ص�������.
sum[s]��ʾ��ǰ��ƴ���ɿ�����״̬Ϊsʵ�ʵ����.
dp[x][s]=0/1��ʾ�����ɿ���ƴ�ɵ�״̬Ϊs,��̱�Ϊx���״̬�Ƿ�Ϸ�.
*/
//ac 230ms ���仯����
//���Ӷ�(32768*100=3276800)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
using namespace std;

int n,r,c,a[N],sum[1<<N],dp[M][1<<N];

int bitcount(int val){
    return val == 0?0:bitcount(val>>1)+(val&1);
}

int dfs(int x,int s){
    if(dp[x][s] != -1)
        return dp[x][s];
    if(bitcount(s) == 1)//��ʼ״̬Ϊ ��ǰ�����ɿ���ֻ��a[1..n]�е���һ������,��˵����ǰ���ֲ���ǺϷ���
        return dp[x][s]=1;
    int y=sum[s]/x;//��ǰ�����ɿ����Ŀ�
    //ö��s���ϵ��Ӽ�,��:ö�ٵ�ǰ�ɿ����Ĳ�ַ����ļ���
    //ÿ��s0-1,s0-1 ��Ķ�����λ��1�п�����s��û�е�,�����Ҫ��s��λ��,��������û�е�1,���Բ�����,��������s���Ӽ�
    //ע���ʼ״̬Ҳ����Ҫ��λ��s,s0=(s-1)&s,s����(n<<1)-1ʱ,������λ����1,��ʱ����λ��sҲ��s���Ӽ�
    for(int s0=(s-1)&s;s0;s0=(s0-1)&s){
        //���ų�x�и�,sum[s0]%x==0��ʾ�Ϸ�
        //dfs(min(x,sum[s0]/x),s0)��ʾ�ָ�ɵĵ�һ����,���Ϊs0,Ϊ�˱�ʾΨһ��dp[x][s]��״̬,��ȡ��С��min(x,sum[s0]/x)
        //dfs(min(x,sum[s0^s]/x),s0^s)��ʾ�ָ�ɵĵڶ�����,���Ϊs-s0=s0^s.
        if(!(sum[s0]%x) && dfs(min(x,sum[s0]/x),s0) && dfs(min(x,sum[s0^s]/x),s0^s))
            return dp[x][s]=1;
        //���ſ�y�и�,sum[s0]%y==0��ʾ�Ϸ�
        if(!(sum[s0]%y) && dfs(min(y,sum[s0]/y),s0) && dfs(min(y,sum[s0^s]/y),s0^s))
            return dp[x][s]=1;
    }
    return dp[x][s]=0;//����s���Ӽ������Ϸ�,��dp[x][s]���Ϸ�.
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        memset(sum,0,sizeof(sum));
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&r,&c);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(i & 1<<j)
                    sum[i]+=a[j];
            }
        }
        if(sum[(1<<n)-1]!=r*c)//n���ɿ���ƴ�ɵ��������պù��ɳ�ʼr*c�ľ���
            printf("Case %d: No\n",cas);
        else{
            if(dfs(r,(1<<n)-1))
                printf("Case %d: Yes\n",cas);
            else
                printf("Case %d: No\n",cas);
        }
    }
    return 0;
}
