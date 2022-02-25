/*
����:һ�������������� 0 �� 9 ��ɣ����� 1 �� 9 ����ϸ����
ϸ���Ķ���Ϊ��ϸ��������������������ϸ��������Ϊͬһϸ����
������������е�ϸ��������
1<=n,m<=100.
����:https://www.luogu.com.cn/problem/P1451
˼·:dfs.
*/
#include<cstdio>
#include<cstring>
#include<cstring>
using namespace std;
char map0[110][110];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int r,c,cnt;

void dfs(int x,int y){
    int x0,y0;
    map0[x][y]='0';
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(map0[x0][y0]>='1' && map0[x0][y0]<='9') dfs(x0,y0);
    }
}

int main(){
    scanf("%d%d",&r,&c);
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++)
            scanf(" %c",&map0[i][j]);
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++)
        if(map0[i][j] != '0'){
            dfs(i,j);
            cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
