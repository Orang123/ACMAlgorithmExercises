#include<cstdio>
#include<stdlib.h>//poj abs() cmath�ⲻ��ʶ����Ҫstdlib.h��׼��
#include<cstring>
#include<vector>
#define N 550
using namespace std;
//ac 235ms ��������
/*
����:��ʦ����n��ѧ����ȥ����,��������
�˴�֮���Ϊ��ż,���ڹ涨����4��ֻҪ����
��������һ�������˳�Ϊ��ż�Ŀ����Ծͽϵ�:
(1).�����������40cm.
(2).�����Ա���ͬ.
(3).����ϲ�������ַ��ͬ.
(4).����ϲ�����˶���ͬ.
��������ʦ����ܴ������ѧ����ȥ����,ʹ��
���������˱�����������Ҫ�������һ������.
����:http://poj.org/problem?id=2771
˼·:����������ϵ�Ǳ˴˲��ܳ�Ϊ��ż������,��ô�����෴
������������������ͬѧ��Ϊ��ż����Ҫ�����4������,
�����ѧ��i��j����ȡ�����ĸ�����,��ѧ��i��j���ܳ�Ϊ��ż,
����i-j�������,��Ϊ�Ա�ֻ����Ů��������,���ڵ��Ա�ض���ͬ,
���㽻��Ⱦɫ��,�������滷,������ս��ɵ�ͼһ���Ƕ���ͼ,
��ô����Ҫ��ļ�������֮�䲻��������(�����Ϊ��ż),
���������ļ���һ������������,����������=������-���ƥ��.
��Ϊ���е㶼������������,�����2.

ע��:����Ҳ�ɰ����Ա���Ů�ֳ�2������ ֻ������->Ů�������,
ֻ����һ�����ϳ�������Ե�������ƥ��,������������2.

*/
int n,vis[N],match[N],ans;
vector<int> G[N];
struct Node{
    int h;
    char sex,music[20],sport[20];
}node[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
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
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d %c %s %s",&node[i].h,&node[i].sex,node[i].music,node[i].sport);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                //��߲����40,�Ա�ͬ,������ͬ,�����˶���ͬ �ǳ�Ϊ��ż��Ҫ���������
                if(abs(node[i].h-node[j].h)<=40 && node[i].sex != node[j].sex &&
                   !strcmp(node[i].music,node[j].music) && strcmp(node[i].sport,node[j].sport)){
                    G[i].push_back(j);
                    G[j].push_back(i);
                   }
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans/2);
    }
    return 0;
}

/*
//ac 172ms ����Ů��ϵ�ֳ�2������,ֻ�����м����еĵ���ȡƥ��,��������
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<vector>
#define N 550
using namespace std;

int n,vis[N],match[N],ans,color[N];
vector<int> G[N];
struct Node{
    int h;
    char sex,music[20],sport[20];
}node[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
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
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%d %c %s %s",&node[i].h,&node[i].sex,node[i].music,node[i].sport);
        for(int i=1;i<=n;i++){
            if(node[i].sex == 'F') color[i]=1;//���i Ϊ��
            for(int j=i+1;j<=n;j++){
                if(abs(node[i].h-node[j].h)<=40 && node[i].sex != node[j].sex &&
                   !strcmp(node[i].music,node[j].music) && strcmp(node[i].sport,node[j].sport)){
                    if(color[i])//ֻ�����е�Ů�ĵ����
                        G[i].push_back(j);
                    else
                        G[j].push_back(i);
                   }
            }
        }
        for(int i=1;i<=n;i++){
            if(!color[i]) continue;//ֻ�����м����еĵ���ȡ��Ե�
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);
    }
    return 0;
}
*/
