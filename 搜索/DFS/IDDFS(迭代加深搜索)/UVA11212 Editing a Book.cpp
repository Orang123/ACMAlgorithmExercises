/*
����:
����һƪn(2��n��9)����Ȼ����ɵ����£�ϣ�����������г�1��2������n��
������Ctrl+X�����У���Ctrl+V��ճ������ݼ����������ÿ�ο���
����һ����������Ȼ�Σ�ճ��ʱ����˳��ճ����ע�⣬������ֻ��һ����
���Բ��������������Σ�ֻ�ܼ��к�ճ�����档���磬Ϊ�˽�{2��4��1��5��3��6}��Ϊ����
���Լ���1����ŵ�2ǰ��Ȼ�����3����ŵ�4ǰ�����磬����{3��4��5��1��2}��
ֻ��һ�μ��к�һ��ճ�����ɡ�����{3��4��5}����{1��2}�󣬻��߽�{1��2}����{3��4��5}ǰ��
����:https://www.luogu.com.cn/problem/UVA11212
˼·:IDA*,dfsö��ÿ��Ҫ�и��ȡ����[i,j],��ϸ������.
��˫�����.
*/
//ac 150ms IDA*
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
using namespace std;

int n,a[N];

//�ж��Ƿ��ϸ�����
int check(){
    for(int i=1;i<n;i++){
        if(a[i] != a[i+1]-1)
            return 0;
    }
    return 1;
}

//���������� ��С��ϵ����ȷ�����ָ���
int h(){
    int cnt=0;
    for(int i=1;i<n;i++){
        if(a[i] != a[i+1]-1)
            cnt++;
    }
    if(a[n]!=n)
        cnt++;
    return cnt;
}

int dfs(int d,int dep){
    if(d == dep){
        if(check())
            return 1;
        else
            return 0;
    }
    //һ�θ���ճ������ܸı�3�����ֵĴ�С��ϵ
    //������ٻ�������Ĵ���Ϊh/3,������d+h()/3>dep ��Ҫ����
    //���ǳ������г�������С������,��˱�Ϊ�˷�.
    if(3*d+h()>3*dep)
        return 0;
    int cnt,old[N],b[N];
    memcpy(old,a,sizeof(a));//��a���鸳ֵ��old����,����ָ�ԭʼ��[i,j]�����
    for(int i=1;i<=n;i++){//ö��Ҫ���� ճ���������[i,j]
        for(int j=i;j<=n;j++){
            cnt=0;
            for(int k=1;k<=n;k++){//��[1,i-1]��[j+1,n]����b������
                if(k<i || k>j)
                    b[++cnt]=old[k];
            }
            for(int k=1;k<=cnt;k++){//ö��[i,j]�����Ҫճ����b������[1,k]�ĺ���
                int l=0;
                for(int t=1;t<=k;t++)//��[1,k]����a������
                    a[++l]=b[t];
                for(int t=i;t<=j;t++)//��old[i,j]����[1,k]����
                    a[++l]=old[t];
                for(int t=k+1;t<=cnt;t++)//ԭ��b[k+1,cnt]β�浽[i,j]�������
                    a[++l]=b[t];
                if(dfs(d+1,dep))
                    return 1;
            }
        }
    }
    return 0;
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=0;;i++){
            if(dfs(0,i)){
                printf("Case %d: %d\n",cas,i);
                break;
            }
        }
    }
    return 0;
}

/*
//TLE dfs+��֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define INF 1000
using namespace std;

int n,a[N],ans;

int check(){
    for(int i=1;i<n;i++){
        if(a[i] != a[i+1]-1)
            return 0;
    }
    return 1;
}

int h(){
    int cnt=0;
    for(int i=1;i<n;i++){
        if(a[i] != a[i+1]-1)
            cnt++;
    }
    if(a[n]!=n)
        cnt++;
    return cnt;
}

void dfs(int d){
    if(check()){
    	if(d<ans)
    		ans=d;
    	return;
	}
    if(3*d+h()>3*ans)
        return;
    int cnt,old[N],b[N];
    memcpy(old,a,sizeof(a));
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cnt=0;
            for(int k=1;k<=n;k++){
                if(k<i || k>j)
                    b[++cnt]=old[k];
            }
            for(int k=1;k<=cnt;k++){
                int l=0;
                for(int t=1;t<=k;t++)
                    a[++l]=b[t];
                for(int t=i;t<=j;t++)
                    a[++l]=old[t];
                for(int t=k+1;t<=cnt;t++)
                    a[++l]=b[t];
                dfs(d+1);
            }
        }
    }
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        ans=INF;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dfs(0);
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}
*/

/*
//ժ�Բ���:https://www.cnblogs.com/Bowen-/p/4952431.html
//��ͨ��bfs+hash���� TLE
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 400000, MAXHASHSIZE = 100003;//MAXHASHSIZE=1000003Ҳ��TLE
int n, idx, target;
int a[10], _head[MAXHASHSIZE], _next[MAXN], st[MAXN];

struct Node {
    int arr[10], dis, num;
    Node (int d = 0): dis(d) {}
    void trans() {
        num = 0;
        for (int i = 0; i < n; i++) {
            num *= 10;
            num += arr[i];
        }
    }
};

bool try_to_insert(Node &cur) {
    int h = cur.num % MAXHASHSIZE;
    int u = _head[h];
    while (u) {
        if (st[u] == cur.num) return false;
        u = _next[u];
    }
    st[idx] = cur.num;
    _next[idx] = _head[h];
    _head[h] = idx++;
    return true;
}

void create(Node &from, Node &des, int start, int len, int k) {
    int z = 0, i = 0;
    for (; z < k; z++) {
        if (z >= start && z < start + len) { z += (len - 1); continue;}
        des.arr[i++] = from.arr[z];
    }
    for (z = 0; z < len; z++) des.arr[i++] = from.arr[start + z];
    for (z = k; z < n; z++) {
        if (z >= start && z < start + len) { z += (len - 1); continue;}
        des.arr[i++] = from.arr[z];
    }
}

bool impossible(Node &cur) {
    int cnt = 0;
    for (int i = 1; i < n; i++) if (cur.arr[i - 1] + 1 != cur.arr[i]) cnt++;
    cnt = cnt ? cnt + 1 : 0;
    return cnt > 3 * (5 - cur.dis);
}

int bfs() {
    queue<Node> q;
    Node start;
    for (int i = 0; i < n; i++) start.arr[i] = a[i];
    start.trans();
    try_to_insert(start);
    q.push(start);
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        cur.trans();
        if (cur.num == target) return cur.dis;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= n; j++)
                for (int k = 0; k <= n; k++) {
                    if (k >= i && k <= j) { k = j; continue;}
                    Node nextn;
                    create(cur, nextn, i, j - i, k);
                    nextn.trans();
                    if (!impossible(nextn) && try_to_insert(nextn)) {
                        nextn.dis = cur.dis + 1;
                        q.push(nextn);
                    }
                }
    }
    return 0;
}

int main() {
    int T = 0;
    while (scanf("%d", &n) == 1 && n) {
        printf("Case %d: ", ++T);
        target = idx = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            target *= 10;
            target += i + 1;
        }
        memset(_head, 0, sizeof(_head));
        int ans = bfs();
        printf("%d\n", ans);
    }
    return 0;
}
*/

/*
//ժ�Բ���:https://blog.csdn.net/wsx1754175/article/details/24499571
//ac 340ms bfs˫�����+����չ������
//�����Ŀֱ��bfs�ᳬʱ�ģ�״̬�Ļ��������ֻ��9!�Σ�������������������أ�
//����Ҫ��˫��Ŀ��ѣ�������������һ�㣬Ȼ������һ�㣬�����ǽӴ����ˣ�����ͳ����ˡ�
#include<iostream>
#include<cstdio>
#include<string>
#include<string.h>
#include<algorithm>
#include<list>
#include<vector>
using namespace std;
const int maxn = 11;
const int maxs = 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 2;
int fact[maxn];
int n;
int t;

bool visit[11];
int buf[maxn];
struct State
{
	int v[maxn];
	void insert(int l, int r, int p)
	{
		memcpy(buf, v + l, sizeof(int)*(r - l + 1));

		if (l > p) {
			//		v.erase(v.begin() + l, v.begin() + r + 1);
			memmove(v + r - (l - p - 1) + 1, v + p + 1, 4 * (l - p - 1));
			memmove(v + p + 1, buf, 4 * (r - l + 1));
			//			v.insert(v.begin() + (1 + p), buf.begin(), buf.end());
		}
		else if (p > r) {
			memmove(v + l, v + r + 1, 4 * (p - r));
			memmove(v + l + p - r, buf, 4 * (r - l + 1));
		}
	}
	int hash() const
	{
		int ret = 0;
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < n; ++i) {
			int cnt = 0;
			for (int j = i + 1; j < n; ++j)
			if (v[i]>v[j]) ++cnt;
			ret += fact[n - i - 1] * cnt;
		}
		return ret;
	}
	void out() const
	{
		for (int i = 0; i < n; ++i) printf(" %2d", v[i]);
		puts("");
	}
};

State target;
int d[2][maxs];
State q[2][maxs];
int front[2], rear[2];

int bfs()
{
	int cur = 0;
	for (int i = 0; i < 2; ++i) front[i] = rear[i] = 0;
	memset(d, -1, sizeof(d));
	State start;
	for (int i = 0; i < n; ++i) start.v[i] = i + 1;
	int x = start.hash(); d[cur][x] = 0, d[cur ^ 1][t] = 0;
	q[cur][rear[cur]++] = start;
	q[cur ^ 1][rear[cur ^ 1]++] = target;
	State tmp, now;
	int dep[2] = { 0, 0 };
	while (true) {
		if (front[cur] >= rear[cur]) cur ^= 1;
		if (front[cur] >= rear[cur]) break;
		tmp = q[cur][front[cur]++];
		x = tmp.hash();
		if (d[cur][x] > dep[cur]) {
			dep[cur] = d[cur][x];
			cur ^= 1;
			continue;
		}
		if (d[cur ^ 1][x] != -1) {
	//		tmp.out();
			return d[cur][x] + d[cur ^ 1][x];
		}
		for (int l = 0; l < n; ++l)
		for (int r = l; r < n; ++r) {
			for (int k = -1; k < n; ++k) {
				if (l <= k&&k <= r) continue;
				now = tmp;
	//			now.out();
				now.insert(l, r, k);
	//			now.out();
	//			puts("");
				int y = now.hash();
				if (d[cur][y] != -1) continue;
				d[cur][y] = d[cur][x] + 1;
				q[cur][rear[cur]++] = now;
			}
		}
	}
}

void GetData()
{
	int a[10];
	for (int i = 0; i < 9; ++i) a[i] = i + 1;
	freopen("in.txt", "w", stdout);
	do {
		printf("9\n");
		for (int i = 0; i < 9; ++i) printf("%d ", a[i]);
		printf("\n");
	} while (next_permutation(a, a + 9));
	printf("0\n");
}

int main()
{
//	GetData(); return 0;
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	fact[0] = 1;
	for (int i = 1; i <= 10; ++i) fact[i] = fact[i - 1] * i;
	int cas = 0;
	while (scanf("%d", &n), n) {
		target = State();
		++cas;
		for (int i = 0; i < n; ++i) {
			int x; scanf("%d", &x);
			target.v[i] = x;
		}
		t = target.hash();
		printf("Case %d: %d\n", cas, bfs());
	}
}
*/
