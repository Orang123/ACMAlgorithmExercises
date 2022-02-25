/*
����:
"Help Jimmy" ������ͼ��ʾ�ĳ�������ɵ���Ϸ
�����а���������Ⱥ͸߶ȸ�����ͬ��ƽ̨����������͵�ƽ̨���߶�Ϊ�㣬�������ޡ�
Jimmy������ʱ��0�Ӹ�������ƽ̨��ĳ����ʼ���䣬���������ٶ�ʼ��Ϊ1��/�롣
��Jimmy�䵽ĳ��ƽ̨��ʱ����Ϸ��ѡ�����������������ܣ����ܶ����ٶ�Ҳ��1��/�롣
��Jimmy�ܵ�ƽ̨�ı�Եʱ����ʼ�������䡣Jimmyÿ������ĸ߶Ȳ��ܳ���MAX�ף���Ȼ�ͻ�ˤ������ϷҲ�������
���һ�����򣬼���Jimmy���׵���ʱ���ܵ�����ʱ�䡣
1 <= N <= 1000��-20000 <= X, X1[i], X2[i] <= 20000��0 < H[i] < Y <= 20000��i = 1..N��
����:http://poj.org/problem?id=1661
˼·:ÿ������ʱ,��Ȼֻ�ܴӵ�ǰ�߶ȵ�̨�ӵ������Ҳ�,���䵽���ڵ�ǰ̨�ӵ���߸߶ȵ�
̨����,Ȼ�����ߵ����̨�ӵ������Ҳ�,�ٽ�����һ��̨�Ӽ������½�,������滹�б��̨��
�ܽ�ס��,�Ͳ���ֱ�����䵽����,���ǵ�ǰx���겻�������κ�һ��̨�ӵ����귶Χ��,�����ֱ��
���䵽����.����������������ĸ߶��ǹ̶���,��ͬ���Ǵ�һ��̨�ӽ��䵽��һ��̨��,����ѡ��
���������Ҳ�,������ľ����ǲ�ͬ��.���ҴӸ߶Ȳ�ͬ��̨��������,���ܻ��䵽ͬһ��̨�ӵ�ͬһ��,
��˶���ĳ��̨�ӵ������Ҳ��п��ܻᱻ�ظ�������,����̨ͬ�ӽ��䵽������Ҫ������ʱ����ǰ���
�ϸ߲��̨���޹�,��˴��������ӽṹ���ص�������,��Ȼ���仯����.
����Ҫ��̨�ӽ�������.
dp[k][0]��ʾ��k���̨�Ӵ���ཱུ���䵽��������������ʱ��
dp[k][1]��ʾ��k���̨�Ӵ��Ҳཱུ���䵽��������������ʱ��
dp[k][d]=INF,��ʾ�ڽ���߶�����Ϊmaxh���޽�,dp[k][d]=-1��ʾ��ʼ״̬,��δ����.
����ֵ����ʾ�н�
*/
//ac 0ms ���仯����
//ʱ�临�Ӷ�(1000*2)=2000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,maxh,x1[N],x2[N],h[N],dp[N][2];

struct Node{
    int x1,x2,h;
    bool operator <(const Node &x)const{
        return h>x.h;//���ո߶Ƚ�������
    }
}node[N];

int dfs(int x,int k,int d){//��ǰ�ڵ�k��̨����
    if(dp[k][d] != -1)
        return dp[k][d];
    dp[k][d]=INF;//INF�޽�Ҳ��Ҫ��¼
    for(int i=k+1;i<=n+1;i++){
        //��ǰ��k��̨��λ�õĺ������ڵ�i��̨�ӵ����Ҳ෶Χ�� �Ҹ߶Ȳ�����maxh ���ɽ���
        if(i!=n+1 && x>=node[i].x1 && x<=node[i].x2 && node[k].h-node[i].h<=maxh){
            //x-node[i].x1�ƶ�����i��̨�����,node[i].x2-x�ƶ�����i��̨���Ҳ�,����߶ȶ���node[k].h-node[i].h
            dp[k][d]=min(x-node[i].x1+dfs(node[i].x1,i,0),node[i].x2-x+dfs(node[i].x2,i,1))+node[k].h-node[i].h;
            //�ҵ�һ��������������ߵ�̨�ӽ���,�ͽ���,�������Ļ������ֱ���жϵ�n+1ֱ���䵽����,
            //���м�����̨�ӻ��ס��,��Ҫ�����ƶ����ܼ������½���
            break;
        }
        if(i == n+1 && node[k].h<=maxh)//��ǰ��̨�Ӷ����ڵ�k��̨�ӽ��䷶Χʱ,����ֱ�ӽ��䵽����
            dp[k][d]=node[k].h;
    }
    return dp[k][d];
}

int main(){
    int T,x,y;
    scanf("%d",&T);

    while(T--){
        memset(dp,-1,sizeof(dp));
        scanf("%d%d%d%d",&n,&x,&y,&maxh);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].x1,&node[i].x2,&node[i].h);
        sort(node+1,node+1+n);
        node[0].h=y;//��ʼ�߶�Ϊy
        printf("%d\n",dfs(x,0,0));
    }
    return 0;
}

/*
//ac 47ms dfs+��֦
//dp[k][0]��ʾ�ӳ�ʼ�߶Ƚ��䵽��k���̨���������������ʱ��
//dp[k][1]��ʾ�ӳ�ʼ�߶Ƚ��䵽��k���̨���Ҳ�����������ʱ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,maxh,x1[N],x2[N],h[N],dp[N][2],ans;

struct Node{
    int x1,x2,h;
    bool operator <(const Node &x)const{
        return h>x.h;
    }
}node[N];

void dfs(int x,int pre,int k,int time){
	if(k == n+1){
		if(node[pre].h<=maxh && time+node[pre].h<ans)
			ans=time+node[pre].h;
		return;
	}
	if(time>=ans)
		return;
	if(x>=node[k].x1 && x<=node[k].x2 && node[pre].h-node[k].h<=maxh){
		time+=node[pre].h-node[k].h;
		if(x-node[k].x1+time<dp[k][0]){//��֦:�����ǰ���� ���ܱ�֮ǰ�����򲻽�������
			dp[k][0]=x-node[k].x1+time;
			dfs(node[k].x1,k,k+1,dp[k][0]);
		}
		if(node[k].x2-x+time<dp[k][1]){
			dp[k][1]=node[k].x2-x+time;
			dfs(node[k].x2,k,k+1,dp[k][1]);
		}
	}
	else//��k�������㽵������ �ж���һ��
		dfs(x,pre,k+1,time);
}

int main(){
    int T,x,y;
    scanf("%d",&T);
    while(T--){
    	ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d%d%d",&n,&x,&y,&maxh);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].x1,&node[i].x2,&node[i].h);
        sort(node+1,node+1+n);
        node[0].h=y;
        dfs(x,0,1,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/
