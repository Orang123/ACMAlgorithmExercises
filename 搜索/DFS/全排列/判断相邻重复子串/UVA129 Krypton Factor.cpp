/*
题意:将一个包含两个相邻的重复子串的子串，称为“容易的串”，
其他为“困难的串”。 输入正整数n和l,输出由前l个字符组成的，
字典序第k小的困难的串。
l<=26.
链接:https://www.luogu.com.cn/problem/UVA129
思路:同UVA11127 ,就是每添加一个字符,从后缀判断是否包含
相邻的重复子串.
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
            if(!(i%64) || i+1 == k)//要先判断 输出换行在判断 空格 注意这里有可能能被4整除,不被64整除,但是到了最后一个字符 要输出换行
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
