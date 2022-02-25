/*
����:ժ������
ƽ������k���ϰ��㡣 ��(0,0)���������һ����1����λ���ڶ�����2����λ��������
��n����n����λ��ǡ�ûص�(0,0)�� Ҫ��ֻ�����Ŷ������������ߣ���ÿ�α���ת��90��
����������ͬһ����������ߣ�Ҳ���ܺ��ˣ��� �߳���ͼ�ο����Խ��������ܾ����ϰ��㡣
������п��ߵķ���·�����С�
ע��:ÿ����i����,��ͣ���ڸõ�ι�,���Ǹõ�ֻ��ι�һ��.
n<=20.ʵ������
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=161
˼·:dfsÿ���ߵĲ���Ҫ��1,���Ҫ��¼�ϴ��ߵķ���,�����ߵķ�����ϴη���һ��,
�Լ�����������.ÿ����s��,��Ҫ����ÿһ��ÿһ���ж����ߵ�λ���Ƿ�����ϰ���,�Լ��Ƿ�
�����߽�.�п����ϰ�������Ϊ��,�������±겻��Ϊ��,���Լ�¼���ж��ϰ�������(x,y)
ʱҪ���������105,�������������ߵ���󳤶�Ϊ1+2+..20=20*21/2=210,��ʵ����Ϊ����
�����ܳ���һ������һֱ��,��˴��105�����ֱ�߳���.
����һ�����������پ���ļ�֦,�����ǰλ��(x,y)����ԭ��������پ���abs(x)+abs(y)����
ʣ�������ߵľ���sum[n]-sum[s]ʱ ����.
sum[i]��ʾǰi�������ߵ�������.
������Ϊ��û����ȡ��̾���,��˲���bfsҲ�ǿ���ʵ�ֵ�.
*/
//ac 280ms dfs+��֦
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 250
#define maxn 105
using namespace std;

int n,k,sum[21],dir[4][2]={{1,0},{0,1},{0,-1},{-1,0}},mp[N][N],ans;
char path[21],pathDir[4]={'e','n','s','w'};//Ҫ���ֵ��� ��¼·�������ensw��������

int exceed(int x,int y){
    if(abs(x)>maxn || abs(y)>maxn)
        return 1;
    return 0;
}

int check(int x,int y,int d,int s){
    for(int i=1;i<=s;i++){
        x+=dir[d][0];
        y+=dir[d][1];
        if(exceed(x,y) || mp[x+maxn][y+maxn] == -1)//��s�������������ϰ��� Ҫ����
            return 0;
    }
    //��֦:�����ǰλ��(x,y)����ԭ��������پ���abs(x)+abs(y)����ʣ�������ߵľ���sum[n]-sum[s]ʱ ����.
    if(abs(x)+abs(y)>sum[n]-sum[s])//���������پ����֦760ms,���������֦280ms
        return 0;
    return 1;
}

void dfs(int x,int y,int d,int s){
    if(s == n+1){//��n�ε�n������
        if(!x && !y){
            ans++;
            for(int i=1;i<=n;i++)
                printf("%c",path[i]);
            printf("\n");
        }
        return;
    }
    int nx,ny;
    for(int i=0;i<4;i++){
        if(i == d || i+d == 3)//���ܳ��ź��ϴη���һ�·����� Ҳ����������
            continue;
        if(!check(x,y,i,s))
            continue;
        nx=x+dir[i][0]*s;
        ny=y+dir[i][1]*s;
        if(!mp[nx+maxn][ny+maxn]){//��s����,ͣ���ڵ�(nx,ny)�� ֻ��ͣ��һ��
            mp[nx+maxn][ny+maxn]=1;//��Ǹõ��ѷ���
            path[s]=pathDir[i];//��¼����
            dfs(nx,ny,i,s+1);
            mp[nx+maxn][ny+maxn]=0;
        }
    }
}

int main(){
    int T,x,y;
    for(int i=1;i<=20;i++)
        sum[i]=sum[i-1]+i;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(mp,0,sizeof(mp));
        scanf("%d%d",&n,&k);
        while(k--){
            scanf("%d%d",&x,&y);
            if(exceed(x,y))
                continue;
            mp[x+maxn][y+maxn]=-1;
        }
        dfs(0,0,-1,1);
        printf("Found %d golygon(s).\n\n",ans);
    }
    return 0;
}
