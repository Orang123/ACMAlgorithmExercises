/*
题意:给定两个四位素数a、b,要求把a变换到b
变换的过程要保证每次变换出来的数都是一个四位素数,
而且当前这步的变换所得的素数与前一步得到的素数只能
有一个位不同,而且每步得到的素数都不能重复.求从a到b
最少需要的变换次数.无法变换则输出Impossible.
注意:每次变换的数字可以0~9的任意一位,但需保证变换后为
素数,但是最高位的数不能是0,那样就只有3位数了,不是四位数.
链接:http://poj.org/problem?id=3126
思路:先提前预处理出所有4位数的素数判定表prime[N].
之后bfs扩展 对四位数每位尝试变换0~9,需保证变换后
数未被扩展过,并且是素数,新入队的状态变化次数都是加1.
时间复杂度O(N)=9999,每个状态只会被访问一次.
*/
//ac 0ms 筛素数+bfs
//时间复杂度O(N)=9999,每个状态只会被访问一次.
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define N 10000
bool prime[N];
struct node{
	int n;
	int time;
};
void prim(){
	for (int i = 0; i < N; i++)
		prime[i] = true;
	prime[0] = prime[1] = false;
	for (int i = 2; i < 100; i++){
		if (prime[i])
		for (int j = i*i; j < N; j += i)
			prime[j] = false;
	}
}
int BFS(int start,int end){
	if (start == end) return 0;
	int digit[4];
	static bool visit[N];
	memset(visit, false, sizeof(visit));
	queue<node> Q;
	node v;
	visit[start] = true;
	v.n = start, v.time = 0;
	Q.push(v);
	while (!Q.empty()){
		node x;
		x = Q.front();
		Q.pop();
		digit[0] = x.n % 10;
		x.n /= 10;
		digit[1] = x.n % 10;
		x.n /= 10;
		digit[2] = x.n % 10;
		x.n /= 10;
		digit[3] = x.n % 10;
		int tmp;
		node val;
		for (int i = 0; i<4; i++){//枚举位 个位、十位、百位、千位
			tmp = digit[i];
			for (int j = 0; j <= 9; j++){//枚举当前位转换成j
				if (tmp != j){//不能变成本身位的数字
                    //首位不能是0,否则就只有3位数了,要保证是四位数
					if (i == 3 && j == 0) continue;
					digit[i] = j;
					val.n = digit[0] + digit[1] * 10 + digit[2] * 100 + digit[3] * 1000;
                    //当前数必须未被扩展过,并且是素数
					if (!visit[val.n] && prime[val.n]){
						val.time = x.time + 1;
						Q.push(val);
						visit[val.n] = true;
					}
					if (val.n == end) return val.time;
				}
			}
			digit[i] = tmp;
		}
	}
	return -1;
}
int main(){
	int n,start,end,res;
	prim();
	scanf("%d", &n);
	while (n--){
		scanf("%d%d", &start, &end);
		res = BFS(start, end);
		if (res != -1)
			printf("%d\n", res);
		else
			printf("Impossible\n");
	}
	return 0;
}
