/*
����:������дһ�������ҵ�һ������ͼ������Ⱦɫ������Ⱦɫ��ָ��ͼ�ϵĵ�Ⱦɫ��
����ֻ�кڰ׶�ɫ���á�����Ⱦɫ����Ҫ��Ⱦ�ɺ�ɫ�ĵ���ࡣȾɫ���ƣ�
��ֹ��һ���������������㶼Ⱦ��ɫ��
��ĸ���<=100.
����:https://www.luogu.com.cn/problem/UVA193
˼·:���Ե���ö��ÿ����Ⱦ��ɫ���ɫ,����Ⱦ��ɫ���뱣֤�뵱ǰ�������ĵ�
����ɫû��һ����Ⱦ�ɺ�ɫ��.����εĸ��Ӷ�Ϊ2^100,ʵ����Ϊ������
��ɫ��ɫ�����,���Ը��Ӷ�û����ô��.

ע��:���ܰ���ͼ�ı���ͨ˳�� ��������ͼ,��Ϊʵ��Ⱦ�ɺ�ɫ�ĵ����Ŀ���ı���
˳���޹�,֮��ÿ����Ⱦ�ɺ�ɫ���ǰ�ɫ����������й�,�����������ͼ,�����ʵ��
˳��Ҳ��Ϊһ�ֿ���ȥ����,�����ͻ����ػ���,���ӶȾ͹���,�ͻ�TLE.
*/
//ac 10ms ���Ե���ö�ٵ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,mp[N][N],col[N],ans,vis[N];

void dfs(int u,int num){
    if(u == n+1){
        if(num>ans){
            ans=num;
            memcpy(vis,col,sizeof(col));
        }
        return;
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        if(mp[u][i] && col[i]){//�жϺ�u���ڽӵĵ� �Ƿ���Ⱦ��ɫ,�����Ⱦ��ɫ �Ͳ�����Ⱦ��ɫ,ֻ��Ⱦ��ɫ
            flag=1;
            break;
        }
    }
    if(!flag){
        col[u]=1;
        dfs(u+1,num+1);
        col[u]=0;
    }
    dfs(u+1,num);
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(mp,0,sizeof(mp));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=mp[v][u]=1;
        }
        dfs(1,0);
        printf("%d\n",ans);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",i);
                    flag=1;
                }
                else
                    printf(" %d",i);
            }
        }
        printf("\n");
    }
    return 0;
}

/*
//TLE
//���ܰ���ͼ�ı���ͨ˳�� ��������ͼ,��Ϊʵ��Ⱦ�ɺ�ɫ�ĵ����Ŀ���ı���
//˳���޹�,֮��ÿ����Ⱦ�ɺ�ɫ���ǰ�ɫ����������й�,�����������ͼ,�����ʵ��
//˳��Ҳ��Ϊһ�ֿ���ȥ����,�����ͻ����ػ���,���ӶȾ͹���,�ͻ�TLE.
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,col[N],ans,vis[N],b[N];
vector<int> G[N];

void dfs(int u,int num,int k){
    if(k == n){
        if(num>ans){
            ans=num;
            int j=0;
            for(int i=1;i<=n;i++){
            	if(col[i])
            		b[++j]=i;
			}
        }
        return;
    }
    vis[u]=1;
    for(int &v : G[u]){
    	if(vis[v]) continue;
    	int flag=0;
    	for(int &tp : G[v]){
    		if(vis[tp] && col[tp]){
    			flag=1;
    			break;
			}
		}
		if(!flag){
			col[v]=1;
			dfs(v,num+1,k+1);
			col[v]=0;
		}
		dfs(v,num,k+1);
	}
	vis[u]=0;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        	G[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        col[1]=1;
        dfs(1,1,1);
        col[1]=0;
        dfs(1,0,1);
        printf("%d\n",ans);
        int flag=0;
        for(int i=1;i<=ans;i++){
            if(!flag){
                printf("%d",b[i]);
                flag=1;
            }
            else
                printf(" %d",b[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
