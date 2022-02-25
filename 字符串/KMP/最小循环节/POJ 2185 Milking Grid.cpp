/*
题意:摘自网上
给你一个R*C的字符矩阵,要你求最小的子矩阵,我们能通过不断重复该子矩阵
从而得到一个大矩阵把原矩阵包含在内,求这个子矩阵的面积?
注意:
输入样例中的答案"AB",实际能拼成的图案是要大于原始图案的.
ABABAB 多了1列B 只要包含在内就行.
ABABAB        B
r<=10^4,c<=75.
链接:http://poj.org/problem?id=2185
思路:可以把每一行当成一个元素,比较两行是比较所在行对应所有列的元素是否相等,
求出next输出,r-next[r]最小循环节便是最小矩阵的宽.
可以把每一列当成一个元素,比较两列是比较所在列对应所有行的元素是否相等,
求出next输出,c-next[c]最小循环节便是最小矩阵的长.这样便可求得最小面积.
*/
//ac 782ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 80
using namespace std;

int r,c,nxt[N];
char p[N][M];

int checkCol(int i,int j){
    for(int k=0;k<c;k++){
        if(p[i][k]!=p[j][k])
            return 0;
    }
    return 1;
}

int checkRow(int i,int j){
    for(int k=0;k<r;k++){
        if(p[k][i]!=p[k][j])
            return 0;
    }
    return 1;
}

void getNextRow(){
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<r){
        if(i == -1 || checkCol(i,j))
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

void getNextCol(){
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<c){
        if(i == -1 || checkRow(i,j))
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int row,col;
    scanf("%d%d",&r,&c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
            scanf(" %c",&p[i][j]);
    }
    getNextRow();
    row=r-nxt[r];//宽
    getNextCol();
    col=c-nxt[c];//长
    printf("%d",row*col);
    return 0;
}
