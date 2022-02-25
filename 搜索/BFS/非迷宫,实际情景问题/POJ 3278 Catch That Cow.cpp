/*
����:ũ����ţ��һ��������,ũ����ţ��λ�÷ֱ�Ϊn,k .
ţ��λ�ò���,ũ���������ƶ���ʽ:
1.��n�ƶ���n+1λ��.
2.��n�ƶ���n-1λ��.
3.��n�ƶ���2*nλ��.
��ÿ���ƶ���ʽ����Ҫ����1����,��ũ��������Ҫ������ҵ�����ţ.
1<=n,k<=100000
����:http://poj.org/problem?id=3278
˼·:bfs����,����ÿ��λ�ö��������ƶ���ʽpos+1,pos-1,pos*2,
�����ƶ���ʽ��Ӧ�ļ�֦�ֱ���pos+1<=k,pos-1>=0,pos<k.��ʵ���Ӽ�֦
Ҳ�ǿ���ac��.
��Ϊbfs����ÿ��λ�ö��ῼ�������߷��ķ���ͬʱ�����,��ͬʱ�̵ķ���
��ʱ��һ����,����ʱ��һ�δﵽ��λ�õ�״̬��ʱһ�������ٵ�,����vis����
����Ѿ���չ����pos״̬�����ظ����.
*/
//ac 16ms bfs
//��Ϊÿ��λ��ֻ����չһ�� ʱ�临�Ӷ�O(max(2*k,10^5))=10^5
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
using namespace std;

int n,k,vis[N];
struct State{
    int pos,m;
    State(int pos=0,int m=0):pos(pos),m(m){}
};

int bfs(){
    queue<State> Q;
    vis[n]=1;
    Q.push(State(n,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.pos == k)
            break;
        Q.pop();
        //pos+1 ���ܳ���k ���򻹵������� ������
        if(tp.pos+1<=k && !vis[tp.pos+1]){
            vis[tp.pos+1]=1;
            Q.push(State(tp.pos+1,tp.m+1));
        }
        //pos-1���½�����Ϊ0 �����±겻��Ϊ��
        if(tp.pos-1>=0 && !vis[tp.pos-1]){
            vis[tp.pos-1]=1;
            Q.push(State(tp.pos-1,tp.m+1));
        }
        //����2��ǰ��posһ�����ܴ���k,����ص�kֻ����ʱ���� ע��tp.pos*2<NҪ���� ��Ȼ��RE.n,k<=10^5
        if(tp.pos<k && tp.pos*2<N && !vis[tp.pos*2]){
            vis[tp.pos*2]=1;
            Q.push(State(tp.pos*2,tp.m+1));
        }
    }
    return tp.m;
}

int main(){
    memset(vis,0,sizeof(vis));
    scanf("%d%d",&n,&k);
    printf("%d",bfs());
    return 0;
}

/*
//TLE dfs
//dp[pos]��ʾ�ﵽ��ǰposλ�����õ�����ʱ��
//����dfs��Ҫ��dp[pos]��֦,��Ϊ��������������ķ��������λ����ʱ���ܲ��������ٵ�,
//���ݺ� �������߷���������ʹ��dp[pos]����,��֦:��������ķ�������posʱ��m��ʱ���ܱ�֮ǰ��dp[pos]��ʱ���پͲ���������ȥ��
//��Ϊ�����ߵķ������ܱ�֤һ�������ٵ�,�п���ǰ���ߵķ������ǽϴ��,����ʵ�ʼ�֦��Ч�ʲ�����.
//���Ӷ�O(3^10^5) TLE
#include<cstdio>
#include<queue>
#include<cstring>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,k,dp[N],ans;

//���Ӷ�O(3^10^5) TLE
void dfs(int pos,int m){
    //��֦:��������ķ�������posʱ��m��ʱ���ܱ�֮ǰ��dp[pos]��ʱ���پͲ���������ȥ��
    if(m>=dp[pos])
        return;
    //���µ���pos��������ʱ
    dp[pos]=m;
    if(pos == k){
        //�������з��� ��������k���������ʱ
        ans=min(ans,m);
        return;
    }
    if(pos+1<=k)
        dfs(pos+1,m+1);
    if(pos-1>=0)
        dfs(pos-1,m+1);
    if(pos*2<2*k && pos*2<N)
        dfs(pos*2,m+1);
}

int main(){
    ans=INF;
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&k);
    dfs(n,0);
    printf("%d",ans);
    return 0;
}
*/

/*
//TLE dfs������������  log(k)/log(pos)>tot-m+1��֦
//���Ӷ�O(3^10^5) TLE
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,k,dp[N],ans;

//���Ӷ�O(3^10^5) TLE
int dfs(int pos,int m,int tot){
    //��֦1:��������ķ�������posʱ��m��ʱ���ܱ�֮ǰ��dp[pos]��ʱ���پͲ���������ȥ��
    if(m>=dp[pos])
        return 0;
    //���µ���pos��������ʱ
    dp[pos]=m;
    //��֦2:���ʣ�µľ��뿼�ǳ�2����,ʵ����Ҫʱ��Ϊlog(k)/log(pos)�ȹ涨ʵ��tot��ʣ��ʱ�仹�� �򷵻�
    //ע�����ﲻ����abs(k-pos)>tot-m����֦,��Ϊ������Ҫʱ���������,��ʵ�ʿ���ͨ����2����ʱ��,
    //abs(k-pos)>tot-m�������� ���������Ҫ��ʱ�����ı�tot��
    if(log(k)/log(pos)>tot-m+1)//+1����Ϊlog(k)/log(pos)������һ��ȷ��ֵ,�����,�������1,�����Ľ����5
        return 0;
    if(pos == k)
        return 1;
    if(pos+1<=k){
        if(dfs(pos+1,m+1,tot))
            return 1;
    }

    if(pos-1>=0){
        if(dfs(pos-1,m+1,tot))
            return 1;
    }
    if(pos*2<2*k && pos*2<N){
        if(dfs(pos*2,m+1,tot))
            return 1;
    }
    return 0;
}

int main(){
    ans=INF;
    scanf("%d%d",&n,&k);
    for(int i=0;i<N;i++){
        memset(dp,0x3f,sizeof(dp));
        if(dfs(n,0,i)){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
*/

/*
//ac 32ms ��̬�滮һά����ģ������
//ժ�Բ���:https://blog.csdn.net/weixin_37517391/article/details/73611936
//dp[x]��ʾ��N������x����Ҫ����Сʱ��
//��ô�õ�����ת�Ʒ���
//���x < N�Ļ�����ôֻ��ͨ����·��ת�ƣ�����dp[x] = N - x��x <= Nʱ��
//��x > Nʱ�򣬿���ͨ��2�ַ�ʽ��ת��
//��1����·ת�� dp[x] = dp[x-1] + 1
//��2����Ծ����·ת��
//��xΪż����ʱ��
//dp[x] = min(dp[x],dp[x/2]+1,dp[x/2+1]+3)
//��xΪ������ʱ��
//dp[x] = min(dp[x],dp[(x-1)/2]+2,dp[(x+1)/2]+2)

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int N,K;
const int MAX = 100005;
int dp[MAX];

int main(){
	cin>>N>>K;
	for(int i = 0;i <= K;i++){
		dp[i] = abs((int)(N - i));
	}
	for(int i = N+1;i <= K;i++){
		if(i & 1) // ����
		{
			dp[i] = min(dp[i],dp[(i-1)/2]+2);
			dp[i] = min(dp[i],dp[i-1]+1);
			dp[i] = min(dp[i],dp[(i+1)/2]+2);
		}
		else{
			dp[i] = min(dp[i],dp[i/2]+1);
			dp[i] = min(dp[i],dp[i-1]+1);
			dp[i] = min(dp[i],dp[i/2 + 1]+3);
		}
	}
	cout<<dp[K]<<endl;
	return 0;
}
*/
