/*
题意:m*n的网格,'*'表示障碍物,'.'表示走廊,'|'或者'-'表示一个楼梯,
并且标明了它在一开始时所处的位置:'|'表示的楼梯在最开始是竖直方向,
'-'表示的楼梯在一开始是水平方向.地图中还有一个'S'是起点,'T'是目标.
地图中不会出现两个相连的梯子.一开始楼梯在竖直方向,一分钟以后它移动
到了水平方向,再过一分钟它又回到了竖直方向.Harry只能每次走到相邻的
格子而不能斜走,每移动一次恰好为一分钟,并且Harry登上楼梯并经过楼梯
到达对面的整个过程只需要一分钟,Harry从来不在楼梯上停留.并且每次楼梯
都恰好在Harry移动完毕以后才改变方向.
0<=n,m<=20.
说明:harry是否能走楼梯取决于在走到楼梯之前楼梯的方向是否和行走的方向
一致,而不是走到楼梯过了1分钟后,楼梯的方向是否和行走方向一致.
harry可以在非楼梯位置等待直到楼梯的方向和自己的行走方向一致.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2216
思路:bfs.假设楼梯初始状态为'|',当时间点是偶数时,楼梯会回到初始状态'|',
只允许垂直方向通过.当时间点是奇数时,楼梯的状态是'-'只允许水平方向通过.
如果人在走到楼梯之前楼梯的方向与行走方向不一致,人需要在原位置多等待1分钟才能通过.
人不能停留在楼梯上,除了楼梯外其余位置第一次经过时就是最短时间.
有两种入度方式:
方式1:对于楼梯方向和行走方向不一致时需要在原位置多等待1分钟这个转态单独作为新的状态
入队,所以每次入队的所有状态增加的时间都是1,因此可用普通队列.
方式2:对于楼梯方向和行走方向不一致时需要在原位置多等待1分钟,这个状态并不单独入队,而是
直接多等待一分钟,再用一分钟走到楼梯,通过楼梯到达下一个网格作为新的状态,这个状态花费的
时间是2,每次入队的状态增加的时间不同,先到达的比一定时间较少,因此用优先队列.
*/
//ac 0ms bfs 普通队列 根据时间的奇偶性判断楼梯方向
//方式1:对于楼梯方向和行走方向不一致时需要在原位置多等待1分钟这个转态单独作为新的状态
//入队,所以每次入队的所有状态增加的时间都是1,因此可用普通队列.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 21
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == '*')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    queue<State> Q;
    mp[sx][sy]='*';
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,flag;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.x][tp.y] == 'T')
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            flag=0;
            //行走方向为上下
            if(i<2){
                //(nx,ny)初始状态为'|',当前用时为奇数,(nx,ny)状态为'-',需要等待1分钟
                //注意这里是否能直接通行,不是根据走到楼梯(nx,ny)的时间点tp.t+1,而是根据在原(tp.x,tp.y)的时间tp.t来看,这里当时wa了好久
                if(mp[nx][ny] == '|' && tp.t%2)
                    flag=1;
                //(nx,ny)初始状态为'-',当前用时为偶数,(nx,ny)仍状态为'-',需要等待1分钟
                if(mp[nx][ny] == '-' && tp.t%2==0)
                    flag=1;
            }
            //行走方向为左右
            else{
                //(nx,ny)初始状态为'|',当前用时为偶数,(nx,ny)状态为'|',需要等待1分钟
                if(mp[nx][ny] == '|' && tp.t%2==0)
                    flag=1;
                //(nx,ny)初始状态为'-',当前用时为奇数,(nx,ny)状态为'|',需要等待1分钟
                if(mp[nx][ny] == '-' && tp.t%2)
                    flag=1;
            }
            if(flag){
                //将在(tp.x,tp.y)单独等待1分钟作为新的状态入队
                //所有新状态用时均为1分钟,普通队列即可.
                Q.push(State(tp.x,tp.y,tp.t+1));
                continue;
            }
            //对于楼梯 直接在该方向通行到 下一个合法网格,人不能再楼梯停留
            //楼梯通过了,还能再通过
            if(mp[nx][ny] == '|' || mp[nx][ny] == '-'){
                if(!check(nx+dir[i][0],ny+dir[i][1])){
                    nx+=dir[i][0];
                    ny+=dir[i][1];
                }
                else//不合法 不入队
                    continue;
            }
            if(mp[nx][ny] != 'T')//'T'结束状态不能标记,否则结束条件无法判定
                mp[nx][ny]='*';//已到达的状态标记为'*'障碍物
            Q.push(State(nx,ny,tp.t+1));
        }
    }
    return tp.t;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&m,&n)!=EOF){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}

/*
//ac 0ms bfs 优先队列
//方式2:对于楼梯方向和行走方向不一致时需要在原位置多等待1分钟,这个状态并不单独入队,而是
//直接多等待一分钟,再用一分钟走到楼梯,通过楼梯到达下一个网格作为新的状态,这个状态花费的
//时间是2,每次入队的状态增加的时间不同,先到达的比一定时间较少,因此用优先队列.
//遇到楼梯需要在原位置等待的状态不入队,而是直接将原状态时长加1分钟后,
//直接再花1分钟通过楼梯跳到下一位置,因此从(tp.x,tp.y)到(nx,ny)共花时间2分钟
//因此bfs每一步花费时间不同,因此要用优先队列才能保证第一个到达'T'点的时间是最少的.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 21
using namespace std;

int n,m,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
		return t>a.t;
	}
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == '*')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
	priority_queue<State> Q;
    mp[sx][sy]='*';
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,nt;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y] == 'T')
            break;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            //注意这里 时间要用一个临时变量nt来保存,因为下面对于'|' 、'-'的处理会使得(tp.x,tp.y)时间+1,
			//如果check(nx,ny)不入队,tp.t在下个方向dir[i] 就不是原先最先出队的值,结果就会出错
            nt=tp.t;
            if(check(nx,ny))
                continue;
            //对于楼梯方向和行走方形不一致要多等待的情况 直接将时间nt多加1
            if(mp[nx][ny] == '|'){
            	if(i<2 && tp.t%2)
            		nt++;
            	else if(i>=2 && tp.t%2==0)
            		nt++;
            	nx+=dir[i][0];//楼梯通行的下一个网格作为新状态,用时为2分钟
                ny+=dir[i][1];
			}
			else if(mp[nx][ny] == '-'){
				if(i<2 && tp.t%2==0)
					nt++;
				else if(i>=2 && tp.t%2)
					nt++;
				nx+=dir[i][0];
                ny+=dir[i][1];
			}
            if(check(nx,ny))
            	continue;
            if(mp[nx][ny] != 'T')
                mp[nx][ny]='*';
            Q.push(State(nx,ny,nt+1));
        }
    }
    return tp.t;
}

int main(){
    int sx,sy;
    while(scanf("%d%d",&m,&n)!=EOF){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'S')
                    sx=i,sy=j;
            }
        }
        printf("%d\n",bfs(sx,sy));
    }
    return 0;
}
*/

/*
测试数据来自HDU Discuss模块
input
3 4
S|.|
-T-.
.|..

20 20
S.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.|
|.|.|.|.|.|.|.|.|.|.
.|.|.|.|.|.|.|.|.|.T

output
7
20

*/
