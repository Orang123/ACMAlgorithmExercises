/*
题意:摘自网上
一个n*n的数字矩阵，每次操作可以对任意一行或者一列进行循环移动，
操作次数任意。求每种情况每一列的最大值的最小值。
n<=7.
链接:http://poj.org/problem?id=2078
思路:枚举每一行移动后对应的矩阵的状态,每一行有n种移动可能,
那么有n行,根据乘法原理 矩阵可能的所有状态 有n^n=7^7=823543.
1s内可以接受.
*/
//ac 329ms dfs
#include<cstdio>
#define INF1 -0x3f3f3f3f
#define INF2 0x3f3f3f3f
int map[8][8];
int min_sum,n;
void shift(int row){
    int tmp=map[row][n];
    for(int i=n;i>=2;i--)
        map[row][i]=map[row][i-1];
    map[row][1]=tmp;
}

void dfs(int row){
    if(row == n+1){
        int sum,max_sum=INF1;
        bool flag=true;
        //统计当前移动n行后对应矩阵的最大列的值的最小值是否会更新
        for(int i=1;i<=n;i++){
            sum=0;
            for(int j=1;j<=n;j++)
                sum+=map[j][i];
            //如果某一列的值都不比之前的min_sum小 就没有必要去计算其余列了，因为max_sum只会取这些列中最大的
            if(sum>=min_sum){
                flag=false;
                break;
            }
            max_sum=(sum>max_sum?sum:max_sum);
        }
        if(flag)//只有当 所有列没有比min_sum大于等于的时候才会更新
            min_sum=(max_sum<min_sum?max_sum:min_sum);
        return;
    }
    for(int i=1;i<=n;i++){//枚举第row行移位的可能性,共有n种可能,其中移动n次后,当前行就会回到 初始状态
        shift(row);
        dfs(row+1);
    }
}
int main(){
    while(scanf("%d",&n)&&n!=-1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&map[i][j]);
            }
        }
        min_sum=INF2;
        dfs(1);
        printf("%d\n",min_sum);
    }
    return 0;
}

/*
//ac 391ms dfs
#include<cstdio>
#define INF1 -0x3f3f3f3f
#define INF2 0x3f3f3f3f
int map[8][8];
int min_sum,n;
void shift(int row){
    int tmp=map[row][n];
    for(int i=n;i>=2;i--)
        map[row][i]=map[row][i-1];
    map[row][1]=tmp;
}

void dfs(int row){
    if(row>n) return;
    int sum,max_sum=INF1;
    bool flag=true;
    for(int i=1;i<=n;i++){
        shift(row);
        for(int i=1;i<=n;i++){
            sum=0;
            for(int j=1;j<=n;j++){
                sum+=map[j][i];
            }
            if(sum>min_sum){
                flag=false;
                break;
            }
            max_sum=(sum>max_sum?sum:max_sum);
        }
        if(flag)
            min_sum=(max_sum<min_sum?max_sum:min_sum);
        else
            flag=true;
        dfs(row+1);
    }
}
int main(){
    while(scanf("%d",&n)&&n!=-1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&map[i][j]);
            }
        }
        min_sum=INF2;
        dfs(1);
        printf("%d\n",min_sum);
    }
    return 0;
}
*/
