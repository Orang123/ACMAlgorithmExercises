/*
//题意摘自网上
题意:在坦克大战游戏中，要让自己找到敌人并消灭它。问：给你一个地图，
Y表示自己，T表示敌人，E表示空地，B表示砖墙，R表示河流，S表示金属墙，
你只能通过E和T，只需一步，B，需两步，因为要先打掉它。并且你只能从四个方向走，
即上下左右。求出到达敌人位置的最小步数。如若不能到达，输出-1。
链接:http://poj.org/problem?id=2312
思路:由于B砖墙和E通过时间不同,因此优先队列.
*/
//ac 63ms
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct node{
	int x, y;
	int step;
	friend bool operator< (const node &a,const node &b){
		return a.step>b.step;//最少 小顶堆
	}

};
char map[310][310];
bool visit[301][301];
int pos[4][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };
bool judge(int x, int y){
	if (map[x][y] == 'R' || map[x][y] == 'S')
		return false;
	if (x < 0 || y < 0 || x >= 310 || y >= 310)
		return false;
	return true;
}
int BFS(int x, int y){
	priority_queue<node> Q;
	memset(visit, false, sizeof(visit));
	node tmp,next;
	visit[x][y] = true;
	tmp.x = x, tmp.y = y, tmp.step = 0;
	Q.push(tmp);
	while (!Q.empty()){
		tmp = Q.top();
		Q.pop();
		for (int i = 0; i < 4; i++){
			next.x =tmp.x+ pos[i][1];
			next.y =tmp.y+ pos[i][0];
			if (!visit[next.x][next.y] && judge(next.x, next.y)){
				if (map[next.x][next.y] == 'B')
					next.step = tmp.step + 2;
				else
					next.step = tmp.step + 1;
				visit[next.x][next.y] = true;
				Q.push(next);
				if (map[next.x][next.y] == 'T') return next.step;
			}
		}
	}
	return -1;
}
int main(){
	int n, m,x,y;
	while (scanf("%d%d", &n, &m), n || m){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				scanf(" %c", map[i] + j);
				if (map[i][j] == 'Y'){
					x = i, y = j;
				}
			}
		}
		printf("%d\n", BFS(x, y));
	}
	return 0;
}
