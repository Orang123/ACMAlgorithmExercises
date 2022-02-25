/*
����:�ȶ�����һֻϲ��̽�յ��ܣ�һ��żȻ�����һ��m*n������Թ���
���Թ�ֻ�ܴӾ������Ͻǵ�һ������ʼ�ߣ�ֻ���ߵ����Ͻǵĵ�һ������
�����߳��Թ���ÿһ��ֻ����һ����ֻ������������������ǰû���߹��ĸ��ӣ�
ÿһ�������ж���һЩ��ң������򸺣��п�������ǿ����·���٣��ȶ�������
��ҿ���Ϊ������Ҫ��ǿ��дǷ�������ȶ��ܸտ�ʼʱ���Ͻ����Ϊ0���ʶȶ�
���߳��Թ�ʱ����������ж��ٽ�ң�
m,n<=100,-100<=�������<=100.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4826
˼·:dfs���仯����
dp[x][y][d] ��ʾ��d���򵽴�(x,y),��(x,y)�����ٵ�(1,n)���ܻ�õ��������.
֮����dp����Ҫ���Ϊ��ά���һ������(x,y)�ķ���,����Ϊ���߶��ķ�����3��,
�ϡ��¡��Ҷ��ڵݹ�����(x,y)����Ŀ���(1,n)�������ʱ,ǰ�游�ڵ��߹���
�����������䷴����,��Ӱ�����Ž��ѡȡ,���Ҳ�ͬ·������õ�ķ���ͬ,
���ڸõ�������ߵ��ķ���Ҳ��ͬ,���֮ǰ������,���ڲ���������,��֮֮ǰ������,
���ڲ���������(������ѭ��),��֮ǰ���ұ�,����3�����򶼿���.�����Ҫ��ÿ����
����һ������õ�ķ�����Ϊ���,��������ͳ�Ƴ�(x,y)�������з���Ľ�,�Ա�Ƚ�������Ž�.
*/
//ac 78ms ���仯����
//dp[x][y][d] ��ʾ��d���򵽴�(x,y),��(x,y)�����ٵ�(1,n)���ܻ�õ��������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int m,n,mp[N][N],dp[N][N][3],dir[3][2]={{-1,0},{1,0},{0,1}};

int dfs(int x,int y,int d){
    if(dp[x][y][d]!=INF)//�ص������� ֱ�ӷ��ؽ��
        return dp[x][y][d];
    if(x == 1 && y == n)
        return dp[x][y][d]=mp[x][y];
    int nx,ny,res=INF;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>m || ny<1 || ny>n)
            continue;
        //���֮ǰ����������,���ھͲ��ܴ��������� �� ���֮ǰ����������,���ھͲ��ܴ���������
        if((d == 0 && i == 1) || (d == 1 && i == 0))
            continue;
        res=max(res,mp[x][y]+dfs(nx,ny,i));
    }
    return dp[x][y][d]=res;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INF;//�п������Ž���0���Ǹ���,���dp��ʼ��Ϊ������
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        printf("Case #%d:\n",cas);
        printf("%d\n",dfs(1,1,1));//ע�����ﵽ��(1,1)��ķ����ʼʱҪ����Ϊ1����,�����Ų���Ӱ��dfsʱ��(1,1)��������(d=0,i=1����������)
    }
    return 0;
}

/*
//ac 62ms ����dp
//dp[x][y][0]��ʾ��(1,1)�����������������ߵ�(x,y)��õ��������
//dp[x][y][1]��ʾ��(1,1)�����������������ߵ�(x,y)��õ��������
//���ұ���,dp[x][y-1][0]��dp[x][y-1][1]����״̬������ת�Ƶ�dp[x][y][0]��dp[x][y][1]
//�ο�����:https://blog.csdn.net/keshuai19940722/article/details/26517843
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int m,n,mp[N][N],dp[N][N][2];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        //��0�к�m+1�� �ǲ��Ϸ�״̬,����Ϊ������
        for(int i=1;i<=n;i++)
            dp[0][i][0]=dp[m+1][i][1]=INF;
        dp[0][1][0]=0;//�����ʼ����һ�� dp[i][1][0]=dp[i-1][1][0]+mp[i][1];
        for(int i=1;i<=m;i++){
            dp[i][1][0]=dp[i-1][1][0]+mp[i][1];
            dp[i][1][1]=INF;//������������,�տ�ʼ���ɴ������������ߵĵ�һ��ת�ƶ�����
        }
        for(int j=2;j<=n;j++){
            for(int i=1;i<=m;i++)//��������������
                dp[i][j][0]=max(dp[i-1][j][0],max(dp[i][j-1][0],dp[i][j-1][1]))+mp[i][j];
            for(int i=m;i>=1;i--)//��������������
                dp[i][j][1]=max(dp[i+1][j][1],max(dp[i][j-1][0],dp[i][j-1][1]))+mp[i][j];
        }
        printf("Case #%d:\n",cas);
        //ע���п���ֻ��һ�м�:n=1,��ʱdp[1][n][1]�ǲ��Ϸ���,��Ϊ�տ�ʼ����(1,1)�㲻��Ҫ�߶�,���Ѿ������� Ŀ���(1,n)=(1,1)
        printf("%d\n",max(dp[1][n][0],dp[1][n][1]));
    }
    return 0;
}
*/

/*
//ac 62ms ���������Ż� һά����dp
//���Բ���:https://www.cnblogs.com/Tovi/p/6194807.html
//dp����һ�����ֱ���������Ϊֻ��һ���߷������£���Ȼ����������֡�==����|| ���ϡ�
//���Ƶ���״̬����Ϊ
//dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + a[i][j] �����£�
//dp[i][j] = max(dp[i+1][j], dp[i][j-1]) + a[i][j] (���ϣ�
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <utility>

#define INF 0xfffffff
#define max1 110

int a[max1][max1], dp[max1][max1], dp1[max1], dp2[max1];

int max(int a, int b) {
	return a>b?a:b;
}

int main() {
	int t, flag = 1;
	scanf("%d",&t);
	while (t --) {
		memset(a, 0, sizeof(a));
		int m, n;
		scanf("%d%d",&m, &n);
		for (int i = 1; i<=m; i++)
			for (int j = 1; j<=n; j++)		scanf("%d",&a[i][j]);
		memset(dp, 0, sizeof(dp));
		for (int i = 2; i<=m; i++) {
			a[i][1] = a[i][1] + a[i-1][1];
		}
		dp1[0] = dp2[0] = dp1[m+1] = dp2[m+1] = -9999999;
		for (int j = 2; j<=n; j++) {
			//����
			for (int i = 1; i<=m; i++) {
				dp1[i] = max(dp1[i-1], a[i][j-1]) + a[i][j];
			}
			//����
			for (int i = m; i>=1; i--) {
				dp2[i] = max(dp2[i+1], a[i][j-1]) + a[i][j];
			}
			for (int i = 1; i<=m; i++) {
				a[i][j] = max(dp1[i], dp2[i]);
			}
		}
		printf("Case #%d:\n%d\n",flag++, a[1][n]);
	}
	return 0;
}
*/
