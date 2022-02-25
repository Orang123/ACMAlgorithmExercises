/*
����:ժ������
��4���ǹ���ÿһ����n���ǹ�����һ�����ӣ�������ӵ��������Ϊ5���ǣ�
ÿһ�δ����Ķ���ѡ��һ�ѣ�Ȼ����������ǹ����������ŵ���������ȥ��
�������ͬ�����ǵľͰ��⣻�������ó���������ﵽ��5���ǣ�������5����
����������ͬ�ľͽ�����Ϸ�����㣬������ó����ٶ���.
n<=40.�ǵ���ɫ�����[1,20]
����:https://www.luogu.com.cn/problem/UVA10118
˼·:��Ϊÿ���Ǵ�4���ǵ������濪ʼ��,�Ǿ�ö���õĿ�����,����4���ǵ�
һ�������±�,���õ�n��ʱ�ͽ���,ֻ����ö�ٵĹ����ж���4���ǵ�ǰ����
��ÿ���ǵĶ��� ���п����ظ����ص�,�����Ҫ���仯�������ص��������������.
dp[top[1]][top[2]][top[3]][top[4]]��ʾ��ǰ4���Ƕ����ֱ�����top[1]��top[2]
��top[3]��top[4]����ʣ���4�������ܴ��������ó���ͬ��һ�Ե����Ķ���.
ע�����0Ҳ�������Ľ��,���dp��ʼ��Ϊ-1,���ҽ���������һ���ܸպ�����5��,
���ܱ����ܹ���ֻ��4���ǹ�,���dp����ʱ�ĳ�ʼֵ��Ϊ0.
*/
//ac 80ms ���仯����
//dp[top[1]][top[2]][top[3]][top[4]]��ʾ��ǰ4���Ƕ����ֱ�����top[1]��top[2]
//��top[3]��top[4]����ʣ���4�������ܴ��������ó���ͬ��һ�Ե����Ķ���.
//��Ϊÿ�������40��,��41��������ʾ״̬ ��ֵ��dp[top[1]][top[2]][top[3]][top[4]]Ҫ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
using namespace std;

int n,dp[N][N][N][N],a[5][N],top[5],vis[21];

int dfs(int k){
    int &res=dp[top[1]][top[2]][top[3]][top[4]];
    if(res!=-1)
        return res;
    if(k == 5)
        return res=0;
    res=0;
    for(int i=1;i<=4;i++){
        if(top[i] == n)
            continue;
        top[i]++;
        if(!vis[a[i][top[i]]]){//��ǰ��i���ǹ���top[i]�� ��δ��
            vis[a[i][top[i]]]=1;
            res=max(res,dfs(k+1));//��ǰ��������ǹ���+1
            vis[a[i][top[i]]]=0;
        }
        //��ǰ��i���ǹ���top[i]����ɫΪa[i][top[i]]���ǹ��������Ѿ���һ����,�ڷ���һ�� �պôճ�һ��,
        //���Խ����ó���,������ʣ���ǹ����ͼ�1,�ó����ǹ�����+1
        else{
            vis[a[i][top[i]]]=0;
            res=max(res,dfs(k-1)+1);
            vis[a[i][top[i]]]=1;
        }
        top[i]--;
    }
    return res;
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=4;j++)
                scanf("%d",&a[j][i]);
        }
        printf("%d\n",dfs(0));
    }
    return 0;
}

/*
//ac 80ms ���仯����+״ѹ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
using namespace std;

int n,dp[N][N][N][N],a[5][N],top[5];

//��������õ���Զ��ֻ��һ����ɫ���ǹ�,��������ͬ��ɫ��ʱ����ԭ�ȵ�����ȡ��
int dfs(int sta,int k){
    int &res=dp[top[1]][top[2]][top[3]][top[4]];
    if(res!=-1)
        return res;
    if(k == 5)
        return res=0;
    res=0;
    for(int i=1;i<=4;i++){
        if(top[i] == n)
            continue;
        top[i]++;
        int tp=1<<a[i][top[i]]-1;
        if(sta & tp)
            res=max(res,dfs(sta^tp,k-1)+1);//��λ��� ������a[i][top[i]]��ɫ���ǹ�
        else
            res=max(res,dfs(sta|tp,k+1));//��λ�� ��a[i][top[i]]��ɫ���ǹ�������λ����
        top[i]--;
    }
    return res;
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=4;j++)
                scanf("%d",&a[j][i]);
        }
        printf("%d\n",dfs(0,0));
    }
    return 0;
}
*/
