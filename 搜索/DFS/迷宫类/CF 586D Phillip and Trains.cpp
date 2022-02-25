/*
题意:三条铁轨，上边有若干火车，人刚开始在最左边，
每一回合人可以向右走一格然后选择上移、下移或不动，
然后所有火车会向左平移2格，问人是否可能安全到达最右边
链接:https://codeforces.ml/contest/586/problem/D
思路:人向右移1位,火车向左移2位,根据相对运动,那么实际相当于人向右移动了3位,
只不过在做的时候需要特判原先位置的右边1位是否能移动,因为人向上下移动之前先要右移一位,
但是在判断的时候是按照上中下三条铁轨的后三位判断的,这里会忽略之前人是否能向右移动的那一位,
如果原先都无法右移一位,火车也无法向左移动2位,自然就没有相对运动3步之说.
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n,k,vis[4][110],flag;
char mp[4][110];

int dfs(int x,int y){
    if(y>n) return 1;
    if(mp[x][y+1]!='.') return 0;//特判人是否能先行移动向右的那一步,否则回退.
    vis[x][y]=1;
    for(int i=-1;i<=1;i++){
        if(x+i<1 || x+i>3) continue;
        int flag=0;
        for(int j=1;j<=3;j++){//人向右相对移动不能和火车相撞
            if(mp[x+i][y+j] != '.'){
                flag=1;
                break;
            }
        }
        if(vis[x+i][y+3]) continue;//走过的状态无需重复走
        if(!flag){
            if(dfs(x+i,y+3)) return 1;
        }
    }
    return 0;
}

int main(){
    int x,y,T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=3;i++){
            for(int j=1;j<=n;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 's') x=i,y=j;
            }
            for(int h=1;h<=3;h++)//有可能移动会超过原先铁轨的列的范围
                mp[i][n+h]='.';
        }
        if(dfs(x,y))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
