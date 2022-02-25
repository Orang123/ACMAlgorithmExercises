#pragma comment(linker, "/STACK:16777216")//������ĿҪ���ֶ������ջ�ռ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

/*
����:һ��n���ڵ����,��������㶼����ͬһ��·���ϵ���Ԫ��(A,B,C)����ж�����
�����㲻��ͬһ��·����ָ����,������ֱ���������֧��������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4705
˼·:���Դӷ��濼��,dfs�����������ͬһ��·���Ϻ�2������ͬһ��·���ϵ�������,
Ҳ������������һ����֧�ϻ�2������ͬһ��֧��.
����C[n][3]��ȥ���������������㶼������һ��·���ϵĿ���.
*/

int cnt,n,head[N],siz[N];
ll sum;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=1;
    ll tmp=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        //tmp�����Ѿ������������Ľڵ����
        tmp+=siz[v];
        /*
        ������ѡ��siz[v]�����е�һ���ڵ�,��ѡ��u�ڵ�,
        ��ѡ������ڵ�(�������u�ĸ��׽�����ϻ�u��������δ�����������ڵ�),
        ��ѡ��������ϵĸ��׽���������㶼��ͬһ��·����,
        ��ѡ��δ�����������нڵ�����������ͬһ��·����.
        */
        sum+=siz[v]*1*(n-tmp-1);
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=sum=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        //n*(n-1)*(n-2)/6 ��n������ȡ������3���ж��ٿ���
        printf("%lld\n",(ll)n*(n-1)*(n-2)/6-sum);
    }
    return 0;
}
