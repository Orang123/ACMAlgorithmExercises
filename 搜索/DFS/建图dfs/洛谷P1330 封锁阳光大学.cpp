/*
����:��һ����n����㹹�ɵ���m���ߵ�ͼ����û��Ҫ��ĳ
�������Ϸ��ú�з����з��ռ��õ��ϵ����бߣ����ڵĺ�з
֮��ᷢ����ͻ��������Ҫ�ú�зռ������ͼ��
1<=n<=10^4,1<=m<=10^5.
����:https://www.luogu.com.cn/problem/P1330
˼·:dfs,����Ⱦɫ,�������ظ����ʹ��ĵ��ж��Ƿ����ɫ��ͬ,�����ɫ����ͬ,
����ͻ,��:���ڱ����˶�����ú�з,�����ɫ��ͬ�򲻻��ͻ.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,ans,head[N],cnt,vis[N],color[N],sum[2];

struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int col){
    if(vis[u]){//���ֱ�����֮ǰȾ��ɫ�ĵ�,�ж����ڵ�Ⱦɫ�Ƿ�͵�ʱһ��,����һ���� ì��,һ�������˳�
        if(color[u]!=col)
            return 0;
        return 1;
    }
    vis[u]=1;
    color[u]=col;//u��Ⱦɫ
    sum[col]++;//��ɫ��Ŀ+1
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfs(v,col^1)) return 0;//���ڵ�Ⱦɫ����һ�� ����ͻ�ì�� ֱ���˳�,���±����µĿ�
    }
    return 1;
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            memset(sum,0,sizeof(sum));
            if(dfs(i,1))
                ans+=min(sum[0],sum[1]);
            else{
                printf("Impossible\n");
                return 0;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

/*
���鼯����
#include<bits/stdc++.h>
using namespace std;
int f[10001],a,b,n,m,t[10001],bj[10001],h[10001],ans;
int find(int x)//ģ�庯����
{
    if(f[x]!=x) f[x]=find(f[x]);
    return f[x];
}
void xx(int x,int y)//�жϺ�����
{
    int qq=find(x);
    if(qq!=y)//������Ǹ��ײ���Ƚ����Ǻϲ���
    {
        f[y]=qq;
        t[qq]+=t[y];
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        f[i]=i;
        t[i]=1;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        int x1=find(a),x2=find(b);
        if(x1!=x2)//��������һ����ɫ��
        {
            if(h[a]) xx(h[a],x2);//a�ĸ��׽ڵ�һ��
            //��a��ɫ��һ����a����ɫ��ͬɫ�����Խ�����
            //�ϲ���
            if(h[b]) xx(h[b],x1);//ͬ�ϣ�
            h[a]=x2;//h�����a����ɫ�㣻
            h[b]=x1;//ͬ�ϣ�
        }
        else//�������ͬɫ����ʾ���У�
        {
            cout<<"Impossible";
            return 0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        int q=find(i);
        if(!bj[q])//��ʾ������ϵĴ𰸻�û��ѡ����
        {
            int q1=find(h[i]);
            bj[q]=1;
            bj[q1]=1;
            ans+=min(t[q],t[q1]);//���������Сֵ��
        }
    }
    cout<<ans;
    return 0;
}
*/
