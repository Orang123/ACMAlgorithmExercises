/*
����:����һ������С��5�����У�����Ҫ����Щ���зֱ��ź���
��ÿһ�β���ֻ�ܶ�һ�������е�ĳ����Ԫ�ؽ��н�����
���������С���������ж����ַ�����
����:https://www.luogu.com.cn/problem/UVA331
˼·:ð�ݷ�,������������a[i]>a[i+1]�������,����һ�������ٵ�.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 6
using namespace std;

int n,a[N],ans;

int check(){
    for(int i=1;i<n;i++){
        if(a[i]>a[i+1])
            return 0;
    }
    return 1;
}

void dfs(){
    if(check()){
        ans++;
        return;
    }
    for(int i=1;i<n;i++){
        if(a[i]>a[i+1]){
            swap(a[i],a[i+1]);
            dfs();
            swap(a[i],a[i+1]);
        }
    }
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        if(check()){//��ʼ��� �����������,������Ϊ0.
            printf("There are 0 swap maps for input data set %d.\n",cas);
            continue;
        }
        dfs();
        printf("There are %d swap maps for input data set %d.\n",ans,cas);
    }
    return 0;
}
