/*
����:[l,r]�����ڵ���2����λֻ��1��0�ĸ����Ƕ��١�
1<=l,r<=10^18.
����:https://codeforces.ml/problemset/problem/611/b
˼·:���Դ�1��ʼö��,ÿ������һλ,�������û��0,��ֻ���Ʋ���1,
��֤��һ��0,������0��û��0,��Ҫ����һλ+1��
*/
//ac 31ms
//�2^64,��ʵ�ʲ�����ÿ�ζ�ö��2��dfs,���һ�����r�Ĵ�С����.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

ll l,r,cnt;

void dfs(ll x,int flag){
    if(x>r) return;
    if(flag && x>=l && x<=r)
        cnt++;
    if(!flag)//������λ��û��1����0
        dfs(x<<1,1);//ѡ������һλĩλ��0,�����dfs���ƺ���+1,��ΪҪ���������λֻ��һ��0�ĸ���
    dfs((x<<1)+1,flag);//�����п���ȫ��1,Ҳ�п���ֻ��һ��0
}

int main(){
    scanf("%lld%lld",&l,&r);
    dfs(1,0);//��ʼ1 �ǻ�û��0��,����flag=0
    printf("%lld",cnt);
    return 0;
}

/*
bfsҲ������
*/
