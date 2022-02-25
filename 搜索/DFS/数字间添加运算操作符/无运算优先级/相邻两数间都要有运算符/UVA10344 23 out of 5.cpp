/*
����:ժ������
����������� �ж��Ƿ�������ʹ��ʽ��( ( a(1) o a(2) ) o a(3) ) o a(4) ) o4 a(5)����23��
���������������oΪ�������+������-������*����
����:https://www.luogu.com.cn/problem/UVA10344
˼·:����ȫ����,Ȼ��dfsö�����������.
���ⲻ��������01�����Ǹ�״̬ת������,��Ϊ�������
������ɴ�50^5=312,500,000,�ռ临�ӶȲ���.
*/
//ac 70ms ���Ӷ�(5!*3^4)
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 6
using namespace std;

int a[N];

int dfs(int k,int sum){
    if(k == 6){
        if(sum == 23)
            return 1;
        else
            return 0;
    }
    if(dfs(k+1,sum+a[k]))
        return 1;
    if(dfs(k+1,sum-a[k]))
        return 1;
    if(dfs(k+1,sum*a[k]))
        return 1;
    return 0;
}

int main(){
    int flag;
    while(scanf("%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&a[5]) && a[1]+a[2]+a[3]+a[4]+a[5]){
        sort(a+1,a+1+5);
        flag=0;
        do{
            if(dfs(2,a[1])){
                flag=1;
                printf("Possible\n");
                break;
            }
        }while(next_permutation(a+1,a+1+5));
        if(!flag)
            printf("Impossible\n");
    }
    return 0;
}
