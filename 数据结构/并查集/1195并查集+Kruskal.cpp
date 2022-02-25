#include<cstdio>
#include<algorithm>
using namespace std;
struct edge{
	int x;
	int y;
	int price;
}city[10001];
int vertex[1002];
bool cmp(edge a, edge b){
	return a.price > b.price;
}
void Init(int n){
	for (int i = 1; i <= n; i++)
		vertex[i] = i;
}
/*int find(int x){
	int tmp=x;
	while (vertex[x] != x)
		x = vertex[x];
	while (vertex[tmp] != x){
		vertex[tmp] = x;
		tmp = vertex[tmp];
	}
	return x;
}*/
int find(int x){
	if (vertex[x] != x)
		return vertex[x] = find(vertex[x]);
	else
		return x;
}
bool Union(int v, int w){//不是每次都会把这个连通集内的所有结点的父节点都统一的，得看具体加的这条的边的结点在连通集的位置，是不是第一个结点，如果是第一个结点就会全部更新,这并不影响最小树权值的和的求取
	int x = find(v);
	int y = find(w);
	if (x != y){
		vertex[x] = y;
		return true;
	}
	else
		return false;
}
int Kruskal(int m,int n){
	sort(city, city + m, cmp);
	int sum=0,cnt=0;
	for (int i = 0; i < m; i++){
		if (cnt == n - 1) return sum;//对于树而言连通无回路,边数等于点数减1,这里其实是求最大容量所有只要在满足树的条件下继续最大程度地加边
		if (Union(vertex[city[i].x], vertex[city[i].y])){
			sum += city[i].price;
			cnt++;
		}
	}
	return sum;
}
int main(){
	int n, m,num;
	scanf("%d", &num);
	while (num--){
		scanf("%d%d", &n, &m);
		Init(n);
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &city[i].x, &city[i].y, &city[i].price);
		printf("%d\n",Kruskal(m, n));
	}
	return 0;
}
