
#include<stdio.h>
#define p 100003
long long int a[1001][3];
void dp(){
    int i;
    a[0][0]=1;a[1][1]=1;a[0][2]=1;a[1][0]=0;
    for(i=2;i<=1000;i++){
        a[i][0]=(a[i-2][0]+a[i-1][1]+a[i-2][2])%p;
        a[i][1]=a[i-1][2]%p;
        a[i][2]=(a[i][0]+a[i-1][1])%p;
    }
}

int main(){
    int k;
    dp();
    while(scanf("%d",&k)!=EOF&&k){
        printf("%I64d\n",a[k][0]);
    }
} 
