/*
����:����20���� ģ����ܶٻ�·,�������·�� ���е㶼����һ�λ��ܻص���㡣
����:https://acm.hdu.edu.cn/showproblem.php?pid=2181
˼·:dfs.��¼�����ĸ���,���ʹ��ĵ㲻�ٷ���.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int m,fa[30],vis[30],mp[30][30],cnt;

void printPath(int u){
    if(u!=m) printPath(fa[u]);
    else{
        printf("%d:  %d",cnt,u);
        return;
    }
    printf(" %d",u);
}

void dfs(int u,int num){
    vis[u]=1;
    for(int i=1;i<=20;i++){
        if(!mp[u][i]) continue;
        if(i == m && num!=20) continue;//��ʼ�������������е㶼�������� �Ͳ�Ҫ����
        if(vis[i] && i!=m) continue;//�������ĵ������ʼ�� ��������
        if(i == m){//�ص�����ʼ�� ��ӡ·��
            cnt++;
            printPath(u);
            printf(" %d",i);
            printf("\n");
            break;
        }
        fa[i]=u;//��¼���ڵ�
        dfs(i,num+1);
    }
    vis[u]=0;
}

int main(){
    int a,b,c;
    for(int i=1;i<=20;i++){
        scanf("%d%d%d",&a,&b,&c);
        mp[i][a]=mp[i][b]=mp[i][c]=1;
        mp[a][i]=mp[b][i]=mp[c][i]=1;
    }
    while(scanf("%d",&m) && m){
        cnt=0;
        dfs(m,1);
    }
    return 0;
}
