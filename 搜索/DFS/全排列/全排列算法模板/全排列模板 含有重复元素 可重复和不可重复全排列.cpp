#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[10];
void permutation1(int k,int n){//产生可重复的全排列(字典序)(含重复元素)
	if (k == n){
		for (int i = 0; i < n; i++)
			printf("%d ", a[i]);
		putchar('\n');
	}
	else{
		for (int i = k; i < n; i++){
			swap(a[i], a[k]);
			permutation1(k + 1, n);
			swap(a[i], a[k]);
		}
	}
}
int visit[10];
void permutation2(int k, int n){//产生可重复的全排列(字典序)(含重复元素)
	int i;
	if (k == n){
		for (i = 0; i<n; i++) printf("%d ", a[i]);
		printf("\n");
	}
	else{
		for (i = 0; i<n; i++){
			if (!visit[i]){
				a[k] = i + 1;//这里的赋值操作其实就是交换,只不过因为数字的原因,巧妙实现了交换
				visit[i] = 1;
				permutation2(k + 1, n);//下一次退栈会回溯到这里
				visit[i] = 0;//为下一次排列指示应该交换赋值的元素序列
			}
		}
	}
}

bool judge_repetition(int i, int k){
	for (int j = k; j < i;j++)
	if (a[j] == a[i])
		return false;
	return true;
}
void permutation3(int k, int n){//产生不可重复元素全排列(字典序)(含重复元素)
	if (k == n){
		for (int i = 0; i < n; i++)
			printf("%d ", a[i]);
		putchar('\n');
	}
	else{
		for (int i = k; i < n; i++){
			if (!judge_repetition(i, k)) continue;//判断第i个元素是否在k,i－1中出现过,若出现则进行下一个循环,这个其实没太看明白,而且为什么不能改成break,按理只要有相等下一次continue后判断还是会相等的
			swap(a[i], a[k]);
			permutation3(k + 1, n);
			swap(a[i], a[k]);
		}
	}
}


int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	int b[5];
	for (int i = 0; i < n; i++)
		b[i] = a[i];
	permutation3(0, n);
	return 0;
}
/*产生不可重复全排列(含重复元素)
pair<char,int> visit[200];
int cnt=0;

void stat(char *a,int n){
	int i,j;
	for(i=0;i<n;i++){
 		for(j=0;j<cnt&&visit[j].first!=a[i];j++);
 		if(j<cnt) visit[j].second++;
 		else{
 			visit[cnt].first = a[i];
 			visit[cnt].second = 1;
 			cnt++;
 		}
 	}
}

void per(char *a,int k,int n){
	int i,j;
	if(k==n){
		puts(a);
	}
	else{
		for(i=0;i<cnt;i++){
			if(visit[i].second){
				a[k] = visit[i].first;
				visit[i].second--;
				per(a,k+1,n);
				visit[i].second++;
			}
		}
	}
}
*/
