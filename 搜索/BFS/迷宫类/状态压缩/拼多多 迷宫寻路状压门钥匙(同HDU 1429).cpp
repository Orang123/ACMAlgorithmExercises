/*
//和HDU 1429 胜利大逃亡(续)是一道题
这题就是普通的bfs多了‘钥匙’这个状态
 所以book[x][y][key]的意义就是 横坐标为x,纵坐标为y,钥匙状态为key的点是否访问过
 钥匙的状态 就用二进制数表示 最多10 把钥匙 那就是1024
 比如我现在有第二把钥匙和第四把钥匙  那么我的钥匙状态就是 0101000000 也就是 320
链接：https://www.nowcoder.com/questionTerminal/e3fc4f8094964a589735d640424b6a47
来源：牛客网

假设一个探险家被困在了地底的迷宫之中，要从当前位置开始找到一条通往迷宫出口的路径。迷宫可以用一个二维矩阵组成，有的部分是墙，有的部分是路。
迷宫之中有的路上还有门，每扇门都在迷宫的某个地方有与之匹配的钥匙，只有先拿到钥匙才能打开门。请设计一个算法，帮助探险家找到脱困的最短路径。
如前所述，迷宫是通过一个二维矩阵表示的，每个元素的值的含义如下 0-墙，1-路，2-探险家的起始位置，3-迷宫的出口，大写字母-门，小写字母-对应大
写字母所代表的门的钥匙

输入描述:
迷宫的地图，用二维矩阵表示。第一行是表示矩阵的行数和列数M和N
后面的M行是矩阵的数据，每一行对应与矩阵的一行（中间没有空格）。M和N都不超过100, 门不超过10扇。


输出描述:
路径的长度，是一个整数

输入
5 5
02111
01a0A
01003
01001
01111
输出
7
 */

#include<cstdio>
#include<queue>
using namespace std;
struct node{
    int x,y;
    int key;
    int len;
};

char map0[110][110];
int pos[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
bool visit[110][110][1100];
int m,n;

bool judge(int x,int y,int &key){
    if(x<=-1||y<=-1||x>=m||y>=n||map0[x][y]=='0')
        return false;
    if(map0[x][y]>='A'&&map0[x][y]<='J'&&!(key&(1<<(map0[x][y]-'A')))){
        return false;
    }
    if(map0[x][y]>='a'&&map0[x][y]<='j'){
        key|=(1<<(map0[x][y]-'a'));
    }
    if(visit[x][y][key])
        return false;
    return true;

}

int BFS(int x,int y){
    queue<node> Q;
    node tmp,next;
    tmp.x=x,tmp.y=y,tmp.len=0,tmp.key=0;//别忘了 对key初始化为0
    int key;
    Q.push(tmp);
    while(!Q.empty()){
        tmp=Q.front();
        Q.pop();
        if(map0[tmp.x][tmp.y]=='3') return tmp.len;
        for(int i=0;i<4;i++){
            key=tmp.key;
            next.x=tmp.x+pos[i][0];
            next.y=tmp.y+pos[i][1];
            if(judge(next.x,next.y,key)){
                next.len=tmp.len+1;
                next.key=key;
                Q.push(next);
                visit[next.x][next.y][key]=true;
            }
        }
    }
    return -1;//这个编译器这里必须有返回值,不然会报错
}

int main(){
    int x,y;
    //freopen("input.txt","r",stdin);
    scanf("%d%d",&m,&n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf(" %c",map0[i]+j);
            if(map0[i][j]=='2'){
                x=i,y=j;
                visit[x][y][0]=true;
            }
        }
    }
    printf("%d",BFS(x,y));
    return 0;
}

