/*
����:һ��N��M���ɷǸ��������ɵ����־�������Ҫ������ȡ�����ɸ����֣�
ʹ��ȡ���������������ֲ����ڣ���һ������������һ����������8��������
��һ������Ϊ�������������ڣ�����ȡ�����ֺ�����Ƕ��١�
n,m<=6.
����:https://www.luogu.com.cn/problem/P1123
˼·:ö��ÿ������ȡ��ȡ,��Ҫ���ȡ���ĸ��ӵ�8�������ǲ���ȡ��.
*/
#include<cstdio>
#include<cstring>
int a[8][8],n,m,vis[8][8],maxs;

int judge(int x,int y){
    if(!vis[x][y-1]&&!vis[x-1][y] &&!vis[x][y+1]&&!vis[x+1][y]&&!vis[x-1][y-1]&&!vis[x-1][y+1]&&!vis[x+1][y-1]&&!vis[x+1][y+1])
        return 1;
    else
        return 0;
}
//���Գ���++mark[x+d[fx][0]][y+d[fx][1]];
void dfs(int x,int y,int sum){
    if(x>n){
        if(sum>maxs) maxs=sum;
        return;
    }
    if(y>m)
        x++,y=1;
    if(judge(x,y)){//Ҳ����ȡ��ĳ����,�Ͱ�8��������Ϊ����ȡ,dfs(x,y+1)vis�жϵ�ǰ(x,y)�Ƿ���ȡ,
        vis[x][y]=1;
        dfs(x,y+1,sum+a[x][y]);//y+1,����ʱҲ���ٿ��Ǻ���Ľ��,ֻ�������������ѡȡ,��ô����Ԫ�ص�Ӱ��Ҳ��ı�
        vis[x][y]=0;
    }
    dfs(x,y+1,sum);//y+1,ǰ��Ĳ�������̽,��Ϊdfs��ȱ����Ѿ�������ǰ���λ�ñ�������,���ظ�������.
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        maxs=0;
        memset(a,0,sizeof(a));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        dfs(1,1,0);
        printf("%d\n",maxs);
    }
    return 0;
}
