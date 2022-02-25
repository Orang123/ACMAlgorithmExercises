#include<cstdio>
#define mod 10000
/*[Fn+1,Fn,Fn,Fn-1] * [1,1,1,0]=[Fn+2,Fn+1,Fn+1,Fn];
矩阵连乘的过程恰好就是计算斐波那契数列的过程 以[0][0]这个位置的数为例Fn+1*1+Fn*1=Fn+2  [0][1]上的数Fn+1*1+Fn*0=Fn+1*/

void cal(int x[][2],int y[][2],int z[][2]){//矩阵连乘
    int tmp[2][2]={0,0,0,0};
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                tmp[i][j]+=x[i][k]*y[k][j]%mod;
                tmp[i][j]%=mod;
            }
        }
    }
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            z[i][j]=tmp[i][j];
}

int Fib(int n){//二分求解矩阵快速幂 时间复杂度O(log(n) +1 ) 相比较O(n)直接相乘的次数效率提高
    int a[2][2]={1,1,1,0},E[2][2]={1,0,0,1};
    while(n){
        if(n&1)//如果当前位是1说明可能是奇数次幂,那就用a和之前的E相乘
            cal(a,E,E);
        cal(a,a,a);//累计偶数次幂 化解乘法次数
        n>>=1;//每次右移一位
    }
    return E[0][1];
}

int main(){
    int n;
    while(scanf("%d",&n)&&n!=-1){
        printf("%d\n",Fib(n));
    }
    return 0;
}

