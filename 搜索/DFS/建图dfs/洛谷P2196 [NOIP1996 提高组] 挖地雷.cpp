/*
����:��һ����ͼ����n���ؽ�(n��20)��ÿ���ؽ�������һ�������ĵ��ס�
ͬʱ�������ؽ�֮�������·�������ؽѼ������ӵ����ݸ���֮��
ĳ�˿��Դ���һ����ʼ�ڵ��ף�Ȼ���������ָ�������������ڣ�����ѡ��һ��·������
��������ʱ�ڵ��׹������������һ���ڵ��׵ķ�����ʹĳ�����ڵ����ĵ��ס�
ע��:�����������ǵ�������.
����:https://www.luogu.com.cn/problem/P2196
˼·:����ö��ÿ������Ϊ��� ����dfs.
*/
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n,a[30],vis[30],cnt,ans=-1,b[30],c[30],num;
vector<int> edge[30];

void dfs(int u,int k,int sum){
    int flag=1;
    b[k]=u;
    vis[u]=1;
    //ֱ���������¼����sum
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        flag&=vis[v];
        if(!vis[v])
            dfs(v,k+1,sum+a[v]);
    }
    if(flag){
        if(sum>ans){
            ans=sum;
            for(int i=1;i<=k;i++)
                c[i]=b[i];
            num=k;
        }
    }
    vis[u]=0;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int tmp;
    for(int i=n-1;i>=1;i--){//i=1..n-1
        for(int j=i-1;j>=0;j--){//j=i+1
            scanf("%d",&tmp);
            if(tmp)
                edge[n-i].push_back(n-j);//�������ǵ�������
        }
    }
    for(int i=1;i<=n;i++)
        dfs(i,1,a[i]);
    printf("%d",c[1]);
    for(int i=2;i<=num;i++)
        printf(" %d",c[i]);
    printf("\n");
    printf("%d\n",ans);
    return 0;
}
