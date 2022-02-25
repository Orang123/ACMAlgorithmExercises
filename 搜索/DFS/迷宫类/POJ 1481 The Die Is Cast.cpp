/*
����:ժ������
w*h������,�� * . X��ɣ�����ÿ����*��X��ɵĲ����Ƕ�����һ���棬
ÿ��������X��������ֱ�ʾ�������ͼ��ÿ����������Ƕ��٣�����С��������
w,h<=50.
����:http://poj.org/problem?id=1481
˼·:���Զ�ÿ��'*'��ʼdfs1�ı���,��dfs1�ҵ�'X'ʱ,�ٶ�X���������
����dfs2,ÿ����һ��dfs2��ʹ�õ�ǰģ�鲻��ͨ�õ�'X'�������+1.
*/
//ac 0ms dfs����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
using namespace std;

int w,h,dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}},sum[N*N],cnt;
char mp[N][N];

void dfs2(int x,int y){
    mp[x][y]='*';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>h || ny<1 || ny>w)
            continue;
        if(mp[nx][ny] == 'X')
            dfs2(nx,ny);
    }
}

void dfs1(int x,int y){
    mp[x][y]='.';
    int nx,ny;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx<1 || nx>h || ny<1 || ny>w)
            continue;
        //ע������Ҫ���ж�'X',��ΪXdfs2�������,��ʹ��mp[nx][ny]���'*',����ֱ�ӽ���dfs1 ����X��ʹ��'*'���ָ�,ʹ��cnt��Ŀƫ��
        if(mp[nx][ny] == 'X'){
            sum[cnt]++;//��ǰ'*'���ɵĿ��в���ͨ��'X'���ɵĿ� ��Ŀ��1
            dfs2(nx,ny);
        }
        if(mp[nx][ny] == '*')//'*'��dfs1���� 'X'��dfs2��
            dfs1(nx,ny);
    }
}

int main(){
    int cas=0;
    while(scanf("%d%d",&w,&h) && w+h){
        cnt=0;
        cas++;
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                if(mp[i][j] == '*'){
                    cnt++;
                    dfs1(i,j);
                }
            }
        }
        sort(sum+1,sum+1+cnt);
        printf("Throw %d\n",cas);
        for(int i=1;i<=cnt;i++){
            if(i == 1)
                printf("%d",sum[i]);
            else
                printf(" %d",sum[i]);
        }
        printf("\n\n");
    }
    return 0;
}
