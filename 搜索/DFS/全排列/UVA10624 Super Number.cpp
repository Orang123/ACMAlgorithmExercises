/*
����:ժ������
����n��mҪ���ҳ�������mλ�����ӵ�nλ����mλ������ǰiλ�ǿ��Ա�i������
���û���������������-1.�ж��������ֵ�����С���Ǹ���
0<n<m<30.
����:https://www.luogu.com.cn/problem/UVA10624
˼·:ö��ÿһλ��ȡֵ,��Ϊ��������29λ,������longlong�ķ���,
Ϊ�����۳˵Ĺ��������,���۳˵Ĺ��̱�ȡ����۳�,
����ǰkλ,�ж��Ƿ���ȡ��Ĺ�����,��ǰi-1λ��������10���ϵ�iλ������
�ٶ�kȡ��.
for(int i=1;i<=k;i++)
    sum=(sum*10+a[i])%k;
*/
//ac 1.70s dfs����
//�ʱ���10^29,ʵ�����ݿ���ƫ���� ������������,����ֱ�ӱ���������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,a[N],flag;

int check(int k){
    int sum=0;
    for(int i=1;i<=k;i++)
        sum=(sum*10+a[i])%k;
    return sum;
}

void dfs(int k){
    if(k == m+1){
        flag=1;
        return;
    }
    for(int i=0;i<=9;i++){
        if(!i && k==1) continue;
        a[k]=i;
        if(k>=n){
            if(!check(k))
                dfs(k+1);
        }
        else
            dfs(k+1);
        if(flag)
            return;
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        flag=0;
        cas++;
        scanf("%d%d",&n,&m);
        dfs(1);
        printf("Case %d: ",cas);
        if(flag){
            for(int i=1;i<=m;i++)
                printf("%d",a[i]);
        }
        else
            printf("-1");
        printf("\n");
    }
    return 0;
}
