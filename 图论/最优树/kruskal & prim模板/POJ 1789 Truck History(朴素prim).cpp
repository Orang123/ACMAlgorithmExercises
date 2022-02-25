#include<cstdio>
#include<cstring>
#define maxn 2010
#define INF 0x3f3f3f3f

/*
����:n�����ƺ�,�տ�ʼֻ��һ������,�������ƶ�����һ������ֱ�ӻ��Ӳ���
һ�����Ƶ���һ�����ƵĲ���Ȩֵ������֮������ֲ�ͬ�ĸ���,to��ԭʼ����,
td�Ǵ������������ͣ�d��to��td��������֮��ľ���.
��ʷѧ����ͼ�ҳ���һ���¾�����ν�������ƻ������������������������������,
�Լ����������г��Ƶ������ƻ����������,��ô�����ҳ�ÿ������֮��Ŀ�������
���,Ҳ����Ҫ��֤���г���֮������������й�ϵ���ӻ�ͨ��,����Ҫ��֤��������
�������ܺ���С,��Ϊ��ʽ�еķ���Ϊ1,��ĸΪt0,td�ľ����ܺ�,Ҫ�������,���ĸ��С,
��ʽֵԽ��.
����:http://poj.org/problem?id=1789
˼·:���������С��������Ȩֵ��,��Ϊ��ȫͼ,������prim���Щ.
*/

int G[maxn][maxn],n,cost[maxn];
bool visit[maxn];
void init(){
    memset(visit,false,sizeof(visit));
    memset(cost,0x3f,sizeof(cost));
    cost[1]=0;
}
int prim(){
    int sum=0,pos,minDis;
    init();
    for(int i=1;i<=n;i++){
        minDis=INF;
        for(int j=1;j<=n;j++){
            if(!visit[j]&&cost[j]<minDis){
                pos=j;
                minDis=cost[j];
            }
        }
        visit[pos]=true;
        sum+=minDis;
        for(int k=1;k<=n;k++){
            if(!visit[k]&&G[pos][k]<cost[k]){
                cost[k]=G[pos][k];
            }
        }
    }
    return sum;
}
int main(){
    char str[maxn][9];
    int sum;
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            for(int j=1;j<=i;j++){
                sum=0;
                for(int k=1;k<=7;k++){
                    if(str[i][k]!=str[j][k])
                        sum++;
                }
                G[i][j]=G[j][i]=sum;
            }
        }
        printf("The highest possible quality is 1/%d.\n",prim());
    }
    return 0;
}
