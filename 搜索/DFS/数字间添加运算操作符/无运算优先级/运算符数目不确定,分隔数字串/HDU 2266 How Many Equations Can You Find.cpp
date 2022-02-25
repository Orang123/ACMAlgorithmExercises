/*
����:����ԭ�ַ���str����֮�����һЩ+��-��,ʹ���õ�ֵ������ֵn��ͬ,
�ж����ֲ�ͬ�ķ���.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2266
˼·:ֱ�ӱ���ö������Щ���ֵļ�����'+'��'-'.
*/
//ac 15ms dfs ��������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

char str[N];
int n,len,ans;

//ʱ�临�Ӷ�O(2^len) ÿ��������ǷŲ����÷ָ��� �ܹ�2^len�����
void dfs(int st,int sum){
    if(st == len+1){
        if(sum == n)
            ans++;
        return;
    }
    int res=0;
    for(int i=st;i<=len;i++){
        res=res*10+str[i]-'0';
        dfs(i+1,sum+res);
        if(st!=1)//ע�⿪ͷ�ĵ�һ������ �����Ǽ���
            dfs(i+1,sum-res);
    }
}

int main(){
    while(scanf("%s%d",str+1,&n)!=EOF){
        ans=0;
        len=strlen(str+1);
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}
