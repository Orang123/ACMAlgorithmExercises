#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;
//ac 468ms 最优匹配 最小差值放在匈牙利dfs里记录 O(V^2*E)
//较好的题解附带KM算法松弛函数图解 https://blog.csdn.net/wuxinxiaohuangdou/article/details/14056987
/*
最小差值放在匈牙利dfs里记录相比slack数组松弛优化要大多数时候慢些
原因如下:
//一个博客中说到的原因:https://www.cnblogs.com/fzl194/p/8848061.html
//和全局变量不同的是,全局变量在每次while循环中都需要赋值成INF,
//每次求出的是所有点的最小值,而slack数组在每个while外面就初始化好,
//每次while循环slack数组的每个值都在用到,一次增广路中求出的slack值会更准确,
//循环次数比全局变量更少,why"循环次数比全局变量更少"???
*/

/*
相关概念:
参考博客:
https://www.cnblogs.com/wenruo/p/5264235.html
https://www.cnblogs.com/zpfbuaa/p/7218607.html
https://www.cnblogs.com/Lanly/p/6291214.html
https://www.cnblogs.com/fzl194/p/8848061.html
1.KM(Kuhn－Munkras)算法:是对匈牙利算法的一种贪心扩展,这种贪心不是对边的权值的贪心,
算法发明者引入了一些新的概念,从而完成了这种扩展.时间复杂度O(V^3),确切来讲是O(V^2*E).
用来求解边权和最大的匹配,也叫最优匹配(最佳匹配).
2.可行顶标:对于原图中的任意一个结点i,给定一个函数l(i)求出结点的顶标值.
我们用数组lx(x)记录集合X中的结点顶标值，用数组ly(y)记录集合Y中的结点顶标值.
那么对于原图中任意一条边edge(x,y),都满足lx(x)+ly(y)>=weight(x,y)。
3.相等子图:相等子图是原图的一个生成子图(生成子图即包含原图的所有结点,但是不包含所有的边),
并且该生成子图中只包含满足lx(x)+ly(y)=weight(x,y)的边,这样的边我们称之为可行边.
就是当前已求解出的匹配边的集合.而最优匹配的边权和也就转化为每条匹配边对应的x、y顶标之和,
只要将顶标之和(lx[i]+ly[i])最大化即可.
4.定理:对于某组可行顶标,如果其相等子图存在完美匹配,那么该匹配就是原二分图的最大权完美匹配.
算法流程:
(1).初始化可行顶标的值 (设定lx,ly的初始值)
(2).用匈牙利算法寻找相等子图的完备匹配,实际就是搜索满足lx[u]+ly[v] == w(x,y)的增广路
(3).若未找到增广路则修改可行顶标的值,搜索增广路过程中相等子图中可行边上的顶点对应的顶标lx减少d,ly增加d.
关于这个顶标更新策略的我的理解:
eg:以草稿纸上的x1-y1,x2-y2,x3-y3,x4 y4为例.
首先现在最优匹配最大的匹配边权和转化为了对应各个匹配边顶标之和最大,每次更新顶标的差值d一定是在所以可供选择的
可行边中最小的,而将待加入可行边x3-y4的lx[3]顶标减少d后,为了使得之前的顶标之和不受到影响,之前相等子图x3-y3匹配,
就需要将之前x3-y3匹配的y3的ly[3]+d,事实上现在新的相等子图的顶标之和差值d在lx[4]-d和ly[3]+d已经抵消掉了,至于说
后续lx[2]-d ly[2]+d lx[1]-d ly[1]+d lx[4]-d也要更新差值d,首先增广路中为了使匹配边+1,原先非匹配边会与匹配边交换,
也就是现在x4-y1,x1-y2,x2-y3,x3-y4,而KM算法贪心顶标之和最大的正确性是建立在可行边满足lx[u]+ly[v] == w(x,y)的基础上,
所以此时新的相等子图x2-y3是配对的,因此x2也得lx[2]-d才能满足 lx[2]+ly[3] == w(2,3),此时lx[3]-d ly[3]+d lx[2]-d,多减了d,
又回到为了保持之前相等子图的顶标之和不变,而之前相等子图x2-y2匹配又得更新ly[2]+d,-d,+d抵消掉,但此时新的相等子图x1-y2是配对的,
因此lx[1]-d,新的可行边lx[1]+ly[2]==w(1,2),而现在有多出lx[1]-d,然后又为了保持之前相等子图顶标之和不变,之前相等子图x1-y1匹配,
ly[1]+d,-d,+d又抵消掉,而新的相等子图x4-y1配对,因此lx[4]-d,新的可行边lx[4]+ly[1]==w(4,1).
上述证明是一种解释,不过从代码运行角度来讲原因是:"增广失败,将访问过的点(包括增广失败的点)形成的树称为交错树."这段注释即:更新顶标代码上面注释.
关于可行边lx+ly==w(x,y)的贪心正确性应该是有一个比较严格的证明的,KM算法正是建立在可行边顶标之和等于边权重这个原则
进行贪心求解最大匹配边权和的.
(4).重复(2)(3)直到找到相等子图的完备匹配为止

注意:
1.KM算法O(V^2*E)一般数据量不会超过500.
2.最大权匹配也叫最佳匹配.
3.KM算法必须限定原二分图X集合中的点都能在Y中找到不相同的配对点才行,
即不一定要求必须是X和Y点个数相等的完美匹配,只要满足|X|<=|Y|,
并且X中的点都能在Y中找到不相同的配对点就可保证算法的正确性不会陷入死循环.if(dfs(i)) break;
不能出现X集合中2个点对配对Y集合中同一点的情况,这样X集合中必然会有1点在Y中是无法找到配对点的,
这样KM中while(1)会进入死循环.
4.考虑到二分图中两个集合中的点并不总是相同,为了能应用KM算法解决二分图的最大权匹配,
需要先作如下处理:将两个集合中点数比较少的补点,使得两边点数相同,之后将补点和之前集合多出的点连边,
再将不存在的边权重设为0,这种情况下,问题就转换成求最大权完美匹配问题,从而能应用KM算法求解.
*/

/*
题意:n个村民分配n个房子,输入为邻接矩阵mp[i][j]表示第i个村民对第j间房出的价格.
现在问如何分配才能使得收入村领导收入最大.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2255
思路:村民和房子刚好构成二分图,二分图最大权匹配.
这个输入存储矩阵保证了这个问题一定存在完美匹配,
不会出现某个村民买不到房子的情况,满足KM算法的前提条件.KM算法模板.
注意:此题卡费用流.
*/

//记录X集合中的点和Y集合中的点是否访问过,用来dfs避免重复搜索和更新顶标lx[i]、ly[i]值
bool visitX[N],visitY[N];
//min_gap用来记录顶标之和与边权的差值的最小值,这样更新时所有的顶标之和可相对保证最大,即匹配边权和也最大
int mp[N][N],lx[N],ly[N],link[N],n,min_gap;

//搜索新的相等子图的可行边,纳入可增广路径边集中 O(V)
bool dfs(int x){
    int gap;
    visitX[x]=true;//标记X集合中的x已访问
    for(int i=0;i<n;i++){//KM算法需要保证X集合中点对Y集合中的每一个点都有连边所以无需判断邻接矩阵哪些是存在的边
        if(!visitY[i]){
            gap=lx[x]+ly[i]-mp[x][i];//计算差值
            if(gap==0){//之前顶标更新过后 所加入可供选择连接的可行边作为匹配
                visitY[i]=true;//标记Y集合中的i已访问
                if(link[i]==-1 || dfs(link[i])){//匈牙利腾出配对点
                    link[i]=x;//标记Y集合中i的配对点是X集合中的x
                    return true;
                }
            }
            else
                min_gap=min(min_gap,gap);//如果差值不为0,记录这个最小的差值 以便后续更新顶标
        }
    }
    return false;
}


//O(V^2*E)
//KM的算法过程可以描述为不断地扩张相等子图,向相等子图中加入匹配边(可行边),
//直到将X集合中的点的配对点都找到为止.
int km(){
    /*
    顶标初始化采用贪心的策略:lx[i]初始化为X集合中i所连的最大边权的值,ly[i]初始化为0.
    这样每次根据lx[x]+ly[i]-mp[x][i]==0的连接条件,这样每次匈牙利算法更新的最小差值,
    可使得每次所选择的匹配边权值都是次大,尽可能大.
    */
    for(int i=0;i<n;i++){
        lx[i]=ly[i]=0;
        for(int j=0;j<n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=0;i<n;i++){//O(V)
        while(1){//O(V)
            min_gap=INF;
            memset(visitX,false,sizeof(visitX));//每次dfs搜索增广路时,要初始化访问点标记
            memset(visitY,false,sizeof(visitY));
            //当没有搜索到新的增广路径时,适当更新顶标值,降低其值即:(lx[i]-min_gap)+ly[j] == mp[i][j]
            //使其在下一次dfs 搜索增广路时可作为相等子图的可行边考虑,进而找到新的匹配边
            /*
            dfs(i)返回ture,说明找到了增广路径,即相等子图中的边恰好比之前最大匹配多1,这时无需更新顶标.
            dfs(i)返回false,说明原先的匹配边集中存在被占据配对的X中的点没能配对到满足lx[x]+ly[i] == weight Y集合中的点i
            这样就需要适当更新顶标值,降低其值即:(lx[i]-min_gap)+ly[j]==mp[i][j]来满足配对边权,但是这条边配对后,
            再次搜索增广路时,可能仍然会遇到lx[i]+ly[j]!=mp[i][j]的点不配对情况,也就是没有搜索到新的可行边,仍旧
            需要更新顶标值来使其配对,最坏情形下顶标要更新V-1次,才能找到一条增广路,可行边即匹配数加1,即O(V).
            这个做法必须限定原二分图X集合中的点都能在Y中找到不相同的配对点才行,即不一定要求必须是X和Y点个数相等的完美匹配,
            只要满足|X|<=|Y|,并且X中的点都能在Y中找到不相同的配对点就可保证算法的正确性不会陷入死循环.
            不然存在X集合中某点x搜索不到增广路即原先匹配点被占据没有点可匹配时,min_gap仍旧是INF,
            这样就会出错,dfs(i)永远也无法返回ture,陷入死循环.
            */
            if(dfs(i)) break;//O(E)
            /*
            min_gap==INF,说明当前点i的连边对应Y集合的点除过被抢占的外,
            已经没有连边没有配对边了,该点无法进行配对,求不出最优匹配.
            为避免死循环,应在这里结束函数体 返回-1,事实上一般KM问题会
            确保X集合中的每个点都存在配对点,这个if判定只是为了算法思维
            更完善些,也许一组错误的输入无法保证X集合中点的配对,这时if就
            能保障程序不会进入死循环.
            */
            //if(min_gap == INF) return -1;
            /*
            这个例子在草稿纸上
            (lx[4]-min_gap+ly[1]+min_gap)+(lx[1]-min_gap+ly[2]+min_gap)+(lx[2]-min_gap+ly[3]+min_gap)+(lx[3]-min_gap+ly[4])
            这里可以看到即使是之前的匹配点被改变但是边权值总和计算的顶标项是没有改变的(因为都是-min_gap和+min_gap交替),
            但因为最后的lx[3]配对上ly[4]作为可行边要适当降低lx[3]的顶标值,因为要维持先前匹配集中可行边的顶标之和不变,先前的可行边顶标也要变化min_gap,
            等待下一次dfs搜索增广路匹配成功时顶标之和就和这个例子一样会发现在原有匹配权的和基础上又增加了lx[4]和ly[4]-min_gap,而其余顶标之和因为减min_gap
            和加min_gap交替出现数值并没有变化,而新增加的顶标是lx[4]和ly[4],只是减了min_gap,而其余顶标项之和是恒定的,因此要想顶标和最大即匹配边权最大,
            只有当min_gap是最小的时候,相减后的值才最大,这也证实了贪心算法的正确性.
            */

            /*
            增广失败,将访问过的点(包括增广失败的点)形成的树称为交错树.
            更新匈牙利遍历的相等子图中访问到的交错树中点顶标值,lx降低,ly减少.
            实际只有某一条交错路上的点的顶标需要变化,但是因为不清楚这条交错路
            的顶标变化后会不会影响别的交错路可行边lx+ly==w(x,y)是否成立,这就会影响
            接下来再次搜索增广路时,可能之前能走通的交错路因为顶标没有及时统一更新,
            导致无法走通,因此走不到之前确定出的那条交错路,自然也就无法加入可行边,
            因此更新顶标时才会将之前增广过程中访问的所有点的顶标都更新,这样再次增广,
            就能按照之前走过的路径一路走到将要加入的可行边,此时因为lx减少已经满足lx+ly=w(x,y),
            因此增广成功.
            */
            for(int i=0;i<n;i++){
                if(visitX[i]) lx[i]-=min_gap;
                if(visitY[i]) ly[i]+=min_gap;
            }
        }
    }
    int sum=0;
    //累加最终匹配的最大边权和 也可用顶标累加表示最大权值和 lx[link[i]]+ly[i]
    for(int i=0;i<n;i++){
        if(link[i]!=-1)//Y集合中的点要确保已和X集合中的点配对
            sum+=mp[link[i]][i];//累加匹配边权
    }
    /*
    //link初始化为0,无需判断
    //对于Y集合中未匹配的点mp[0][i]都是0,直接累加,结果也不影响
    for(int i=1;i<=n;i++)
        sum+=mp[link[i]][i];
    */
    return sum;
}

void init(){
    memset(link,-1,sizeof(link));//memset可以初始化为0,但点的编号一定得从1开始算
}

int main(){
    int cost;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&mp[i][j]);//mp[i][j]表示第i个村民对第j间房出的价格.
        //注意应用KM算法的前提条件,待匹配集合X中的点一定在Y集合中要有配对点.
        //不能出现X集合中2个点对配对Y集合中同一点的情况,这样X集合中必然会有1点在Y中是无法找到配对点的,
        //这样KM中while(1)会进入死循环.
        printf("%d\n",km());
    }
    return 0;
}

/*
//ac 483ms O(V^4) 最小差值d放在KM() while(1) 里求解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;

//记录X集合中的点和Y集合中的点是否访问过,用来dfs避免重复搜索和更新顶标lx[i]、ly[i]值
bool visitX[N],visitY[N];
//min_gap用来记录顶标之和与边权的差值的最小值,这样更新时所有的顶标之和可相对保证最大,即匹配边权和也最大
int mp[N][N],lx[N],ly[N],link[N],n,min_gap;

//搜索新的相等子图的可行边,纳入可增广路径边集中 O(V)
bool dfs(int x){
    int gap;
    visitX[x]=true;//标记X集合中的x已访问
    for(int i=0;i<n;i++){//KM算法需要保证X集合中点对Y集合中的每一个点都有连边所以无需判断邻接矩阵哪些是存在的边
        if(!visitY[i]){
            gap=lx[x]+ly[i]-mp[x][i];//计算差值
            if(gap==0){//之前顶标更新过后 所加入可供选择连接的可行边作为匹配
                visitY[i]=true;//标记Y集合中的i已访问
                if(link[i]==-1 || dfs(link[i])){//匈牙利腾出配对点
                    link[i]=x;//标记Y集合中i的配对点是X集合中的x
                    return true;
                }
            }
        }
    }
    return false;
}


//O(V^4)
//KM的算法过程可以描述为不断地扩张相等子图,向相等子图中加入匹配边(可行边),
//直到将X集合中的点的配对点都找到为止.
int km(){
    for(int i=0;i<n;i++){
        lx[i]=ly[i]=0;
        for(int j=0;j<n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=0;i<n;i++){//O(V)
        while(1){//O(V)
            min_gap=INF;
            memset(visitX,false,sizeof(visitX));//每次dfs搜索增广路时,要初始化访问点标记
            memset(visitY,false,sizeof(visitY));
            if(dfs(i)) break;//O(E)
			for(int j=0;j<n;j++){//O(V^2)
				if(!visitX[j]) continue;
				for(int k=0;k<n;k++){
					if(!visitY[k])
						min_gap=min(min_gap,lx[j]+ly[k]-mp[j][k]);
				}
			}
            //if(min_gap == INF) return -1;
            for(int i=0;i<n;i++){
                if(visitX[i]) lx[i]-=min_gap;
                if(visitY[i]) ly[i]+=min_gap;
            }
        }
    }
    int sum=0;

    for(int i=0;i<n;i++){
        if(link[i]!=-1)//Y集合中的点要确保已和X集合中的点配对
            sum+=mp[link[i]][i];//累加匹配边权
    }

    return sum;
}

void init(){
    memset(link,-1,sizeof(link));//memset可以初始化为0,但点的编号一定得从1开始算
}

int main(){
    int cost;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&mp[i][j]);//mp[i][j]表示第i个村民对第j间房出的价格.
        printf("%d\n",km());
    }
    return 0;
}
*/

/*
//ac 546ms slack数组优化 O(V^2*E) 时间反而较长
//这个松弛优化主要是在每次更新顶标,确定最小差值时,因为用slack[i]数组记录了Y集合中每个点i作为待加入可行边的端点i需要的最小差值
//这样最终在比较所有Y集合中作为待加入可行边端点的差值时,可以一层for循环就比较出Y集合中最小的差值.
//否则不用slack数组就会导致,这里需要两层for循环先考虑x集合中vis[x]=1的点,再考虑x连边的Y集合visy[y]=0的点.
//但是这里和不用slack数组直接在dfs里记录这个最小差值d 感觉没啥区别啊,为啥不用这个slack数组就慢.(大多数时候,有时差不多,甚至slack要慢些)

//摘自博客:https://blog.csdn.net/c20182030/article/details/73330556?locationNum=3&fps=1
//貌似加入slack数组后 边权值大小还会影响其性能
//对于随机数据来说,时间复杂度约为O(V^2*E),但是
//如果我们考虑极限数据,把每条边的边权mp[i][j]=i*j,试试看吧,会怎样？   "会很耗时吗,我的理解"
//只针对随即数据O(n^3),对于极限数据（w[i][j]很大）slack优化作用不显著

//摘自博客:https://www.cnblogs.com/Iking123/p/11300885.html
//这个优化似乎是很有用,但并不能把KM优化到O(n^3).这其实和原算法差不多,
//还是要为左部n个点匹配,每次匹配还是最多要增广n次,每次增广还是O(n+m).
//如果是完全图,并且出题人稍微构造一下数据,依然是O(n^4).


//加入slack数组优化最小差值,个人觉得这个数组的设置没啥用,
//好像就只是为了在KM()函数中比较求解最小min_gap,而这个min_Gap实际可以在dfs中就直接求解出来
//而松弛时 不在交错树中的点i slack[i]-d有点没搞明白
//一个优化是对YY顶点引入松弛函数slack，slack[j]保存跟当前节点j相连的节点i的lx[i]+ly[j]−weight(i,j)的最小值,
//于是求delta时只需O(n)枚举不在交错树中的Y顶点的最小slack值即可.

//松弛值可以在匈牙利算法检查相等子树边失败时进行更新，同时在修改标号后也要更新，具体参考代码实现。
//实际上，O(n^4)的KM算法表现不俗，使用O(n^3)并不会很大的提高KM的运行效率
//需要在O(1)的时间找到任意一条边，使用邻接矩阵存储更为方便,实际上这道题我用这个slack版本去交 发现居然比不用slack优化还慢...

//另一种说法优化的关键在dfs,用bfs增广的KM是n^3的,用dfs增广的KM是n^4的
//为什么dfs会成为算法时间复杂度减小的瓶颈呢?
//每更新顶标,就要重新从当前点开始dfs找一遍增广路,有很多冗余的操作
//实际上,更新完顶标之后,交错树只会增加新的点
//那么窝萌不妨用bfs来增广,每次修改完顶标,把没访问到的右侧点的slack值也相应地减去d,
//那么slack值为0就相当于多了一条可行边,就相当于能够访问到新的节点,也就可以继续找增广路了
//这样再把新的点加进队列，就避免了dfs增广的版本中的冗余操作
//这样就发挥了slack这一优化的优势，复杂度自然降到O(n^3)  摘自https://it610.com/article/4862180.htm
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;
bool visitX[N],visitY[N];
int mp[N][N],lx[N],ly[N],link[N],n,slack[N];

bool dfs(int x){
    int gap;
    visitX[x]=true;
    for(int i=0;i<n;i++){
        if(!visitY[i]){
            gap=lx[x]+ly[i]-mp[x][i];
            if(gap==0){
                visitY[i]=true;
                if(link[i]==-1 || dfs(link[i])){
                    link[i]=x;
                    return true;
                }
            }
            else
                slack[i]=min(slack[i],gap);
        }
    }
    return false;
}
//O(V^2*E)
int km(){
    int min_gap;
    for(int i=0;i<n;i++){
        lx[i]=ly[i]=0;
        for(int j=0;j<n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    memset(link,-1,sizeof(link));
    for(int i=0;i<n;i++){
        //放在while(1)之外的原因是每次搜索增广路时lx+ly!=w(x,y)对应的Y集合中的点应该都是不同的,
        //所以只需初始化一次放在考虑i点配对的while(1)循环外
        memset(slack,INF,sizeof(slack));//X集合中每个点开始配对时都要初始化INF
        while(1){
            min_gap=INF;
            memset(visitX,false,sizeof(visitX));
            memset(visitY,false,sizeof(visitY));
            if(dfs(i)) break;//O(E)
            for(int i=0;i<n;i++){//O(V)
                if(!visitY[i]) min_gap=min(slack[i],min_gap);//slack的作用好像就只体现在这里
            }
            for(int i=0;i<n;i++){
                if(visitX[i]) lx[i]-=min_gap;
                if(visitY[i]) ly[i]+=min_gap;
                else slack[i]-=min_gap;//实际不写slack[i]-=min_gap;结果也是对的
                //修改顶标后，要把所有的slack值都减去delta
                //这是因为lx[i] 减小了delta
                //slack[j] = min(lx[i] + ly[j] -w[i][j]) --j不属于交错树--也需要减少delta,第二类边
            }
        }
    }
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=mp[link[i]][i];
    return sum;
}

void init(){
    memset(link,-1,sizeof(link));//memset可以初始化为0,但点的编号一定得从1开始算
}

int main(){
    int cost;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&mp[i][j]);
        printf("%d\n",km());
    }
    return 0;
}
*/

/*
//bfs做法 ac 452ms 暂时不理解 复杂度严格O(V^3)
//来自博客:https://blog.csdn.net/qq_35950004/article/details/83508443
//还有别的的BFS板子可读性好些:http://blog.leanote.com/post/icontofig/1fa992ed3790
//https://fanfansann.blog.csdn.net/article/details/108976135
//https://www.cnblogs.com/Iking123/p/11300885.html bfs版本复杂度说是O(n^2+n*m),n、m为X、Y集合元素个数
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define maxn 405
using namespace std;

int n,dx[maxn],dy[maxn],s[maxn],cy[maxn],pre[maxn],a[maxn][maxn],tim;
int vis[maxn];

void bfs(int now)
{
	int y=0,x,Minloc;
	cy[y] = now;
	memset(s,0x3f,sizeof s);
	for(;cy[y];y=Minloc)
	{
		Minloc = 0;
		x = cy[y] , vis[y] = tim;
		for(int i=1;i<=n;i++)
			if(vis[i]!=tim){
				if(dx[x]+dy[i]-a[x][i]<s[i]) s[i]=dx[x]+dy[i]-a[x][i],pre[i]=y;
				if(s[i]<s[Minloc]) Minloc = i;
			}
		for(int i=0,inc=s[Minloc];i<=n;i++)
			if(vis[i]==tim) dx[cy[i]]-=inc,dy[i]+=inc;
			else s[i]-=inc;
	}
	for(;y;y=pre[y]) cy[y] = cy[pre[y]];
}

int KM()
{
	memset(cy,0,sizeof cy);
	for(int i=1;i<=n;i++)
		tim++,bfs(i);
	int ans = 0;
	for(int i=1;i<=n;i++) ans+=dx[i]+dy[i];
	return ans;
}

int main()
{
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
			scanf("%d",&a[i][j]);
			dx[i] = max(dx[i] , a[i][j]);
            }
        printf("%d\n",KM());
    }

}
*/

/*
//bfs模板 可读性较好 摘自博客:http://blog.leanote.com/post/icontofig/1fa992ed3790
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 405;
const int INF = 0x3f3f3f3f
ll n, a[maxn],b[maxn],c[maxn],p[maxn];
ll w[maxn][maxn];
ll lx[maxn] , ly[maxn];
ll linker[maxn];
ll slack[maxn];
bool visy[maxn];
ll pre[maxn];
void bfs( ll k ){
    ll x , y = 0 , yy = 0 , delta;
    memset( pre , 0 , sizeof(pre) );
    for(int i = 1 ; i <= n ; i++ ) slack[i] = INF;
    linker[y] = k;
    while(1){
        x = linker[y]; delta = INF; visy[y] = true;
        for(int i = 1 ; i <= n ;i++ ){
            if( !visy[i] ){
                if( slack[i] > lx[x] + ly[i] - w[x][i] ){
                    slack[i] = lx[x] + ly[i] - w[x][i];
                    pre[i] = y;
                }
                if( slack[i] < delta ) delta = slack[i] , yy = i ;
            }
        }
        for(int i = 0 ; i <= n ; i++ ){
            if( visy[i] ) lx[linker[i]] -= delta , ly[i] += delta;
            else slack[i] -= delta;
        }
        y = yy ;
        if( linker[y] == -1 ) break;
    }
    while( y ) linker[y] = linker[pre[y]] , y = pre[y];
}

ll KM(){
    memset( lx , 0 ,sizeof(lx) );
    memset( ly , 0 ,sizeof(ly) );
    memset( linker , -1, sizeof(linker) );
    for(int  i = 1 ; i <= n ; i++ ){
        memset( visy , false , sizeof(visy) );
        bfs(i);
    }
    ll res = 0 ;
        for(int i = 1 ; i <= n ; i++ ){
            if( linker[i] != -1 ){
                res += w[linker[i]][i] ;
            }
        }
        return res;
}
*/
