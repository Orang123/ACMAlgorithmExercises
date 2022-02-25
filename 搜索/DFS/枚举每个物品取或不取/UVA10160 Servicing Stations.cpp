/*
����:ժ������
����һ������ͼ����n�����,m����,����Ҫ��n���㴦��������վ��
����վ���Ը����������ӵĵ�(�������������)����������Ҫ����
����վ���Ը������н�㡣
n<=35.
����:https://www.luogu.com.cn/problem/UVA10160
˼·:ö��ÿ�����Ƿ���÷���վ,���ڵ�ĸ��ǲ�ȡ�����ķ�ʽ,
�����ǵĵ����Ŀ����n��ʱ,�ͼ�¼�������վ���ٵĸ���.
2����֦:
��֦1:����ǰ���������վ��Ŀ��С��֮ǰ��¼�ķ���վ��Ŀʱ����.
��֦2:��ǰ��ѡ���������վ�ĵ�uǰ��������δ���ǵĵ�i,����i��
�ڽӵĵ������Ŷ���uС,��i����Ҳ�����ܱ�����,��:��ǰ����
�����ܸ������нڵ�,����.
*/
//ac 1.05s
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],vis[N],maxv[N],ans;

//sumΪ��ǰ���ǵ�ĸ���,numΪ�ڼ����㽨�����վ����Ŀ
void dfs(int u,int sum,int num){
    if(num>=ans)//�������վ����Ŀ ��С��֮ǰ����Сֵ ����
        return;
    if(sum == n && num<ans){//���ǵ����Ŀ����n�� ��¼��
        ans=num;
        return;
    }
    if(u == n+1)
        return;
    //��֮ǰ�����δ���ǵĵ�i,����i���ڽӵ������ű�u��С,
    //��u����u+1..u+2����ĵ�Ҳ�������ܺ�i���ڽ�,��i�㲻���ܱ�����,��ǰ�����޷�����ȫ����,����.
    for(int i=1;i<u;i++){
        if(!vis[i] && maxv[i]<u)
            return;
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(mp[u][i] && !vis[i])//ֻ��i�㻹δ���ǲż�¼ �¸��ǵ�ĸ���
            cnt++;
        //����ǰi���ڽ�ʱ,vis[i]++,�����ۼ���Ϊ�˷������ʱ,vis[i]-- ��Ӱ��vis[i]��Ϊ0���ж�,
        //��Ϊ���˵�ǰ��u����i��,�������б�ĵ㸲�ǵ�i
        if(mp[u][i])
            vis[i]++;
    }
    if(cnt)//��u�㽨�����վ��ǰ���������¸��ǵ������Ϊ0,ֻ������num���ܱ�֤����
        dfs(u+1,sum+cnt,num+1);
    for(int i=1;i<=n;i++){
        if(mp[u][i])
            vis[i]--;
    }
    //����u�㽨�����վ
    dfs(u+1,sum,num);//�����п��� �¸��ǵ�ĸ��������Ϊ0,Ҳ�п����¸��ǵ������Ϊ0
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=INF;
        memset(vis,0,sizeof(vis));
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++)
            mp[i][i]=1;//ÿ������i�㽨�����վ,�ܸ��������
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=mp[v][u]=1;
        }
        for(int i=1;i<=n;i++){
            maxv[i]=-1;
            for(int j=1;j<=n;j++){
                if(mp[i][j])
                    maxv[i]=max(maxv[i],j);//maxv[i]��¼i�㱾�� �ڽӵ����ĵ�ı��
            }
        }
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 490ms �������ڽӾ���,�����ڽӱ�,�����ж�u��δ�ڽӵĵ�
//ժ�Բ���:https://blog.csdn.net/HelloWorld10086/article/details/38659641
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 36;
int n,m;
int edge[N][N];
int vis[N];
int s[N];
int ans;

void dfs(int u,int sum,int cur) {
	if(cur == n && sum < ans) {
		ans = sum;
		return;
	}
	if(u > n || sum >= ans) {
		return;
	}
	for(int i = 1; i < u; i++) {
		if( !vis[i] && edge[i][s[i]-1] < u) {
			return ;
		}
	}
	int cnt = 0;
	for(int i = 0; i < s[u]; i++) {
		if( !vis[edge[u][i]] ) {
			cnt++;
		}
		vis[edge[u][i]]++;
	}
	if(cnt) {
		dfs(u+1,sum+1,cur+cnt);
	}
	for(int i = 0; i < s[u]; i++) {
		vis[edge[u][i]]--;
	}
	dfs(u+1,sum,cur);
}
int main() {
	int u,v;
	while(scanf("%d%d",&n,&m) != EOF && (n || m)) {
		memset(edge,0,sizeof(edge));
		memset(s,0,sizeof(s));
		memset(vis,0,sizeof(vis));

		for(int i = 0; i < m; i++) {
			scanf("%d%d",&u,&v);
			edge[u][s[u]++] = v;
			edge[v][s[v]++] = u;
		}
		for(int i = 1; i <= n; i++) {
			edge[i][s[i]++] = i;
			sort(edge[i],edge[i]+s[i]);
		}
		ans = n;
		dfs(1,0,0);
		printf("%d\n",ans);
	}
	return 0;
}
*/
