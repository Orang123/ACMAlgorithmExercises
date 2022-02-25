#include<cstdio>
#include<algorithm>
using namespace std;

/*
����:���ʹ�����г����໥��ͨ�ĵ�·���跽��,����ʹ�õ�·��
��ֵԽ��ı߾�����С.ɾ������ĵ�·����,��·�е�����ֵ.
����:https://loj.ac/problem/2149
˼·:����ʹ�õ�·�з�ֵԽ��ı߾�����С,��С������������Ȩ��������������
����Ȩ����С��,���Ժ�����Kruskal���һ��������,�����ⲻһ����ͨ,�������
���ռӱߵĸ���������Ȩ.
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
bool Union(int v, int w){//����ÿ�ζ���������ͨ���ڵ����н��ĸ��ڵ㶼ͳһ�ģ��ÿ�����ӵ������ıߵĽ������ͨ����λ��,Խ�ں����Խ��·��ѹ��ͳһָ����ڵ㣬�ǲ��ǵ�һ����㣬����ǵ�һ�����ͻ�ȫ������,�Ⲣ��Ӱ����С��Ȩֵ�ĺ͵���ȡ
	int x = find(v);
	int y = find(w);
	if (x != y){
		vertex[x] = y;//������µ���Զ����ĳ����ͨ���ڵĸ��ڵ�ĸ��ڵ�
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
                return;//������������ͨ�޻�·,�������ڵ�����1,������ʵ���������������ֻҪ���������������¼������̶ȵؼӱ�
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
