#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;

/*
����:һ��n���ڵ����,����Ҫ����k���ڵ�,���Դ�����ڵ㿪ʼ����,
����Ҫ�ߵ����·������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4607
˼·:�����������ֱ���������Ľڵ����ans,���k<=ans,��Ҫ��k-1����.
���k>ans,������̰��ѡ������ֱ��ֻ��һ��,�����ֱ���������ӵ�����·����Ҫ
һ��һ��������,�������ջ���Ϊans-1+(k-ans)*2,�������ֱ��������ڵ�ĸ�������
��Ҫ�ߵ�·���ĳ���,��Ϊ����·��������ֱ���ϵ�,���Ըպ�����ڵ�����������·������.
*/

int cnt,n,m,k,head[N],dis[N],ans,st;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis[u]>ans){
        st=u;
        ans=dis[u];
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=dis[u]+1;
        dfs(v,u);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dis[1]=0;
        dfs(1,-1);
        dis[st]=0;
        dfs(st,-1);
        while(m--){
            scanf("%d",&k);
            if(k<=ans+1)//Ҫ���ʽڵ���С��ֱ���ڵ��� ֱ�����k-1����
                printf("%d\n",k-1);
            else
                printf("%d\n",ans+(k-ans-1)*2);//ֱ������+����㹹��·������*2
        }
    }
    return 0;
}
