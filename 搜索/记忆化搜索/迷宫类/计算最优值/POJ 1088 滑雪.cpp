/*
����:Michaelϲ����ѩ���Ⲣ�����,��Ϊ��ѩ��ȷ�ܴ̼�.����Ϊ�˻���ٶ�,
�����������������б,���ҵ��㻬���µ�,�㲻�ò��ٴ������»��ߵȴ�������������.
Michael��֪����һ����������׻���.������һ����ά�������.�����ÿ�����ִ����ĸ߶�.
������һ������
1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
һ���˿��Դ�ĳ���㻬���������������ĸ���֮һ,���ҽ����߶ȼ�С.�������������,
һ���ɻ��еĻ���Ϊ24-17-16-1.��Ȼ25-24-23-...-3-2-1����.��ʵ��,�������һ��.
����ĵ�һ�б�ʾ���������R������C(1 <= R,C <= 100)��������R�У�ÿ����C������������߶�h��0<=h<=10000��
��������ĳ��ȡ�
ע��:ʵ����Ŀ�ʵ�����������ߵĵ�ĸ���
����:http://poj.org/problem?id=1088
˼·:���ڼ��仯��������̬�滮��̰�Ľ��ͺܺõĲ���:https://blog.csdn.net/Harington/article/details/86534326
���仯���� �ݹ�ش�Ŀ��״̬(�����ߵ�״̬)���ʼ״̬ת��,�Ѿ�����
�����ص�������ֱ�ӷ���dp[x][y]����������.
dp[x][y]��ʾ��(x,y)������ߵ��������ߵ�λ����������ߵĵ�ĸ���
*/
//ac 16ms ���仯���� �ݹ�ش�Ŀ��״̬(�����ߵ�״̬)���ʼ״̬(1,1)ת��
//dp[x][y]��ʾ��(x,y)������ߵ��������ߵ�λ����������ߵĵ�ĸ���
//ʱ�临�Ӷ�O(n*m)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int map[105][105],k,n,m;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int dp[105][105];
bool check(int x,int y){
    if(x<0||x>n-1||y<0||y>m-1)
        return false;
    return true;
}
//���仯���������Ѿ���������·��û��Ҫ�ظ���������֦��������·���������ߣ����õ�����·��Ӧ����
int dfs(int x,int y){
    if(dp[x][y])//��Ϊ�Ǽ��仯���������dp[x][y]��Ϊ0�������㿪ʼ��ö�ٵ�·���Ǳ��������ã���Ҫȥ�ظ��������Ǿ�ֱ����֮ǰ��������ֵ�ͺ�
        return dp[x][y];
    int xx,yy,res=0;
    for(int j=0;j<4;j++){//ö�ٷ���
        xx=x+dir[j][0];
        yy=y+dir[j][1];
        if(check(xx,yy)&&map[xx][yy]<map[x][y]){
            res=max(dfs(xx,yy),res);//����dp�е�״̬ת�Ʒ��̣�ȡmax�ľ��߷���
        }
    }
    dp[x][y]=res+1;//��Ϊ�����ǻ��µ���󳤶�
    return dp[x][y];
}
int main(){
    int res=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&map[i][j]);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            res=max(res,dfs(i,j));
        printf("%d\n",res);
    return 0;
}

/*
//ac 16ms ��Ϊ�����͵Ķ�̬�滮
//�ο�����:https://blog.csdn.net/Harington/article/details/86534326
//����ı��ʣ�������Ҫ�ҵ�һ��������������У������ǾͿ����룬�����Ķ�̬�滮��״̬���̣�
//�����Լ�˼��������������������ƣ��ҵ���С�ĵ㣬Ȼ����������������������ҵĵ㣬�����
//����㵽��������4������������б� ��4���㱾����������� �䳤�˾͸��²���¼��ֱ���ҵ����ֵ��
//��һ����������Ҫ�����еĵ㰴 ������������
//�ڶ��������Ǵ���͵�����������ҵ�4���㣬ֱ��ÿ�����㶼���ˡ�
//����������������ҵĹ����е����ֵ��
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int map[105][105],k,n,m;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int dp[105][105];
struct Node{
    int x,y,h;
    bool operator <(const Node &x)const{
        return h<x.h;
    }
}node[11000];
bool check(int x,int y){
    if(x<0||x>n-1||y<0||y>m-1)
        return false;
    return true;
}
int main(){
    int len=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&map[i][j]);
            node[len++]=(Node){i,j,map[i][j]};
            dp[i][j]=1;
        }
    }
    //���ո߶ȴ�С��������,��Ϊdpǰ��Ľ��������µ������ٸ���Ϊֹ,����ȥ���º���Ľ��
    sort(node,node+len);
    int x0,y0,ans=1;
    //�Ӹ߶�С����߶ȸߵ�dp,������ÿ��ߵ����·��
    for(int i=0;i<len;i++){
        int x=node[i].x;
        int y=node[i].y;
        for(int k=0;k<4;k++){
            x0=x+dir[k][0];
            y0=y+dir[k][1];
            if(!check(x0,y0)) continue;
            if(map[x0][y0]<=node[i].h) continue;//��Ϊ�ǴӸߵ���͵��ߵ�
            if(dp[x0][y0]>=dp[x][y]+1) continue;
            dp[x0][y0]=dp[x][y]+1;
            ans=max(ans,dp[x0][y0]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/

/*
//ac 16ms ����Ϊ���� ��̬�滮
//�ο�����:https://blog.csdn.net/Harington/article/details/86534326
//���ָ����仯������࣬���Ŀ������ÿһ��������������У�����������ֵȡ��ʲô�أ�
//�ǲ���ȡ��������������4���������������У����õݹ�ͺ�д�ˣ����ǰ���ת���ɶ�̬�滮��
//���˼·�����ҵ�״̬���̣������ǰ��������ֽ⣬������ÿ��������������У��������ҵ��߽磬
//������͵��Ǹ��㡣�������Ϊ���ͺ���Ϊ�����͵�Ψһ��һ�����������Ϊ������ ����������������4���㣬
//������Ϊ���;�������Χ4����������һ���㡣�ҵ�һ����Χ4����û���������ģ���������͵��Ǹ���ô��
//���Ǿ���������״̬���̣��ӱ߽������ƣ�ֱ���Ƶ����һ���㣨��ߵĵ㣩
//��һ�����Ƚ��е������������
//�ڶ������ҵ���С�ĵ㣬���������ҵĵ��������Ȼ���С��һֱ����󣬣��������һ��ѭ����OK��
//���������ҵĹ����м�¼ÿ�����״̬�����ҵ����ֵ.
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
	int n ,m;
struct node{
	int x;
	int y;
	int data;
};

bool cmp(node a, node b){
	return a.data < b.data;
}

bool check(int x, int y){
	if( x >= 1 && y >= 1 && x <= n && y <= m)
		return 1;
	else
		return 0;
}

int main (){

	int high[105][105];
	int maxLen[105][105];
	int to[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int ans = 1;
	cin >> n >> m;
	int k = 0;
	node s[10006];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &high[i][j]);
			s[++k].data = high[i][j];
			s[k].x = i;
			s[k].y = j;
			maxLen[i][j] = 1;
		}
	}
	sort(s + 1, s + k + 1, cmp);
	for(int i = 1 ; i <= k; i++){
		int x1, y1;

		for(int j = 0; j < 4; j++){
			int x = s[i].x;
			int y = s[i].y;
			x1 = x + to[j][0];
			y1 = y + to[j][1];
			if(check(x1, y1)){
				if(high[x][y] > high[x1][y1]){
					maxLen[x][y] = max(maxLen[x1][y1] + 1, maxLen[x][y]);
					ans = max(ans, maxLen[x][y]);
				}
			}
		}
	}
	cout << ans <<  endl;
	return 0;
}
*/

/*
//dfs�������� �౳��dp�׶��Լ�֦ TLE
//������� �����Իᳬʱ,��Ϊÿ�ε���㶼��ͬ,ÿ����������Ҫ��ʼ��dp�������¼���
//dp[x][y]��ʾ�ӳ����㵽��(x,y)������ߵ�·������
//��֦1 �����ǰ��(1,1)�������ߵ�·�����Ȳ���֮ǰ����(x,y)���� �Ͳ�����������ȥ

//Ϊɶһ��Ҫ �ӽ���״̬���ʼ״̬�����Ž���Ҫԭ����:
//����ӳ�ʼ״̬ �����ߵ�״̬�����Ž�,����� ���ǻ����¼���������,�������������Ļ���һ��������,
//��֦�ĸ�Ч�Ծ��޷���֤,����ֹ״̬ȥ����,��Ϊ�Ѿ�ͣ����,���������¼���������,�Ͳ����ظ�����,
//�������Ǳ�֤�˶����ӽ׶ε�״̬�Ѿ��������ŵ���,���ԲŸ���Ч��.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;

void dfs(int x,int y,int sum){
    if(sum<=dp[x][y])//��֦1 �����ǰ��(1,1)����������Ҳ���֮ǰ��õĶ� �Ͳ�����������ȥ
        return;
    dp[x][y]=sum;
    ans=max(ans,sum);
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>n || ny<1 || ny>n)
            continue;
        if(mp[nx][ny]>=mp[x][y])
            continue;
        dfs(nx,ny,sum+1);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //������� �����Իᳬʱ,��Ϊÿ�ε���㶼��ͬ,ÿ����������Ҫ��ʼ��dp�������¼���
            memset(dp,0,sizeof(dp));
            dfs(i,j,1);
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/
