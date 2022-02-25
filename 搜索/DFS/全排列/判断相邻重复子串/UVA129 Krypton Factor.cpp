/*
����:��һ�������������ڵ��ظ��Ӵ����Ӵ�����Ϊ�����׵Ĵ�����
����Ϊ�����ѵĴ����� ����������n��l,�����ǰl���ַ���ɵģ�
�ֵ����kС�����ѵĴ���
l<=26.
����:https://www.luogu.com.cn/problem/UVA129
˼·:ͬUVA11127 ,����ÿ���һ���ַ�,�Ӻ�׺�ж��Ƿ����
���ڵ��ظ��Ӵ�.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300
using namespace std;

int n,l,cnt;
char str[N];

int check(int len){
    int flag;
    for(int i=1;i*2<=len;i++){
        flag=0;
        for(int j=len;j>=len-i+1;j--){
            if(str[j]!=str[j-i]){
                flag=1;
                break;
            }
        }
        if(!flag)
            return 0;
    }
    return 1;
}

int dfs(int k){
    if(++cnt == n){
        for(int i=1;i<k;i++){
            printf("%c",str[i]);
            if(!(i%64) || i+1 == k)//Ҫ���ж� ����������ж� �ո� ע�������п����ܱ�4����,����64����,���ǵ������һ���ַ� Ҫ�������
                printf("\n");
            else if(!(i%4))
                printf(" ");
        }
        printf("%d\n",k-1);
        return 1;
    }
    for(int i=0;i<l;i++){
        str[k]='A'+i;
        if(check(k)){
            if(dfs(k+1))
                return 1;
        }
    }
    return 0;
}

int main(){
    while(scanf("%d%d",&n,&l) && n+l){
        cnt=-1;
        dfs(1);
    }
    return 0;
}
