/*
题意:m*n的矩阵,,其中0代表空的地板,1代表墙,2代表箱子的起始位置,
3代表箱子要被推去的位置,4代表搬运工的起始位置.搬运工的工作就是
把箱子推到指定的位置,注意,搬运工只能推箱子而不能拉箱子,因此如果
箱子被推到一个角上(如图2)那么箱子就不能再被移动了,如果箱子被推到
一面墙上,那么箱子只能沿着墙移动,请你计算出搬运工要将箱子推导3位置,
至少要推动箱子多少格.如果不能推到指定位置则输出-1.
2<=m,n<=7.
注意:人可能需要推着箱子重复经过相同的位置,这是为了调换推箱子的方向,
使得箱子能朝着目标位置3前进.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1254
思路:两种解法.

解法1:因为人可以推着箱子以不同方向到达相同位置,可以将状态设置为4维的
vis[bx][by][px][py],其中(bx,by)是箱子的位置,(px,py)是人的位置.枚举人朝
四个方向走,如果人能走到当前状态下箱子的位置,那么箱子也朝着人走的方向走一格,
步数+1,如果人走不到箱子位置,那么箱子就待在原位置不动,只记录人走的位置,步数不变,作为新的状态入队.

注意:这里实际先入队的是人所走的步数较少的,但箱子所走的步数不一定是最少的,
实际箱子所走的最短步数,应该是以箱子为中心,计算箱子到目标位置的最短曼哈顿距离,
然后人应该尽可能走到箱子移动方向的推动方向的反方向后面推导箱子即可,这个过程无需
考虑箱子到底走了几步.因此应该使用优先队列先出队箱子移动步数较少的状态,那么第一次
到达目标位置3的状态箱子移动步数一定是最少的.

解法2:可以将状态设置为vis[bx][by][4],最后的4代表到达这个位置的4个方向.以箱子为
移动的中心,箱子移动时判断人是否能移动到箱子移动的反方向的后一个位置,这样人才能
推着箱子走.因为bfs扩展状态本身就是以箱子为中心,使用普通队列先进先出,这样第一次
到达目标位置3时的状态步数一定是最少的.判断人是否能走到箱子反方向的后一个位置用
dfs/bfs皆可,箱子移动用bfs.同样vis标记用三维的方向就是为了标记箱子所走得到当前位置
在哪一个方向上,4个方向第一次走到的才是最短的.
*/
//ac 0ms bfs vis[bx][by][px][py]4维数组标记 (箱子位置,人的位置)作为一个元组
//以人为中心扩展,人走到当前箱子位置时,人才能推着箱子移动.
//时间复杂度O(m*n*m*n)=7^4=2401 空间复杂度O(m*n*m*n)=7^4=2401
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

int m,n,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N],vis[N][N][N][N];
struct State{
    int bx,by,px,py,t;
    State(int bx=0,int by=0,int px=0,int py=0,int t=0):bx(bx),by(by),px(px),py(py),t(t){}
    bool operator < (const State &a)const{
        //因为是以人为中心扩展点,先出队的是人走格子较少的,不是箱子移动个数较少的,
        //有可能后入队的实际人走的多的,但箱子移动个数较少,因此用优先队列.
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == 1)
        return 1;
    return 0;
}

int bfs(int bx,int by,int px,int py){
    priority_queue<State> Q;
    vis[bx][by][px][py]=1;
    Q.push(State(bx,by,px,py,0));
    State tp;
    int nbx,nby,npx,npy,ok;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.bx][tp.by] == 3)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nbx=tp.bx;
            nby=tp.by;
            npx=tp.px+dir[i][0];
            npy=tp.py+dir[i][1];
            if(check(npx,npy))
                continue;
            ok=0;
            if(npx == tp.bx && npy == tp.by ){//判断人是否能走到当前箱子的位置,能走到的话 箱子才朝着人走的方向移动,箱子移动步数才+1
                if(check(nbx+dir[i][0],nby+dir[i][1]))
                    continue;
                nbx+=dir[i][0];
                nby+=dir[i][1];
                ok=1;
            }
            if(!vis[nbx][nby][npx][npy]){
                vis[nbx][nby][npx][npy]=1;
                Q.push(State(nbx,nby,npx,npy,tp.t+ok));
            }
        }
    }
    return -1;
}

int main(){
    int T,bx,by,px,py;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                if(mp[i][j] == 2)//箱子初始位置
                    bx=i,by=j;
                else if(mp[i][j] == 4)//人初始位置
                    px=i,py=j;
            }
        }
        printf("%d\n",bfs(bx,by,px,py));
    }
    return 0;
}

/*
//ac 124ms bfs以箱子为中心走箱子,dfs判断人是否能走到推箱子反方向的位置(fx,fy)
//状态标记用三维vis[bx][by][4],代表箱子可以以4个不同的方向走到(bx,by)位置,每个方向只走一次,第一次是最短的.
//时间复杂度O(m*n*4)*O(人是否能走到箱子移动的反方向(时间界不确定)) 空间复杂度O(m*n*m*4)=7^2*4=196
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

int m,n,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N],vis[N][N][4];
struct State{
    int bx,by,px,py,t;
    State(int bx=0,int by=0,int px=0,int py=0,int t=0):bx(bx),by(by),px(px),py(py),t(t){}
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == 1)
        return 1;
    return 0;
}

//dfs判断人是否能走到推箱子反方向的后一个位置(ex,ey),这样人才能推着箱子走,箱子走才是合法的
//O(n*m)=49 最快是初始人的位置到(ex,ey)的曼哈顿距离
int dfs(int px,int py,int ex,int ey){
	if(px == ex && py == ey)
		return 1;
	int npx,npy,flag;
	for(int i=0;i<4;i++){
		npx=px+dir[i][0];
		npy=py+dir[i][1];
		if(!check(npx,npy)){
			flag=mp[npx][npy];
			mp[npx][npy]=1;
			if(dfs(npx,npy,ex,ey)){
				mp[npx][npy]=flag;
				return 1;
			}
			mp[npx][npy]=flag;
		}
	}
	return 0;
}

//O(n*m*4)=196
int bfs(int bx,int by,int px,int py){
    queue<State> Q;
    //注意这里初始时箱子所在位置 不标记,因为箱子还未以任何一种方向到达(bx,by)初始位置
    //vis[bx][by][]=1;
    Q.push(State(bx,by,px,py,0));
    State tp;
    int nbx,nby,fx,fy;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.bx][tp.by] == 3)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            //(nbx,nby)箱子移动的位置
            nbx=tp.bx+dir[i][0];
            nby=tp.by+dir[i][1];
            //(fx,fy)当前箱子状态(tp.bx,tp.by)箱子移动的反方向位置
            fx=tp.bx-dir[i][0];
            fy=tp.by-dir[i][1];
            if(check(nbx,nby) || check(fx,fy) || vis[nbx][nby][i])
                continue;
            //判断人是否走到箱子移动反方向,是不能经过箱子当前位置的(tp.bx,tp.by),所以做标记
            mp[tp.bx][tp.by]=1;
            mp[tp.px][tp.py]=1;
            if(dfs(tp.px,tp.py,fx,fy)){
            	vis[nbx][nby][i]=1;
            	Q.push(State(nbx,nby,tp.bx,tp.by,tp.t+1));
			}
			//取消状态标记
			mp[tp.bx][tp.by]=0;
            mp[tp.px][tp.py]=0;
        }
    }
    return -1;
}

int main(){
    int T,bx,by,px,py;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                if(mp[i][j] == 2)
                    bx=i,by=j;
                else if(mp[i][j] == 4)
                    px=i,py=j;
            }
        }
        printf("%d\n",bfs(bx,by,px,py));
    }
    return 0;
}
*/

/*
测试数据:
input
3

7 4
0 0 0 0
0 0 1 0
0 2 0 3
1 4 1 0
1 0 1 0
1 0 1 0
1 0 0 0

4 4
0 0 1 1
0 0 1 1
0 2 3 1
1 4 1 1

5 6
0 0 0 0 0 3
1 0 1 4 0 1
0 0 1 0 0 1
1 0 2 0 0 1
0 0 0 0 0 1

output
2
3
6
*/
