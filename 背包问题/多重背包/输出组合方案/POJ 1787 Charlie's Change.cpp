/*
����:4����ֵΪ1��5��10��25��Ӳ�Ҹ���num[i]ö,������ǡ���ܴճ�p��ֵǮ��
Ӳ�ҵ�������,�����������ֵӲ�����õĸ���.
����:http://poj.org/problem?id=1787
˼·:����Ʒ�������Ƶ���ȫ����+һά�ռ��¼·��,������Ϊjʱ�����i��Ӳ��
����Ӳ�Ҹ�������ʱ,��¼pre[j]=j-val[i],��ôʵ���������ʱ����j-pre[j]����
֪��ĳһ����j״̬��������һ��Ӳ��.

ע��:���ﲻ�ܼ�¼pre[j-val[i]]=j,��Ϊͳ��ÿ��Ӳ��ѡ�˼���ʱ,j�Ǵ�0��ʼת�Ƶ�,
��������ֹ״̬�����ܱ�֤�Ǹ����Ľ��p.
*/
//ac 94ms 428K ����Ʒ�������Ƶ���ȫ����+һά�ռ��¼·��
//���������������,�����ú����2������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define M 10010
using namespace std;

//pre[j]��¼��������Ϊjʱ���Ž����һ״̬,pre[j]<j,��ֹ״̬Ϊpre[j]=0
int val[N]={0,1,5,10,25},num[N],p,pre[M],cnt[M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=4;i++){
            memset(cnt,0,sizeof(cnt));
            for(int j=val[i];j<=p;j++){
                if(dp[j-val[i]] == -1) continue;
                if(dp[j-val[i]]+1>dp[j] && cnt[j-val[i]]<num[i]){
                    dp[j]=dp[j-val[i]]+1;
                    cnt[j]=cnt[j-val[i]]+1;
                    pre[j]=j-val[i];//��¼�ϸ�״̬���õ�i��Ӳ��ʱǡ�ôճ�����ֵ
                }
            }
        }
        if(dp[p]<0){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        //ע������num[i]������ֵΪi��Ӳ�ҵĸ���,��ǰ���num[i]�ǵ�i��Ӳ�ҵĸ���
        memset(num,0,sizeof(num));
        int j=p;
        while(j){//��Ϊ��ǡ��װ��,���Գ�ʼ״̬һ���� 0��ֵ
            num[j-pre[j]]++;//j-pre[j]��������Ϊjʱ���Ӳ�Ҹ������Ž��Ƿ�����ֵΪj-pre[j]��Ӳ��,����Ӳ�Ҹ���+1
            j=pre[j];//���Ž����һ״̬
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[5],num[10],num[25]);
    }
    return 0;
}

/*
//ac 94ms 544K ����Ʒ�������Ƶ���ȫ����+��ά�����¼����·��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define M 10010
using namespace std;

//vis[i][j]=k��ʾǡ��װ����������jʱ,���õ�Ӳ�������ķ�����,��i��Ӳ������k��
int val[N]={0,1,5,10,25},num[N],p,vis[N][M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=4;i++){
            for(int j=val[i];j<=p;j++){
                if(dp[j-val[i]] == -1) continue;
                if(dp[j-val[i]]+1>dp[j] && vis[i][j-val[i]]<num[i]){
                    dp[j]=dp[j-val[i]]+1;
                    vis[i][j]=vis[i][j-val[i]]+1;
                }
            }
        }
        if(dp[p] == -1){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        memset(num,0,sizeof(num));
        int i=4,j=p;
        while(j){
            if(vis[i][j]){//������෽����ʹ�õ���vis[i][j]����i��Ӳ��
                num[i]=vis[i][j];
                j-=val[i]*num[i];//���ŷ�������һ״̬ �Ǳ�������Ϊj-val[i]*num[i]
            }
            i--;
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[2],num[3],num[4]);
    }
    return 0;
}
*/

/*
//ac 329ms 544K �������Ż�+��ά�����¼����·��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define M 10010
using namespace std;

//vis[i][j]=k��ʾǡ��װ����������jʱ,���õ�Ӳ�������ķ�����,��i��Ӳ������k��
int val[N]={0,1,5,10,25},num[N],p,vis[N][M],dp[M];

int main(){
    while(scanf("%d%d%d%d%d",&p,&num[1],&num[2],&num[3],&num[4])){
        if(p+num[1]+num[2]+num[3]+num[4] == 0)
            break;
        memset(vis,0,sizeof(vis));
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        int tv;
        for(int i=1;i<=4;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tv=k*val[i];
                for(int j=p;j>=tv;j--){
                    if(dp[j-tv] == -1) continue;
                    if(dp[j-tv]+k>dp[j]){
                        dp[j]=dp[j-tv]+k;
                        vis[i][j]=vis[i][j-tv]+k;//��i��Ӳ������k��
                    }
                }
            }
        }
        if(dp[p] == -1){
            printf("Charlie cannot buy coffee.\n");
            continue;
        }
        memset(num,0,sizeof(num));
        int i=4,j=p;
        while(j){
            if(vis[i][j]){
                num[i]=vis[i][j];
                j-=val[i]*num[i];
            }
            i--;
        }
        printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",num[1],num[2],num[3],num[4]);
    }
    return 0;
}
*/
