/*
����:
n*m������,��'X'��'.'���,�ʺ���Է���������λ��,
�ʺ�����ķ�Χ�������ںᡢ�����Խ���,�����ٷż����ʺ��ܷ�������'X'.
1<n,m<10.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2155
˼·:��˻ʺ�����,ö��ÿһ��λ��(x,y)�Ƿ���ûʺ�,��Ҫ���
row[x]=col[y]=lr[x-y+m]=rl[x+y]=1,�С��С����Խ��ߡ��ζԽ���,
�ڻʺ������Χ��,�������Խ�������֮���Ƕ�ֵ,�ζԽ�������֮���Ƕ�ֵ.
ֱ�ӱ�������ʱ�临�Ӷȿɴ�2^81,�����Ҫ������������IDDFSö�ٷ��ûʺ�
��������������֦.
*/
//ac 240ms IDDFS
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
using namespace std;

int n,m,row[N],col[N],lr[N<<1],rl[N<<1];
char mp[N][N];

int check(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //����ÿ��'X' ��������С��С������Խ��߶�û�лʺ� �򲻱�����,����0
            if(mp[i][j] == 'X' && !row[i] && !col[j] && !lr[i-j+m] && !rl[i+j])
                return 0;
        }
    }
    return 1;//����'X' �����С��С������Խ��߶����ٴ���һ���ʺ��ܷ�����'X'
}

int dfs(int cur,int k,int dep){
    if(k == dep)
        return check();
    if(cur == n*m)
        return 0;
    int x=cur/m,y=cur%m;
    int a,b,c,d;
    a=row[x],b=col[y],c=lr[x-y+m],d=rl[x+y];
    row[x]=col[y]=lr[x-y+m]=rl[x+y]=1;
    if(dfs(cur+1,k+1,dep))
        return 1;
    row[x]=a,col[y]=b,lr[x-y+m]=c,rl[x+y]=d;//����ʱ ��ԭ���������Խ��ߵ�״̬
    if(dfs(cur+1,k,dep))
        return 1;
    return 0;
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        scanf("%d",&m);
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(lr,0,sizeof(lr));
        memset(rl,0,sizeof(rl));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;;i++){
            if(dfs(0,0,i)){
                printf("Case %d: %d\n",cas,i);
                break;
            }
        }
    }
    return 0;
}

/*
//dfs 6.86s ������Ӧ��TLE��,UVA ���Ǹ�ac��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int n,m,row[N],col[N],lr[N<<1],rl[N<<1],ans;
char mp[N][N];

int check(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mp[i][j] == 'X' && !row[i] && !col[j] && !lr[i-j+m] && !rl[i+j])
                return 0;
        }
    }
    return 1;
}

void dfs(int cur,int k){
    if(check()){
    	if(k<ans)
    		ans=k;
        return;
	}
	if(k>=ans)
		return;
    if(cur == n*m)
        return;
    int x=cur/m,y=cur%m;
    int a,b,c,d;
    a=row[x],b=col[y],c=lr[x-y+m],d=rl[x+y];
    row[x]=col[y]=lr[x-y+m]=rl[x+y]=1;
    dfs(cur+1,k+1);
    row[x]=a,col[y]=b,lr[x-y+m]=c,rl[x+y]=d;
    dfs(cur+1,k);
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        scanf("%d",&m);
        ans=INF;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                scanf(" %c",&mp[i][j]);
        }
        dfs(0,0);
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}
*/
