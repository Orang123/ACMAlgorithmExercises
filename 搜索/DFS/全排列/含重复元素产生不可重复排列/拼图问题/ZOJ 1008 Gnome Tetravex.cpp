/*
����:��n*n�������ν������У���Ҫ�ж����ڵ������ε������������ϱߵ������ǲ��Ƕ���ȡ�
0<=n<=5.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827364507
˼·:ö��ÿ�������η�����n*nͼ���е�λ��,�Ǹ���������.
ֻ�������25��������,Ҫע�ⲻ��ö���ظ�����,���Ҫ����.
*/
//ac 1624ms Ԥ����ʱ,���ظ������η�����ͬһ���,vis[i]ͳ�Ƶ�i�������εĸ���
//��Ч����,��������λ������,����Ҫ�жϵķ�λ���ж�,��Ҫ�жϵĵط����ж�
#include<cstdio>
#include<cstring>
int n,num,vis[30],record[30],cnt;
struct Node{
    int top,right,bottom,left;
}node[30],tmp;

int dfs(int k){
    if(k == n*n) return 1;
    int x=k/n,y=k%n;//x-�е��±� y-�е��±�
    for(int i=0;i<num;i++){
        if(!vis[i]) continue;
        //��������ڵ�һ�� �Ǿ���Ҫ�Ƚϵ�ǰλ�õ��ϲ����һ�и�λ�ô����²��Ƿ����
        if(x>0 && node[i].top!=node[record[k-n]].bottom) continue;
        //��������ڵ�һ�� �Ǿ���Ҫ�Ƚϵ�ǰλ�õ�������һ��λ�ô����Ҳ��Ƿ����
        if(y>0 && node[i].left!=node[record[k-1]].right) continue;
        vis[i]--;
        record[k]=i;
        if(dfs(k+1)) return 1;
        vis[i]++;
    }
    return 0;
}
int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=0;
        for(int i=0,j;i<n*n;i++){
            scanf("%d%d%d%d",&tmp.top,&tmp.right,&tmp.bottom,&tmp.left);
            for(j=0;j<num;j++){
                //��ǰ�����ͬ,ֱ�ӽ���j����������+1
                if(node[j].top==tmp.top && node[j].right==tmp.right && node[j].bottom==tmp.bottom && node[j].left==tmp.left){
                    vis[j]++;
                    break;
                }
            }
            if(j == num){//��ǰ���û����ͬ��,�Ͱѵ�ǰ�� ��Ϊһ���µ����
                node[num]=tmp;
                vis[num++]++;
            }
        }
        if(cnt!=1) printf("\n");
        if(dfs(0)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}

/*
//ac 6730ms dfsö������+ö�ٹ���������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
using namespace std;

int n,num,vis[N*N],mp[N][N],cnt;

struct Node{
    int str[5];
    bool operator <(const Node &x)const{
        for(int i=0;i<4;i++){
            if(str[i] != x.str[i])
                return str[i]<x.str[i];
        }
        return 1;
    }
}node[N*N];

int check(int x,int y,int i){
    //��������ڵ�һ�� �Ǿ���Ҫ�Ƚϵ�ǰλ�õ�������һ��λ�ô����Ҳ��Ƿ����
    if(y>0 && node[i].str[3]!=node[mp[x][y-1]].str[1])
        return 0;
    //��������ڵ�һ�� �Ǿ���Ҫ�Ƚϵ�ǰλ�õ��ϲ����һ�и�λ�ô����²��Ƿ����
    if(x>0 && node[i].str[0]!=node[mp[x-1][y]].str[2])
        return 0;
    return 1;
}

int cmp(int *tp,int k){
    for(int i=0;i<4;i++){
        if(tp[i] != node[k].str[i])
            return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == num)
        return 1;
    int x=k/n,y=k%n;//x-�е��±� y-�е��±�
    int tp[5]={-1,-1,-1,-1};//��ʼֵ-1 ��֤��һ�β����ظ�
    for(int i=0;i<num;i++){
        if(vis[i] || !check(x,y,i) || cmp(tp,i)) continue;
        vis[i]=1;
        mp[x][y]=i;
        memcpy(tp,node[i].str,sizeof(tp));
        if(dfs(k+1)) return 1;
        vis[i]=0;;
    }
    return 0;
}

int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=n*n;
        for(int i=0;i<num;i++)
            scanf("%d%d%d%d",&node[i].str[0],&node[i].str[1],&node[i].str[2],&node[i].str[3]);
        sort(node,node+num);
        if(cnt!=1) printf("\n");
        if(dfs(0)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}
*/

/*
//ac 2086ms
#include<cstdio>
#include<cstring>

int n,num,vis[30],record[30],cnt;
struct Node{
    int top,right,bottom,left;//top����С�������ϲ������
}node[30],tmp;

int dfs(int k){
    if(k == n*n+1) return 1;
    for(int i=1;i<=num;i++){
        if(!vis[i]) continue;
        if(k==1){//���õ�һ�е�һ��С������ ����Ҫ����ֱ�ӷ���
            vis[i]--;
            record[k]=i;//��¼���λ�÷����С�����ε�������,�����������ʱ��ǰ��Ľ��бȽ�
            if(dfs(k+1)) return 1;//��������,����һλ��ѡ�������С������
            vis[i]++;
        }
        else if(k<=n){//���ڵ�һ���ڵ�С������ ������һ�����������Ҫ��ǰ��λ�õ��������һ��λ�õ��Ҳ����
            if(node[i].left == node[record[k-1]].right){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
        else if(k%n==1){//���ڳ���һ����ĵ�һ��,���жϵ�ǰλ�õ��ϲ����һ�и�λ�ô����²��Ƿ����
            if(node[i].top == node[record[k-n]].bottom){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
        else{//�������м�λ����Ҫ�жϵ�ǰλ�õ�������һλ�õ��Ҳ��Լ���ǰλ�õ��ϲ����һ�е�ǰλ�õ��²��Ƿ����
            if(node[i].left == node[record[k-1]].right && node[i].top == node[record[k-n]].bottom){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
    }
    return 0;
}
int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=0;
        for(int i=1,j;i<=n*n;i++){
            scanf("%d%d%d%d",&tmp.top,&tmp.right,&tmp.bottom,&tmp.left);
            for(j=1;j<=num;j++){
                //��֦ ������ͬ���͵�С������(��:�ϡ����¡������־���ͬ)��¼Ϊͬһ����,���Լ���dfsʱѭ���Ĵ���
                if(node[j].top==tmp.top && node[j].right==tmp.right && node[j].bottom==tmp.bottom && node[j].left==tmp.left){
                    vis[j]++;
                    break;
                }
            }
            if(j == num+1){
                node[++num]=tmp;
                vis[num]++;
            }
        }
        if(cnt!=1) printf("\n");
        if(dfs(1)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}
*/
