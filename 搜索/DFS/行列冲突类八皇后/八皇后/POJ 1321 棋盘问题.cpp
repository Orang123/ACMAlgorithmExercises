/*
题意:在一个给定n*n形状的棋盘（形状可能是不规则的）上面摆放k个棋子，棋子没有区别。
要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列，请编程求解对于给
定形状和大小的棋盘，摆放k个棋子的所有可行的摆放方案C。
k<=n;
链接:http://poj.org/problem?id=1321
思路:因为棋子的数量可能少于棋盘行的个数,那么就存在放不满的情况,
在经典的八皇后问题上 再枚举每行是否放置棋子.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,cnt,col[10];
char map0[10][10];

void dfs(int row,int num){
    if(num == k){
        cnt++;
        return;
    }
    if(row == n+1) return;
    for(int i=1;i<=n;i++){
        if(map0[row][i]=='#' && !col[i]){
            col[i]=1;
            dfs(row+1,num+1);
            col[i]=0;
        }
    }
    /*
    因为有可能k<n&k<'#'棋盘的位置个数,所以有可能棋子都摆放完了,
    但是后面的行还有剩余的棋盘位置,所以假定先不摆前面的行,先摆后面的行,
    这样就能枚举出所有可能的摆法.
    */
    dfs(row+1,num);
}

int main(){
    while(scanf("%d%d",&n,&k) && n!=-1&&k!=-1){
        cnt=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&map0[i][j]);
        }
        dfs(1,0);
        printf("%d\n",cnt);
    }
	return 0;
}
/*
//位运算版本
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,cnt,col[10];
char map0[10][10];

void dfs(int row,int num,int c){
    if(num == k){
        cnt++;
        return;
    }
    if(row == n+1) return;
    for(int i=0;i<n;i++){
        int j=1<<i;
        if(~c&j && map0[row][i+1]=='#')
            dfs(row+1,num+1,c|j);
    }
    dfs(row+1,num,c);
}

int main(){
    while(scanf("%d%d",&n,&k) && n!=-1&&k!=-1){
        cnt=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&map0[i][j]);
        }
        dfs(1,0,0);
        printf("%d\n",cnt);
    }
	return 0;
}

*/
