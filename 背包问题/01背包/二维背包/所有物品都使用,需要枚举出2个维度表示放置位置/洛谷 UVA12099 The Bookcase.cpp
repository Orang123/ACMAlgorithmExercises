#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;
//ac 230ms ̰��+01����
//��POJ 1948����
/*
����:����n����ĸ�h�Ϳ�w,Ҫ����һ����������,
����������������,ÿ�㲻��Ϊ��,ÿ��ĸ߶�Ϊ��
����ߵ���ĸ߶�,ÿ��Ŀ��Ϊ�ò�������Ŀ�Ⱥ�
��ܵĿ��Ϊ����������,��ܵĸ߶�Ϊ�����
�߶Ⱥ�,����������������Сֵ,��:��ܸ߶ȳ˿�ȵ���Сֵ
n<=70,h<=300,w<=30.
����:https://www.luogu.com.cn/problem/UVA12099
˼·:�����鰴�ո߶Ƚ�������.
Ӱ�������������ÿ��Ŀ�Ⱥ͸߶�,��ÿ����Ŀ�Ⱥ͸߶�
�䲢û��ֱ�ӵĹ�ϵ,��Ȼ��Ҫö�ٳ�ÿ���������һ��,Ҫô��
��һ��,Ҫô�ŵڶ���,Ҫô�ŵ�����,Ȼ���ж�ÿ�����ǲ��Ǹ������
�Ž�ȥ�ĵ�һ����,�ǵĻ� ��ܸ߶Ⱦ��ǵ�һ����߶�,ֱ�������鶼
�Ž������,�ж��Ƿ���������϶�����,֮���¼��С�������.����
n<=70,3sʱ�޿϶�TLE.
���ǿ���dp,���ȸ߶���ߵ��Ǳ������ŵĲ�,�ò�߶�һ�����Ȿ��ĸ߶�,
��ô�߶���ߵ����ȷ����ڵ�������.����dp[i][j][k]����ǰi���������
ǰ������,��һ����Ϊj,�ڶ�����Ϊk�������,ǰ������С�ĸ߶Ⱥ�.
ʵ�ʿ��Թ��������Ż�����һά��i,���Խ������鰴�߶ȴӸߵ����ź�,����
dp״̬ת��ʱ,�����ǰ��i�����Ǹò������õĵ�һ����,��ô��ǰ��ĸ߶�
���ǵ�i����ĸ߶�,�����Ƿ��õ�i�����ڸò�Ͳ����õ�i�����ڸò��
ǰi-1��������Ž�Ƚ������ǰ���Ž�.��Ϊ��i���鼴�ɷ����ڵ�һ��,Ҳ��
�����ڵڶ���,��ô��ʼ״̬dp[0][0]=0,����ǰ����һ����Ҳû�з�,�߶Ⱥ�Ϊ0,
����״̬����INF,��Ϊʵ�ʵ�ǰ2����ܵĿ��һ��Ҫ��ǰ������ܵĸ߶ȺͶ�Ӧ��,
�����ж���.
*/
//dp[i][j][k]����ǰi����(������һ����ߵ�)������ǰ������,��һ����Ϊj,�ڶ�����Ϊk�������,ǰ������С�ĸ߶Ⱥ�.
//����������Ż��������һά��i,��dp[j][k]
int n,dp[M][M],sum;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
            sum+=bk[i].w;//������Ŀ�Ⱥ�
        }
        sort(bk+1,bk+1+n);//�鰴�ո߶Ƚ�����
        dp[0][0]=0;//��ʼ״̬ ǰ���� ���Ϊ0
        int maxw=sum-bk[1].w;//Ĭ�ϸ߶���ߵ��� �����ڵ�����,������ĸ߼�Ϊ���
        for(int i=2;i<=n;i++){//�ӵ�2�ߵ��鿪ʼ��,Խ�����鱾�߶�Խ��
            //ע��jһ��Ҫ����,��Ϊdp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[j][k]);
            //�����dp[j][k]�����ʾǰi-1��������Ž�,���j����,dp[j][k]���ǵ�i�����Ѿ������һ���״̬,
            //��Ϊ��j��Сʱdp[j+bk[i].w][k]�Ѿ����¹���.
            for(int j=maxw;j>=0;j--){
                //ͬ��kҲ���뽵��,��Ϊdp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][k]);
                //dp[j][k]�����ʾǰi-1��������Ž�,���k����,ͬ���ᵼ��dp[j][k]�ǵ�i�����Ѿ�����ڶ����״̬
                for(int k=maxw;k>=0;k--){
                    if(dp[j][k] == INF) continue;//���Ϸ�״̬ ������
                    if(!j)
                        //�����1�㻹δ�����鱾,���ǽ���i�������,�߶Ⱦ�Ϊ��1��߶ȼ�:dp[0][k]+bk[i].h
                        //��ǰi-1��������Ž�Ƚ�,����dp[j+bk[i].w][k]
                        dp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[0][k]+bk[i].h);
                    else
                        //�����1���Ѿ����ù���,��ô�߶��Ѿ�ȷ���˾���dp[j][k]
                        //��ǰi-1��������Ž�Ƚ�,����dp[j+bk[i].w][k]
                        dp[j+bk[i].w][k]=min(dp[j+bk[i].w][k],dp[j][k]);
                    if(!k)
                        //�����2�㻹δ�����鱾,���ǽ���i�������,�߶Ⱦ�Ϊ��2��߶ȼ�:dp[j][0]+bk[i].h
                        //��ǰi-1��������Ž�Ƚ�,����dp[j][k+bk[i].w]
                        dp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][0]+bk[i].h);
                    else
                        //�����2���Ѿ����ù���,��ô�߶��Ѿ�ȷ���˾���dp[j][k]
                        //��ǰi-1��������Ž�Ƚ�,����dp[j][k+bk[i].w]
                        dp[j][k+bk[i].w]=min(dp[j][k+bk[i].w],dp[j][k]);
                }
            }
        }
        int ans=INF;
        //��ΪҪȷ�����㶼���ٷ���һ����,����ǰ��������޴�1��ʼ
        for(int i=1;i<=maxw;i++){
            for(int j=1;j<=maxw;j++){
                if(dp[i][j] == INF) continue;
                int h=dp[i][j]+bk[1].h;//�ܸ߶�Ϊǰ�������С�߶�+������ĸ߶�(��һ����ĸ߶�)
                int w=max(sum-i-j,max(i,j));//������Ŀ��Ϊsum-i-j,��ܵĿ��Ϊ����������
                ans=min(ans,w*h);//������w*h,����Сֵ
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 540ms ������״̬ת�Ʒ���
//dp[j-bk[i].w][k] dp[j][k-bk[i].w]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[M][M],sum;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
            sum+=bk[i].w;
        }
        sort(bk+1,bk+1+n);
        int maxw=sum-bk[1].w;
        dp[0][0]=0;
        for(int i=2;i<=n;i++){
            //j k���뽵�� ���ܱ�֤dp[j-bk[i].w][k]��dp[j][k-bk[i].w]��ǰi-1��������Ž�
            for(int j=maxw;j>=0;j--){//�½�0 ��Ϊ���ܹ���������ʼ״̬dp[0][0]
                for(int k=maxw;k>=0;k--){
                    if(j >= bk[i].w){//��֤j-bk[i].w�����±겻Ϊ��
                        if(dp[j-bk[i].w][k]!=INF && j == bk[i].w)
                             //j == bk[i].w �պ��ǵ�һ�� ֻ�����i����ʱ
                             dp[j][k]=min(dp[j][k],dp[0][k]+bk[i].h);
                        else
                            //ǰi-1��������Ž�������i��������Ž�ȽϽ��,��Ϊ��һ���Ѿ���������,���Ը߶Ⱦ���dp[j-bk[i].w][k]
                            dp[j][k]=min(dp[j][k],dp[j-bk[i].w][k]);
                    }
                    if(dp[j][k-bk[i].w]!=INF && k >= bk[i].w){
                        if(k == bk[i].w)
                            dp[j][k]=min(dp[j][k],dp[j][0]+bk[i].h);
                        else
                            dp[j][k]=min(dp[j][k],dp[j][k-bk[i].w]);
                    }
                }
            }
        }
        int ans=INF;
        for(int i=1;i<=maxw;i++){
            for(int j=1;j<=maxw;j++){
                if(dp[i][j] == INF) continue;
                int h=dp[i][j]+bk[1].h;
                int w=max(sum-i-j,max(i,j));
                ans=min(ans,w*h);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//TLE �������� O(n^3) n<=70
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 80
#define M 2500
#define INF 0x3f3f3f3f
using namespace std;

int n,ans,h1,h2,h3;
struct Book{
    int h,w;
    bool operator <(const Book &x)const{
        return h>x.h;
    }
}bk[N];

//O(n^3) n<=70
void dfs(int i,int w1,int w2,int w3){
    if(i == n+1){
        if(w1 && w2 && w3)
            ans=min(ans,max(max(w1,w2),w3)*(h1+h2+h3));
        return;
    }
    dfs(i+1,w1+bk[i].w,w2,w3);
    if(!w2)
        h2=bk[i].h;
    dfs(i+1,w1,w2+bk[i].w,w3);
    if(!w3)
        h3=bk[i].h;
    dfs(i+1,w1,w2,w3+bk[i].w);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&bk[i].h,&bk[i].w);
        }
        sort(bk+1,bk+1+n);
        h1=bk[1].h;
        dfs(2,bk[1].w,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 30ms
//�������_J_C_ 30ms������
#include <cstdio>
#include <cstdlib>

#include <algorithm>

namespace my
{
	inline void getmin(int& a, int b) { if (b < a) a = b; }
	inline int max(int a, int b, int c)
	{
		if (a > b) return a > c ? a : c;
		return b > c ? b : c;
	}
}

const int maxn(71), maxw(31);
class book
{
public:
	int h, w;
	bool operator<(const book& b) const
	{ return h > b.h; }
}all[maxn];
int forward[maxn];

int T;
int n;

bool exist[maxn * maxw];
int posw[maxn * maxw], end;

inline void get_exist(int now, int v)
{
	for (int i(forward[now]); i >= v; --i)
		exist[i] |= exist[i - v];
	exist[v] = true;
	end = 0;
	for (int i(0); i <= forward[now]; ++i)
		if (exist[i]) posw[end++] = i;
}

int bVis[2][maxn * maxw][maxn * maxw], NextVis(1), next;
int dp[2][maxn * maxw][maxn * maxw];

inline void init()
{
	exist[0] = true;
	for (int i(1); i != maxn * maxw; ++i) exist[i] = false;
	end = 0;
	posw[end++] = 0;
	next = 0;
}

inline void moveto(int i, int j, int k, int v)
{
	if (bVis[i][j][k] == NextVis + 1) my::getmin(dp[i][j][k], v);
	else bVis[i][j][k] = NextVis + 1, dp[i][j][k] = v;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		init();
		scanf("%d", &n);
		for (int i(1); i <= n; ++i)
		{
			scanf("%d%d", &all[i].h, &all[i].w);
		}
		std::sort(all + 1, all + 1 + n);
		for (int i(1); i <= n; ++i) forward[i] = forward[i - 1] + all[i].w;
		bVis[0][0][0] = ++NextVis;
		dp[0][0][0] = all[1].h;
		next = 0;
		int ans(2123456789);
		for (int i(1); i <= n; ++i)
		{
			get_exist(i, all[i].w);
			for (int j(0); j != end; ++j)
			{
				int w2(posw[j]);
				for (int k(0); k != end; ++k)
				{
					int w3(posw[k]);
					int w1(forward[i] - w2 - w3);
					if (w1 < 0) break;
					if (bVis[next][w2][w3] == NextVis)
					{
						if (i == n)
						{
							if (w1 && w2 && w3)
								my::getmin(ans, my::max(w1, w2, w3) * dp[next][w2][w3]);
						}
						else
						{
							moveto(next ^ 1, w2, w3, dp[next][w2][w3]);
							if (w2 != 0)
								moveto(next ^ 1, w2 + all[i + 1].w, w3, dp[next][w2][w3]);
							else
								moveto(next ^ 1, w2 + all[i + 1].w, w3, dp[next][w2][w3] + all[i + 1].h);
							if (w3 != 0)
								moveto(next ^ 1, w2, w3 + all[i + 1].w, dp[next][w2][w3]);
							else
								moveto(next ^ 1, w2, w3 + all[i + 1].w, dp[next][w2][w3] + all[i + 1].h);
						}
					}
				}
			}
			++NextVis;
			next ^= 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
*/
