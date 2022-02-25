//HDU 5627
//https://www.cnblogs.com/spfa/p/6594738.html
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5+6;
int x[maxn], y[maxn], w[maxn], flag[maxn], fa[maxn];
int find_set(int x){if(x == fa[x]) return x; return fa[x] = find_set(fa[x]);}
void union_set(int x, int y){x = find_set(x), y = find_set(y); if(x!=y) fa[x] = y;}
int n, m;

int main(){
    int T; scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; i++) scanf("%d%d%d", &x[i], &y[i], &w[i]);
        int ans = 0;
        for(int i = 30; i >= 0; i--){
            for(int j = 1; j <= n; j++) fa[j] = j;
            for(int j = 1; j <= m; j++){
                if((w[j]&ans) == ans && (w[j]>>i&1)) flag[j] = 1;
                else flag[j] = 0;
            }
            for(int j = 1; j <= m; j++){
                if(flag[j]){
                    union_set(x[j], y[j]);
                }
            }
            bool ok = 1;
            int p = find_set(1);
            for(int j = 2; j <= n; j++){
                if(find_set(j) != p){
                    ok = 0;
                }
            }
            if(ok) ans |= (1<<i);
        }
        printf("%d\n", ans);
    }
    return 0;
}
