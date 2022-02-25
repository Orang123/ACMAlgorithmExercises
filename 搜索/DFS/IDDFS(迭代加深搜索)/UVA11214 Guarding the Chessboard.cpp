/*
题意:
n*m的棋盘,由'X'和'.'组成,皇后可以放置在任意位置,
皇后防御的范围是他所在横、竖、对角线,问最少放几个皇后能防守所有'X'.
1<n,m<10.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2155
思路:类八皇后问题,枚举每一个位置(x,y)是否放置皇后,需要标记
row[x]=col[y]=lr[x-y+m]=rl[x+y]=1,行、列、主对角线、次对角线,
在皇后防御范围内,其中主对角线坐标之差是定值,次对角线坐标之和是定值.
直接暴力回溯时间复杂度可达2^81,因此需要迭代加深搜索IDDFS枚举放置皇后
的最少数量来剪枝.
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
            //对于每个'X' 如果所在行、列、主副对角线都没有皇后 则不被防御,返回0
            if(mp[i][j] == 'X' && !row[i] && !col[j] && !lr[i-j+m] && !rl[i+j])
                return 0;
        }
    }
    return 1;//所有'X' 所在行、列、主副对角线都至少存在一个皇后能防御该'X'
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
    row[x]=a,col[y]=b,lr[x-y+m]=c,rl[x+y]=d;//回溯时 还原行列主副对角线的状态
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
//dfs 6.86s 按道理应该TLE的,UVA 还是给ac了
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
