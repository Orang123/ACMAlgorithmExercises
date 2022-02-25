/*
���⣺�ҵ�һ��ֻ��0��1��ɵ����ܰ�n��������ʵ���λ��20λ�����޷��� __int64 ����20λ��
Ȼ���������ݲ�������Сֵ,��Ŀ���ֻҪ�����ܳ�������,�������ֽ����������С�Ľ�.
����:http://poj.org/problem?id=1426
˼·:ö��ÿһλҪôȡ0,Ҫôȡ1.
*/
//ac
//O(2^n)=2^20=10^%6
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned __int64 ll;
int n,flag;
void dfs(ll sum,int num){
    if(num == 19) return;
    if(flag) return;
    if(sum%n==0){
        printf("%I64d\n",sum);
        flag=1;
        return;
    }
    dfs(sum*10,num+1);//157ms
    dfs(sum*10+1,num+1);//ò������ö����һλ1 �������������,0ms
}

int main(){
    while(scanf("%d",&n) && n){
        flag=0;
        dfs(1,0);
    }
    return 0;
}

/*
bfsҲ������
*/
