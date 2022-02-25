#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 110
using namespace std;
//ac 16ms 01�������������Ϸ��� �����ܶ��װ��
/*
����:��÷÷ϲ�������浽�����.�������䵽��һ�һ��ǵ���,
������ҵ��и��ر�Ĺ��:��������κ������Ӳ�Ҹ�Ǯ,����
��������,��ȻҲ����Ƿծ.��÷÷�ֱ���10^4ö���Ը��������Ӳ��,
��Ҫ�����������һ��,�Ƿ���ܾ�ȷ�ճ�Ҫ���Ŀ��v.����ж�����Ž�,
�Ͱ���Ӳ����ֵ���ֵ����������Ӳ����ֵ����Ϸ���.���������ܴճ�v��
Ӳ����Ϸ���,�����"No Solution".
����:https://pintia.cn/problem-sets/994805046380707840/problems/994805054207279104
˼·:������vis[i][j]����ڱ�������Ϊjʱ,�����i����Ʒ,��ΪҪ�����ֵ�ֵ�����С
�����,�����Ƚ�������,Խ�������Ӳ����ֵԽС,֮���vis[n][m]ģ��ʵ��dp�Ĺ�������
�������.
*/
//vis[i][j]=1����������Ϊjʱ,���Ž�����˵�i����Ʒ
//vis[i][j]=0����������Ϊjʱ,���Ž�û�з����˵�i����Ʒ
//ע������vis[i][j]ֻ�ǵ����ر�ʾ��i����Ʒ�ڱ�������jʱ���Ž�����Ƿ�װ��,���ܴ���ʵ�ʵĵ��ƹ�ϵ
int n,v,val[N],dp[M],vis[N][M];

bool cmp(int a,int b){
    return a>b;
}

int main(){
    memset(dp,0,sizeof(dp));//������װ������,��ʼ��Ϊ0
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    sort(val+1,val+1+n,cmp);
    for(int i=1;i<=n;i++){
        for(int j=v;j>=val[i];j--){
            if(dp[j]<=dp[j-val[i]]+val[i]){//���ѡ����Ӳ����ֵ��������Ӳ��������,���ȿ���ѡ������ֵС��,ע��������"<="
                dp[j]=dp[j-val[i]]+val[i];
                vis[i][j]=1;//��Ǳ�������Ϊjʱ,���Ž����ֵ������������ǵ�i��Ӳ��
            }
        }
    }
    if(dp[v]!=v)//ֻ�е�ǡ���ܴ�����ֵΪv��Ӳ��ʱ ���н� �����Ǿ����ܶ��װ������
        printf("No Solution");
    else{//������Ž��Ӳ����Ϸ��� ����ֵ��С�������
        int i=n,j=v;
        //��Ϊ��ǡ��װ��,���Խ�������һ���Ǳ�������Ϊ0 ��Ϊdp[j]����j,��dp[v]!=vʱ,
        //��ʼ���dp[j]��������0,��Ϊ��ʱ�Ѿ���ǰn����Ʒ��״̬��,ֻ��ǰ0����Ʒdp[j]����0
        while(j){
            if(vis[i][j]){//j������,�з����i��Ӳ��
                j-=val[i];//������������,��Ϊ��ͬ���������� ���Ž�ķ�����ͬ,����Ҫ�������������������v�µ����Ž�
                if(j)
                    printf("%d ",val[i]);
                else//j == 0�����һ����ֵ����Ӳ��
                    printf("%d",val[i]);
            }
            i--;
        }
    }
    return 0;
}

/*
//ac 8ms 01�������������Ϸ��� ��������ǡ��װ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 110
using namespace std;

int n,v,val[N],dp[M],vis[N][M];

bool cmp(int a,int b){
    return a>b;
}

int main(){
    memset(dp,-0x3f,sizeof(dp));//��������ǡ��װ��
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    sort(val+1,val+1+n,cmp);
    dp[0]=0;//��ʼ״̬��0
    for(int i=1;i<=n;i++){
        for(int j=v;j>=val[i];j--){
            if(dp[j]<=dp[j-val[i]]+val[i]){
                dp[j]=dp[j-val[i]]+val[i];
                vis[i][j]=1;
            }
        }
    }
    if(dp[v]<0)//��Ϊ��ǡ��װ��ֻ���ж� ����Ϊv�Ƿ�Ϸ�
        printf("No Solution");
    else{
        int i=n,j=v;
        while(j){
            if(vis[i][j]){
                j-=val[i];
                if(j)
                    printf("%d ",val[i]);
                else
                    printf("%d",val[i]);
            }
            i--;
        }
    }
    return 0;
}
*/

/*
�����õݹ��������,��Ϊdp[i][j] == dp[i-1][j] ��j����ȫ��װ��ǰi����ǰi-1����Ʒ,ʱ������Ϊû��ѡ���i����Ʒ,
��ʵ���ֵ��򷽰� ������ѡ���˵�i������Ʒ��,���Եݹ��޷�����ֵ��򷽰�,ֻ��˵�����������һ�ַ���.
���嵽�ֵ�������Ҫvis[i][j]���������ж�
*/
