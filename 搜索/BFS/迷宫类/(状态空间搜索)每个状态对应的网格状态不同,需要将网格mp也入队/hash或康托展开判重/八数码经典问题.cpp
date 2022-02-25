/*
八数码问题描述:
在3×3的棋盘,摆有八个棋子,每个棋子上标有1至8的某一数字,
不同棋子上标的数字不相同.棋盘上还有一个空格'x',与空格相邻
的棋子可以和空格交换位置.棋盘的状态表示为从(0,0)到(2,2)自左向右,
自上而下形成的排列串,要求解决的问题是:给出一个初始状态和一个
目标状态,求出初始状态转变成目标状态的所需移动的最少步数.

方法 有两种 一种hash判重 一种康托展开判重 下面代码是康托展开判重
hash判重参考POJ 1077
*/
//stl queue队列实现 (State)pre数组记录当前排列的上一状态tp(State)
//dir[4][2]方向数组来动态模拟'x'('0')号数码向四周移动
//康托展开用排列次序判重 用'0'代替'x' +逆序数 奇偶性质剪枝判断 无解的情况
#include<cstdio>
#include<queue>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factor为前8个数的阶乘 0~8 0的阶乘0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],st,ed;
struct State{
    int pos,order,s;
    char str[10];
};

int cantor(char *a){
    int order=0,sum;
    for(int i=0;i<9;i++){
    	sum=0;
    	//计算[i+1,8]中比a[i]小的元素的个数
    	for(int j=i+1;j<9;j++){
    		if(a[i]>a[j])
    			sum++;
		}
		//那么实际比a[i]小的元素的个数可以放在a[i]的位置,而[i+1,8]中的数随意排列,个数为(9-i-1)!,这样的排列是比当前排列字符串a要小的
		//sum为比a[i]小的数放在a[i]的位置, factor[9-i-1]为[i+1,8]中的数的全排列个数 (9-i-1)! 阶乘
		order+=sum*factor[9-i-1];
	}
	//所有结果累加完后,那么比当前排列字符串a小的排列个数为order,因为次序是从0开始的,那么当前排列得到次序就是order.
    return order;
}

int bfs(State s){
	queue<State> Q;
    vis[s.order]=1;
    Q.push(s);
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(!Q.empty()){
        tp=Q.front();
        //'x'用'9'代替 123456789的康托展开的次序是0
        //如果'x'用'0'来代替 123456780的康托展开次序是 46233
        if(tp.order == ed)
            break;
        Q.pop();
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            order=cantor(next.str);
            if(!vis[order]){
            	vis[order]=1;
                next.pos=tpos;
                next.order=order;
                next.s=tp.s+1;
                Q.push(next);
            }
        }
    }
    return tp.s;
}

int cal(char *a){
	int sum=0;
    //直接根据初始状态和目标状态的逆序奇偶性是否相同判断是否可达
    //注意排列逆序数不包括空格位'x',实际只算8个数,但事实 即使把'x'换成'0'或'9'原先两排列的 奇偶性质是否相同也是不影响的
    for(int i=0;i<9;i++){
        if(a[i] == '0')//空格位' '不算
            continue;
        for(int j=i+1;j<9;j++){
            if(a[j]!='0' && a[j]<a[i])//a[j]!='0' 空格位' '不算
                sum++;
        }
    }
    return sum;
}

int main(){
    State s;
    char t[10];
    int ron1,ron2,flag1=0,flag2=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&s.str[i]);
        if(s.str[i] == 'x'){
            s.str[i]='0';
            s.pos=i;
        }
    }
    for(int i=0;i<9;i++){
        scanf(" %c",&t[i]);
        if(t[i] == 'x')
            t[i]='0';
    }
    //ron为逆序数-"reverse order number"
    ron1=cal(s.str);
    ron2=cal(t);
    if(ron1%2)
    	flag1=1;
    if(ron2%2)
    	flag2=1;
    if(flag1 ^ flag2){
    	printf("unsolvable");//初始态和目标态 不可达 八数码无解
    	return 0;
	}
    st=s.order=cantor(s.str);
    s.s=0;
    ed=cantor(t);//ed为目标状态的次序
    //初始态和目标态逆序数奇偶性质相同一定是可达的,无需再输出 unsolvable无解
    printf("%d",bfs(s));//八数码 从初始状态st到目标状态ed最少需要移动的操作步数
    return 0;
}
/*
测试数据案例
input
23415x768
12345678x
output
19

input
12345678x
12345678x
output
0

input
2831647x5
123784x65
output
5

input
2831x4765
1238x4765
output
4

input
87152634x 逆序数 18 偶数
87162534x 逆序数 19 奇数 奇偶性质不同无法转换
output
unsolvable

input
12345678x 逆序数 0 偶数
61234578x 逆序数 5 奇数 奇偶性质不同无法转换
output
unsolvable

*/
