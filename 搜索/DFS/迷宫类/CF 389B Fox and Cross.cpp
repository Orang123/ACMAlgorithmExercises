/*
题意:问n*n的地图由'.'和'#'构成,问'#'能否有十字图案完全填充完毕.暴力即可.
链接:https://codeforces.ml/problemset/problem/389/B
思路:直接暴力判断即可.
*/
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int dir[4][2]={{1,-1},{1,0},{1,1},{2,0}};
int n;
char mp[110][110];

int judge1(int x,int y){
    if(x>=1 && x<=n && y>=1 && y<=n && mp[x][y] == '#') return 1;
    else return 0;
}

int judge2(int x,int y){
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(!judge1(x0,y0)) return 0;
    }
    return 1;
}

void change(int x,int y){
    mp[x][y]='.';
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        mp[x0][y0]='.';
    }
}

int main () {
    int cnt=0;
	scanf("%d", &n);
	for (int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> mp[i][j];
            if(mp[i][j] == '#') cnt++;
        }
	}
	int num=0;
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mp[i][j] == '#' && judge2(i,j)){
                change(i,j);
                num+=5;
            }
        }
	}
	if(num == cnt) printf("YES");
	else printf("NO");
	return 0;
}
