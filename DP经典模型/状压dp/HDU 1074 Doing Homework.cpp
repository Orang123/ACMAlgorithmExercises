/*
����:ժ������
��N����ҵ��N<=15)��ÿ����ҵ���ʱ����һ����ֹ���ޡ����ڶ������Ҫ�۶��ٷ֡�
�����ٱ��۶��ٷ֣��Ұ��ֵ����������ҵ˳��
����:https://acm.hdu.edu.cn/showproblem.php?pid=1074
˼·:״ѹdp.dp[sta]��ʾ��������ҵ״̬Ϊstaʱ������Щ��ҵ���ټ��ٵķ���
*/
//ac 15ms ���仯����
//ʱ�临�Ӷ�O((1<<n)*n)
//dp[sta]��ʾ��������ҵ״̬Ϊstaʱ������Щ��ҵ���ټ��ٵķ���
//time[sta]��ʾ������ҵ״̬Ϊstaʱ�����ѵ���ʱ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,-1,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=cur?INF:0;
    int sta,res1,res2;
    for(int i=n-1;i>=0;i--){
        if(cur & 1<<i){
            sta=cur ^ 1<<i;
            res1=dfs(sta);
            res2=time[sta]+course[i].t-course[i].d;
            if(res2<=0)
                res2=0;
            if(res1+res2<dp[cur]){
                dp[cur]=res1+res2;
                pre[cur]=sta;
                record[cur]=i;
            }
        }
    }
    return dp[cur];
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        printf("%d\n",dfs((1<<n)-1));
        print((1<<n)-1);
    }
    return 0;
}

/*
//ac 15ms ���仯����
//dp[sta]��ʾ��������ҵ״̬Ϊ(1<<n)-1-staʱ������Щ��ҵ���ټ��ٵķ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,-1,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=cur == (1<<n)-1?0:INF;//(1<<n) -1��ʾ�Ѿ���������ҵѡ������
    int sta,res1,res2;
    for(int i=n-1;i>=0;i--){
        if(!(cur & 1<<i)){
            sta=cur | 1<<i;
            res1=dfs(sta);
            //����time��ʱ���Ӧ��״̬Ϊ(1<<n)-1-sta
            res2=time[(1<<n)-1-sta]+course[i].t-course[i].d;
            if(res2<=0)
        		res2=0;
            if(res1+res2<dp[cur]){
                dp[cur]=res1+res2;
                pre[cur]=sta;
                record[cur]=i;
            }
        }
    }
    return dp[cur];
}

void print(int sta){
    if(sta == (1<<n)-1)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        printf("%d\n",dfs(0));
        print(0);
    }
    return 0;
}
*/

/*
//ac 15ms ����dp �Ʒ��� dp[i]=min(dp[i],dp[sta]+res)
//dp[sta]��ʾ��������ҵ״̬Ϊstaʱ������Щ��ҵ���ټ��ٵķ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,0x3f,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        int sta,res;
        dp[0]=0;//��ʼ״̬
        for(int i=0;i<(1<<n);i++){
        	for(int j=n-1;j>=0;j--){//����jҪ������ܱ�֤ �����ͬʱ,�����ֵ�����С д�ɵ��Ʋ��ý������ｵ��,�е���ѧ
        		if(i & 1<<j){
        			sta=i ^ 1<<j;
        			res=time[sta]+course[j].t-course[j].d;
        			if(res<=0)
        				res=0;
					if(dp[sta]+res<dp[i]){
						dp[i]=dp[sta]+res;
						pre[i]=sta;
						record[i]=j;
					}
				}
			}
		}
		printf("%d\n",dp[(1<<n)-1]);
        print((1<<n)-1);
    }
    return 0;
}
*/

/*
//ac 15ms ����dp ת�Ʒ��� dp[sta]=min(dp[sta],dp[i]+res)
//dp[sta]��ʾ��������ҵ״̬Ϊstaʱ������Щ��ҵ���ټ��ٵķ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
#define M 110
#define INF 0x3f3f3f3f
using namespace std;

int n,time[1<<N],dp[1<<N],pre[1<<N],record[1<<N];
struct Course{
    char s[M];
    int d,t;
}course[N];

void init(){
    memset(dp,0x3f,sizeof(dp));
    memset(time,0,sizeof(time));
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(i & 1<<j)
                time[i]+=course[j].t;
        }
    }
}

void print(int sta){
    if(!sta)
        return;
    print(pre[sta]);
    printf("%s\n",course[record[sta]].s);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s %d %d",course[i].s,&course[i].d,&course[i].t);
        init();
        int sta,res;
        dp[0]=0;
        for(int i=0;i<(1<<n);i++){
        	for(int j=n-1;j>=0;j--){//����jҪ������ܱ�֤ �����ͬʱ,�����ֵ�����С
        		if(!(i & 1<<j)){//j��ҵ��δд
        			sta=i | 1<<j;//��һ״̬Ҫ����j
        			res=time[i]+course[j].t-course[j].d;
        			if(res<=0)
        				res=0;
					if(dp[i]+res<dp[sta]){
						dp[sta]=dp[i]+res;
						pre[sta]=i;
						record[sta]=j;
					}
				}
			}
		}
		printf("%d\n",dp[(1<<n)-1]);
        print((1<<n)-1);
    }
    return 0;
}
*/
