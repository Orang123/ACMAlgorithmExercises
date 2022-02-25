/*
题意:摘自网上
有一个r*c的密码锁，给定解密方式是一个3*3的矩阵，‘*’表示灯亮，’.‘表示灯灭。
对于密码锁，触动一个按键，相当于把这个按键对应到3*3矩阵中间的按键处，
然后对应’*'的位置的灯都会亮，如果本来是亮的就会灭掉。计算最快按哪些按钮
可以使密码锁上每个按键的灯都亮。
0<r,c<=5.
链接:https://www.luogu.com.cn/problem/UVA10318
思路:需要将3*3的矩阵的按键影响方式记录下来,记录方式是从下标为0开始,记录
为'*'灯亮的地方(i,j),而(i-1,j-1)就是相对(i,j)的需要变化的距离方向.
需要枚举r*c个按键,对于每个按键来说到底按还是不按,对于r*c灯的点亮情况
的表示,可以用二进制状压(最多只有25个格子),搜索结束标志是所有灯都被点亮,
状态为 (1<<r*c)-1或枚举完所有按键时.
有两个剪枝:
剪枝1:当所枚举的按键位置超过第二行时,判断当前行-2的行,是否都被点亮,如果还存在没
点亮的 那么就永远无法点亮了,因为按键只会影响前一行,无法影响超过一行以上的位置.
剪枝2:当前方案按下的按键数量如果已经超过之前记录的最小数目,就返回.

实际不加两个剪枝也能800msac.
*/
//ac 0ms 状压+枚举位置选取与否+剪枝
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int r,c,cnt,s[25],tp[25],res[25],ans;
char mp[3][3];
vector<pair<int,int> > dir;

void dfs(int cur,int sta,int k){
    if(k>ans)//剪枝2:当前方案按下的按键数量如果已经超过之前记录的最小数目,就返回.
        return;
    if(sta == (1<<cnt)-1){
        if(k<ans){
            ans=k;
            memcpy(res,tp,ans*4);
        }
        return;
    }
    if(cur == cnt)
        return;
    int x=cur/c;
    //剪枝1:当所枚举的按键位置超过第二行时,判断当前行-2的行,是否都被点亮,如果还存在没
    //点亮的 那么就永远无法点亮了,因为按键只会影响前一行,无法影响超过一行以上的位置.
    if(x>=2){//没有这个剪枝 780ms
        int tx=x-2;
        for(int i=0;i<c;i++){
            if(!(sta & 1<<(tx*c+i)))
                return;
        }
    }
    tp[k]=cur+1;
    dfs(cur+1,sta^s[cur],k+1);
    dfs(cur+1,sta,k);
}

int main(){
    int x,y,nx,ny,cas=0;
    while(scanf("%d%d",&r,&c) && r+c){
        cas++;
        cnt=r*c;
        ans=INF;
        memset(s,0,sizeof(s));
        dir.clear();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '*')
                    dir.push_back(make_pair(i-1,j-1));
            }
        }
        for(int i=0;i<cnt;i++){
            x=i/c;
            y=i%c;
            for(pair<int,int> &tp : dir){
                nx=x+tp.first;
                ny=y+tp.second;
                if(nx<0 || nx>=r || ny<0 || ny>=c)
                    continue;
                s[i]|=1<<(nx*c+ny);
            }
        }
        dfs(0,0,0);
        printf("Case #%d\n",cas);
        if(ans == INF)
            printf("Impossible.\n");
        else{
            printf("%d",res[0]);
            for(int i=1;i<ans;i++)
                printf(" %d",res[i]);
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 0ms 无状压
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int r,c,cnt,tp[25],res[25],ans,vis[N][N];
char mp[3][3];

int check(){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(!vis[i][j])
                return 0;
        }
    }
    return 1;
}

void update(int x,int y){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(mp[i][j] == '*' && x+i-1>=0 && x+i-1<r && y+j-1>=0 && y+j-1<c)
                vis[x+i-1][y+j-1]^=1;
        }
    }
}

void dfs(int cur,int k){
    if(k>ans)
        return;
    if(check()){
        if(k<ans){
            ans=k;
            memcpy(res,tp,ans*4);
        }
        return;
    }
    if(cur == cnt)
        return;
    int x=cur/c;
    int y=cur%c;
    if(x>=2){
        int tx=x-2;
        for(int i=0;i<c;i++){
            if(!vis[tx][i])
                return;
        }
    }
    tp[k]=cur+1;
    update(x,y);
    dfs(cur+1,k+1);
    update(x,y);
    dfs(cur+1,k);
}

int main(){
    int cas=0;
    while(scanf("%d%d",&r,&c) && r+c){
        cas++;
        cnt=r*c;
        ans=INF;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                scanf(" %c",&mp[i][j]);
        }
        dfs(0,0);
        printf("Case #%d\n",cas);
        if(ans == INF)
            printf("Impossible.\n");
        else{
            printf("%d",res[0]);
            for(int i=1;i<ans;i++)
                printf(" %d",res[i]);
            printf("\n");
        }
    }
    return 0;
}
*/
