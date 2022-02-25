/*
��ȫͼ:ÿ�Բ�ͬ�Ķ���֮�䶼ǡ����һ��������.
����:����ͼ�н����Ϊs����ȫ��ͼ����.
��������1:1->2 2->3 3->43�������Ϊ2����ȫ��ͼ
����:https://acm.hdu.edu.cn/showproblem.php?pid=5952
˼·:dfs,ö��ÿ���㳢�Լ�����ȫ��ͼ,�жϺ�֮ǰ�ĵ��Ƿ񶼴��ڱ��ڽ�.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m,s,head[120],mp[120][120],cnt,q[120],sum;
struct Node{
    int to,next;
}edge[2100];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int judge(int v,int len){
    for(int i=1;i<=len;i++){
        if(!mp[v][q[i]]) return 0;
    }
    return 1;
}

void dfs(int u,int num){
    if(num == s){//�ڵ�����s������
        sum++;
        return;
    }
    q[num]=u;//��u�����Ϊ������ȫ��ͼ
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;//��Ϊ�����ߵ�ʱ�����ֻ������С�������,���Բ���Ҫvis��������
        //�����Ѿ����ʹ��ļ�����ȫ��ͼ�ĵ�,ʵ����Ϊmp[i][i]������0,���Բ����ظ�����. ���û����visz������
        if(!judge(v,num)) continue;//�жϸõ��Ƿ���Ѿ�����ȫ��ͼ�еĵ㶼�б�����,�������������ȫ��ͼ
        dfs(v,num+1);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof head);
        memset(mp,0,sizeof(mp));
        scanf("%d%d%d",&n,&m,&s);
        while(m--){
            scanf("%d%d",&u,&v);
            //����Ϊ�˱����ظ�������ȫ��ͼ������1:1->2 2->1�����2����ͬ����ȫ��ͼ. ֻ�����ڵ��Ž�С���ڵ��Žϴ�ĵ����
            if(u>v) swap(u,v);
            addEdge(u,v);
            mp[u][v]=1,mp[v][u]=1;//��¼��ʱ���¼˫���
        }
        for(int i=1;i<=n;i++)
            dfs(i,1);
        printf("%d\n",sum);
    }
    return 0;
}
