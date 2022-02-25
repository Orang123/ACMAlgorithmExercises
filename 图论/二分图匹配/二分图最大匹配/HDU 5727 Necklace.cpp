#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;
//最大匹配建模问题
//手写枚举全排列TLE 不知何原因,但是用stl的next_permutation就莫名其妙过了
/*
题意:有n个有阴石,n个阳石,有m条规则,eg:u-v
表示阳石u和阴石v相邻时,阳石u就会变得阴暗,
现在要用这2n颗石子做成环形项链,求出至少会
有多少阳石变得阴暗.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5727
思路:因为是做成环形的项链,可以先将阴石固定一个位置枚举剩下
n-1个阴石的全排列再考虑枚举所有的阳石i插入任意的2个阴石子j和j+1之间,
这里对于阳石与阴石j、j+1相邻不会变阴暗时建立阳石i到阴石j的有向边,
之后匈牙利求出最大匹配cnt即是能正常插入n个环形阴石内不会变阴暗的阳石最大数量,
那么n-cnt即是剩下会变得阴暗的阳石,对于每次排列比较n-cnt的最小值即是答案.

其实这个也可以用阳石枚举全排列,插入阴石,因为阳石 阴石个数都为n.
*/

int n,m,mp[N][N],vis[N],match[N],ans,a[N];
vector<int> G[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void hungary(){
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=n;i++){//枚举要插入的阳石i
        int l,r;//l代表a[j] r代表a[j+1]
        for(int j=1;j<=n;j++){//枚举任意相邻的阴石j和j+1
            l=a[j];
            if(j == n) r=a[1];//j==n时,相邻的阴石为a[n]和a[1]
            else r=a[j+1];
            if(!mp[i][l] && !mp[i][r])//若阳石i和l、r均不会发生反应变阴暗,则i->j的有向边
                G[i].push_back(j);
        }
    }
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    //最大匹配代表最大能插入的不会变阴暗的阳石数量,
    //则n-最大匹配就是剩余会变阴暗的阳石数量每次排列取最小值
    ans=min(ans,n-cnt);
}

void permutation(int cnt){
    //如果剩下变阴暗的阳石数量已经达到0(最小),就不必再枚举全排列了.
    if(!ans) return;
    if(cnt == n+1){
        hungary();//枚举完阴石全排列,考虑插入阳石
        return;
    }
    for(int i=2;i<=n;i++){//数值1已经固定在第一个位置,所以从2开始
        if(!vis[i]){
            vis[i]=1;
            a[cnt]=i;
            permutation(cnt+1);
            vis[i]=0;
        }
    }
}

void init(){
    ans=INF;
    memset(mp,0,sizeof(mp));
    memset(vis,0,sizeof(vis));
    //因为是环排列,所以123和321是重复的,因此固定第一个位置放1,
    //枚举剩下n-1个位置的全排列即可.
    a[1]=1;
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        permutation(2);//第一个位置已经固定,从第二个位置开始枚举
        printf("%d\n",ans);
    }
    return 0;
}

/*
//stl 枚举全排列过了
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],vis[N],match[N],ans,a[N];
vector<int> G[N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void hungary(){
    for(int i=1;i<=n;i++) G[i].clear();
    for(int i=1;i<=n;i++){
        int l,r;
        for(int j=1;j<=n;j++){
            l=a[j];
            if(j == n) r=a[1];
            else r=a[j+1];
            if(!mp[i][l] && !mp[i][r])
                G[i].push_back(j);
        }
    }
    int cnt=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    ans=min(ans,n-cnt);
}

void permutation(int cnt){
    if(!ans) return;
    if(cnt == n+1){
        hungary();
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            a[cnt]=i;
            permutation(cnt+1);
            vis[i]=0;
        }
    }
}

void init(){
    ans=INF;
    memset(mp,0,sizeof(mp));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) a[i]=i;
    a[1]=vis[1]=1;
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(!n){
            printf("0\n");
            continue;
        }
        init();
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=1;
        }
        do{
            hungary();
        }while(next_permutation(a+2,a+n+1) && ans);
        //permutation(2);
        printf("%d\n",ans);
    }
    return 0;
}
*/
