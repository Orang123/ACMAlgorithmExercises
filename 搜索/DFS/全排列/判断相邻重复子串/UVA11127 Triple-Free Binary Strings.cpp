/*
����:ժ������
��������Ϊn���ַ������ַ����ɡ�1������0������*����ɣ�
���С�*�����������滻Ϊ��1������0�����󲻴�������3��
��ͬ�Ӵ����ַ�������������
n<31.
����:https://www.luogu.com.cn/problem/UVA11127
˼·:����'*'λ��ö�����ֿ���һ��'0'һ��'1',����
ö�ٳ����е��ַ������ж��Ƿ��������3����ͬ�Ӵ�
�϶��ᳬʱ,�ַ����ĸ���������Ϊ2^30=1073741824��.
���Ҫ��ö�ٵĹ����ж�[1,k]���Ӵ��ж��Ƿ��������3��
��ͬ�Ӵ�,�������,��ֹͣ����.
*/
//ac 100ms dfs����
//���Ӷ�O(2^n) nΪ'*'�ĸ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
using namespace std;

int n,ans;
char str[N];//strС���1��ʼ

//�ж�[1,k]���Ӵ��ж��Ƿ��������3����ͬ�Ӵ�
//����ж�ֻ�ῼ���¼���ĩβ���ַ�str[k]�ܷ��ǰ���Ӵ���������3����ͬ�Ӵ�
//��Ϊ[1,k-1] [1,k-2] [1,k-3] ���Ӵ�֮ǰ�Ѿ��жϹ���.
int check(int k){
    int flag;
    for(int i=1;i*3<=k;i++){//ö���Ӵ��ĳ���
        flag=0;
        //�����������Ӵ����±귶ΧΪ [k-i+1,k],���Ӵ��е�ÿһλ�͵ڶ����Ӵ� ��һ���Ӵ���Ӧλ�õ����ж�
        for(int j=k;j>=k-i+1;j--){
            if(str[j] != str[j-i] || str[j] != str[j-2*i]){//ֻҪĳһλ��ͬ �Ϳ���˵����ǰ����i�²���������3���Ӵ����,ֱ�ӽ���
                flag=1;
                break;
            }
        }
        if(!flag)//�����ĳһ����i�� ��������3������Ӵ� ��ֱ�ӷ���0 ���ɼ���������ȥ��
            return 0;
    }
    return 1;
}

void dfs(int k){
    if(k == n+1){
        ans++;//��Ŀ��1
        return;
    }
    if(str[k] == '0' || str[k] == '1'){
        if(check(k))
            dfs(k+1);
    }
    else{
        str[k]='0';
        if(check(k))
            dfs(k+1);
        str[k]='1';
        if(check(k))
            dfs(k+1);
        str[k]='*';
    }
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        if(!n)
            break;
        scanf("%s",str+1);
        cas++;
        ans=0;
        dfs(1);
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}

/*
//ac 30ms ������λ�����Ż� ��̫����������
//ժ�Բ���:https://blog.csdn.net/u011345461/article/details/38660695
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 32;

char str[MAXN];
int n, ans;

bool judge(int s, int d) {
    int k = (1 << d) - 1;
    int a = s & k;
    s = s >> d;
    int b = s & k;
    s = s >> d;
    int c = s & k;
    if (a == b && b == c)
        return true;
    else
        return false;
}//����λ���㣬����dλ���ж��Ƿ����3���Ӵ���ͬ

void dfs(int s, int cnt) {
    int num = cnt / 3;
    int t = n - cnt - 1;
    for (int i = 1; i <= num; i++) {
        if (judge(s >> (t + 1), i))
            return;
    }
    if (cnt == n) {
        ans++;
        return;
    }
    else if (str[cnt] == '0') {
         dfs(s, cnt + 1);
    }
    else if (str[cnt] == '1') {
         dfs(s + (1 << t), cnt + 1);
    }
    else if (str[cnt] == '*') {
         dfs(s, cnt + 1);
         dfs(s + (1 << t), cnt + 1);
    }
    return;
}

int main() {
    int cas = 1;
    while (scanf("%d", &n) && n) {
        scanf("%s", str);
        ans = 0;
        dfs(0, 0);
        printf("Case %d: %d\n", cas++, ans);
    }
    return 0;
}
*/
