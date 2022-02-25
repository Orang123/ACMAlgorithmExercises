#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000100
using namespace std;
//dfs+̰��
/*
����:һ��n���ڵ����,����Ҫ�����е�ĳЩ�߶Ͽ�������,
ʹ��������һ��n���ڵ�n����ÿ����Ķ�Ϊ2�Ļ�,��֪
�Ͽ�������һ���ߵĻ���Ϊ1,����������ɻ�����С�����Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4714
˼·:dfs+̰��,���Ƕ���һ������n����֧,�����϶���Ҫ���������ܱ��һ����,
���Ǳ�������з�,�����и��λ�ò�ͬ,���õĻ��ѿ϶�Ҳ��һ��.���ݹ۲췢��,
�������ѡ��Ͽ��븸�׽ڵ�����߽����ٴ����Ӻϲ������������,���������и����ӵĻ��ѻ�Ƚ�С.
���Է�������̰�ĶϿ��븸�׵����ߺϲ������������ʹ�ø��׽ڵ�ķ�֧Խ��Խ��,ֱ��û�з�֧��Ϊһ����Ϊֹ.
*/

int cnt,n,head[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa){
    int son=0;//���㸸�׽ڵ�u�ж��ٸ���֧
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        son+=dfs(v,u);
    }
    if(son>=2){//������ķ�֧������2
        /*
        ���u���Ǹ��ڵ�,��ô����Ļ��Ѿ���(��֧��-1)x2,
        x2�ǶϿ�һ���߱���Ҫ���������Ի�����2 ��������ﻨ��1�������Ͽ���ǰu�ڵ��븸�׵����ߵ�,
        ʣ��Ļ��������������Ͽ��ϲ���һ���������ӵ���һ����֧��.
        */
        if(u!=1) ans+=(son-1)<<1;
        //��u��1���ڵ�,�򻨷�Ϊ(��֧��-2)x2,��Ϊ���ڵ����ʣ��2����֧,�ȵ����ճ�Ϊһ��ֱ��ʱ�������������˵�,ans+1
        else ans+=(son-2)<<1;
        return 0;//��Ϊu�������Ѿ����븸�ڵ���һ�������ӵ���ķ�֧����,���������Ѿ�û�з�֧�� ����0.
    }
    return 1;//��û�з�֧��ֻ��һ����֧ʱ,ͳһ����һ������һ����֧���� ����1
}

int main(){
    int u,v,T;
    scanf("%d",&T);
    while(T--){
        cnt=ans=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",ans+1);//����ٽ����յ�һ��ֱ�����˵����ӳ�Ϊ��ĿҪ��Ļ�,���ans+1
    }
    return 0;
}

/*
����dp���� �����
#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> G[1000005];
int dp[1000005][3],vis[1000005];                //dp[i][j]��ʾ��iΪ���ڵ�����������ö�
void dfs(int s){                                //Ϊjʱ���ķ�֧����Ҳ���ǻ�������j���ڵ�
    int i,tmp;                                  //ʱ���ķ�֧��
    vis[s]=1;
    dp[s][0]=dp[s][1]=dp[s][2]=1;
    for(i=0;i<G[s].size();i++){
        tmp=G[s][i];
        if(!vis[tmp]){
        dfs(tmp);                               //������֧�ϲ����1
        dp[s][0]=min(dp[s][0]+dp[tmp][0],dp[s][1]+dp[tmp][1]-1);
        dp[s][1]=min(dp[s][1]+dp[tmp][0],dp[s][2]+dp[tmp][1]-1);
        dp[s][2]=dp[s][2]+dp[tmp][0];           //��֤s�ڵ�Ϊ�����������ö�Ϊ2��������������ӽڵ�
        }
    }
}
int main(){
    int i,j,t,u,v,n,ans;
    scanf("%d",&t);
    while(t--){
        ans=0;
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        G[i].clear();
        for(i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1);
        ans=min(min(dp[1][0],dp[1][1]),dp[1][2]);
        printf("%d\n",2*ans-1);                 //֪����֧������𰸾��Ƿ�֧��-1+��֧����Ҳ����
    }                                           //�ȷ����ںϲ�
    return 0;
}
*/
