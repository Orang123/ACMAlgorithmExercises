/*
����:
����24�����ž�������˶����������������������ƣ�����A(1),2,3,4,5,6,7,8,9,10,J(11),Q(12),K(13)��
Ҫ��ֻ��'+','-','*','/'������Լ����Ÿı�����˳��ʹ������������Ϊ24(ÿ���������ҽ�����һ��)��
��Ϸ�ܼ򵥣��������޽������������˺����ơ��������������ÿһ����������������ƣ��ж��Ƿ��н⡣
��������涨��������������ж����ܳ���С����
����:https://acm.hdu.edu.cn/showproblem.php?pid=1427
˼·:��Ϊֻ��4����,���п���������ϻ����ұ�����,ö��ȫ����
ʹ��stl�е�next_permutation.
*/
//ac 109ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4
using namespace std;

char str[N];
int a[N],flag;

void dfs(int k,int res1,int res2){
    if(flag)
        return;
    if(k == 4){
        if(res1+res2 == 24 || res1-res2 == 24 || res1*res2 == 24 || (res2 && res1%res2 == 0 && res1/res2 == 24))
            flag=1;
        return;
    }
    dfs(k+1,res1+res2,a[k]);
    dfs(k+1,res1-res2,a[k]);
    dfs(k+1,res1*res2,a[k]);
    if(res2 && res1%res2 == 0)
        dfs(k+1,res1/res2,a[k]);
    dfs(k+1,res1,res2+a[k]);
    dfs(k+1,res1,res2-a[k]);
    dfs(k+1,res1,res2*a[k]);
    if(a[k] && res2%a[k] == 0)
        dfs(k+1,res1,res2/a[k]);

}

int main(){
    while(scanf("%s",str)!=EOF){
        for(int i=0;i<4;i++){
            if(i)
                scanf("%s",str);
            if(strlen(str) == 2)
                a[i]=10;
            else if(str[0] == 'A')
                a[i]=1;
            else if(str[0] == 'J')
                a[i]=11;
            else if(str[0] == 'Q')
                a[i]=12;
            else if(str[0] == 'K')
                a[i]=13;
            else
                a[i]=str[0]-'0';
        }
        sort(a,a+4);
        flag=0;
        do{
            dfs(2,a[0],a[1]);
            if(flag){
                printf("Yes\n");
                break;
            }
        }while(next_permutation(a,a+4));
        if(!flag)
            printf("No\n");
    }
    return 0;
}
