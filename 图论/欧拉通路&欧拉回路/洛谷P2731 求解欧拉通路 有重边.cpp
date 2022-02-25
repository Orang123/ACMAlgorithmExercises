#include<cstdio>
#include<stack>
#include<algorithm>
#define N 550
using namespace std;
int G[N][N],n,de[N];
stack<int> s;
void dfs(int u){
    for(int i=1;i<=n;i++){//����Ĭ�Ͼ��ǰ����ֵ���,��С�ĵ��ȱ���
        if(G[u][i]){//u��i��֮���Ƿ��б߿���
            G[u][i]--;
            G[i][u]--;
            dfs(i);
        }
    }
    s.push(u);
}
int main(){
    int m,a,b;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&a,&b);
        G[a][b]++;
        G[b][a]++;
        de[a]++;
        de[b]++;
        n=max(n,max(a,b));
    }
    int start=1;//��ԭͼ��ŷ����·������1��Ϊ��㿪ʼ����
    for(int i=1;i<=n;i++){//�������С�������Ϊ���
        if(de[i]&1){
            start=i;
            break;
        }
    }
    dfs(start);
    int v;
    while(!s.empty()){//��ջ ���ŷ����·
        v=s.top();
        printf("%d\n",v);
        s.pop();
    }
    return 0;
}
