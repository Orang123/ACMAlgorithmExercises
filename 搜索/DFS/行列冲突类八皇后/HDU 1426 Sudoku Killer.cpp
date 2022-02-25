/*
题意:摘自网上
数独游戏的规则是这样的：在一个9x9的方格中，你需要把数字1-9填写到空格当中，
并且使方格的每一行和每一列中都包含1-9这九个数字。同时还要保证，空格中用
粗线划分成9个3x3的方格也同时包含1-9这九个数字。比如有这样一个题，
大家可以仔细观察一下，在这里面每行、每列，以及每个3x3的方格都包含1-9这九个数字。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1426
思路:可以枚举在每个'?'位置能放置的数字,必须保证同行同列,
九宫格内不能和之前放置好的重复.
对于九宫格内的数字的位置计算方式为[x/3*3,x/3*3+2],[y/3*3,y/3*3+2].

还有个解决数独更快的做法:dance-link 还没看
*/
//ac 140ms dfs回溯
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 9
using namespace std;

struct Pos{
    int x,y;
    Pos(int x=0,int y=0):x(x),y(y){}
}pos[N*N];
char mp[N][N];
int cnt;

int check(int x,int y,char val){
    for(int i=0;i<9;i++){
        if(mp[x][i] == val || mp[i][y] == val)
            return 0;
    }
    int xx=x/3*3,yy=y/3*3;
    for(int i=xx;i<xx+3;i++){
        for(int j=yy;j<yy+3;j++){
            if(mp[i][j] == val)
                return 0;
        }
    }
    return 1;
}

int dfs(int cur){
    if(cur == cnt){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(!j)
                    cout << mp[i][j];
                else
                    cout << " "<< mp[i][j];
            }
            cout << endl;
        }
        return 1;
    }
    int x=pos[cur].x,y=pos[cur].y;
    for(int i=1;i<=9;i++){
        if(check(x,y,'0'+i)){
            mp[x][y]='0'+i;
            if(dfs(cur+1))
                return 1;
            mp[x][y]='?';
        }
    }
    return 0;
}

int main(){
    int flag=0;
    while(cin >> mp[0][0]){
        cnt=0;
        if(mp[0][0] == '?')
            pos[cnt++]=Pos(0,0);
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(i+j == 0) continue;
                cin >> mp[i][j];
                if(mp[i][j] == '?')
                    pos[cnt++]=Pos(i,j);
            }
        }
        if(flag)
            cout<<endl;
        dfs(0);
        flag=1;
    }
    return 0;
}

/*
//POJ 2676 摘自博客:https://tigerisland.blog.csdn.net/article/details/104491808
//另一种空间换时间的做法 定义三个二维数组 表示 行列九宫格是否放置过1~9的数字

#include <iostream>
#include <cstring>

using namespace std;

const int N9 = 9;
const int N = 10;
int map[N][N];
bool row[N][N], col[N][N], grid[N][N];


bool dfs(int r, int c)
{
    if(r == N9) return true;
    bool flag = false;
    if(map[r][c]) {
        if(c == 8) flag = dfs(r + 1, 0);
        else flag = dfs(r, c + 1);
        return flag;
    }
    int k = (r / 3) * 3 + c / 3;
    for(int i=1; i<=9; i++) {
        if(!row[r][i] && !col[c][i] && !grid[k][i]) {
            row[r][i] = col[c][i] = grid[k][i] = true;
            map[r][c] = i;
            if(c == 8) flag = dfs(r + 1, 0);
            else flag = dfs(r, c + 1);
            if(flag) return true;
            map[r][c] = 0;
            row[r][i] = col[c][i] = grid[k][i] = false;
        }
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL),
    std::cout.tie(NULL);

    int t;
    cin >> t;
    while(t--)	{
        memset(row,false,sizeof(row));
        memset(col,false,sizeof(col));
        memset(grid,false,sizeof(grid));

        for(int i = 0; i < N9; i++)
            for(int j = 0; j < N9; j++) {
                char ch;
                cin >> ch;
                map[i][j] = ch - '0';
                if(map[i][j]) {
                    row[i][map[i][j]] = true;
                    col[j][map[i][j]] = true;
                    grid[(i / 3) * 3 + j / 3][map[i][j]] = true;
                }
            }

        dfs(0, 0);

        for(int i = 0; i < N9; i++) {
            for(int j = 0; j < N9; j++)
                cout << map[i][j];
            cout << endl;
        }
    }

    return 0;
}

*/
