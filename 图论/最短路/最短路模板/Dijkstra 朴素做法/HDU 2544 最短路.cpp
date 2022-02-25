#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
/*
����:��1->n�����·
����:http://acm.hdu.edu.cn/showproblem.php?pid=2544
˼·:���·����,����Dijkstra�����ذ汾.
*/

int G[110][110];
int cost[110],n;
bool visit[110];
void init(){//��ʼ����1����������ľ���
    for(int i=1;i<=n;i++){
        G[i][i]=0;
        cost[i]=G[1][i];
    }
}
//O(n^2+m)~=O(n^2)
int Dijkstra(){
    int minVal,minIndex;
    init();
    for(int i=1,j;i<=n;i++){
        minVal=INF;//����minval��ʼ��INFҪ���ڵ�һ��ѭ���Ŀ�ʼ������ʱ��Ϊ���λ�÷Ŵ��� wrong�˺þ�
        for(j=1;j<=n;j++){//̰��
            if(!visit[j]&&cost[j]<minVal){
                minVal=cost[j];//��⵱ǰ��1�������������̾���
                minIndex=j;
            }
        }
        visit[minIndex]=true;
        for(int k=1;k<=n;k++){//���������������С��ȥ�����ܸ��������㼯
            if(!visit[k]&&cost[minIndex]+G[minIndex][k]<cost[k]){
                cost[k]=cost[minIndex]+G[minIndex][k];
            }
        }
    }
    return cost[n];
}

int main(){
    int m,x,y,val,res;
    while(scanf("%d%d",&n,&m)&&n+m){
        memset(G,INF,sizeof(G));
        memset(visit,false,sizeof(visit));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&x,&y,&val);
            G[x][y]=G[y][x]=val;
        }
        printf("%d\n",Dijkstra());
    }
    return 0;
}
