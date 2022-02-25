/*
����:ժ������
һ���Ǳ��ֳ���m*n���飬Ȼ�������ÿ����һ�����֣�������ִ����ŵ������
���������������ţ���ô1��Ҫ�ӵ���������С��������鱱�����ţ���ô2
��Ҫ�ӵ���������С��������鶫�����ţ���ô4��Ҫ�ӵ���������С������
�����������ţ���ô8�ͼӵ���������С�����Ǳ��ķ��������Ǳ�����󷿼��������ķ�������
n,m<=50.
����:http://poj.org/problem?id=1164
˼·:�������������������ϳ�ʼ��,ÿ���ж�(mp[x][y] & 1<<i),���
Ϊ1 ˵��������򲻿���.
*/
//ac 0ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
using namespace std;

int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int n,m,mp[N][N],vis[N][N],cnt,ans,sum;

void dfs(int x,int y){
    int nx,ny;
    vis[x][y]=1;
    sum++;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>n || ny<1 || ny>m || vis[nx][ny] || (mp[x][y] & 1<<i))
            continue;
        dfs(nx,ny);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum=0;
            if(!vis[i][j]){
                cnt++;
                dfs(i,j);
                ans=max(ans,sum);
            }
        }
    }
    printf("%d\n",cnt);
    printf("%d",ans);
    return 0;
}
