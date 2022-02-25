/*
����:ժ������
����n��k����n�ֻ�ѧҩ�����ͺ���1~n��Ȼ�����n * n�д�����Ӧ������
��ѧҩ����Ӧ����������Լ��ͷŵ�������Ȼ�����k���Թܣ�ÿ���Թ���
�ж�Ӧ��ҩ����Ҫ��m��ҩ����Ӧ�ϳ�һ�֣���Ҫ��Ӧ��ҩ�������࣬
Ҫ��Ӧ��ɢ�����������١�
ע�⣺i��j��Ӧ������j��i��Ӧ��ͬ����Ӧ�������ȣ�ÿ�������/������
1<=n<=6,2<=k<=10.
����:https://www.luogu.com.cn/problem/UVA10604
˼·:���仯����,ö�ٷ�Ӧ��˳��,״̬��ʾ��n�ֻ�ѧҩ��ʣ�������.
2��״̬��ʾ��:
1.dp[11][11][11][11][11][11]=10^6=1000000 6�ֻ�ѧҩ��ʣ���������ܲ�������С����
2.��Ϊÿ�ֻ�ѧҩ�����10��,������11��������ʾ״̬,dp[10*11^5]=1610510
n�ֻ�ѧҩ��ʣ���������ܲ�������С����
*/
//ac 80ms ���仯����
//dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]] 6�ֻ�ѧҩ��ʣ���������ܲ�������С����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define INF 0x3f3f3f3f
using namespace std;

int n,k,type[N][N],heat[N][N],cnt[N],dp[11][11][11][11][11][11];

int judge(){
    int num1=0,num2=0;
    for(int i=1;i<=n;i++){
        if(cnt[i] == 1)
            num1++;//����Ϊ1��ҩ��
        else if(!cnt[i])
            num2++;//����Ϊ0��ҩ��
    }
    if(num1 == 1 && num2 == n-1)//����״̬�� ֻʣ��һ��ҩ������Ϊ1,���һ�鷴Ӧ��Ȼ������һ���µ�ҩ��,����ҩ��������Ϊ0
        return 1;
    return 0;
}

int dfs(){
    int &res=dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]];
    if(res!=INF)
        return res;
    if(judge())
        return res=0;
    for(int i=1;i<=n;i++){
        if(!cnt[i])
            continue;
        cnt[i]--;//��i�ַ�Ӧ����������1
        for(int j=1;j<=n;j++){
            if(!cnt[j])
                continue;
            cnt[j]--;//��j�ַ�Ӧ����������1
            cnt[type[i][j]]++;//i��j��Ӧ�������µ�����type[i][j]
            res=min(res,dfs()+heat[i][j]);
            cnt[j]++;//���ݺ�ԭ
            cnt[type[i][j]]--;
        }
        cnt[i]++;
    }
    return res;
}

int main(){
    int T,x;
    char str[3];
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d%d",&type[i][j],&heat[i][j]);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d",&x);
            cnt[x]++;
        }
        scanf("%s",str);
        printf("%d\n",dfs());
    }
    return 0;
}


/*
//ac 100ms 11��������ʾ״̬
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 7
#define M 2000000//1610510 11^5*10=1610510(�������״̬)
#define INF 0x3f3f3f3f
using namespace std;

int n,k,type[N][N],heat[N][N],cnt[N],dp[M];

int judge(){
    int num1=0,num2=0,sum=0;
    for(int i=1;i<=n;i++){
        if(cnt[i] == 1)
            num1++;
        else if(!cnt[i])
            num2++;
        sum=sum*11+cnt[i];//N�ֻ�ѧ�����������ɵ�11������(ÿ�ֻ�ѧ�������10��)
    }
    if(num1 == 1 && num2 == n-1)
        return 0;
    return sum;
}

int dfs(){
    int sta=judge();
    int &res=dp[sta];
    if(res!=INF)
        return res;
    if(!sta)
    	return res=0;
    for(int i=1;i<=n;i++){
        if(!cnt[i])
            continue;
        cnt[i]--;
        for(int j=1;j<=n;j++){
            if(!cnt[j])
                continue;
            cnt[j]--;
            cnt[type[i][j]]++;
            res=min(res,dfs()+heat[i][j]);
            cnt[j]++;
            cnt[type[i][j]]--;
        }
        cnt[i]++;
    }
    return res;
}

int main(){
    int T,x;
    char str[3];
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d%d",&type[i][j],&heat[i][j]);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d",&x);
            cnt[x]++;
        }
        scanf("%s",str);
        printf("%d\n",dfs());
    }
    return 0;
}
*/
