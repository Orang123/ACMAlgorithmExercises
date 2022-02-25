/*
题意:八数码输出最短操作方案.
在3×3的棋盘,摆有八个棋子,每个棋子上标有1至8的某一数字,
不同棋子上标的数字不相同.棋盘上还有一个空格'x',与空格相邻
的棋子可以和空格交换位置.棋盘的状态表示为从(0,0)到(2,2)自左向右,
自上而下形成的排列串,要求解决的问题是:给出一个初始状态和一个
目标状态,其中向上移动表示为'u',向下移动表示为'd',向左移动表
示为'l',向右移动表示为'r',找出一种从初始状态转变成目标状态的移动
空格步数最少的移动方案步骤.输出这个方案.
注意:空格'x'实际表示成'0'或'9' 方便哈希判重或康托展开判重
此题POJ 1077的数据较弱,貌似数据没有不可达的样例,HDU 1043数据较强,
感觉普通的单向bfs会TLE,只能用双向广搜或A*搜索才能过.
链接:http://poj.org/problem?id=1077
思路:相关大牛博客:https://blog.csdn.net/u012283461/article/details/79078653
https://www.cnblogs.com/goodness/archive/2010/05/04/1727141.html

八数码问题,关键是9个数构成排列对应的10进制是9位数,无法直接开
大小为10^8的数组,会MLE.有三种解决方案可以压缩状态空间.

方案1:hash判重,哈希函数为除留取余 对哈希表取模,表长可设置为1000003(素数),
这样对于不同排列取模产生的冲突,用链地址法存放在一个单独的链表里.实际哈希表
的长度可设置为362880,而分离链接法的链表表头长度为1000003.这样状态判重的空间复杂度就得到了压缩.
但是hash判重法因为要输出具体操作过程,这里因为不同排列的hash取模值可能是相同的,
对于冲突在同一个链表中的状态,不好记录,因此不好用stl 中的queue去记录上一状态.
因此只能手写实现队列,队列大小为362880(9个数所有可能排列个数).虽然实际9个数的
排列状态总共有9!=362880个,但实际初始状态的排列只能到达和它逆序性质相同的排列,
也就是奇排列只能到达奇排列,偶排列也只能到达偶排列,奇偶排列之间不能相互转换.
所以实际哈希表的长度 并不会有9!=362880这么大.

注意:不是所有的时候都有类似cantor展开这样计算出唯一序号的判重方法,更加常用的是hash.


方案2:康托展开判重,用对某一排列a用康托展开计算x=sum[0]*(n-1-0)!+sum[1]*(n-1-1)!+...+sum[n-2]*1!+sum[n-1]*0!
其中sum[i]表示a[i+1]~a[n-1]中比a[i]小的数的个数.
计算结果x表示当前排列a在所有排列的次序为x.
列如:12345排列次序为0,12354排列次序为1.
这样原先的状态空间由10^8就可压缩到9!=366280,这样就可以判断某个排列次序
(<366280,实际某些排列状态不可达,远小于9!)是否已经搜索过,而不必直接判断
当前排列这个10进制数值是否出现过.
康托展开参考博客:https://blog.csdn.net/ltrbless/article/details/87696372

方案3:摘自Eric ppt
也可以使用STL中的set，map来判重
基本等价于平衡树
O(logn)的查找，插入效率
一般的，运行效率比hash要慢
但是容易编写
可以使用set,map做跳板，如果TLE，再换成Hash（不过最好先预估一下是否会TLE）
map+bfs的实现可参考:https://blog.csdn.net/u012283461/article/details/79078653

一个简单的常数剪枝:
一个状态表示成一维的形式,求出除空格'0'之外所有数字的逆序数之和,也就是每个数字
后面比它小的数字的个数的和,称为这个状态的逆序数.也可以求每个数字前面比它大的数字个数的和.
逆序数奇偶性质相同的排列一定是可达的,逆序数奇偶性质不同的排列一定是不可达的,
计算逆序数时可不算空格位'x'.
证明:当左右移动空格时,逆序不变.当上下移动空格时,相当于将一个数字向前（或向后）移动两格,
跳过的这两个数字要么都比它大（小）,逆序可能±2;要么一个较大一个较小,逆序不变.
所以可得结论:只要是相互可达的两个状态,它们的逆序奇偶性相同.
上述证明摘自博客:https://blog.csdn.net/hnust_xiehonghao/article/details/7951173
标准的根据逆序数判断是否有解的标程:https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/

遗留问题:还差双向广搜、A*搜索的实现.
*/

//手写队列实现
//ac 110ms dir[4][2]方向数组来动态模拟'x'('0')号数码向四周移动
//hash链地址法判重
//时间复杂度主要是在hash判重里 实际入队的状态个数最多9!=362880
#include<cstdio>
#include<cstring>
#define M 363000//362880 9个数的全排列最多有9!=362880个
#define HS 1000003//HS取得越小 耗时越高
using namespace std;

//head邻接表表头 数组下标表示的是 hash除留取余后的数组 head[x]表示hash取模值为x的对应的edge链表的数组下标
//因此数组大小设置为hash表的长度,这里表长取得应尽可能大,尽可能取取素数 能保证尽可能降低插入时的冲突次数
//这样大多数排列的查询就可在常数时间内查找到
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},cnt,head[HS];
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir;//pso表示'x'在str中的位置下标,pre记录上个状态在队列Q中的下标,dir记录当前状态转移的方向
    char str[10];
}Q[M];//队列中存放的状态个数的上限是 0~8 这9个数全排列的个数

struct HashTable{
    int val,next;//val是实际排列串所对应的10进制数值,next是指针指向 hash后 除留取余数值hval相同的排列链表中的别的状态
}edge[M];//分离链接法的邻接表数组长度 也是0~8 这9个数全排列的个数

//算法全排列数组 对应的10进制数值
int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

//尝试插入哈希表 构建索引
int tryInsert(char *a){
    int s=Hash(a);
    int hval=s%HS;//算出除留取余模哈希表长度后的数值hval
    //判断链地址法邻接表中是否 已经存入了s这个排列状态
    for(int i=head[hval];i!=-1;i=edge[i].next){//时间复杂度为 取模后的哈希值相等的最长的链表
        if(edge[i].val == s)//已经到达过val这个状态 不再重复插入
            return 0;
    }
    //对于除留取余后hash值冲突的情况 用分离链接法 将冲突的值放到一个同链表里
    //这里是采用了 头插法(类似链式前向星那种插边方式),O(1)时间插入
    edge[cnt]=(HashTable){s,head[hval]};
    //head中下标是hash取模后的值hval 而不是实际排列的10进制值val,
    //val太大无法开出10位数长度的数组,因此采用hash取模压缩空间,使得冲突的状态用链地址法 放在一个链表里
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    //head、tail表示队头、队尾指针
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tx,ty,nx,ny,tpos;
    while(head<tail){
        tp=Q[head++];//标准的出队方式是head=(head+1)%M
        //这里用strcmp判断str会wa,不知何原因,用memcmp就能ac
        //memcmp这里因为 用了"123456780" 要指定字节长度为9byte
        if(!memcmp(tp.str,"123456780",9))
            return head-1;
        tx=tp.pos/3;
        ty=tp.pos%3;
        for(int i=0;i<4;i++){
            nx=tx+dir[i][0];
            ny=ty+dir[i][1];
            if(nx<0 || nx>=3 || ny<0 || ny>=3)
                continue;
            tpos=nx*3+ny;//新状态 'x'在str中的位置
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            if(tryInsert(next.str)){
                next.pos=tpos;
                next.pre=head-1;
                next.dir=i;
                //标准的入队方式是队尾tail=(tail+1)%M,但是这里已经定义了队列数组长度最大M,实际绝对达不到这个长度,因此不必取模
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    /*
    int sum=0;
    //直接根据初始状态和目标状态的逆序奇偶性是否相同判断是否可达
    //注意排列逆序数不包括空格位'x',实际只算8个数,但事实 即使把'x'换成'0'或'9'原先两排列的奇偶性质是否相同也是不影响的
    for(int i=0;i<9;i++){
        if(st.str[i] == '0')//空格位'x'不算
            continue;
        for(int j=i+1;j<9;j++){
            //每个数字str[i]后面str[i+1,8]中比它小的数字个数 也可求str[i]前面str[0,i-1]中比str[i]大的数字个数的和
            if(st.str[j]!='0' && st.str[j]<st.str[i])//st.str[j]!='0' 空格位'x'不算
                sum++;
        }
    }
    if(sum%2!=0){//目标态"12345678x"逆序数为0(偶数),若初始状态逆序数不为偶数为奇数,则不可达
        printf("unsolvable\n");
        return 0;
    }
    */
    st.pre=-1;
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else//所有奇偶性质相同的排列均是可达的,如果有上面奇偶性质判断,这里的不可达输出可省略
		printf("unsolvable");
    printf("\n");
    return 0;
}

/*
//手写队列实现
//ac 110ms hash链地址法判重 Eric 课件中的做法 用dir[9][4]数组表示0号数码 四个方向的位置在对应排列数组str中的位置下标
//用'0'代替'x'
#include<cstdio>
#include<cstring>
#define M 363000//362880 9个数的全排列最多有9!=362880个
#define HS 1000003
using namespace std;

//dir[pos][0/1/2/3] 表示八数码中的'x'('0')在数码对应排列串str数组的pos位置时,
//其所对应3*3网格中其上(0)下(1)左(2)右(3)位置在str数组中的位置数组下标
//dir[pos][i]=-1时,说明'x'('0')i方向的位置是不合法的 超过了0~2网格的下标范围
int dir[9][4]={-1,3,-1,1,
                -1,4,0,2,
                -1,5,1,-1,
                0,6,-1,4,
                1,7,3,5,
                2,8,4,-1,
                3,-1,-1,7,
                4,-1,6,8,
                5,-1,7,-1};
int cnt,head[HS];//邻接表表头 为Hash表大小,设置为素数,尽可能大
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,val;
    char str[10];
}Q[M];//队列中存放的状态个数的上限是 0~8 这9个数全排列的个数

struct HashTable{
    int val,next;
}edge[M];//分离链接法的邻接表数组长度 也是0~8 这9个数全排列的个数

int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

int tryInsert(int s){
    int hval=s%HS;
    for(int i=head[hval];i!=-1;i=edge[i].next){
        if(edge[i].val == s)
            return 0;
    }
    edge[cnt]=(HashTable){s,head[hval]};
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tpos,s;
    while(head<tail){
        tp=Q[head++];
        //这里用strcmp判断str会wa,不知何原因,用memcmp就能ac
        //这里是采用了 记录10进制数值val的 直接判断是否到达目标状态
        if(tp.val == 123456780)
            return head-1;
        for(int i=0;i<4;i++){
            tpos=dir[tp.pos][i];
            if(tpos == -1)//说明当前位置超过了 3x3网格边界
                continue;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='0';
            s=Hash(next.str);//hash计算出str排列对应的10进制数值
            if(tryInsert(s)){
                next.pos=tpos;
                next.val=s;
                next.pre=head-1;
                next.dir=i;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.val=Hash(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//手写队列实现
//ac 125ms dir[4][2]方向数组来动态模拟'x'('9')号数码向四周移动
//康托展开用排列次序判重 用'9'代替'x' 132456789的次序为0
//康托展开详细讲解参考:https://blog.csdn.net/ltrbless/article/details/87696372
//康托逆展开还未看
#include<cstdio>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factor为前8个数的阶乘 0~8 0的阶乘0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M];
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,order;
    char str[10];
}Q[M];

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

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    vis[st.order]=1;
    Q[tail++]=st;
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(head<tail){
        tp=Q[head++];
        //'x'用'9'代替 123456789的康托展开的次序是0
        //如果'x'用'0'来代替 123456780的康托展开次序是 46233
        if(tp.order == 0)
            return head-1;
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
            next.str[tpos]='9';
            order=cantor(next.str);
            if(!vis[order]){
            	vis[order]=1;
                next.pos=tpos;
                next.pre=head-1;
                next.dir=i;
                next.order=order;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='9';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.order=cantor(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//stl queue队列实现 (State)pre数组记录当前排列的上一状态tp(State)
//ac 204ms dir[4][2]方向数组来动态模拟'x'('0')号数码向四周移动
//康托展开用排列次序判重 用'0'代替'x' 123456780的次序为46233
#include<cstdio>
#include<queue>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factor为前8个数的阶乘 0~8 0的阶乘0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],st,ed;
char opt[4]={'u','d','l','r'};
struct State{
    int pos,dir,order;
    char str[10];
}pre[M];

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

void print(int i){
    if(pre[i].order == st){
    	printf("%c",opt[pre[i].dir]);
        return;
	}
    print(pre[i].order);
    printf("%c",opt[pre[i].dir]);
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
            return 1;
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
                pre[order]=tp;
                //注意这个因为要输出操作方式,因为实际并没有记录 目标状态的State,因此每一步的操作记录到了 前一状态tp这里 因此 pre[order].dir=i才能将所有操作都输出完
                //否则到达目标状态的操作无法输出
                pre[order].dir=i;
                Q.push(next);
            }
        }
    }
    return 0;
}

int main(){
    State s;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&s.str[i]);
        if(s.str[i] == 'x'){
            s.str[i]='0';
            s.pos=i;
        }
    }
    st=s.order=cantor(s.str);
    ed=cantor("123456780");//123456780的次序为46233
    if(bfs(s))
    	print(ed);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//手写队列实现
//ac 125ms dir[4][2]方向数组来动态模拟'x'('0')号数码向四周移动
//康托展开用排列次序判重 用'0'代替'x' 123456780的次序为46233
#include<cstdio>
#include<cstring>
#define M 363000
using namespace std;

int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//factor为前8个数的阶乘 0~8 0的阶乘0!=1
int factor[9]={1,1,2,6,24,120,720,5040,40320},vis[M],ed;
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,order;
    char str[10];
}Q[M];

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

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    vis[st.order]=1;
    Q[tail++]=st;
    int tx,ty,nx,ny,tpos,order;
    State tp,next;
    while(head<tail){
        tp=Q[head++];
        //'x'用'9'代替 123456789的康托展开的次序是0
        //如果'x'用'0'来代替 123456780的康托展开次序是 46233
        if(tp.order == ed)
            return head-1;
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
                next.pre=head-1;
                next.dir=i;
                next.order=order;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='0';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.order=cantor(st.str);
    ed=cantor("123456780");//123456780的次序为46233
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//ac 94ms hash链地址法判重 Eric 课件中的做法 用dir[9][4]数组表示0号数码 四个方向的位置在对应排列数组str中的位置下标
//用'9'代替'x'
#include<cstdio>
#include<cstring>
#define M 363000//362880 9个数的全排列最多有9!=362880个
#define HS 1000003
using namespace std;

//dir[pos][0/1/2/3] 表示八数码中的'x'('0')在数码对应排列串str数组的pos位置时,
//其所对应3*3网格中其上(0)下(1)左(2)右(3)位置在str数组中的位置数组下标
//dir[pos][i]=-1时,说明'x'('0')i方向的位置是不合法的 超过了0~2网格的下标范围
int dir[9][4]={-1,3,-1,1,
                -1,4,0,2,
                -1,5,1,-1,
                0,6,-1,4,
                1,7,3,5,
                2,8,4,-1,
                3,-1,-1,7,
                4,-1,6,8,
                5,-1,7,-1};
int cnt,head[HS];//邻接表表头 为Hash表大小,设置为素数,尽可能大
char opt[4]={'u','d','l','r'};
struct State{
    int pos,pre,dir,val;
    char str[10];
}Q[M];//队列中存放的状态个数的上限是 0~8 这9个数全排列的个数

struct HashTable{
    int val,next;
}edge[M];//分离链接法的邻接表数组长度 也是0~8 这9个数全排列的个数

int Hash(char *a){
    int s=0;
    for(int i=0;i<9;i++)
        s=s*10+a[i]-'0';
    return s;
}

int tryInsert(int s){
    int hval=s%HS;
    for(int i=head[hval];i!=-1;i=edge[i].next){
        if(edge[i].val == s)
            return 0;
    }
    edge[cnt]=(HashTable){s,head[hval]};
    head[hval]=cnt++;
    return 1;
}

void print(int i){
    if(Q[i].pre == -1)
        return;
    print(Q[i].pre);
    printf("%c",opt[Q[i].dir]);
}

int bfs(State st){
    int head=0,tail=0;
    Q[tail++]=st;
    State tp,next;
    int tpos,s;
    while(head<tail){
        tp=Q[head++];
        if(tp.val == 123456789)
            return head-1;
        for(int i=0;i<4;i++){
            tpos=dir[tp.pos][i];
            if(tpos == -1)//说明当前位置超过了 3x3网格边界
                continue;
            memcpy(next.str,tp.str,sizeof(tp.str));
            next.str[tp.pos]=next.str[tpos];
            next.str[tpos]='9';
            s=Hash(next.str);//hash计算出str排列对应的10进制数值
            if(tryInsert(s)){
                next.pos=tpos;
                next.val=s;
                next.pre=head-1;
                next.dir=i;
                Q[tail++]=next;
            }
        }
    }
    return -1;
}

int main(){
	int ans;
    State st;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<9;i++){
        scanf(" %c",&st.str[i]);
        if(st.str[i] == 'x'){
            st.str[i]='9';
            st.pos=i;
        }
    }
    st.pre=-1;
    st.val=Hash(st.str);
    ans=bfs(st);
    if(ans!=-1)
    	print(ans);
	else
		printf("unsolvable");
    printf("\n");
    return 0;
}
*/

/*
//ac 0ms A*搜索 启发式搜索 stl优先队列实现
//摘自网上
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
#include<math.h>
using namespace std;
int c[4][2]= {0,1,1,0,-1,0,0,-1};
char D[4]= {'r','d','u','l'};
int book[3700000];
int C[9]= {1,1,2,6,24,120,720,5040,40320};

struct node
{
    int pos;
    int step;
    int state[10];
    int HMD;
    int cantor;
    bool operator < (const node h)const
    {
        return step+HMD>h.step+h.HMD;
    }
};

struct yun
{
    int Node;
    int dis;
} path[3700000];

int is_solve(int a[])
{
    int i,j,ans=0;
    for(i=0; i<8; i++)
        for(j=i+1; j<9; j++)
        {
            if(a[i]==9||a[j]==9)continue;
            if(a[j]<a[i])
                ans++;
        }

    if(ans&1)
        return 1;
    else
        return 0;
}

int hmd(int ma[])
{
    int ans=0,i;
    for(i=0; i<9; i++)
    {
        if(ma[i]==9)
            continue;
        ans+=fabs((ma[i]-1)/3-i/3)+fabs((ma[i]-1)%3-i%3);
    }
    return ans;
}

int Cantor(int a[])
{
    int i,j,l,ans=0;
    for(i=0; i<8; i++)
    {
        l=0;
        for(j=i+1; j<9; j++)
            if(a[j]<a[i])
                l++;
        ans+=C[8-i]*l;
    }
    return ans;
}

void A_star(int pos,int a[])
{
    int i;
    priority_queue<node> Q;
    node st,en;
    for(i=0; i<9; i++)
        st.state[i]=a[i];
    st.pos=pos;
    st.HMD=hmd(st.state);
    st.cantor=Cantor(st.state);
    st.step=0;
    Q.push(st);
    while(Q.size())
    {
        st=Q.top();
        Q.pop();//printf("Cantor: %d  Step: %d  Pos: %d\n",st.cantor,st.step,st.pos);
        if(st.cantor==0)
        {
            int k=0;
            int p[10000];
            for(i=1; i<=st.step; i++)
            {
                p[i]=path[k].dis;
                k=path[k].Node;
            }
            for(i=st.step;i>=1;i--)
                printf("%c",D[p[i]]);
            printf("\n");
            return ;
        }
        int x=st.pos/3;
        int y=st.pos%3;
        for(i=0; i<4; i++)
        {
            int dx=x+c[i][0];
            int dy=y+c[i][1];
            int dz=dx*3+dy;
            if(dx<0||dy<0||dx>2||dy>2)
                continue;

            for(int j=0; j<9; j++)
                en.state[j]=st.state[j];
            swap(en.state[dz],en.state[st.pos]);
         //   printf("%d \n",dz);
            int kk=Cantor(en.state);
         //   printf("KK %d KK\n",kk);
            if(book[kk])
                continue;
         //   printf("%d****\n",i);
            book[kk]=1;
            en.cantor=kk;
            en.pos=dz;

            en.step=st.step+1;
         //   printf("%d**>>\n");
            en.HMD=hmd(en.state);
            path[kk].dis=i;
            path[kk].Node=st.cantor;

            Q.push(en);
        }
    }
}

int main()
{
    char str[100];
    gets(str);
    int puzzle[10],pos;
    int k=0,i;
    for(i=0; i<strlen(str); i++)
    {
        if(str[i]!=' ')
        {
            if(str[i]=='x')
            {
                puzzle[k++]=9;
                pos=k-1;
            }
            else
                puzzle[k++]=str[i]-'0';
        }
    }
    int is=is_solve(puzzle);
    if(is)
        printf("unsolvable\n");
    else
        A_star(pos,puzzle);
}
*/
