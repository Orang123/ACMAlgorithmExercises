#include<cstdio>
#include<cstring>
#include<vector>
#define N 6//数据量很小 所以暴力回溯枚举所有放置碉堡可行的位置也是可以的
using namespace std;
//ac 0ms 二分图最大匹配
/*
题意:n*n的正方形网格,有空地'.'和墙'X'组成,现在要在空地
上放置碉堡,碉堡可以向同一行同一列射击,但是子弹会被墙挡住,
也就是墙会将同一行和同一列的2个碉堡隔开避免它们相互射击,
现在问n*n网格中最多能放置多少个碉堡使得它们之间任意两个相互不射击.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1045
思路:可以借鉴HDU 1281的行列划分思维,因为墙可以隔开2个碉堡避免它们之间射击,
所以可以将墙体'X'分割开的行连通块、列连通块作为行集合和列集合中的节点设置不同的编号,
各个合法的碉堡位置对应的行连通块和列连通块的标号idx,idy一定是互不相同的,所以转化为了
匹配问题,之后求解二分图最大匹配即可.
因为最大只能是6*6网格,所以暴力回溯枚举所有放置碉堡可行的位置也是可以的
*/
int n,vis[N*N],match[N*N],row[N][N],col[N][N],idx,idy,ans;
char mp[N][N];
vector<int> G[N*N];

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

void init(){
    ans=0;
    idx=idy=1;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n*n;i++) G[i].clear();
}

int main(){
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == 'X') continue;//只有'.'空地可放置碉堡
                //当遍历到下一行或上一个位置mp[i][j-1]被墙'X'隔开时,就遇到了新的行连通块,编号idx+1
                if(j == 1 || mp[i][j-1] == 'X')
                    idx++;
                row[i][j]=idx;
            }
            for(int j=1;j<=n;j++){
                if(mp[j][i] == 'X') continue;
                //当遍历到下一列或上一个位置mp[j-1][i]被墙'X'隔开时,就遇到了新的列连通块,编号idy+1
                if(j == 1 || mp[j-1][i] == 'X')
                    idy++;
                col[j][i]=idy;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '.')//空地可放置碉堡时 将对应的行连通块和列连通块建立idx->idy的有向边
                    G[row[i][j]].push_back(col[i][j]);
            }
        }
        for(int i=1;i<=idx;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms dfs暴力回溯 枚举在每个空地'.'放置碉堡,暴力遍历所有放置的可能性.
//因为并不清楚放置碉堡的最大数目(当前放置的行列匹配不一定是最大匹配),所以要枚举所有放置碉堡位置的可能性
#include<cstdio>
char map[6][6];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int n,max_cnt;
//判断map[x][y]同一行、同一列是否已经放置了碉堡.
bool judge(int x,int y){
    int xx,yy;
    for(int i=0;i<4;i++){
        xx=x,yy=y;
        while(xx>0&&xx<=n&&yy>0&&yy<=n){
            xx+=dir[i][0];
            yy+=dir[i][1];
            if(map[xx][yy]=='Y'){//遇到'Y'说明该方向已经放置了碉堡 map[x][y]放置碉堡会相互射击
                return false;
            }
            if(map[xx][yy]=='X'){//遇到墙体说明该方向上 可保证互不射击 结束
                break;
            }
        }
    }
    return true;
}

//暴力枚举在空地'.'位置放置碉堡
//这个时间复杂度应该和八皇后那种差不多,O(N^N),是NP(Nondeterministic Polynomial-非确定性多项式难题)问题 
//八皇后是NPC(Non-deterministic Polynomial Complete)即多项式复杂程度的非确定性问题,NP完全的
void dfs(int row,int col,int cnt){
    if(cnt>max_cnt)
        max_cnt=cnt;
    for(int i=row;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==row&&j<col)
                continue;
            if(map[i][j]=='.'&&judge(i,j)){
                //若该位置满足4个方向互不射击,在该空地'.'放置碉堡.
                map[i][j]='Y';
                if(j<n)
                    dfs(i,j+1,cnt+1);
                else
                    dfs(i+1,1,cnt+1);
                //因为并不清楚放置碉堡的最大数目,所以要枚举所有放置碉堡位置的可能性,
                //回溯时再还原map[i][j]为空地,尝试在下一个可能的空地位置放置碉堡
                map[i][j]='.';
            }
        }
    }
}

int main(){
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&map[i][j]);
            }
        }
        max_cnt=-1;
        dfs(1,1,0);
        printf("%d\n",max_cnt);
    }
    return 0;
}
*/
