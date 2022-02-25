#include<cstdio>
#include<cstring>
#include<vector>
#define N 1100
using namespace std;
//ac 15ms ��������
//���������������� https://blog.csdn.net/u011498819/article/details/38339115
/*
����:1*2��ֽ�Ʒֳ�n��ˮƽ��������Ϊ(x,y)��(x+1,y),
m�Ŵ�ֱ��������Ϊ(x,y)��(x,y+1),�ֱ�֤ͬһ������õ�
ֽ�Ʋ����ص�,��ˮƽ����ʹ�ֱ������ܻ��ص�,����Ҫ�Ƴ�
һЩֽ��,ʹ��ʣ�µ�ֽ�������໥֮�䲻���ص�,���������
ʣ�µĻ����ֽཻ�Ƶ��������.
����:�����=��ͼ����������,�����ཻ��ϵ�������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4619
˼·:���Խ�n��ˮƽ�����ƿ����󼯺�,m�Ŵ�ֱ���õ��ƿ����Ҽ���.
��ôn��ˮƽ���õ���i��m�Ŵ�ֱ���õ���j�ཻ�����,
��Ϊ�������(x1==x2&&y1==y2)||(x1+1==x2&&y1==y2)||(x1+1==x2&&y1==y2+1)||(x1==x2&&y1==y2+1)
���߼�i->j�������,��ֻ�������С���㸲��,ʣ��ĵ�ض�����������,
��ֽ�Ƽ以���ཻ,�������������������,��������=������(n+m)-���ƥ��.
*/
int n,m,vis[N],match[N],ans;
vector<int> G[N];
struct Node{
    int x,y;
}node1[N],node2[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=N;i++) G[i].clear();
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node1[i].x,&node1[i].y);
        for(int i=1;i<=m;i++)
            scanf("%d%d",&node2[i].x,&node2[i].y);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int x1=node1[i].x,y1=node1[i].y;
                int x2=node2[j].x,y2=node2[j].y;
                //ˮƽ�ʹ�ֱ�ཻ��Ϊ4�����
                if((x1==x2&&y1==y2)||(x1+1==x2&&y1==y2)||(x1+1==x2&&y1==y2+1)||(x1==x2&&y1==y2+1))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){//��ˮƽ�ڷŵ��Ƶ��󼯺Ͽ������ ��������2
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n+m-ans);
    }
    return 0;
}
