/*
����:ժ������
����R�Ժ�ɫľ��,G����ɫľ��,B����ɫľ���ĳ���r[i]��g[i]��b[i],
ÿ�ο���ѡ��������ɫ��ͬ��ľ���Ա���ɫ��ͬ,�ڱ���ɫ��ͬ���һ������,
ÿ��ľ��ֻ��ʹ��һ��,ľ��������ʣ��.�����������ɵľ��ε����.
R,G,B<=200
����:https://codeforces.com/contest/1398/problem/D
˼·:����Ҫ������Ҫ��ıߺʹ�ı������һ�� ����������,���Ǹ�̰�ĵ�˼·.
��˶�������ɫ��ľ�����Ƚ�������,ö������ѡ�񳤶Ƚϴ��ľ��ȥ���,���Ƕ���
ʣ��ľ����ö�ٵĹ����л�����ص�������,��˼��仯����,��������������ľ������
Ϊ0��ֻʣ��1��ľ���޷���ɾ���.����״̬�ǲ�ȷ����.
dp[i][j][k]��ʾ�ں�ɫľ��ʣ��i��,��ɫľ��ʣ��j��,��ɫľ��ʣ��k��ʱ,������ɵ�
���ε�������.
*/
//ac 77ms ���仯����
//dp[i][j][k]��ʾ�ں�ɫľ��ʣ��i��,��ɫľ��ʣ��j��,��ɫľ��ʣ��k��ʱ,������ɵ�
//���ε�������.
//ʱ�临�Ӷ�O(200*200*200)=8*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int R,G,B,r[N],g[N],b[N],dp[N][N][N];

int dfs(int ri,int gi,int bi){
    int &res=dp[ri][gi][bi];
    if(res)
        return res;
    if(ri && gi)
        res=max(res,r[ri]*g[gi]+dfs(ri-1,gi-1,bi));
    if(ri && bi)
        res=max(res,r[ri]*b[bi]+dfs(ri-1,gi,bi-1));
    if(gi && bi)
        res=max(res,g[gi]*b[bi]+dfs(ri,gi-1,bi-1));
    return res;//����������res=0,����ʣ��ľ���޷�����ɾ���
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&R,&G,&B);
    for(int i=1;i<=R;i++)
        scanf("%d",&r[i]);
    for(int i=1;i<=G;i++)
        scanf("%d",&g[i]);
    for(int i=1;i<=B;i++)
        scanf("%d",&b[i]);
    sort(r+1,r+1+R);
    sort(g+1,g+1+G);
    sort(b+1,b+1+B);
    printf("%d",dfs(R,G,B));
    return 0;
}
