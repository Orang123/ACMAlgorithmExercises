#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
//ac 499ms
/*
����:һ��n���ڵ�m��˫��ߵ�ͼG,ÿ���߱�Ⱦ�ɰ�ɫ(��ȨΪ1)���ɫ(��ȨΪ0),
������ͼG����������������û�п��ܰ�ɫ�ߵ���ĿΪһ��쳲�������,�������
Yes,��û�����No.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4786
˼·:���ȿ�������������а�ɫ����Ŀ�����������ı�Ȩ��,����һ����������δ����mst�ı߼���mst�����
һ���ջ�,��ô��Ҫ�����ջ�·���ϵ�һ����ʹ���ٶȱ��һ����,���Ǳջ�����ڱߺͰױ߲�����ȷ��,
�п���ֻ�аױ�Ҳ�п���ֻ�кڱ�,��Ҳ�п��ܺڰױ߶���,ʵ�ʰױߵ����ӻ���ٻ�ȡ�������ӵı���ɫ,
�������ͼG����С�����������������,��ô������С���������֮�������״̬��һ������ͨ���ӱ߱价�ټ���
��ʹ�ðױ���Ŀ���ٻ����ӵ�,��Ϊ��С����������ṩ��һ���ױ���Ŀ���½���Ͻ�,����м�����״̬������,��ô
���½�����������.��ô�����С�����������������Ȩֵ֮�����쳲�������,
��ô����������Ϳ���ͨ������ʹ�ð�ɫ����Ŀ�ﵽ���쳲�������,��ô�ʹ���
fibonacci��.
*/

/*
ժ�� https://blog.csdn.net/u013618229/article/details/18996219
��ѧ���ɷ�֤�����㷨����ȷ��:
��ͼ�еĶ�����Ŀ���й��ɣ� n = 2, ��Ȼ������
����n <= kʱ����������������n = k + 1ʱ
��������������T������һ���ڱߣ�ȥ�������ڱߵõ�2����ͨ����T1(V1)��  T2(V2),
���{V1��V2}�ĸ����һ���ױߣ��滻�����ɡ�
������Ϊ�������ֵΪM������m)���������� ��Ȼ��ĳ����ͨ���򣬲�����ΪT1����һ��������T3��
����T3�İױ���������T1������������֤��ԭͼG1�бض�����һ���ױ�����Ϊm(T1)+1����С������,
��Ϊv(T1) <= k, min(G1)  <= m(T1) , MAX(G1) >= m(T3)����ѧ���ɷ�֪��
G1��һ������һ���ױ���Ŀ���ڵ���min(G1)С�ڵ���max(G1������С��������
��Ϊm(T1) + 1 >= m(T1) >= min(G1) m(T1) + 1 <= m(T3)<=max(G1), ���Գ���.
*/

int n,m,fa[N],dp[N],vis[N];

struct Edge{
    int u,v,w;
}edge[M];

bool cmp1(Edge x,Edge y){
    return x.w<y.w;
}

bool cmp2(Edge x,Edge y){
    return x.w>y.w;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;
    return sum;
}

int main(){
    int T,minsum,maxsum,cas=0;
    vis[1]=dp[1]=dp[2]=1;
    for(int i=3;i<N;i++){
        dp[i]=dp[i-1]+dp[i-2];
        if(dp[i]>=N) break;
        vis[dp[i]]=1;//���dp[i]Ϊ쳲�������
    }
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m,cmp1);
        minsum=kruskal();
        if(minsum == -1){
            printf("Case #%d: No\n",cas);
            continue;
        }
        sort(edge+1,edge+1+m,cmp2);
        maxsum=kruskal();
        int flag=0;
        for(int i=minsum;i<=maxsum;i++){
            if(vis[i]){//�ж�i����[minsum,maxsum]�Ƿ����쳲�������
                flag=1;
                break;
            }
        }
        if(flag)
            printf("Case #%d: Yes\n",cas);
        else
            printf("Case #%d: No\n",cas);
    }
    return 0;
}
/*
//�����ж�쳲��������İ취
#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;

int n,m,fa[N],dp[N];

struct Edge{
    int u,v,w;
}edge[M];

bool cmp1(Edge x,Edge y){
    return x.w<y.w;
}

bool cmp2(Edge x,Edge y){
    return x.w>y.w;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;
    return sum;
}

int main(){
    int T,minsum,maxsum,cas=0;
    dp[1]=dp[2]=1;
    for(int i=3;i<N;i++)
        dp[i]=dp[i-1]+dp[i-2];
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m,cmp1);
        minsum=kruskal();
        if(minsum == -1){
            printf("Case #%d: No\n",cas);
            continue;
        }
        sort(edge+1,edge+1+m,cmp2);
        maxsum=kruskal();
        for(int i=1;i<=n;i++){
            if(dp[i] == minsum){//�ҵ���һ����minsum���fib ���ж����Ƿ�С�ڵ���maxsum���������,���򲻴���
                printf("Case #%d: Yes\n",cas);
                break;
            }
            else if(dp[i]>minsum){
                if(dp[i]<=maxsum)
                    printf("Case #%d: Yes\n",cas);
                else//���������maxsum�� ����������maxsum���� �����ٱȽ���
                    printf("Case #%d: No\n",cas);
                break;
            }
        }
    }
    return 0;
}
*/
