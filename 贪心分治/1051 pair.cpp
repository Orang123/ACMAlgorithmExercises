#include<cstdio>
#include<algorithm>
using namespace std;
pair<int, int> stick;
int main(){
	pair<int, int> stick[5001];
	bool flag[5001];
	int k, n, minutes, note;
	scanf("%d", &k);
	while (k--){
		minutes = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			scanf("%d%d", &stick[i].first, &stick[i].second);
			flag[i] = false;
		}
		sort(stick, stick+ n);
		for (int i = 0; i < n; i++){
			if (!flag[i]){
				minutes++;
				flag[i] = true;
				note = i;
				for (int j = i + 1; j < n; j++)
				if (!flag[j]&&stick[j].second >= stick[note].second){
					flag[j] = true;
					note = j;
				}
			}
		}
		printf("%d\n", minutes);
	}
	return 0;
}