/*
题意:8*8的网格,'x'和'o'分别代表两个人的棋，游戏
规则就是围棋,'.'代表还能下棋的格子,问x再下一个棋
能不能杀死o的至少一个棋子,就是说'X'要把能够围起来的
'O'完全围住,X围住的部分不能有'.'空白格子.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5546
思路:可以考虑枚举每个'O',从'O'开始dfs,遇到'O'继续搜索,
遇到'.'停止,统计遇到'.'的数目,如果超过了1个,则不会被1个'X'
围住,否则如果'.'个数恰好等于1个,则可以被围住.
*/
//ac 15ms dfs
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
char mp[11][11];
int vis[11][11],cnt,num;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct Node{
    int x,y;
}node[100];
int judge(int x,int y){
    if(x>=1 && x<=9 && y>=1 &&y<=9) return 1;
    else return 0;
}
//判断以'o'连接的连通块周围是否能只有一个'.'则说明可以
int dfs(int x,int y){
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0)){
            if(mp[x0][y0]=='o' && !vis[x0][y0]){
                vis[x0][y0]=1;
                if(dfs(x0,y0)) return 1;
            }
            if(mp[x0][y0]=='.' && !vis[x0][y0]){//同一个连通块不能连续访问同一个’.'
                vis[x0][y0]=1;
                cnt++;
            }
            if(cnt>1) return 1;
        }
    }
    return 0;
}

int main(){
    int T,num,cas=0,flag;
    scanf("%d",&T);
    while(T--){
        cas++;
        num=0;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 'o') node[num].x=i,node[num++].y=j;
            }
        }
        flag=0;
        for(int i=0;i<num;i++){
            cnt=0;
            //这里每次都要初始化vis,因为上次会把'.'标记为已访问,会影响下一次对'.'的统计
            memset(vis,0,sizeof(vis));
            vis[node[i].x][node[i].y]=1;
            dfs(node[i].x,node[i].y);
            if(cnt == 1){
                flag=1;
                break;
            }
        }
        if(flag)
            printf("Case #%d: Can kill in one move!!!\n",cas);
        else
            printf("Case #%d: Can not kill in one move!!!\n",cas);
    }
    return 0;
}
/*
//ac 0ms bfs版本
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
char mp[11][11];
int vis[11][11],cnt;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct Node{
    int x,y;
}node[100];
int judge(int x,int y){
    if(x>=1 && x<=9 && y>=1 &&y<=9) return 1;
    else return 0;
}
int bfs(int x,int y){
    queue<Node> Q;
    Node now,tmp;
    tmp.x=x,tmp.y=y;
    Q.push(tmp);
    int x0,y0;
    while(!Q.empty()){
        tmp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            x0=tmp.x+dir[i][0];
            y0=tmp.y+dir[i][1];
            if(judge(x0,y0)){
                if(mp[x0][y0]=='o' && !vis[x0][y0]){
                    vis[x0][y0]=1;
                    now.x=x0,now.y=y0;
                    Q.push(now);
                }
                if(mp[x0][y0]=='.' && !vis[x0][y0]){
                    vis[x0][y0]=1;
                    cnt++;
                    if(cnt>1) return 1;
                }
            }
        }
    }
    return 0;
}

int main(){
    int T,num,cas=0,flag;
    scanf("%d",&T);
    while(T--){
        cas++;
        num=0;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 'o') node[num].x=i,node[num++].y=j;
            }
        }
        flag=0;
        for(int i=0;i<num;i++){
            memset(vis,0,sizeof(vis));
            cnt=0;
            vis[node[i].x][node[i].y]=1;
            bfs(node[i].x,node[i].y);
            if(cnt == 1){
                flag=1;
                break;

            }
        }
        if(flag)
            printf("Case #%d: Can kill in one move!!!\n",cas);
        else
            printf("Case #%d: Can not kill in one move!!!\n",cas);
    }
    return 0;
}
*/
