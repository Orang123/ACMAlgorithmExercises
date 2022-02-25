#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int n, ti[1001], qi[1001];
	while (scanf("%d", &n), n){
		for (int i = 0; i < n; i++)
			scanf("%d", ti + i);
		for (int i = 0; i < n; i++)
			scanf("%d", qi + i);
		sort(ti, ti + n);
		sort(qi, qi + n);
		int low_ti = 0, low_qi = 0, fast_ti = n - 1, fast_qi = n - 1,sum=0;
		for (int i = 0; i < n; i++){
			if (ti[fast_ti]>qi[fast_qi]){//如果田忌最快的马比齐王最快的马快,则赢掉
				sum += 200;
				fast_ti--, fast_qi--;
			}
			else if (ti[fast_ti] == qi[fast_qi]){//如果相等
				if (ti[low_ti] > qi[low_qi]){//如果田忌最慢的马比齐王最慢的马快则赢掉
					sum += 200;
					low_qi++, low_ti++;
				}
				else if (ti[low_ti] <= qi[low_qi]){
					if (ti[low_ti] < qi[fast_qi]){//如果田忌最慢的马比齐王最快的马小于,则用最慢的马输掉齐王最快的马
						sum -= 200;
					}
					else if(ti[low_ti]==qi[fast_qi]){//如果相等,则用最慢的马和最快的马打成平局
					}
					low_ti++, fast_qi--;
				}
				}
			else{//如果田忌最快的马比齐王最慢的马慢,则用田忌最慢的马输掉齐王最快的马
				sum -= 200;
				low_ti++, fast_qi--;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}