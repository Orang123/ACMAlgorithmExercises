#include<cstdio>
#include<cstring>
#define N 110
#define M 1100
using namespace std;
//ac 0ms ��С���㸲��
/*
����:2������A��B�ֱ���n��m��ģʽ,ģʽ���Ϊ0~n-1��0~m-1,
��ʼʱ2̨����������ģʽ0,��k����ҵ,ÿ����ҵi��һ����Ԫ��
(i,u,v)����ʾ������ҵi����A������ģʽu��ת��B������ģʽv��ת,
����ÿ�ε��������Ĺ���ģʽ����Ҫ�ֶ�����,������������Ҫ����
���ٴλ����������������ҵ.
����:http://poj.org/problem?id=1325
˼·:ժ��https://blog.csdn.net/wangjian8006/article/details/7963546
A,B��̨��������һ������ͼ,��ߴ���A����,
��n����,������n��ģʽ�ұߴ���B����,��m����,
������m��ģʽ,���ڶ���ÿ����ҵ,i,a,b��ʹ���
a��ָ���ұ�b�㼴��,�����������Ҫ�����е���ҵ����,
�ǲ����ҳ���С�ĵ㸲�ǽ����еı߶����ǵ�����,
Ȼ����С�㸲�ǵ������ƥ��.

ע��:������ʼ״̬��ģʽ0,������ҵ��ת����ģʽ0�����������.
*/
int n,m,k,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(match,-1,sizeof(match));
    memset(head,-1,sizeof(head));
}

int main(){
    int i,u,v;
    while(scanf("%d",&n) && n){
        scanf("%d%d",&m,&k);
        init();
        while(k--){
            scanf("%d%d%d",&i,&u,&v);
            //ʵ��ֻ�ж�!v����,��Ϊ������������A������B�����л�,��B������ʼ��ģʽ0
            if(!u || !v) continue;//������ʼ״̬��ģʽ0,������ҵ��ת����ģʽ0�����������.
            addEdge(u,v);
        }
        for(int i=1;i<n;i++){//A������ģʽ��Χ0~n-1 ��ΪA������ʼ״̬����ģʽ0,���Բ�����״̬0.
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
