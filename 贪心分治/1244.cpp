#include<cstdio>//典型的最大值最小化问题
int main(){
	int a[10001], T, n, m,maxn,sum;
	scanf("%d", &T);
	while (T--){
		scanf("%d%d", &n, &m);
		sum = 0, maxn = -1;
		for (int i = 0; i < n; i++){
			scanf("%d", a + i);
			sum += a[i];
			if (a[i]>maxn)
				maxn = a[i];
		}
			int mid,every_eaten,cnt;
			while (maxn < sum){//对最大值和总和进行二分
				every_eaten = 0, cnt = 0;
				mid = (maxn + sum) / 2;
				for (int i = 0; i < n;i++)
				if (every_eaten + a[i] <= mid)//如果比mid小,则继续累加别的巧克力
					every_eaten += a[i];
				else{//否则大于mid这个标准则可以作为每天吃巧克力的一个最小值
					cnt++;
					every_eaten = a[i];//并且把导致超过mid的a[i]作为另外一天要吃的
				}
				cnt++;//把不够的那最后一份也作为一天的巧克力份量
				if (cnt <= m)//如果天数小于规定的天数说明,每天吃的巧克力过多
					sum = mid;
				else
					maxn = mid+1;//每天吃的巧克力过小
			}
			printf("%d\n", sum);
	}
	return 0;
}
