/*
����:��mp�Թ��Ƿ�������ͬ��ɫ�����ɵĻ�.
����:https://codeforces.ml/problemset/problem/510/B
˼·:dfs.ö��ÿ�������ɫ,���Ƿ��ص�֮ǰ���ʹ��ĵ�,
ע�������һ�����߹��ĵ�,����������,���Լ�¼ǰ���ڵ��
��һ�����ߵķ���,ֻҪ�����ϴη���ķ�����ͺ�.
*/
//ac
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,vis[60][60];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char mp[60][60];

int dfs(int x,int y,char col,int fx,int fy){
    vis[x][y]=1;
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(x0<1 || x0>n || y0<1 || y0>m) continue;
        if(x0 == fx && y0 == fy) continue;//���ܻص�֮ǰ�õ����׸���,��Ϊ����������һ����,��С�Ļ���2x2,������4,�͸�����ȸ�����2
        if(mp[x0][y0] != col) continue;//dfs������ͬ����ɫȥ����
        if(vis[x0][y0]) return 1;//����ɫ��ͬ���һص���֮ǰ���ʹ��ĵ�,��˵��������һ����ͬ��ɫ�Ļ�
        if(dfs(x0,y0,col,x,y)) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> mp[i][j];
        }
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){//ö��ÿһ�������ɫ
                if(dfs(i,j,mp[i][j],-1,-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) break;
    }
    if(flag) printf("Yes");
    else printf("No");
    return 0;
}

/*
//ac 30ms ��¼��һ���ķ���,�����߷�����
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,vis[60][60];
int dir[4][2]={{1,0},{0,-1},{0,1},{-1,0}};//S W E N
char mp[60][60];

int dfs(int x,int y,char col,int d){
    vis[x][y]=1;
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(x0<1 || x0>n || y0<1 || y0>m || i+d == 3) continue;//i+d == 3�ǻ�Ϊ������
        if(mp[x0][y0] != col) continue;//dfs������ͬ����ɫȥ����
        if(vis[x0][y0]) return 1;//����ɫ��ͬ���һص���֮ǰ���ʹ��ĵ�,��˵��������һ����ͬ��ɫ�Ļ�
        if(dfs(x0,y0,col,i)) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> mp[i][j];
        }
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!vis[i][j]){//ö��ÿһ�������ɫ
                if(dfs(i,j,mp[i][j],-1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) break;
    }
    if(flag) printf("Yes");
    else printf("No");
    return 0;
}
*/
