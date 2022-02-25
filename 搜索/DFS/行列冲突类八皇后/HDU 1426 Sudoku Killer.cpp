/*
����:ժ������
������Ϸ�Ĺ����������ģ���һ��9x9�ķ����У�����Ҫ������1-9��д���ո��У�
����ʹ�����ÿһ�к�ÿһ���ж�����1-9��Ÿ����֡�ͬʱ��Ҫ��֤���ո�����
���߻��ֳ�9��3x3�ķ���Ҳͬʱ����1-9��Ÿ����֡�����������һ���⣬
��ҿ�����ϸ�۲�һ�£���������ÿ�С�ÿ�У��Լ�ÿ��3x3�ķ��񶼰���1-9��Ÿ����֡�
����:https://acm.hdu.edu.cn/showproblem.php?pid=1426
˼·:����ö����ÿ��'?'λ���ܷ��õ�����,���뱣֤ͬ��ͬ��,
�Ź����ڲ��ܺ�֮ǰ���úõ��ظ�.
���ھŹ����ڵ����ֵ�λ�ü��㷽ʽΪ[x/3*3,x/3*3+2],[y/3*3,y/3*3+2].

���и�����������������:dance-link ��û��
*/
//ac 140ms dfs����
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
//POJ 2676 ժ�Բ���:https://tigerisland.blog.csdn.net/article/details/104491808
//��һ�ֿռ任ʱ������� ����������ά���� ��ʾ ���оŹ����Ƿ���ù�1~9������

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
