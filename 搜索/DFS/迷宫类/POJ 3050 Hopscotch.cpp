/*
����:ժ������
����һ��5*5�ĵ�ͼ��ÿ����������һ�����֡���һ�����ӳ�������������4�����򣩣�
��5�����������������Թ����һ��6λ�����ʸõ�ͼ���Թ�������ٸ���ͬ��6λ����
����:http://poj.org/problem?id=3050
˼·:��һ����СΪ10^6��val�����¼,6λ������ֵ�Ƿ��Ѿ�������,ע����ͬ�ĸ���
�ǿ����ظ��ߵ�,ֻ�ò�������������.
*/
//ac 32ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
#define M 1000000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int mp[N][N],val[M],ans;

void dfs(int x,int y,int sum,int cnt){
    sum=sum*10+mp[x][y];
    if(cnt == 5){
        if(!val[sum]){
            val[sum]=1;
            ans++;
        }
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>5 || ny<1 || ny>5)
            continue;
        dfs(nx,ny,sum,cnt+1);
    }
}

int main(){
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++)
            scanf("%d",&mp[i][j]);
    }
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++)
            dfs(i,j,0,0);
    }
    printf("%d",ans);
    return 0;
}
