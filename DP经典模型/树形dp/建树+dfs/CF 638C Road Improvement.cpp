/*
����:��һ�������ɵĳ��е�·,����Ҫ��·,ͬһ����
���޵ĵ�·��������,��������Ҫ�����������.��ʵ����
�Ĳ������ٵ�����,����ÿ�������������·.
n<=200000.
����:https://codeforces.ml/problemset/problem/638/C
˼·:n<=20000,����������dp,���ڽڵ�u���ӽڵ������ı�
��������ͬһ����,������α��Ϊ1,2,3..,�ڱ��ʱҪע��,
Ҳ������u�ĸ��ڵ����ڵı���ͬһ����,����費ͬ,�����Ҫ
��¼ÿ���ڵ�u�븸�ڵ������ıߵı��.
*/
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200100
using namespace std;
int n,head[N],cnt,maxDay;
vector<int> ans[N];
struct Node{
    int to,next,id;
}edge[N<<1];

void addEdge(int from,int to,int id){
    edge[cnt]=(Node){to,head[from],id};
    head[from]=cnt++;
}

//day��ʾ�븸�ڵ������ıߵı��
void dfs(int u,int fa,int day){
    int day0=0;//ÿ�α���day0���ӵ�һ�쿪ʼ,����u�ڵ������������ıߵı�Ŷ���1,2,3..���α��
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        day0++;
        if(day0 == day) day0++;//���ܺ��丸�ڵ�����ڱ���ͬһ����,���Ҫ�ŵ���һ����
        ans[day0].push_back(edge[i].id);//С��day���ڱߵ�,���ӵ�һ���޿�ʼ����.
        dfs(v,u,day0);
    }
    maxDay=max(maxDay,day0);//��¼������˶�����
}

int main(){
    int u,v;
    memset(head,-1,sizeof head);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v,i);
        addEdge(v,u,i);
    }
    dfs(1,0,-1);
    printf("%d\n",maxDay);
    for(int i=1;i<=maxDay;i++){
        printf("%d",ans[i].size());
        for(int j=0;j<ans[i].size();j++)
            printf(" %d",ans[i][j]);
        printf("\n");
    }
    return 0;
}
