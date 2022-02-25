#include<cstdio>
int student[1010];

void init(int n){
    for(int i=1;i<=n;i++){
        student[i]=i;
    }
}

int find(int x){
    int tmp=x;
    while(student[x]!=x){
        x=student[x];
    }
    while(student[tmp]!=x){
        student[tmp]=x;
        tmp=student[tmp];
    }
    return x;
}

void union0(int x,int y){//����պ��Ǹ��ڵ� ������o(1)���ӶȾ������,·��ѹ��Ҳ��ֱ�ӽ��ӽڵ�ָ����ڵ�,���������n����ϵ�Ĳ���Ч��ΪO(m)mΪ��ϵ����
    int v=find(x);
    int w=find(y);
    if(v!=w)
        student[v]=w;
}
int main(){
    int T,n,m,x,y,ans,num;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init(n);
        ans=0;
        while(m--){
            scanf("%d%d",&x,&y);
            union0(x,y);
        }
        for(int i=1;i<=n;i++){
            if(student[i]==i)//�ж��м�����������ͨ��
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
/*dfs ��������ͼ��� ��ÿ��δ���ʵĵ����,����Ҫ���ʼ���,��˵���м�����ͨ����
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
bool vis[1005],lj[1005][1005];
int n,m;
void dfs(int start)
{
    vis[start]=false;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]&&lj[start][i])
        {
            vis[i]=false;
            dfs(i);
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b,cnt=0;
        memset(vis,true,sizeof(vis));
        memset(lj,false,sizeof(lj));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            lj[a][b]=lj[b][a]=true;
        }
        for(int j=1;j<=n;j++)
        {
            if(vis[j])
            {
                //printf("%d\n",j);
                cnt++;
                dfs(j);
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/
