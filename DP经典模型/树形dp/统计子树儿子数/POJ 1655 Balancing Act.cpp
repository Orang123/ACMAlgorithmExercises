#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
/*
����:һ�������ҵ�һ����,�����е����������������ڵ����١�ʵ�ʾ�������������.
����:http://poj.org/problem?id=1655
dp[u]������uΪ���ڵ�������Ķ�����
*/

vector <int> map[20005];
int dp[20005],N,min_n,min_bal;
bool visit[20005];
void dfs(int root){
    int son,balance=-1;
    for(int i=0;i<map[root].size();i++){
        son=map[root][i];
        if(!visit[son]){
            visit[son]=true;
            dfs(son);//����������ȵ�ԭ������ɾ��Ҷ�ӽڵ������ƽ���ֵ
            dp[root]+=dp[son]+1;//��rootΪ�������������Ľڵ��ۼӺ�,Ϊ�������root��ǰ�ĸ��ڵ����׼��
            balance=max(balance,dp[son]+1);//�����rootΪ���ڵ�������нڵ�������Ǹ�������ƽ��
        }
    }
    balance=max(balance,N-dp[root]-1);//����������֮ǰ���ڵ���ѡ��ϴ����Ϊroot��ƽ��
    if(balance<min_bal||(balance==min_bal&&root<min_n)){//�����С��ƽ��,��ƽ����ȵ������ѡ��ڵ��Ž�С��
        min_n=root;
        min_bal=balance;
    }
}
int main(){
    int t,a,b;
    scanf("%d",&t);
    while(t--){
        memset(dp,0,sizeof(dp));
        memset(visit,false,sizeof(visit));
        min_bal=INF;
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            map[i].clear();
        for(int i=1;i<=N-1;i++){
            scanf("%d%d",&a,&b);
            map[a].push_back(b);//����������,Ϊ���ܽ���������ÿ���ڵ㶼��ȱ�������������Ϊ�˱���������ȵݹ飬������visit���
            map[b].push_back(a);
        }
        visit[1]=true;//������ĸ��ڵ㿪ʼ�������ǿ��Եģ����ǲ�֪�����м����ڵ㣬����ѡ��ӽڵ�1��ʼ����
        dfs(1);
        printf("%d %d\n",min_n,min_bal);
    }
    return 0;
}
