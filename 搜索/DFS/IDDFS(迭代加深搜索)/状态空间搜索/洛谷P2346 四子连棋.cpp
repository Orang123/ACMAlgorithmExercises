/*
题意:在一个4*4的棋盘上摆放了14颗棋子，其中有7颗白色棋子，7颗黑色棋子，
有两个空白地带，任何一颗黑白棋子都可以向上下左右四个方向移动到相邻的空格，
这叫行棋一步，黑白双方交替走棋，任意一方可以先走，如果某个时刻使得任意一种
颜色的棋子形成四个一线（包括斜线），这样的状态为目标棋局。
从文件中读入一个4*4的初始棋局，黑棋子用B表示，白棋子用W表示，空格地带用O表示。
用最少的步数移动到目标棋局的步数。
链接:https://www.luogu.com.cn/problem/P2346
思路:因为实际4*4的棋盘上实际有14颗棋子,但只有2个空格位,由于要黑白棋交替走,很明显
不好以棋子作为中心点扩展,可以类似八数码将这2个空格位作为中心点去和周围棋子交换位置.
两种做法.

做法1:bfs 需要将 棋盘状态,以及上一步所走黑棋还是白棋标注出来,以方便下一步交换位置时
是交换黑棋还是白棋.由于棋牌只有4*4,所以可以不对状态判重,第一次出现4棋一线时的步数就是
最少的.实际也不好去设置状态 去判重,因为它并不想八数码那样是一个数字排列,一个棋盘整体无法
压缩状态.
真的要判重 可以这样将每一次入队的棋盘状态都存入vis中,vis是存放所有出现过的棋盘状态,每次入队
时和之前出现的棋盘状态比较,如有重复取消入队,这种做法只有单棋盘行列<10时 空间才可承受的住,不然也是TLE,MLE.
struct Vis{
    char mp[4][4];
};
vector<Vis> vis;

做法2:迭代加深搜索
迭代加深搜索(IDDFS-Iterative Deepening-dfs)是在速度上接近广度优先搜索,空间上和深度优先搜索相当的搜索方式.
由于在使用过程中引入了深度优先搜索,所以也可以当作深度优先搜索的优化方案.
迭代加深搜索适用于当搜索深度没有明确上限的情况(就是求解最值).
在进行深度优先搜索前先规定好这次搜索的最大深度dep,当搜索到达dep却还没搜索到结果时回溯.
之后不断加大搜索深度,重新搜索,直到找到结果为止.虽然这样搜索次数会累计很多次,但每一次搜索的范围和下一次搜索
的范围相比微不足道,所以整体搜索速度不会受太大影响.

迭代加深搜索 线性递增可能需要的步数,在某个规定的步数内dfs这样复杂度会较低,
这样就可以避免遍历所有可能的走法通过比对求出最小步数.
*/
//ac 12ms bfs
#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

struct Node{
    int x[2],y[2],step;//x[2]、y[2]代表棋盘上2个空格的位置
    char map0[6][6],col;//因为每次移动棋盘的摆放情况会发生变化,因此map0也作为状态的一部分保存
    int judge(){
        for(int i=1;i<=4;i++){
            if(map0[i][1] == map0[i][2] && map0[i][2] == map0[i][3] && map0[i][3] == map0[i][4]) return 1;
            if(map0[1][i] == map0[2][i] && map0[2][i] == map0[3][i] && map0[3][i] == map0[4][i]) return 1;
        }
        if(map0[1][1] == map0[2][2] && map0[2][2] == map0[3][3] && map0[3][3] == map0[4][4]) return 1;
        if(map0[1][4] == map0[2][3] && map0[2][3] == map0[3][2] && map0[3][2] == map0[4][1]) return 1;
        return 0;
    }
}n1,n2,tmp;

int judge(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=4) return 1;
    else return 0;
}

int bfs(){
    queue<Node> Q;
    n1.col='B';//先开始移动黑棋子
    Q.push(n1);
    n1.col='W';//后移动白棋子
    Q.push(n1);
    int x,y;
    while(!Q.empty()){
        tmp=Q.front();
        if(tmp.judge()) return tmp.step;//因为队列先进先出,最先满足四子连棋的就是步数最小的
        Q.pop();
        for(int j=0;j<2;j++){//枚举移动2个空位置
            for(int i=0;i<4;i++){
                x=tmp.x[j]+dir[i][0];
                y=tmp.y[j]+dir[i][1];
                if(judge(x,y) && tmp.map0[x][y]==tmp.col){
                    n2=tmp;
                    swap(n2.map0[n2.x[j]][n2.y[j]],n2.map0[x][y]);//交换空格的位置
                    n2.step++;
                    n2.col=(n2.col=='B'?'W':'B');//下一次移动的颜色相反
                    n2.x[j]=x,n2.y[j]=y;
                    Q.push(n2);
                }
            }
        }
    }
    return -1;
}

int main(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cin >> n1.map0[i][j];
            if(n1.map0[i][j]=='O' && !n1.x[0]) n1.x[0]=i,n1.y[0]=j;
            else if(n1.map0[i][j]=='O') n1.x[1]=i,n1.y[1]=j;
        }
    }
    printf("%d\n",bfs());
	return 0;
}

/*
//ac 11ms 迭代加深搜索
//枚举dfs时所能走的最大步数,每次迭代 最大步数+1,第一次出现4子连棋时即是 所需的最小步数.
//迭代加深搜索(IDDFS-Iterative Deepening-dfs)是在速度上接近广度优先搜索,空间上和深度优先搜索相当的搜索方式.
//由于在使用过程中引入了深度优先搜索,所以也可以当作深度优先搜索的优化方案.
//迭代加深搜索适用于当搜索深度没有明确上限的情况(就是求解最值).
//在进行深度优先搜索前先规定好这次搜索的最大深度dep,当搜索到达dep却还没搜索到结果时回溯.
//之后不断加大搜索深度,重新搜索,直到找到结果为止.虽然这样搜索次数会累计很多次,但每一次搜索的范围和下一次搜索的范围相比微不足道,
//所以整体搜索速度不会受太大影响.
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
char map0[6][6];
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},ans;
int judge1(){
    for(int i=1;i<=4;i++){
        //行 列判断是否四子连棋
        if(map0[i][1] == map0[i][2] && map0[i][2] == map0[i][3] && map0[i][3] == map0[i][4]) return 1;
        if(map0[1][i] == map0[2][i] && map0[2][i] == map0[3][i] && map0[3][i] == map0[4][i]) return 1;
    }
    //主副对角线判断是否四子连棋
    if(map0[1][1] == map0[2][2] && map0[2][2] == map0[3][3] && map0[3][3] == map0[4][4]) return 1;
    if(map0[1][4] == map0[2][3] && map0[2][3] == map0[3][2] && map0[3][2] == map0[4][1]) return 1;
    return 0;
}

int judge2(int x,int y){
    if(x>=1 && x<=4 && y>=1 && y<=4) return 1;
    else return 0;
}
//(x,y)代表第1个空格的位置 (x0,y0)代表第2个空格的位置
//dfs搜索在当前step限定下 从初始 2空格出发 向四周移动 能否出现4子连棋
int dfs(int x,int y,int x0,int y0,char col,int step){
    if(step == ans){
        if(judge1())//是否存在四子连棋
            return 1;
        else return 0;
    }
    int x1,y1,x2,y2;
    for(int i=0;i<4;i++){
        x1=x+dir[i][0];
        y1=y+dir[i][1];
        x2=x0+dir[i][0];
        y2=y0+dir[i][1];
        //两个if代表枚举2个 和用哪一个空格去交换
        if(judge2(x1,y1) && col==map0[x1][y1]){
            swap(map0[x][y],map0[x1][y1]);//交换棋子的位置
            //这里不用考虑是否会重复遍历又和之前的棋子重复交替还原,因为下次交替的棋子颜色必然和上一次不同色
            if(dfs(x1,y1,x0,y0,col=='B'?'W':'B',step+1)) return 1;//若此次选择的是黑棋,那么下一个只能选择白棋这样交替进行
            swap(map0[x1][y1],map0[x][y]);//还原

        }
        if(judge2(x2,y2) && col==map0[x2][y2]){
            swap(map0[x0][y0],map0[x2][y2]);
            if(dfs(x,y,x2,y2,col=='B'?'W':'B',step+1)) return 1;
            swap(map0[x2][y2],map0[x0][y0]);
        }
    }
    return 0;
}

//这里因为要黑白棋交替和空格交换,那么选择黑白棋作为移动的中心有很大的不确定性,到底移动哪个黑白棋,
//而题目中空格的位置只有2个,并且每次移动都是和空格交换,那么可以把空格作为移动的中心枚举点,
//从空格向四周扩展,然后黑白棋的交替,通过在dfs离控制颜色.

int main(){
    int x=0,y,x0,y0;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cin >> map0[i][j];//这题的输入数据有问题,每一行字符后面可能有空格,为了避免这种问题,推荐用scanf("%s",map0[i])一行整体读入,或cin>>
            if(map0[i][j]=='O' && !x) x=i,y=j;
            else if(map0[i][j]=='O') x0=i,y0=j;
        }
    }
    //迭代加深搜索 线性递增可能需要的步数,在某个规定的步数内dfs这样复杂度会较低,
    //这样就可以避免遍历所有可能的走法通过比对求出最小步数.

    //这个本身交替就有可能 会遍历到重复的位置的棋子,但是因为实际是黑白棋交替下,
    //因此也不会一直正反两方向交替那种死循环,但是不设自步长上限,实际复杂度还是有点大.
    for(ans=0;;ans++){//枚举最小的步数,枚举第一次交替的颜色
        if(dfs(x,y,x0,y0,'B',0)) break;
        if(dfs(x,y,x0,y0,'W',0)) break;
    }
    printf("%d\n",ans);
	return 0;
}
*/

/*
直接dfs爆搜,不设置单步搜索步长,按这个走法 会出现不断地搜索重复的状态空间,
进入无线递归.但是按道理不会啊,因为黑白棋是交替变换的,不会出现往回走的那种情况.
*/
