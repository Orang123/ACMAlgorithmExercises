/*
����:r*c������'.'��ʾˮ,'#'��ʾ��ֻ�����,���д�ֻ���Ƿ��ε�,
���������ж��ٴ�ֻ.�������λ�÷ŵ���ȷ����������ֻ�����໥֮��
���ܽӴ��ķ��Σ����������#�����������ڻ���������ȴ�������Ҳ�ͬ��
��ֻ����������Ҵ��໥�Ӵ��ˣ��������һ�λ���There are S ships.��,
S��ʾ��ֻ�����������������Bad placement.�������Ϸ��Ĵ�ֻ��ʵ����'L'��'#�������.
1<=r,c<=1000.
����:https://www.luogu.com.cn/problem/P1331
˼·:dfs.
*/
#include<cstdio>
#include<cstring>
#include<cstring>
using namespace std;
char map0[1010][1010];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int r,c,cnt;

int judge(int x,int y){
    if(x>=1 && x<=r && y>=1 && y<=c) return 1;
    else return 0;
}
//����2x2�Ÿ��ں�������'#'��˵�������Ƿ��ε�
int L(int x,int y){
    int num=0;
    if(judge(x,y) && map0[x][y] == '#') num++;
    if(judge(x,y+1) && map0[x][y+1] == '#') num++;
    if(judge(x+1,y) && map0[x+1][y] == '#') num++;
    if(judge(x+1,y+1) && map0[x+1][y+1] == '#') num++;
    if(num == 3) return 1;
    else return 0;
}

void dfs(int x,int y){
    int x0,y0;
    map0[x][y]='.';
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(map0[x0][y0] == '#') dfs(x0,y0);
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
            if(L(i,j)){
                printf("Bad placement.\n");
                return 0;
            }
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++)
        if(map0[i][j] == '#'){
            dfs(i,j);
            cnt++;
        }
    }
    printf("There are %d ships.\n",cnt);
    return 0;
}
