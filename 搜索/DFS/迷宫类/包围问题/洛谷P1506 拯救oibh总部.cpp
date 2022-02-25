/*
����:n*m������.
oibh��ͻ���ĺ�ˮ��û��>.<����oibh�ܲ�����ĳЩ��Ҫ�ĵط���һЩΧǽ��
��*�ű�ʾ����һ����յ�*�������ˮ�ǽ���ȥ�ġ������ڸ���oibh��Χǽ����ͼ��
��oibh�ܲ�û���͵�����Ҫ������"0"��ʾ���ж��١�
n,m<=500.
����:https://www.luogu.com.cn/problem/P1506
˼·:
�ⷨ1:
dfs,n*m��������з�Χ����Ϊ[1,n],[1,m].������������Χ����0��,n+1��,
0��,m+1�б�ʾ��ˮ,��(0,0)��ʼdfs,��'o'ȫ����û����Ϊ'*',���ͳ��ʣ�µ�'0'
�ĸ���,����û����û��'0'�ĸ���.

�ⷨ2:
����ö��ÿ��'O',dfs����'O'������'O'�Ŀ�ĸ���,����ܹ������߳��Թ��߽�,
����Щ'O'�Ŀ�ͻᱻ��ˮ��û��Ҫ���,��������߳��Թ��߽�,�Ͳ��ᱻ��ˮ��û,
���ۼӴ˴�������'O'���'O'�ĸ���.
*/
//ac 47ms n*m�Թ����һȦ��ʾ��ˮ
#include<cstdio>
#define N 510

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,sum;
char mp[N][N];

void dfs(int x,int y){
    mp[x][y]='*';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<0 || nx>n+1 || ny<0 || ny>m+1 || mp[nx][ny] == '*')
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf(" %c",&mp[i][j]);
    }
    dfs(0,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j] == '0')
                sum++;
        }
    }
    printf("%d\n",sum);
    return 0;
}

/*
//ac 52ms
//����ö��ÿ��'O',dfs����'O'������'O'�Ŀ�ĸ���,����ܹ������߳��Թ��߽�,
//����Щ'O'�Ŀ�ͻᱻ��ˮ��û��Ҫ���,��������߳��Թ��߽�,�Ͳ��ᱻ��ˮ��û,
//���ۼӴ˴�������'O'���'O'�ĸ���.
#include<cstdio>
#define N 510

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int n,m,ans,cnt,flag;
char mp[N][N];

void dfs(int x,int y){
	if(x<1 || x>n || y<1 || y>m){
		flag=0;
		return;
	}
    mp[x][y]='*';
    cnt++;
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(mp[nx][ny] == '*')
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf(" %c",&mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j] == '0'){
            	cnt=0;
            	flag=1;
            	dfs(i,j);
            	if(flag)
            		ans+=cnt;
			}
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/
