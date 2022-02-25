/*
����:����һ���򵥵�������Ϸ�������һ�������˴�һ�����̵���ʼ��(1,1)�ߵ����̵��յ�(n,m)����Ϸ�Ĺ����������£�
1.������һ��ʼ�����̵���ʼ�㲢����ʼ�������е�������
2.������ֻ�����һ��������ߣ�����ÿ��һ������һ��λ������
3.�����˲�����ԭ��ͣ����
4.��������ѡ����һ������·���󣬵����ߵ�����·�����յ�ʱ������ֻ���յ�����ǵ�������
����ͼ��������һ��ʼ��(1,1)�㣬��ӵ��4��λ��������ɫ�����ʾ�����ܵ���ĵ㣬�����
�����·��ѡ����ѡ����յ���(2,4)�㣬��������(2,4)��ʱ��ӵ��1��λ������������ʼ
��һ��·��ѡ��ֱ������(6,6)�㡣���ǵ������ǻ������ж����ַ�ʽ������ߵ��յ㡣
�������һ���ܴ����������Ľ����10000ȡģ��
����:http://acm.hdu.edu.cn/showproblem.php?pid=1978
˼·:����ӳ�ʼ״̬�򵽴���ת�Ʒ�����,�ᵼ���ظ�����,��˴�Ŀ��״̬����ʼ״̬ת��
������,�����ظ����㷽����,�Ѿ���������״ֱ̬�ӷ��ؽ������.
*/
//ac 249ms ���仯���� ��Ŀ��״̬(n,m)����ʼ״̬(1,1)ת�Ʒ�����
//ʱ�临�Ӷ�O(n*m)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define mod 10000
using namespace std;

int n,m,mp[N][N],dp[N][N];

int dfs(int x,int y){
    if(dp[x][y])
        return dp[x][y];
    int nx,ny;
    int k=mp[x][y];
    for(int i=0;i<=k;i++){
        for(int j=0;j<=k;j++){
            nx=x+i;
            ny=y+j;
            //����ͣ����ԭ��,��Ծ���ܲ���ҪС�ڷ����ϵ�����(�����پ���)
            if(i+j==0 || i+j>k || nx>n || ny>m) continue;
            dp[x][y]=(dp[x][y]+dfs(nx,ny))%mod;
        }
    }
    return dp[x][y];
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[n][m]=1;//����·�����ܵ����յ�����һ�ַ���
        printf("%d\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 171ms ����dp ��ö���� ��ö����
//dp[i][j]��ʾ����(i,j)���ʱ�ķ�������
//ʵ�ʳ�ʼ���Ǵ�(1,1)��ʼ����x 1..n,y 1..m��˳�����,���� ����,
//�������ĳ����û�б��������,ǰ���Ǹ����ϵ����ֲ���Ϊ0,����˵��һ����϶�������֮ǰ��״̬��չ����
//����ͻ������ö�ٵĵ���Ϊû����չ������©������,�����ʼ�����м����λ��,ö�ٵĵ��(x,y)�п��ܻ�û
//��չ��,�ͱ�ֹͣ,��������״̬��û�м���,���ս�����Ǵ��.
//ʵ��Ҳ�����ظ����㷽����,��Ϊ��dp[x][y]��ʼ��չ��ʼ,֮�󲻻��е�����չ��dp[x][y],��Ϊֻ�����һ���,��˷��������ظ�����.
//����ֱ��dfs�����ӳ�ʼ�㵽(x,y)�ķ�����,��ᵼ���ظ�����.
#include<cstdio>
#include<iostream>
#include<cstring>
#define mod 10000
using namespace std;

int n,m,mp[110][110],dp[110][110];

int judge(int x,int y){
    if(x<=n && y<=m) return 1;
    else return 0;
}

int main () {
    int T;
	scanf("%d", &T);
	while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[1][1]=1;//����㿪ʼ��һ�ַ���
        //��̬�滮 ����Ҫ�ٶ����ж��Ƿ��ظ�����,��Ϊ������Ǿ����ܶ��ö�����ܵ���ĵ�,��Щ�������Ϊ��ͬ,���ܸ��·�����
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int step=mp[i][j];
                //��ǰ��������û�����,����չ״̬,ʵ�ʳ�ʼ����(1,1)
                //����x 1..n,y 1..m��˳������������ĳ����û�б��������,ǰ���Ǹ����ϵ����ֲ���Ϊ0
                //if(!dp[i][j]) continue;//ʵ����������������,��һ���Ǵ��
                for(int k=0;k<=step;k++){//ö�ٴӸõ�mp[i][j]�������ܵ����mp[i+k][j+h]
                    for(int h=0;h<=step;h++){
                        if(k+h==0 || k+h>step || !judge(i+k,j+h)) continue;
                        //����㿪ʼ,�滮����mp[i+k][j+h]��Ҫ�ķ�����dp[i+k][j+h]+dp[i][j],�Ӳ�ͬ�ĵ�����ܵ�����ͬ�ĵ�,��������ĳ���յ���ж��ַ���
                        dp[i+k][j+h]=(dp[i+k][j+h]+dp[i][j])%mod;
                    }
                }
            }
        }
        printf("%d\n",dp[n][m]);
	}
	return 0;
}
*/

/*
//ac 171ms ����dp,��ö���� ��ö����
#include<cstdio>
#include<iostream>
#include<cstring>
#define mod 10000
using namespace std;

int n,m,mp[110][110],dp[110][110];

int judge(int x,int y){
    if(x<=n && y<=m) return 1;
    else return 0;
}

int main () {
    int T;
	scanf("%d", &T);
	while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        dp[1][1]=1;//����㿪ʼ��һ�ַ���
        //��̬�滮 ����Ҫ�ٶ����ж��Ƿ��ظ�����,��Ϊ������Ǿ����ܶ��ö�����ܵ���ĵ�,��Щ�������Ϊ��ͬ,���ܸ��·�����
        for(int j=1;j<=m;j++){
            for(int i=1;i<=n;i++){
                int step=mp[i][j];
                for(int k=0;k<=step;k++){//ö�ٴӸõ�mp[i][j]�������ܵ����mp[i+k][j+h]
                    for(int h=0;h<=step;h++){
                        if(k+h==0 || k+h>step || !judge(i+k,j+h)) continue;
                        //����㿪ʼ,�滮����mp[i+k][j+h]��Ҫ�ķ�����dp[i+k][j+h]+dp[i][j],�Ӳ�ͬ�ĵ�����ܵ�����ͬ�ĵ�,��������ĳ���յ���ж��ַ���
                        dp[i+k][j+h]=(dp[i+k][j+h]+dp[i][j])%mod;
                    }
                }
            }
        }
        printf("%d\n",dp[n][m]);
	}
	return 0;
}
*/
