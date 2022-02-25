#include<cstdio>
#include<cstring>
#define maxn 2010
#define INF 0x3f3f3f3f

/*
题意:n个车牌号,刚开始只有一个车牌,其他车牌都是由一个车牌直接或间接产生
一个车牌到另一个车牌的产生权值是它们之间的数字不同的个数,to是原始类型,
td是从它派生的类型，d（to，td）是类型之间的距离.
历史学家试图找出的一件事就是所谓的衍生计划——即卡车类型是如何衍生出来的,
以及衍生出所有车牌的派生计划的最高质量,那么就是找出每个车牌之间的可能衍生
情况,也就是要保证所有车牌之间的衍生都是有关系连接互通的,并且要保证所以衍生
的质量总和最小,因为公式中的分子为1,分母为t0,td的距离总和,要质量最高,则分母最小,
分式值越大.
链接:http://poj.org/problem?id=1789
思路:就是求解最小生成树的权值和,因为完全图,所以用prim会快些.
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
