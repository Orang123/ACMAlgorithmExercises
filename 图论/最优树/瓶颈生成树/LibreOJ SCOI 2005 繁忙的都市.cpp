#include<cstdio>
#include<algorithm>
using namespace std;

/*
题意:求解使得所有城市相互连通的道路建设方案,并且使得道路中
分值越大的边尽可能小.删除改造的道路数和,道路中的最大分值.
链接:https://loj.ac/problem/2149
思路:并且使得道路中分值越大的边尽可能小,最小生成树的最大边权是所有生成树中
最大边权中最小的,所以很明显Kruskal求解一棵生成树,但题意不一定连通,所以输出
最终加边的个数和最大边权.
*/

struct Node{
	int x;
	int y;
	int price;
}edge[10001];
int vertex[1002],maxLen,cnt;
bool cmp(Node a, Node b){
	return a.price < b.price;
}
void Init(int n){
	for (int i = 1; i <= n; i++)
		vertex[i] = i;
}
int find(int x){
	if (vertex[x] != x)
		return vertex[x] = find(vertex[x]);
	else
		return x;
}
bool Union(int v, int w){//不是每次都会把这个连通集内的所有结点的父节点都统一的，得看具体加的这条的边的结点在连通集的位置,越在后面的越会路径压缩统一指向根节点，是不是第一个结点，如果是第一个结点就会全部更新,这并不影响最小树权值的和的求取
	int x = find(v);
	int y = find(w);
	if (x != y){
		vertex[x] = y;//这里更新的永远都是某个连通集内的根节点的父节点
		return true;
	}
	else
		return false;
}
void Kruskal(int m,int n){
	sort(edge, edge + m, cmp);
	for (int i = 0; i < m; i++){
		if (Union(vertex[edge[i].x], vertex[edge[i].y])){
			cnt++;
			if (cnt == n - 1){
                maxLen=edge[i].price;
                return;//对于树而言连通无回路,边数等于点数减1,这里其实是求最大容量所有只要在满足树的条件下继续最大程度地加边
			}
		}
	}
}
int main(){
	int n, m;
    scanf("%d%d", &n, &m);
    Init(n);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].price);
    Kruskal(m,n);
    printf("%d %d\n",cnt,maxLen);
	return 0;
}
