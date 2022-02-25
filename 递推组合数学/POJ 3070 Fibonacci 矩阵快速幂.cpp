#include<cstdio>
#define mod 10000
/*[Fn+1,Fn,Fn,Fn-1] * [1,1,1,0]=[Fn+2,Fn+1,Fn+1,Fn];
�������˵Ĺ���ǡ�þ��Ǽ���쳲��������еĹ��� ��[0][0]���λ�õ���Ϊ��Fn+1*1+Fn*1=Fn+2  [0][1]�ϵ���Fn+1*1+Fn*0=Fn+1*/

void cal(int x[][2],int y[][2],int z[][2]){//��������
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

int Fib(int n){//��������������� ʱ�临�Ӷ�O(log(n) +1 ) ��Ƚ�O(n)ֱ����˵Ĵ���Ч�����
    int a[2][2]={1,1,1,0},E[2][2]={1,0,0,1};
    while(n){
        if(n&1)//�����ǰλ��1˵����������������,�Ǿ���a��֮ǰ��E���
            cal(a,E,E);
        cal(a,a,a);//�ۼ�ż������ ����˷�����
        n>>=1;//ÿ������һλ
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

